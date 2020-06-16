/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <stddef.h>
#include <limits.h>
#include <types/errno.h>
#include <device.h>
#include <device_clk.h>
#include <clk.h>
#include <clk_mux.h>
#include <types/short_types.h>
#include <lib/trace.h>

struct dev_clk *get_dev_clk(struct device *device, dev_clk_idx_t idx)
{
	const struct dev_data *data = get_dev_data(device);
	const struct devgroup *devgroup = dev_data_lookup_devgroup(data);
	struct dev_clk *ret = NULL;

	if ((idx < data->n_clocks) && (devgroup != NULL)) {
		u32 offset = data->dev_clk_idx;
		if (clk_id_valid(devgroup->dev_clk_data[offset + idx].clk)) {
			ret = devgroup->dev_clk + offset + idx;
		}
	}

	return ret;
}

const struct dev_clk_data *get_dev_clk_data(struct device *device, dev_clk_idx_t idx)
{
	const struct dev_data *data = get_dev_data(device);
	const struct devgroup *devgroup = dev_data_lookup_devgroup(data);
	const struct dev_clk_data *ret = NULL;

	if ((idx < data->n_clocks) && (devgroup != NULL)) {
		u32 offset = data->dev_clk_idx;
		ret = devgroup->dev_clk_data + offset + idx;
	}

	return ret;
}

struct clk *dev_get_clk(struct device *device, dev_clk_idx_t idx)
{
	const struct dev_clk_data *entry = get_dev_clk_data(device, idx);

	return entry ? clk_lookup((clk_idx_t) entry->clk) : NULL;
}

sbool device_clk_set_gated(struct device *device, dev_clk_idx_t clk_idx, sbool gated)
{
	const struct dev_data *data = get_dev_data(device);
	const struct devgroup *devgroup = dev_data_lookup_devgroup(data);
	struct dev_clk *dev_clk = get_dev_clk(device, clk_idx);
	struct clk *clk = NULL;
	sbool is_enabled = SFALSE;
	sbool ret = STRUE;

	if ((dev_clk == NULL) || (devgroup == NULL)) {
		ret = SFALSE;
	} else {
		sbool is_gated;
		is_gated = !!(dev_clk->flags & DEV_CLK_FLAG_DISABLE);
		if (is_gated != gated) {
			is_enabled = (device->flags & DEV_FLAG_ENABLED_MASK) != 0UL;
			clk = clk_lookup((clk_idx_t) devgroup->dev_clk_data[data->dev_clk_idx + clk_idx].clk);
			if (!clk) {
				/* Clock lookup failed */
				ret = SFALSE;
			}
		}
	}

	if ((clk != NULL) && ((clk->flags & CLK_FLAG_INITIALIZED) == 0U)) {
		/* Clock not yet initialized (outside devgroup) */
		ret = SFALSE;
	} else if (clk && gated) {
		dev_clk->flags |= DEV_CLK_FLAG_DISABLE;
		if (is_enabled) {
			clk_put(clk);

			if (!(dev_clk->flags & DEV_CLK_FLAG_ALLOW_SSC)) {
				clk_ssc_allow(clk);
			}

			if (!(dev_clk->flags &
			      DEV_CLK_FLAG_ALLOW_FREQ_CHANGE)) {
				clk_freq_change_allow(clk);
			}
		}
	} else if (clk) {
		dev_clk->flags &= ~DEV_CLK_FLAG_DISABLE;
		if (is_enabled) {
			if (!(dev_clk->flags & DEV_CLK_FLAG_ALLOW_SSC)) {
				clk_ssc_block(clk);
			}

			if (!(dev_clk->flags &
			      DEV_CLK_FLAG_ALLOW_FREQ_CHANGE)) {
				clk_freq_change_block(clk);
			}

			/* FIXME: Error handling */
			clk_get(clk);
		}
	}

	return ret;
}

