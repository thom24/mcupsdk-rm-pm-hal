/*
 * DMSC firmware
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <clk_fixed.h>
#include <lib/container_of.h>
#include <lib/ioremap.h>
#include <compiler.h>

static u32 clk_fixed_get_freq(struct clk *clk)
{
	const struct clk_data *clk_data;
	const struct clk_range *range;
	u32 ret = 0;

	clk_data = clk_get_data(clk);
	range = clk_get_range(clk_data->range_idx);
	if (range) {
		ret = range->min_hz;
	}

	return ret;
}

static u32 clk_fixed_get_state(struct clk *clk UNUSED)
{
	return CLK_HW_STATE_ENABLED;
}

const struct clk_drv clk_drv_fixed = {
	.get_freq	= clk_fixed_get_freq,
	.get_state	= clk_fixed_get_state,
};
