// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.​
 */

#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/skbuff.h>
#include <linux/rtnetlink.h>
#include <net/pkt_sched.h>

#define CREATE_TRACE_POINTS
#include "rmnet_sch_trace.h"

/* Insert newest first, last 4 bytes of the change id */
static char *verinfo[] = { "39c6d763",
			  "b10f2ea2",
			  "16cd6d33",
			  "795c240e",
			  "7415921c",
			  "ae244a9d"};
module_param_array(verinfo, charp, NULL, 0444);
MODULE_PARM_DESC(verinfo, "Version of the driver");

static const char *rmnet_sch_version = "2.2";

#define RMNET_SCH_MAX_QUEUE 4

/* priority 6, 7, 8, 9 use queue 0, 1, 2, 3 */
static const u8 prio2queue[TC_PRIO_MAX + 1] = { 3, 3, 3, 3, 3, 3, 0, 1,
						2, 3, 3, 3, 3, 3, 3, 3 };

static const int bytes_limit[RMNET_SCH_MAX_QUEUE] = { 256 * 1024, 128 * 1024,
						      64 * 1024, 32 * 1024 };

static const int pkts_limit[RMNET_SCH_MAX_QUEUE] = { 8, 6, 4, 2 };

struct rmnet_sch_priv {
	struct qdisc_skb_head queue[RMNET_SCH_MAX_QUEUE];
	int pkts_quota[RMNET_SCH_MAX_QUEUE];
	int bytes_quota[RMNET_SCH_MAX_QUEUE];
};

enum rmnet_sch_trace_func {
	RMNET_SCH_ENQUEUE,
	RMNET_SCH_NEXT_TO_DEQUEUE,
	RMNET_SCH_DEQUEUE,
};

enum rmnet_sch_trace_evt {
	RMNET_SCH_PKT_QUEUE,
	RMNET_SCH_PKT_DROP,
	RMNET_SCH_QUEUE_SELECT,
	RMNET_SCH_QUOTA_REFRESH,
	RMNET_SCH_PKT_DEQUEUE,
};

static int rmnet_sch_enqueue(struct sk_buff *skb, struct Qdisc *sch,
			     struct sk_buff **to_free)
{
	struct rmnet_sch_priv *priv = qdisc_priv(sch);
	unsigned int pkt_len = qdisc_pkt_len(skb);
	struct qdisc_skb_head *q;

	if (likely(sch->q.qlen < qdisc_dev(sch)->tx_queue_len)) {
		u8 idx = prio2queue[skb->priority & TC_PRIO_MAX];

		q = &priv->queue[idx];
		__qdisc_enqueue_tail(skb, q);
		trace_rmnet_sch_high(RMNET_SCH_ENQUEUE, RMNET_SCH_PKT_QUEUE,
				     idx, q->qlen, 0xDEF, 0xDEF, skb, NULL);
		qdisc_update_stats_at_enqueue(sch, pkt_len);
		return NET_XMIT_SUCCESS;
	}

	trace_rmnet_sch_high(RMNET_SCH_ENQUEUE, RMNET_SCH_PKT_DROP, 0xDEF,
			     0xDEF, 0xDEF, 0xDEF, skb, NULL);
	return qdisc_drop(skb, sch, to_free);
}

/*
 * Next queue number to dequeue. RMNET_SCH_MAX_QUEUE no data available.
 */
static u8 rmnet_sch_next_to_dequeue(struct rmnet_sch_priv *priv)
{
	int qn, candidate = RMNET_SCH_MAX_QUEUE;

	for (qn = 0; qn < RMNET_SCH_MAX_QUEUE; qn++) {
		if (!priv->queue[qn].qlen)
			continue;
		if (priv->pkts_quota[qn] <= 0 || priv->bytes_quota[qn] <= 0) {
			if (qn < candidate)
				candidate = qn;
			continue;
		}

		trace_rmnet_sch_low(RMNET_SCH_NEXT_TO_DEQUEUE,
				    RMNET_SCH_QUEUE_SELECT, qn, 0xDEF,
				    (u64)priv->pkts_quota[qn],
				    (u64)priv->bytes_quota[qn], NULL, NULL);
		return qn;
	}

	/* Either no packet, or all queues with packets have quota consumed,
	 * reset quota */
	for (qn = 0; qn < RMNET_SCH_MAX_QUEUE; qn++) {
		priv->pkts_quota[qn] = pkts_limit[qn];
		priv->bytes_quota[qn] = bytes_limit[qn];
	}

	trace_rmnet_sch_low(RMNET_SCH_NEXT_TO_DEQUEUE, RMNET_SCH_QUOTA_REFRESH,
			    0xDEF, 0xDEF, 0xDEF, 0xDEF, NULL, NULL);
	return candidate;
}

