/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef CLK_DEV_H
#define CLK_DEV_H

#include <clk.h>
#include <soc/device.h>
#include <pm_types.h>

/* SoC clock sourced from an IP block */
struct clk_data_from_dev {
	struct clk_drv_data	data;
	dev_idx_t		dev;
	dev_clk_idx_t		clk_idx;
};

extern const struct clk_drv clk_drv_from_device;

#endif