sbool device_clk_get_hw_ready(struct device *device, dev_clk_idx_t clk_idx)
{
	const struct dev_data *data = get_dev_data(device);
	const struct devgroup *devgroup = dev_data_lookup_devgroup(data);
	struct clk *clk;
	sbool ret = STRUE;


	if (devgroup == NULL) {
		ret = SFALSE;
	}

	if (ret) {
		clk = dev_get_clk(device, clk_idx);
		if (clk == NULL) {
			ret = SFALSE;
		}
	}

	if (ret) {
		switch (devgroup->dev_clk_data[data->dev_clk_idx + clk_idx].type) {
		case DEV_CLK_TABLE_TYPE_INPUT:
			ret = STRUE;
			break;
		case DEV_CLK_TABLE_TYPE_PARENT:
			ret = clk_get_state(clk) == CLK_HW_STATE_ENABLED;
			break;
		case DEV_CLK_TABLE_TYPE_MUX:
			ret = clk_get_state(clk) == CLK_HW_STATE_ENABLED;
			break;
		case DEV_CLK_TABLE_TYPE_OUTPUT:
			ret = STRUE;
			break;
		default:
			ret = SFALSE;
			break;
		}
	}

	return ret;
}

sbool device_clk_get_sw_gated(struct device *device, dev_clk_idx_t clk_idx)
{
	struct dev_clk *dev_clk = get_dev_clk(device, clk_idx);

	return dev_clk && (dev_clk->flags & DEV_CLK_FLAG_DISABLE);
}

void device_clk_set_ssc(struct device *device, dev_clk_idx_t clk_idx, sbool allow)
{
	struct dev_clk *dev_clk = get_dev_clk(device, clk_idx);
	struct clk *clk;
	sbool is_allowed;

	if (!dev_clk) {
		return;
	}

	is_allowed = !!(dev_clk->flags & DEV_CLK_FLAG_ALLOW_SSC);
	if (is_allowed == allow) {
		return;
	}

	dev_clk->flags ^= DEV_CLK_FLAG_ALLOW_SSC;

	if ((device->flags & DEV_FLAG_ENABLED_MASK) == 0UL) {
		return;
	}

	if (dev_clk->flags & DEV_CLK_FLAG_DISABLE) {
		return;
	}

	clk = dev_get_clk(device, clk_idx);

	if (!clk) {
		/* fail */
	} else if (allow) {
		clk_ssc_allow(clk);
	} else {
		clk_ssc_block(clk);
	}
}

sbool device_clk_get_ssc(struct device *device, dev_clk_idx_t clk_idx)
{
	struct dev_clk *dev_clk = get_dev_clk(device, clk_idx);

	return dev_clk && (dev_clk->flags & DEV_CLK_FLAG_ALLOW_SSC);
}

sbool device_clk_get_hw_ssc(struct device *device __attribute__(
				    (unused)), dev_clk_idx_t clk_idx __attribute__((unused)))
{
	/* FIXME: Implement */
	return SFALSE;
}

void device_clk_set_freq_change(struct device *device, dev_clk_idx_t clk_idx, sbool allow)
{
	struct dev_clk *dev_clk = get_dev_clk(device, clk_idx);
	struct clk *clk;
	sbool is_allowed;

	if (!dev_clk) {
		return;
	}

	is_allowed = !!(dev_clk->flags & DEV_CLK_FLAG_ALLOW_FREQ_CHANGE);
	if (is_allowed == allow) {
		return;
	}

	dev_clk->flags ^= DEV_CLK_FLAG_ALLOW_FREQ_CHANGE;

	if ((device->flags & DEV_FLAG_ENABLED_MASK) == 0UL) {
		return;
	}

	if (dev_clk->flags & DEV_CLK_FLAG_DISABLE) {
		return;
	}

	clk = dev_get_clk(device, clk_idx);

	if (!clk) {
		/* fail */
	} else if (allow) {
		clk_freq_change_allow(clk);
	} else {
		clk_freq_change_block(clk);
	}
}

