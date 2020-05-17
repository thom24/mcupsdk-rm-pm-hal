/*
 * System Firmware OSAL Privilege Control Layer
 *
 * OSAL Core Privilege control
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <ti/sysbios/hal/SysCall.h>

#ifdef CONFIG_TRACE_DEBUG_OSAL_CONTEXT_SWITCH
#include <lib/trace.h>

/* Provide a dummy function to work with macro definitions below */
static inline void nop()
{
}

#define osal_enter_priv_mode SysCall_enterPrivMode(); \
	bp_trace_core(TRACE_BP_ACTION_OSAL_CONTEXT_SWITCH, \
		      TRACE_BP_VAL_OSAL_CONTEXT_SWITCH_ENTER); \
	nop
#define osal_restore_priv_mode bp_trace_core(TRACE_BP_ACTION_OSAL_CONTEXT_SWITCH, \
					     TRACE_BP_VAL_OSAL_CONTEXT_SWITCH_RESTORE);	\
	SysCall_restorePrivMode
#define osal_enter_unpriv_mode bp_trace_core(TRACE_BP_ACTION_OSAL_CONTEXT_SWITCH, \
					     TRACE_BP_VAL_OSAL_CONTEXT_SWITCH_EXIT); \
	SysCall_enterUnprivMode
#else
#define osal_enter_priv_mode SysCall_enterPrivMode
#define osal_restore_priv_mode SysCall_restorePrivMode
#define osal_enter_unpriv_mode SysCall_enterUnprivMode
#endif
