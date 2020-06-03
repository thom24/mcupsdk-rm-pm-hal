/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef IO_H
#define IO_H

/*
 * The header below should not be included on its own and its behavior
 * is sensitive to IOREMAP_H and IO_H include guard defines.
 */
#include <lib/io_internal.h>

#if defined(IOREMAP_H)
#warning Only lib/ioremap.h or lib/io.h should be included, not both.
#endif

#endif