sbool device_clk_get_freq_change(struct device *device, dev_clk_idx_t clk_idx)
{
	struct dev_clk *dev_clk = get_dev_clk(device, clk_idx);

	return dev_clk && (dev_clk->flags & DEV_CLK_FLAG_ALLOW_FREQ_CHANGE);
}

void device_clk_set_input_term(struct device *device, dev_clk_idx_t clk_idx, sbool enable)
{
	struct dev_clk *dev_clk = get_dev_clk(device, clk_idx);
	sbool is_term;

	if (!dev_clk) {
		return;
	}

	is_term = !!(dev_clk->flags & DEV_CLK_FLAG_INPUT_TERM);
	if (is_term == enable) {
		return;
	}

	dev_clk->flags ^= DEV_CLK_FLAG_INPUT_TERM;

	/* FIXME: Implement */
}

sbool device_clk_get_input_term(struct device *device, dev_clk_idx_t clk_idx)
{
	struct dev_clk *dev_clk = get_dev_clk(device, clk_idx);

	return dev_clk && (dev_clk->flags & DEV_CLK_FLAG_INPUT_TERM);
}

sbool device_clk_set_parent(struct device *device, dev_clk_idx_t clk_idx, dev_clk_idx_t parent_idx)
{
	struct clk *clk;
	const struct dev_clk_data *clk_data;
	const struct dev_clk_data *parent_data = NULL;
	sbool ret = STRUE;

	clk = dev_get_clk(device, clk_idx);
	clk_data = get_dev_clk_data(device, clk_idx);
	if (clk == NULL || clk_data == NULL) {
		ret = SFALSE;
	}


	if (ret && clk_data->type != DEV_CLK_TABLE_TYPE_MUX) {
		ret = SFALSE;
	}

	if (ret) {
		parent_data = get_dev_clk_data(device, parent_idx);
		if (parent_data == NULL) {
			ret = SFALSE;
		}
	}

	if (ret && parent_data->type != DEV_CLK_TABLE_TYPE_PARENT) {
		ret = SFALSE;
	}

	/* Make sure it's within this clock muxes parents */
	if (ret && parent_idx - clk_idx > clk_data->idx) {
		ret = SFALSE;
	}

	while (ret && clk && clk_get_data(clk)->type != CLK_TYPE_MUX) {
		const struct clk_parent *p;
		p = clk_get_parent(clk);
		if (p) {
			clk = clk_lookup((clk_idx_t) p->clk);
		} else {
			clk = NULL;
		}
	}

	if (!clk) {
		ret = SFALSE;
	}

	if (ret) {
		/* FIXME: Check for other uses of this mux */
		ret = clk_set_parent(clk, parent_data->idx);
	}

	return ret;
}

dev_clk_idx_t device_clk_get_parent(struct device *device, dev_clk_idx_t clk_idx)
{
	const struct dev_data *data = get_dev_data(device);
	const struct devgroup *devgroup = dev_data_lookup_devgroup(data);
	const struct clk_parent *p = NULL;
	struct clk *clk;
	const struct dev_clk_data *clk_data;
	sbool fail = SFALSE;
	dev_clk_idx_t ret = DEV_CLK_ID_NONE;
	dev_clk_idx_t i;

	clk = dev_get_clk(device, clk_idx);
	clk_data = get_dev_clk_data(device, clk_idx);
	if ((clk == NULL) || (clk_data == NULL) || (devgroup == NULL)) {
		fail = STRUE;
	}

	if (!fail && (clk_data->type != DEV_CLK_TABLE_TYPE_MUX)) {
		fail = STRUE;
	}

	while (!fail && (clk != NULL) && (clk_get_data(clk)->type != CLK_TYPE_MUX)) {
		p = clk_get_parent(clk);
		if (p) {
			clk = clk_lookup((clk_idx_t) p->clk);
		} else {
			clk = NULL;
		}
	}

	if (!fail) {
		p = clk_get_parent(clk);
		if (!p) {
			fail = STRUE;
		}
	}

	if (!fail) {
		u32 offset = data->dev_clk_idx;
		fail = STRUE;
		for (i = 0UL; i < clk_data->idx && fail; i++) {
			if (devgroup->dev_clk_data[offset + i + clk_idx + 1U].clk == p->clk) {
				ret = i + clk_idx + 1U;
				fail = SFALSE;
			}
		}
	}

	return ret;
}

