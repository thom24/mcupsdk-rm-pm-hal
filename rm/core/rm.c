/*
 * DMSC RM
 *
 * Resource Manager core infrastructure
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/short_types.h>
#include <types/errno.h>
#include <lib/trace.h>

#include <config.h>

#include <rm.h>
#include <rm_core.h>

#ifdef CONFIG_RM_IRQ
#include <rm_irq.h>
#endif
#ifdef CONFIG_RM_RA
#include <rm_ra.h>
#endif
#ifdef CONFIG_RM_UDMAP
#include <rm_udmap.h>
#endif
#ifdef CONFIG_RM_PROXY
#include <rm_proxy.h>
#endif

s32 rm_init(void)
{
	s32 r = SUCCESS;

	r = rm_core_init();

#ifdef CONFIG_RM_IRQ
	if (r == SUCCESS) {
		r = rm_irq_init();
	}
#endif
#ifdef CONFIG_RM_RA
	if (r == SUCCESS) {
		r = rm_ra_init();
	}
#endif
#ifdef CONFIG_RM_UDMAP
	if (r == SUCCESS) {
		r = rm_udmap_init();
	}
#endif
#ifdef CONFIG_RM_PROXY
	if (r == SUCCESS) {
		r = rm_proxy_init();
	}
#endif

	if (r != SUCCESS) {
		rm_trace_sub(TRACE_RM_ACTION_RM_INIT |
			     TRACE_RM_ACTION_FAIL, 0U, 0U);
	}

	return r;
}

s32 rm_deinit(devgrp_t devgrp)
{
	s32 r = SUCCESS;

#ifdef CONFIG_RM_IRQ
	if (r == SUCCESS) {
		r = rm_irq_deinit(devgrp);
	}
#endif
#ifdef CONFIG_RM_RA
	if (r == SUCCESS) {
		r = rm_ra_deinit(devgrp);
	}
#endif
#ifdef CONFIG_RM_UDMAP
	if (r == SUCCESS) {
		r = rm_udmap_deinit(devgrp);
	}
#endif
#ifdef CONFIG_RM_PROXY
	if (r == SUCCESS) {
		r = rm_proxy_deinit(devgrp);
	}
#endif

	return r;
}
