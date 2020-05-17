/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef ARCH_IOREMAP_H
#define ARCH_IOREMAP_H

#include <config.h>
#include <types/short_types.h>

#define ioremap(a) ioremap_internal(a)
u32 ioremap_internal(u32 a);

#include <lib/io.h>
static inline s32 pm_writel_verified(u32 v, local_phys_addr_t a)
{
	return writel_verified(v, ioremap(a));
}

static inline s32 pm_writew_verified(u32 v, local_phys_addr_t a)
{
	return writew_verified(v, ioremap(a));
}

static inline s32 pm_writeb_verified(u32 v, local_phys_addr_t a)
{
	return writeb_verified(v, ioremap(a));
}

#endif
