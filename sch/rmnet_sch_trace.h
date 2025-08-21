/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
 */

#undef TRACE_SYSTEM
#define TRACE_SYSTEM rmnet_sch

#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .

#undef TRACE_INCLUDE_FILE
#define TRACE_INCLUDE_FILE rmnet_sch_trace

#if !defined(__RMNET_SCH_TRACE_H__) || defined(TRACE_HEADER_MULTI_READ)
#define __RMNET_SCH_TRACE_H__

#include <linux/tracepoint.h>

DECLARE_EVENT_CLASS(rmnet_sch_template,
	 TP_PROTO(u8 func, u8 evt, u32 uint1, u32 uint2,
		  u64 ulong1, u64 ulong2, void *ptr1, void *ptr2),
	 TP_ARGS(func, evt, uint1, uint2, ulong1, ulong2, ptr1, ptr2),
	 TP_STRUCT__entry(__field(u8, func)
			  __field(u8, evt)
			  __field(u32, uint1)
			  __field(u32, uint2)
			  __field(u64, ulong1)
			  __field(u64, ulong2)
			  __field(void *, ptr1)
			  __field(void *, ptr2)
	 ),
	 TP_fast_assign(__entry->func = func;
			__entry->evt = evt;
			__entry->uint1 = uint1;
			__entry->uint2 = uint2;
			__entry->ulong1 = ulong1;
			__entry->ulong2 = ulong2;
			__entry->ptr1 = ptr1;
			__entry->ptr2 = ptr2;
	 ),
TP_printk("fun:%u ev:%u u1:%u u2:%u ul1:%llu ul2:%llu p1:0x%pK p2:0x%pK",
	  __entry->func, __entry->evt,
	  __entry->uint1, __entry->uint2,
	  __entry->ulong1, __entry->ulong2,
	  __entry->ptr1, __entry->ptr2)
)

DEFINE_EVENT(rmnet_sch_template, rmnet_sch_low,
	 TP_PROTO(u8 func, u8 evt, u32 uint1, u32 uint2,
		  u64 ulong1, u64 ulong2, void *ptr1, void *ptr2),
	 TP_ARGS(func, evt, uint1, uint2, ulong1, ulong2, ptr1, ptr2)
);

DEFINE_EVENT(rmnet_sch_template, rmnet_sch_high,
	 TP_PROTO(u8 func, u8 evt, u32 uint1, u32 uint2,
		  u64 ulong1, u64 ulong2, void *ptr1, void *ptr2),
	 TP_ARGS(func, evt, uint1, uint2, ulong1, ulong2, ptr1, ptr2)
);

DEFINE_EVENT(rmnet_sch_template, rmnet_sch_err,
	 TP_PROTO(u8 func, u8 evt, u32 uint1, u32 uint2,
		  u64 ulong1, u64 ulong2, void *ptr1, void *ptr2),
	 TP_ARGS(func, evt, uint1, uint2, ulong1, ulong2, ptr1, ptr2)
);

#endif

#include <trace/define_trace.h>
