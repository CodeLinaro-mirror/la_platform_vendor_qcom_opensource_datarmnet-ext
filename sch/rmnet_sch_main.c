/* Copyright (c) 2021-2022, 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
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
static char*verinfo[]={"\x31\x36\x63\x64\x36\x64\x33\x33",
"\x37\x39\x35\x63\x32\x34\x30\x65","\x37\x34\x31\x35\x39\x32\x31\x63",
"\x61\x65\x32\x34\x34\x61\x39\x64"};module_param_array(verinfo,charp,NULL,
(0xcb7+5769-0x221c));MODULE_PARM_DESC(verinfo,
"\x56\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x74\x68\x65\x20\x64\x72\x69\x76\x65\x72"
);static const char*DATARMNETf1bb41174a="\x32\x2e\x30";
#define DATARMNETe632b2e0b0 (0xd11+230-0xdf3)
static const u8 DATARMNET93bdeed8cb[TC_PRIO_MAX+(0xd26+209-0xdf6)]={
(0xd18+223-0xdf4),(0xd18+223-0xdf4),(0xd18+223-0xdf4),(0xd18+223-0xdf4),
(0xd18+223-0xdf4),(0xd18+223-0xdf4),(0xd2d+202-0xdf7),(0xd26+209-0xdf6),
(0xd1f+216-0xdf5),(0xd18+223-0xdf4),(0xd18+223-0xdf4),(0xd18+223-0xdf4),
(0xd18+223-0xdf4),(0xd18+223-0xdf4),(0xd18+223-0xdf4),(0xd18+223-0xdf4)};static 
const int DATARMNET91bbdde74c[DATARMNETe632b2e0b0]={(0xbf7+4421-0x1c3c)*
(0xdf7+2629-0x143c),(0xef7+694-0x112d)*(0xdf7+2629-0x143c),(0xef7+1142-0x132d)*
(0xdf7+2629-0x143c),(0xeb7+1174-0x132d)*(0xdf7+2629-0x143c)};static const int 
DATARMNET9dd1382d86[DATARMNETe632b2e0b0]={(0xd35+210-0xdff),(0xd03+244-0xdf1),
(0xd11+230-0xdf3),(0xd1f+216-0xdf5)};struct DATARMNET74e95d25df{struct 
qdisc_skb_head DATARMNETb4180393e4[DATARMNETe632b2e0b0];int DATARMNET1de7b3d891[
DATARMNETe632b2e0b0];int DATARMNETf9afebb887[DATARMNETe632b2e0b0];};enum 
DATARMNET0f989391e4{DATARMNETd2d25c93da,DATARMNETd642352c30,DATARMNET2e000d7742,
};enum DATARMNET1d62df85d9{DATARMNET8c2cf1ab97,DATARMNET3ce0140794,
DATARMNETcc082dc693,DATARMNET8f2943dbd1,DATARMNET715f9842aa,};static int 
DATARMNET3a797cc4e9(struct sk_buff*DATARMNET543491eb0f,struct Qdisc*sch,struct 
sk_buff**DATARMNET6af05df5b3){struct DATARMNET74e95d25df*DATARMNETe823dcf978=
qdisc_priv(sch);unsigned int DATARMNET5affe290b8=qdisc_pkt_len(
DATARMNET543491eb0f);struct qdisc_skb_head*q;if(likely(sch->q.qlen<qdisc_dev(sch
)->tx_queue_len)){u8 DATARMNET2133db01db=DATARMNET93bdeed8cb[DATARMNET543491eb0f
->priority&TC_PRIO_MAX];q=&DATARMNETe823dcf978->DATARMNETb4180393e4[
DATARMNET2133db01db];__qdisc_enqueue_tail(DATARMNET543491eb0f,q);
trace_rmnet_sch_high(DATARMNETd2d25c93da,DATARMNET8c2cf1ab97,DATARMNET2133db01db
,q->qlen,(0x16e8+787-0xc0c),(0x16e8+787-0xc0c),DATARMNET543491eb0f,NULL);
qdisc_update_stats_at_enqueue(sch,DATARMNET5affe290b8);return NET_XMIT_SUCCESS;}
trace_rmnet_sch_high(DATARMNETd2d25c93da,DATARMNET3ce0140794,(0x16e8+787-0xc0c),
(0x16e8+787-0xc0c),(0x16e8+787-0xc0c),(0x16e8+787-0xc0c),DATARMNET543491eb0f,
NULL);return qdisc_drop(DATARMNET543491eb0f,sch,DATARMNET6af05df5b3);}static u8 
DATARMNETf9ac3daa83(struct DATARMNET74e95d25df*DATARMNETe823dcf978){int 
DATARMNET2372d14a3d,DATARMNET70fa801d65=DATARMNETe632b2e0b0;for(
DATARMNET2372d14a3d=(0xd2d+202-0xdf7);DATARMNET2372d14a3d<DATARMNETe632b2e0b0;
DATARMNET2372d14a3d++){if(!DATARMNETe823dcf978->DATARMNETb4180393e4[
DATARMNET2372d14a3d].qlen)continue;if(DATARMNETe823dcf978->DATARMNET1de7b3d891[
DATARMNET2372d14a3d]<=(0xd2d+202-0xdf7)||DATARMNETe823dcf978->
DATARMNETf9afebb887[DATARMNET2372d14a3d]<=(0xd2d+202-0xdf7)){if(
DATARMNET2372d14a3d<DATARMNET70fa801d65)DATARMNET70fa801d65=DATARMNET2372d14a3d;
continue;}trace_rmnet_sch_low(DATARMNETd642352c30,DATARMNETcc082dc693,
DATARMNET2372d14a3d,(0x16e8+787-0xc0c),(u64)DATARMNETe823dcf978->
DATARMNET1de7b3d891[DATARMNET2372d14a3d],(u64)DATARMNETe823dcf978->
DATARMNETf9afebb887[DATARMNET2372d14a3d],NULL,NULL);return DATARMNET2372d14a3d;}
for(DATARMNET2372d14a3d=(0xd2d+202-0xdf7);DATARMNET2372d14a3d<
DATARMNETe632b2e0b0;DATARMNET2372d14a3d++){DATARMNETe823dcf978->
DATARMNET1de7b3d891[DATARMNET2372d14a3d]=DATARMNET9dd1382d86[DATARMNET2372d14a3d
];DATARMNETe823dcf978->DATARMNETf9afebb887[DATARMNET2372d14a3d]=
DATARMNET91bbdde74c[DATARMNET2372d14a3d];}trace_rmnet_sch_low(
DATARMNETd642352c30,DATARMNET8f2943dbd1,(0x16e8+787-0xc0c),(0x16e8+787-0xc0c),
(0x16e8+787-0xc0c),(0x16e8+787-0xc0c),NULL,NULL);return DATARMNET70fa801d65;}
static struct sk_buff*DATARMNET11bbc6360d(struct Qdisc*sch){struct 
DATARMNET74e95d25df*DATARMNETe823dcf978=qdisc_priv(sch);struct sk_buff*
DATARMNET543491eb0f=NULL;u8 DATARMNET2372d14a3d;DATARMNET2372d14a3d=
DATARMNETf9ac3daa83(DATARMNETe823dcf978);if(DATARMNET2372d14a3d<
DATARMNETe632b2e0b0){DATARMNET543491eb0f=__qdisc_dequeue_head(&
DATARMNETe823dcf978->DATARMNETb4180393e4[DATARMNET2372d14a3d]);if(likely(
DATARMNET543491eb0f)){DATARMNETe823dcf978->DATARMNET1de7b3d891[
DATARMNET2372d14a3d]--;DATARMNETe823dcf978->DATARMNETf9afebb887[
DATARMNET2372d14a3d]-=qdisc_pkt_len(DATARMNET543491eb0f);trace_rmnet_sch_high(
DATARMNET2e000d7742,DATARMNET715f9842aa,DATARMNET2372d14a3d,DATARMNETe823dcf978
->DATARMNETb4180393e4[DATARMNET2372d14a3d].qlen,(u64)DATARMNETe823dcf978->
DATARMNET1de7b3d891[DATARMNET2372d14a3d],(u64)DATARMNETe823dcf978->
DATARMNETf9afebb887[DATARMNET2372d14a3d],DATARMNET543491eb0f,NULL);
qdisc_update_stats_at_dequeue(sch,DATARMNET543491eb0f);}}return 
DATARMNET543491eb0f;}static struct sk_buff*DATARMNET5842e6aac7(struct Qdisc*sch)
{struct DATARMNET74e95d25df*DATARMNETe823dcf978=qdisc_priv(sch);struct sk_buff*
DATARMNET543491eb0f=NULL;u8 DATARMNET2372d14a3d;DATARMNET2372d14a3d=
DATARMNETf9ac3daa83(DATARMNETe823dcf978);if(DATARMNET2372d14a3d<
DATARMNETe632b2e0b0)DATARMNET543491eb0f=DATARMNETe823dcf978->DATARMNETb4180393e4
[DATARMNET2372d14a3d].head;return DATARMNET543491eb0f;}static int 
DATARMNET757a7de682(struct Qdisc*sch,struct nlattr*DATARMNET8bdeb8bf5c,struct 
netlink_ext_ack*DATARMNET79a1f177ed){struct DATARMNET74e95d25df*
DATARMNETe823dcf978=qdisc_priv(sch);int DATARMNET2372d14a3d;for(
DATARMNET2372d14a3d=(0xd2d+202-0xdf7);DATARMNET2372d14a3d<DATARMNETe632b2e0b0;
DATARMNET2372d14a3d++){qdisc_skb_head_init(&DATARMNETe823dcf978->
DATARMNETb4180393e4[DATARMNET2372d14a3d]);DATARMNETe823dcf978->
DATARMNET1de7b3d891[DATARMNET2372d14a3d]=DATARMNET9dd1382d86[DATARMNET2372d14a3d
];DATARMNETe823dcf978->DATARMNETf9afebb887[DATARMNET2372d14a3d]=
DATARMNET91bbdde74c[DATARMNET2372d14a3d];}sch->flags&=~TCQ_F_CAN_BYPASS;return
(0xd2d+202-0xdf7);}static void DATARMNET9593ab9587(struct Qdisc*sch){struct 
DATARMNET74e95d25df*DATARMNETe823dcf978=qdisc_priv(sch);int DATARMNET2372d14a3d;
for(DATARMNET2372d14a3d=(0xd2d+202-0xdf7);DATARMNET2372d14a3d<
DATARMNETe632b2e0b0;DATARMNET2372d14a3d++){kfree_skb_list(DATARMNETe823dcf978->
DATARMNETb4180393e4[DATARMNET2372d14a3d].head);qdisc_skb_head_init(&
DATARMNETe823dcf978->DATARMNETb4180393e4[DATARMNET2372d14a3d]);
DATARMNETe823dcf978->DATARMNET1de7b3d891[DATARMNET2372d14a3d]=
DATARMNET9dd1382d86[DATARMNET2372d14a3d];DATARMNETe823dcf978->
DATARMNETf9afebb887[DATARMNET2372d14a3d]=DATARMNET91bbdde74c[DATARMNET2372d14a3d
];}}static struct Qdisc_ops DATARMNET9afaec21de __read_mostly={.id=
"\x72\x6d\x6e\x65\x74\x5f\x73\x63\x68",.priv_size=sizeof(struct 
DATARMNET74e95d25df),.enqueue=DATARMNET3a797cc4e9,.dequeue=DATARMNET11bbc6360d,.
peek=DATARMNET5842e6aac7,.init=DATARMNET757a7de682,.reset=DATARMNET9593ab9587,.
owner=THIS_MODULE,};static int __init DATARMNETe97da0a844(void){pr_info(
"\x73\x63\x68\x3a\x20\x69\x6e\x69\x74\x20\x28\x25\x73\x29" "\n",
DATARMNETf1bb41174a);return register_qdisc(&DATARMNET9afaec21de);}static void 
__exit DATARMNET1dc9099e88(void){unregister_qdisc(&DATARMNET9afaec21de);}
MODULE_LICENSE("\x47\x50\x4c\x20\x76\x32");module_init(DATARMNETe97da0a844);
module_exit(DATARMNET1dc9099e88);
