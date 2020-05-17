/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef REMOTE_H
#define REMOTE_H

#include <types/sbool.h>
#include <stddef.h>
#include <device.h>
#include <types/short_types.h>

struct remote_drv_data {
	struct drv_data		drv_data;
	const struct irq_data	*irq_data;
	u8			host;
};

struct resource_irq;

sbool remote_wake_check(u32 host);

s32 remote_do_suspend(struct device *dev);

void remote_pwrdwn_handler(const struct resource_irq *irq, void *data);

extern const struct drv remote_drv;

#endif
