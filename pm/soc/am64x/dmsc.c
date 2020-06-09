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
#include <soc/am64x/devices.h>
#include <lib/ioremap.h>
#include <lib/io.h>
#include <sys-reset.h>
#include <device_pm.h>

#define MAIN_CTRL_BASE  0x43000000UL
#define MCU_CTRL_BASE   0x4500000UL

#define CTRL_MMR0_PARTITION_SIZE                        0x4000

#define CTRLMMR_MCU_RST_CTRL                            0x18170U
#define CTRLMMR_MCU_RST_CTRL_SW_MCU_WARMRST_OFFSET      8U
#define CTRLMMR_MCU_RST_CTRL_SW_MCU_WARMRST_MASK        0xFU
#define CTRLMMR_MCU_RST_CTRL_SW_MCU_WARMRST_VAL         0x6U

static const struct sleep_mode am64x_sleep_modes[] = {
	{
		.name = "WFI",
	},
};

static u8 am64x_sleep_block[ARRAY_SIZE(am64x_sleep_modes)];

static s32 am64x_sys_reset_handler(domgrp_t domain __attribute__((unused)))
{
	u32 v;
	struct device *dev;

	/* MCU_PSC0: Disable MAIN2MCU bridge */
	dev = device_lookup(AM64X_DEV_MAIN2MCU_VD);
	soc_device_ret_enable(dev);
	soc_device_disable(dev, SFALSE);

	/* MCU_PSC0: Disable MCU2MAIN bridge */
	dev = device_lookup(AM64X_DEV_MCU2MAIN_VD);
	soc_device_ret_enable(dev);
	soc_device_disable(dev, SFALSE);

	/* Issue warm reset */
	v = readl(MCU_CTRL_BASE + CTRLMMR_MCU_RST_CTRL);
	v &= ~(CTRLMMR_MCU_RST_CTRL_SW_MCU_WARMRST_MASK <<
	       CTRLMMR_MCU_RST_CTRL_SW_MCU_WARMRST_OFFSET);
	v |= CTRLMMR_MCU_RST_CTRL_SW_MCU_WARMRST_VAL <<
	     CTRLMMR_MCU_RST_CTRL_SW_MCU_WARMRST_OFFSET;
	writel(v, MCU_CTRL_BASE + CTRLMMR_MCU_RST_CTRL);

	return SUCCESS;
}

s32 dmsc_init(void)
{

	sys_reset_handler_register(am64x_sys_reset_handler);

	return sleep_modes_register(am64x_sleep_modes, am64x_sleep_block,
				    ARRAY_SIZE(am64x_sleep_modes));
}
