/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef IOREMAP_EXPLICIT_H
#define IOREMAP_EXPLICIT_H

#include <config.h>
#include <types/short_types.h>

u32 ioremap_internal(u32 a);

#define ioremap_explicit ioremap_internal

#endif
