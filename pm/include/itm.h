/*
 * System Firmware (ITM Print support)
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef ITM_H
#define ITM_H

#include <config.h>
#include <device.h>
#include <types/errno.h>

struct debugss_drv_data {
	struct drv_data drv_data;
	unsigned char	itm_channel;
};

#ifdef CONFIG_ITM
void itm_putchar(s32 c);
s32 itm_init(struct device *dev);
#else
static inline void itm_putchar(s32 c)
{
}
static inline s32 itm_init(struct device *dev)
{
	return -ENODEV;
}
#endif

#endif  /* ITM_H */