dev_clk_idx_t device_clk_get_num_parents(struct device *device, dev_clk_idx_t clk_idx)
{
	struct clk *clk;
	const struct dev_clk_data *clk_data;
	dev_clk_idx_t ret;

	clk = dev_get_clk(device, clk_idx);
	clk_data = get_dev_clk_data(device, clk_idx);
	if (clk == NULL || clk_data == NULL) {
		ret = DEV_CLK_ID_NONE;
	} else if (clk_data->type != DEV_CLK_TABLE_TYPE_MUX) {
		if (clk_get_parent(clk)) {
			ret = 1U;
		} else {
			ret = 0U;
		}
	} else {
		ret = (dev_clk_idx_t) clk_data->idx;
	}

	return ret;
}

/**
 * \brief Set or query the frequency of a device's clock
 *
 * This locates the correct clock and calls the internal clock API
 * query/set function. If the clock is a mux type, we instead send the
 * request to the parent. This is because calling set freq on the mux may
 * switch the mux which is not what we want on muxes that are exposed on
 * devices.
 *
 * \param device
 * The device ID that the clock is connected to.
 *
 * \param clk_idx
 * The index of the clock on this device.
 *
 * \param min_freq_hz
 * The minimum acceptable frequency (Hz).
 *
 * \param target_freq_hz
 * The clock API will attempt to return a frequency as close as possible to the
 * target frequency (Hz).
 *
 * \param max_freq_hz
 * The maximum acceptable frequency (Hz).
 *
 * \param query
 * True if this is a query (make no changes), SFALSE if this is a set (make
 * changes if possible).
 *
 * \return
 * The actual frequency possible (query=STRUE) or set (query=SFALSE). Returns
 * 0 if a frequency could not be found within the limits.
 */
