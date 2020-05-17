/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <mlb.h>
#include <resource.h>
#include <device.h>

void mlb_suspend(struct device *device)
{
	const struct resource_mem *mem = device_resource_mem(device, 0);

	if (mem) {
		unsigned long v;

		/* Allow clock stop and power-off */
		v = mem_readl(mem, MLB_PWR);
		v |= MLB_PWR_MSTANDBY;
		mem_writel(mem, v, MLB_PWR);
	}
}

const struct drv mlb_drv = {
	.suspend	= mlb_suspend,
};
