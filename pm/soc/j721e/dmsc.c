/*
 * DMSC firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <rat.h>
#include <types/array_size.h>
#include <dmsc.h>
#include <soc/j721e/devices.h>
#include <lib/ioremap.h>
#include <lib/io.h>
#include <sys-reset.h>
#include <device_pm.h>
#include <lib/trace.h>

#define WKUP_CTRL_BASE  0x43000000

#define CTRLMMR_WKUP_MCU_WARM_RST_CTRL                  0x1817c

static void j721e_sys_reset_handler(void)
{
	struct device *dev;

	/* PSC0: Disable MAIN2WKUPMCU bridge */
	dev = device_lookup(J721E_DEV_MAIN2WKUPMCU_VD);
	soc_device_ret_enable(dev);
	soc_device_disable(dev);

	/* WKUP_PSC0: Disable WKUPMCU2MAIN bridge */
	dev = device_lookup(J721E_DEV_WKUPMCU2MAIN_VD);
	soc_device_ret_enable(dev);
	soc_device_disable(dev);
#ifdef CONFIG_TRACE
	{
		u32 val;
		val = readl(WKUP_CTRL_BASE + CTRLMMR_WKUP_MCU_WARM_RST_CTRL);

		TRACE_info_arg("reset attempt\n", val);
	}
#endif

	/* Issue warm reset. This register modifies it's own contents. */
	writel(0x60000, WKUP_CTRL_BASE + CTRLMMR_WKUP_MCU_WARM_RST_CTRL);
}

s32 dmsc_init(void)
{
	sys_reset_handler_register(j721e_sys_reset_handler);

	return SUCCESS;
}
