/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/errno.h>
#include <device.h>
#include <device_pm.h>
#include <device_clk.h>
#include <types/short_types.h>
#include <lib/trace.h>
#include <list.h>
#include <notifier.h>

static LIST_HEAD(device_notifiers);

static void device_notify(struct device *dev)
{
	notifier_call(&device_notifiers, dev);
}

void register_device_notifier(struct notifier *n)
{
	notifier_register(&device_notifiers, n);
}

void device_suspend(struct device *dev)
{
	const struct dev_data *data = get_dev_data(dev);

	if (data->flags & DEVD_FLAG_DRV_DATA) {
		const struct drv *drv = to_drv_data(data)->drv;
		if (drv && drv->suspend) {
			drv->suspend(dev);
		}
	}
}

/**
 * \brief Enables a device.
 *
 * Performs the steps necessary to enable a device.
 *
 * \param device
 * The device to modify.
 */
static void device_enable(struct device *dev)
{
	const struct dev_data *data = get_dev_data(dev);
	u32 i;

	for (i = 0UL; i < data->n_clocks; i++) {
		/* FIXME: Error handling */
		device_clk_enable(dev, i);
	}
	soc_device_enable(dev);

	device_notify(dev);
}

/**
 * \brief Disables a device.
 *
 * Performs the steps necessary to disable a device.
 *
 * \param device
 * The device to modify.
 */
static void device_disable(struct device *dev)
{
	const struct dev_data *data = get_dev_data(dev);
	s32 i;

	device_notify(dev);

	soc_device_disable(dev);
	for (i = data->n_clocks - 1L; i >= 0L; i--) {
		device_clk_disable(dev, i);
	}
}

void device_set_state(struct device *device, u8 host_idx, sbool enable)
{
	sbool was_enabled;
	sbool is_enabled;

	was_enabled = (device->flags & DEV_FLAG_ENABLED_MASK) != 0UL;

	if (enable) {
		device->flags |= DEV_FLAG_ENABLED(host_idx);
	} else {
		device->flags &= ~DEV_FLAG_ENABLED(host_idx);
	}

	/*
	 * As soon as any host gets or puts a device, we drop the power
	 * on enabled flag.
	 */
	if (host_idx != DEV_POWER_ON_ENABLED_HOST_IDX) {
		device->flags &= ~DEV_FLAG_POWER_ON_ENABLED;
	}

	is_enabled = (device->flags & DEV_FLAG_ENABLED_MASK) != 0UL;

	if (was_enabled != is_enabled) {
		if (is_enabled) {
			device_enable(device);
		} else {
			device_disable(device);
		}
	}
}

void device_set_retention(struct device *device, sbool retention)
{
	sbool is_retention = !!(device->flags & DEV_FLAG_RETENTION);

	if (retention == is_retention) {
		return;
	}

	if (retention) {
		device->flags |= DEV_FLAG_RETENTION;
		soc_device_ret_enable(device);
	} else {
		device->flags &= ~DEV_FLAG_RETENTION;
		soc_device_ret_disable(device);
	}
}
