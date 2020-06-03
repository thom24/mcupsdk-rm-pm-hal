/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <arch/regs_cm3.h>
#include <lib/ioremap.h>

void scr_enable_sleepdeep(void)
{
	u32 scr_reg;

	scr_reg = readl(SYS_SCR);
	scr_reg |= 1 << SYS_SCR_SD_OFFSET;

	writel(scr_reg, SYS_SCR);
}