static u32 __device_clk_set_freq(struct device *device, dev_clk_idx_t clk_idx,
				 u32 min_freq_hz, u32 target_freq_hz,
				 u32 max_freq_hz, sbool query)
{
	const struct dev_data *data = get_dev_data(device);
	const struct devgroup *devgroup = dev_data_lookup_devgroup(data);
	const struct dev_clk_data *clk_data;
	struct clk *parent = NULL;
	struct clk *unblock1 = NULL;
	struct clk *unblock2 = NULL;
	u32 div = 1U;
	sbool done = SFALSE;
	u32 ret_freq = 0UL;

	if (devgroup == NULL) {
		done = STRUE;
	}

	if (!done) {
		clk_data = get_dev_clk_data(device, clk_idx);
		if (clk_data == NULL) {
			/* Invalid clock idx */
			done = STRUE;
		}
	}

	if (!done) {
		parent = dev_get_clk(device, clk_idx);
		if (parent == NULL) {
			/* Parent not present */
			done = STRUE;
		}
	}

	if (!done) {
		/* Assign div based on selected clock */
		div = clk_data->div;

		/*
		 * We drop the block count on up to two clocks. The clock
		 * id we are directly controlling is the first one.
		 */
		if (!device_clk_get_freq_change(device, clk_idx)) {
			if ((device->flags & DEV_FLAG_ENABLED_MASK) != 0UL &&
			    !device_clk_get_sw_gated(device, clk_idx)) {
				unblock1 = parent;
			}
		}

		if (clk_get_data(parent)->type == CLK_TYPE_MUX &&
		    clk_data->type == DEV_CLK_TABLE_TYPE_MUX) {
			const struct dev_clk_data *parent_clk_data;
			/* Send to parent */
			clk_idx = device_clk_get_parent(device, clk_idx);
			parent = dev_get_clk(device, clk_idx);
			parent_clk_data = get_dev_clk_data(device, clk_idx);
			if (parent_clk_data) {
				/* We are sending to parent, so use that div instead */
				div = parent_clk_data->div;
			}
			if (parent == NULL) {
				/* Mux parent clock not present */
				done = STRUE;
			} else if (!device_clk_get_freq_change(device, clk_idx)) {
				/*
				 * If we are changing a clock with a device
				 * clock mux parent, unblock that clock as
				 * well. (Note, device clock mux parents are
				 * unblocked by default but can be blocked via
				 * the TI-SCI API).
				 */
				if ((device->flags & DEV_FLAG_ENABLED_MASK) != 0UL &&
				    !device_clk_get_sw_gated(device, clk_idx)) {
					unblock2 = parent;
				}
			}
		} else if (clk_data->type == DEV_CLK_TABLE_TYPE_PARENT) {
			/*
			 * If we are changing a mux parent, also unblock the
			 * child clock it connects to. First we need to walk
			 * back the table to find the child clock.
			 */
			s32 i;
			u32 offset = data->dev_clk_idx;
			for (i = clk_idx - 1L; i >= 0L; i--) {
				if (devgroup->dev_clk_data[offset + i].type == DEV_CLK_TABLE_TYPE_MUX) {
					break;
				}
			}
			/*
			 * Make sure the mux has currently selected the target
			 * clock.
			 */
			if (i >= 0 && clk_idx == device_clk_get_parent(device, i)) {
				if (device_clk_get_freq_change(device, i)) {
					if ((device->flags & DEV_FLAG_ENABLED_MASK) != 0UL &&
					    !device_clk_get_sw_gated(device, clk_idx)) {
						unblock2 = dev_get_clk(device, i);
					}
				}
			}
		}
	}

	if (!done) {
		if (clk_data->type == DEV_CLK_TABLE_TYPE_OUTPUT) {
			/* div is only for input clocks */
			div = 1U;
		}

		if (!clk_data->modify_parent_freq) {
			ret_freq = clk_get_freq(parent) / div;
			if (ret_freq < min_freq_hz || ret_freq > max_freq_hz) {
				ret_freq = 0UL;
			}
			done = STRUE;
		}
	}

	if (!done) {
		sbool changed;
		changed = SFALSE;
		/* Drop unblock refs as necessary */
		if (unblock1 != NULL) {
			clk_freq_change_allow(unblock1);
		}
		if (unblock2 != NULL) {
			clk_freq_change_allow(unblock2);
		}
		/* Try to modify the frequency */

		if (clk_data->type == DEV_CLK_TABLE_TYPE_OUTPUT) {
			/*
			 * This is the only place device output clocks can have their
			 * frequency changed, from their own device.
			 */
			ret_freq = clk_value_set_freq(parent, target_freq_hz, min_freq_hz,
						      max_freq_hz, query, &changed);
		} else {
			ret_freq = clk_generic_set_freq_parent(NULL, parent,
							       target_freq_hz,
							       min_freq_hz,
							       max_freq_hz,
							       query, &changed,
							       div);
		}

		/* Put the block refs back */
		if (unblock1 != NULL) {
			clk_freq_change_block(unblock1);
		}
		if (unblock2 != NULL) {
			clk_freq_change_block(unblock2);
		}
	}

	return ret_freq;
}

sbool device_clk_set_freq(struct device *device, dev_clk_idx_t clk_idx, u32 min_freq_hz,
			  u32 target_freq_hz, u32 max_freq_hz)
{
	return __device_clk_set_freq(device, clk_idx, min_freq_hz,
				     target_freq_hz, max_freq_hz, SFALSE) != 0UL;
}

u32 device_clk_query_freq(struct device *device, dev_clk_idx_t clk_idx,
			  u32 min_freq_hz, u32 target_freq_hz,
			  u32 max_freq_hz)
{
	return __device_clk_set_freq(device, clk_idx, min_freq_hz,
				     target_freq_hz, max_freq_hz, STRUE);
}

