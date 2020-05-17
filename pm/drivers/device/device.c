/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <stddef.h>
#include <types/errno.h>
#include <types/short_types.h>
#include <lib/trace.h>
#include <device.h>
#include <device_pm.h>
#include <device_clk.h>
#include <clk.h>
#include <hosts.h>

/** The bitmask of currently enabled devgroups. */
static u32 pm_devgroups_enabled;

/** True if devices have completed deferred init. */
static sbool devices_rw;

void pm_devgroup_set_enabled(devgrp_t groups)
{
	pm_devgroups_enabled |= groups;
}

sbool pm_devgroup_is_enabled(devgrp_t groups)
{
	return (pm_devgroups_enabled & groups) != 0U;
}

/**
 * \brief Initialize a device
 *
 * This performs the necessary device initialization step, including syncing
 * the flags on the device with the real hardware state and calling the clock
 * init function for each clock.
 *
 * \param device
 * The device to init.
 *
 * \return
 * 0 on success, <0 on failure.
 */
static s32 device_init(struct device *dev)
{
	const struct dev_data *data = get_dev_data(dev);
	s32 ret = SUCCESS;
	s32 i;

	if ((data != NULL) && ((data->flags & DEVD_FLAG_DRV_DATA) != 0U) &&
	    ((data->flags & DEVD_FLAG_DO_INIT) != 0U)) {
		const struct drv *drv = to_drv_data(data)->drv;
		if ((drv != NULL) && (drv->pre_init != NULL)) {
			ret = drv->pre_init(dev);
		}
	}

	if (!devices_rw) {
		/* Defer remainder of init */
		data = NULL;
	}

	if ((data != NULL) && (ret == SUCCESS)) {
		ret = soc_device_init(dev);
	}

	/* Calling these multiple times for a deferred device has no effect */
	if ((data != NULL) && (ret == SUCCESS)) {
		for (i = 0U; i < data->n_clocks; i++) {
			device_clk_init(dev, i);
		}

		/* Calling these multiple times for a deferred device has no effect */
		if (device_get_state(dev) != 0U) {
			device_set_state(dev, DEV_POWER_ON_ENABLED_HOST_IDX, STRUE);
			device_set_retention(dev, STRUE);
		}

		/*
		 * FIXME: Set reset isolation flag as marked by LPSC
		 * FIXME: Set local reset bit as marked by LPSC
		 */

		if (((data->flags & DEVD_FLAG_DRV_DATA) != 0U) &&
		    ((data->flags & DEVD_FLAG_DO_INIT) != 0U)) {
			const struct drv *drv = to_drv_data(data)->drv;
			if ((drv != NULL) && (drv->post_init != NULL)) {
				ret = drv->post_init(dev);
			}
		}
	}

	return ret;
}

s32 devices_init(void)
{
	sbool done;
	sbool progress;
	sbool contents;
	sbool errors;
	dev_idx_t idx;
	s32 ret = SUCCESS;

	errors = SFALSE;
	contents = SFALSE;
	do {
		struct device *dev;

		done = STRUE;
		progress = SFALSE;
		dev = soc_devices;

		for (idx = 0U; idx < soc_device_count; idx++, dev++) {
			devgrp_t devgrp;

			if (dev->initialized != 0U) {
				continue;
			}

			if (soc_device_data[idx] == NULL) {
				continue;
			}

			/* Translate compressed internal representation to bitfield */
			if (soc_device_data[idx]->pm_devgrp == PM_DEVGRP_DMSC) {
				devgrp = DEVGRP_DMSC;
			} else {
				devgrp = BIT(soc_device_data[idx]->pm_devgrp - 1U);
			}

			if (!pm_devgroup_is_enabled(devgrp)) {
				continue;
			}

			contents = STRUE;

			ret = device_init(dev);
			if (ret == -EDEFER) {
				done = SFALSE;
			} else {
				progress = STRUE;
				dev->initialized = STRUE;
				if (ret < 0) {
					pm_trace(TRACE_PM_ACTION_FAIL | TRACE_PM_ACTION_DEV_INIT,
						 (((-ret) & TRACE_PM_VAL_DEV_INIT_ERR_MASK) << TRACE_PM_VAL_DEV_INIT_ERR_SHIFT) |
						 ((((u16) idx) & TRACE_PM_VAL_DEV_INIT_DEVICE_ID_MASK) << TRACE_PM_VAL_DEV_INIT_DEVICE_ID_SHIFT));
					errors = STRUE;
				}
			}
		}
	} while (!done && progress);

	if (devices_rw) {
		/* Only necessary after deferred initialization */
		clk_drop_pwr_up_en();
	}

	if (progress) {
		if (devices_rw) {
			/* Only necessary after deferred initialization */
			soc_device_init_complete();
		}

		if (errors == SFALSE) {
			pm_trace(TRACE_PM_ACTION_DEV_INIT, 0x0U);
		}

		ret = SUCCESS;
	} else if (contents) {
		/* We processed at least one device but didn't make progress */
		ret = -EDEFER;
	} else {
		/* We didn't process any devices */
		ret = SUCCESS;
	}

	return ret;
}

s32 devices_init_rw(void)
{
	s32 ret = SUCCESS;

	if (!devices_rw) {
		u32 i;

		/*
		 * Force reinitialization of all devices to get defered
		 * initialization.
		 */
		for (i = 0U; i < soc_device_count; i++) {
			struct device *dev = &soc_devices[i];
			dev->initialized = 0U;
		}

		devices_rw = STRUE;

		/* Perform defered initialization */
		ret = devices_init();
	}

	return ret;
}

void devices_drop_power_up_ref(void)
{
	dev_idx_t idx;

	for (idx = 0U; idx < soc_device_count; idx++) {
		struct device *dev = soc_devices + idx;
		if (dev->initialized != 0U) {
			device_set_state(dev, DEV_POWER_ON_ENABLED_HOST_IDX, SFALSE);
		}
	}
}
