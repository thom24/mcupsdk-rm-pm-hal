/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef IOREMAP_H
#define IOREMAP_H

#include <config.h>
#include <types/short_types.h>

/*
 * The header below should not be included on its own and its behavior
 * is sensitive to IOREMAP_H and IO_H include guard defines.
 */
#include <lib/io_internal.h>

#if defined(IO_H)
#warning Only lib/ioremap.h or lib/io.h should be included, not both.
#endif

static inline s32 pm_writel_verified(u32 v, local_phys_addr_t a)
{
	return writel_verified(v, ioremap(a));
}

static inline s32 pm_writew_verified(u16 v, local_phys_addr_t a)
{
	return writew_verified(v, ioremap(a));
}

static inline s32 pm_writeb_verified(u8 v, local_phys_addr_t a)
{
	return writeb_verified(v, ioremap(a));
}

#endif