u32 device_clk_get_freq(struct device *device, dev_clk_idx_t clk_idx)
{
	struct clk *clk;
	const struct dev_clk_data *clk_data;
	u32 freq_hz;

	clk = dev_get_clk(device, clk_idx);
	clk_data = get_dev_clk_data(device, clk_idx);
	if (clk == NULL || clk_data == NULL) {
		freq_hz = 0UL;
	} else {
		freq_hz = clk_get_freq(clk);
		if (clk_data->type != DEV_CLK_TABLE_TYPE_OUTPUT) {
			freq_hz /= clk_data->div;
		}
	}

	return freq_hz;
}

void device_clk_enable(struct device *device, dev_clk_idx_t clk_idx)
{
	struct dev_clk *dev_clk;
	struct clk *clk = NULL;

	dev_clk = get_dev_clk(device, clk_idx);
	if (dev_clk && !(dev_clk->flags & DEV_CLK_FLAG_DISABLE)) {
		clk = dev_get_clk(device, clk_idx);
	}

	if (clk) {
		if (!(dev_clk->flags & DEV_CLK_FLAG_ALLOW_SSC)) {
			clk_ssc_block(clk);
		}

		if (!(dev_clk->flags & DEV_CLK_FLAG_ALLOW_FREQ_CHANGE)) {
			clk_freq_change_block(clk);
		}

		clk_get(clk);
	}
}

void device_clk_disable(struct device *device, dev_clk_idx_t clk_idx)
{
	struct dev_clk *dev_clk;
	struct clk *clk = NULL;

	dev_clk = get_dev_clk(device, clk_idx);
	if (dev_clk && !(dev_clk->flags & DEV_CLK_FLAG_DISABLE)) {
		clk = dev_get_clk(device, clk_idx);
	}

	if (clk) {
		clk_put(clk);

		if (!(dev_clk->flags & DEV_CLK_FLAG_ALLOW_SSC)) {
			clk_ssc_allow(clk);
		}

		if (!(dev_clk->flags & DEV_CLK_FLAG_ALLOW_FREQ_CHANGE)) {
			clk_freq_change_allow(clk);
		}
	}
}

void device_clk_init(struct device *device, dev_clk_idx_t clk_idx)
{
	struct clk *clk = NULL;
	struct dev_clk *dev_clk;
	const struct dev_clk_data *dev_clk_data;

	dev_clk = get_dev_clk(device, clk_idx);
	dev_clk_data = get_dev_clk_data(device, clk_idx);

	/* Don't configure parent clocks for anything until host does */
	if ((dev_clk_data != NULL) && (dev_clk != NULL)) {
		if (dev_clk_data->type == DEV_CLK_TABLE_TYPE_PARENT) {
			dev_clk->flags |= DEV_CLK_FLAG_DISABLE |
					  DEV_CLK_FLAG_ALLOW_SSC |
					  DEV_CLK_FLAG_ALLOW_FREQ_CHANGE;
		}
	}

	if ((dev_clk_data != NULL) && (dev_clk != NULL)) {
		clk = clk_lookup((clk_idx_t) dev_clk_data->clk);
	}
	if (clk != NULL) {
		const struct clk_data *clk_data = clk_get_data(clk);

		/* It's in another devgroup, don't attempt to bring it up */
		if ((clk->flags & CLK_FLAG_INITIALIZED) == 0U) {
			dev_clk->flags |= DEV_CLK_FLAG_DISABLE;
		}

		/*
		 * For clocks with this flag set, default all dev_clk's to
		 * allow. Otherwise default all dev_clk's to block.
		 */
		if ((clk_data != NULL) && ((clk_data->flags & CLK_DATA_FLAG_ALLOW_FREQ_CHANGE) != 0UL)) {
			dev_clk->flags |= DEV_CLK_FLAG_ALLOW_FREQ_CHANGE;
		}
	}
}
