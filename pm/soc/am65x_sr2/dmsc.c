/*
 * DMSC firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <sleep.h>
#include <rat.h>
#include <types/array_size.h>
#include <dmsc.h>
#include <soc/am65x/devices.h>
#include <lib/ioremap.h>
#include <lib/io.h>
#include <sys-reset.h>
#include <device_pm.h>
#include <lib/trace.h>

#define WKUP_CTRL_BASE  0x43000000

#define CTRLMMR_WKUP_MCU_WARM_RST_CTRL                  0x1817c

static const struct sleep_mode am6_sleep_modes[] = {
	{
		.name = "WFI",
	},
};

static u8 am6_sleep_block[ARRAY_SIZE(am6_sleep_modes)];

static s32 am6_sys_reset_handler(domgrp_t domain __attribute__((unused)))
{
	struct device *dev;
	u8 trace_action = TRACE_PM_ACTION_SYSRESET;
	u32 trace_val = TRACE_PM_ACTION_SYSRESET_ERR_VAL_SUCCESS;

	/* PSC0: Disable MAIN2MCU bridge */
	dev = device_lookup(AM6_DEV_DUMMY_IP_LPSC_MCU2MAIN);
	soc_device_ret_enable(dev);
	soc_device_disable(dev, SFALSE);

	/* WKUP_PSC0: Disable MCU2MAIN bridge */
	dev = device_lookup(AM6_DEV_DUMMY_IP_LPSC_MAIN2MCU);
	soc_device_ret_enable(dev);
	soc_device_disable(dev, SFALSE);

	/* Issue warm reset */
	writel(0, WKUP_CTRL_BASE + CTRLMMR_WKUP_MCU_WARM_RST_CTRL);

	pm_trace(trace_action,
			((domain << TRACE_PM_ACTION_SYSRESET_DOMAIN_SHIFT) &
			TRACE_PM_ACTION_SYSRESET_DOMAIN_MASK) | trace_val);

	return SUCCESS;
}

s32 dmsc_init(void)
{
	sys_reset_handler_register(am6_sys_reset_handler);

	return sleep_modes_register(am6_sleep_modes, am6_sleep_block,
				    ARRAY_SIZE(am6_sleep_modes));
}