static struct sk_buff *rmnet_sch_dequeue(struct Qdisc *sch)
{
	struct rmnet_sch_priv *priv = qdisc_priv(sch);
	struct sk_buff *skb = NULL;
	u8 qn;

	qn = rmnet_sch_next_to_dequeue(priv);

	if (qn < RMNET_SCH_MAX_QUEUE) {
		skb = __qdisc_dequeue_head(&priv->queue[qn]);
		if (likely(skb)) {
			priv->pkts_quota[qn]--;
			priv->bytes_quota[qn] -= qdisc_pkt_len(skb);
			trace_rmnet_sch_high(RMNET_SCH_DEQUEUE,
					     RMNET_SCH_PKT_DEQUEUE,
					     qn, priv->queue[qn].qlen,
					     (u64)priv->pkts_quota[qn],
					     (u64)priv->bytes_quota[qn],
					     skb, NULL);
			qdisc_update_stats_at_dequeue(sch, skb);
		}
	}

	return skb;
}

static struct sk_buff *rmnet_sch_peek(struct Qdisc *sch)
{
	struct rmnet_sch_priv *priv = qdisc_priv(sch);
	struct sk_buff *skb = NULL;
	u8 qn;

	qn = rmnet_sch_next_to_dequeue(priv);

	if (qn < RMNET_SCH_MAX_QUEUE)
		skb = priv->queue[qn].head;

	return skb;
}

static int rmnet_sch_init(struct Qdisc *sch, struct nlattr *arg,
			  struct netlink_ext_ack *extack)
{
	struct rmnet_sch_priv *priv = qdisc_priv(sch);
	int qn;

	for (qn = 0; qn < RMNET_SCH_MAX_QUEUE; qn++) {
		priv->pkts_quota[qn] = pkts_limit[qn];
		priv->bytes_quota[qn] = bytes_limit[qn];
	}

	/* Not work conserving to prevent packets jumping queues */
	sch->flags &= ~TCQ_F_CAN_BYPASS;

	return 0;
}

static void rmnet_sch_reset(struct Qdisc *sch)
{
	struct rmnet_sch_priv *priv = qdisc_priv(sch);
	int qn;

	for (qn = 0; qn < RMNET_SCH_MAX_QUEUE; qn++) {
		__qdisc_reset_queue(&priv->queue[qn]);
		priv->pkts_quota[qn] = pkts_limit[qn];
		priv->bytes_quota[qn] = bytes_limit[qn];
	}

	/* stats will be reset by qdisc_reset */
}

static struct Qdisc_ops rmnet_sch_qdisc_ops __read_mostly = {
	.id = "rmnet_sch",
	.priv_size = sizeof(struct rmnet_sch_priv),
	.enqueue = rmnet_sch_enqueue,
	.dequeue = rmnet_sch_dequeue,
	.peek = rmnet_sch_peek,
	.init = rmnet_sch_init,
	.reset = rmnet_sch_reset,
	.owner = THIS_MODULE,
};

static int __init rmnet_sch_module_init(void)
{
	pr_info("sch: init (%s)\n", rmnet_sch_version);
	return register_qdisc(&rmnet_sch_qdisc_ops);
}

static void __exit rmnet_sch_module_exit(void)
{
	unregister_qdisc(&rmnet_sch_qdisc_ops);
}

MODULE_LICENSE("GPL v2");
module_init(rmnet_sch_module_init);
module_exit(rmnet_sch_module_exit);
