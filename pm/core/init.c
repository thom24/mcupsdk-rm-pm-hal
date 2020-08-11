/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/errno.h>
#include <stddef.h>
#include <types/sbool.h>
#include <startup.h>
#include <lib/trace.h>
#include <types/array_size.h>

#include <clk.h>
#include <device.h>
#include <tisci/pm/tisci_pm_clock.h>
#include <tisci/pm/tisci_pm_core.h>
#include <tisci/pm/tisci_pm_device.h>

#include <dmsc.h>

static s32(*const startups[]) (void) = {
	&dmsc_init,
#ifdef CONFIG_CLOCK
	&clk_init,
#endif
	&devices_init,
#ifdef CONFIG_TESTS
	&test_timer64p_init,
#endif
};

s32 pm_init(void)
{
	sbool startup_done[ARRAY_SIZE(startups)];
	sbool done;
	sbool progress;
	sbool errors;
	u32 i;

	for (i = 0; i < ARRAY_SIZE(startups); i++) {
		startup_done[i] = SFALSE;
	}

	errors = SFALSE;
	do {
		done = STRUE;
		progress = SFALSE;
		for (i = 0; i < ARRAY_SIZE(startups); i++) {
			s32 ret;
			if (startup_done[i]) {
				continue;
			}
			ret = (*startups[i])();
			if (ret == -EDEFER) {
				pm_trace(TRACE_PM_ACTION_FAIL | TRACE_PM_ACTION_INIT,
					 ((((u32) EDEFER) & TRACE_PM_VAL_INIT_ERR_MASK) << TRACE_PM_VAL_INIT_ERR_SHIFT) |
					 ((i & TRACE_PM_VAL_INIT_IDX_MASK) << TRACE_PM_VAL_INIT_IDX_SHIFT));
				done = SFALSE;
			} else {
				progress = STRUE;
				if (ret < 0) {
					pm_trace(TRACE_PM_ACTION_FAIL | TRACE_PM_ACTION_INIT,
						 ((((u32) (-ret)) & TRACE_PM_VAL_INIT_ERR_MASK) << TRACE_PM_VAL_INIT_ERR_SHIFT) |
						 ((i & TRACE_PM_VAL_INIT_IDX_MASK) << TRACE_PM_VAL_INIT_IDX_SHIFT));
					errors = STRUE;
				}
				startup_done[i] = STRUE;
			}
		}
	} while (!done && progress);

	if (!progress) {
		pm_trace(TRACE_PM_ACTION_FAIL | TRACE_PM_ACTION_INIT, TRACE_PM_VAL_INIT_DEFER);
	} else if (errors) {
		pm_trace(TRACE_PM_ACTION_FAIL | TRACE_PM_ACTION_INIT, TRACE_PM_VAL_INIT_ERROR);
	} else {
		pm_trace(TRACE_PM_ACTION_INIT, 0x0U);
	}

	return 0;
}
