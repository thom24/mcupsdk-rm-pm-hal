/*
 * DMSC firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <sleep.h>
#include <rat.h>
#include <types/array_size.h>
#include <dmsc.h>
#include <soc/j7200/devices.h>
#include <lib/ioremap.h>
#include <sys-reset.h>
#include <device_pm.h>
#include <lib/trace.h>

#define MAIN_CTRL_BASE  0x00100000
#define WKUP_CTRL_BASE  0x43000000

#define CTRLMMR_WKUP_MCU_WARM_RST_CTRL                  0x1817c

static const struct sleep_mode j7200_sleep_modes[] = {
	{
		.name = "WFI",
	},
};

static u8 j7200_sleep_block[ARRAY_SIZE(j7200_sleep_modes)];


static s32 j7200_sys_reset_handler(domgrp_t domain __attribute__((unused)))
{
	struct device *dev;
	u32 val;

	/* PSC0: Disable MAIN2WKUPMCU bridge */
	dev = device_lookup(J7200_DEV_MAIN2WKUPMCU_VD);
	soc_device_ret_enable(dev);
	soc_device_disable(dev, SFALSE);

	/* WKUP_PSC0: Disable WKUPMCU2MAIN bridge */
	dev = device_lookup(J7200_DEV_WKUPMCU2MAIN_VD);
	soc_device_ret_enable(dev);
	soc_device_disable(dev, SFALSE);
	val = readl(WKUP_CTRL_BASE + CTRLMMR_WKUP_MCU_WARM_RST_CTRL);

	TRACE_info_arg("reset attempt\n", val);

	/* Issue warm reset. This register modifies it's own contents. */
	writel(0x60000, WKUP_CTRL_BASE + CTRLMMR_WKUP_MCU_WARM_RST_CTRL);

	return SUCCESS;
}

s32 dmsc_init(void)
{
	sys_reset_handler_register(j7200_sys_reset_handler);

	return sleep_modes_register(j7200_sleep_modes, j7200_sleep_block,
				    ARRAY_SIZE(j7200_sleep_modes));
}
