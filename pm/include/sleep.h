/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef SLEEP_H
#define SLEEP_H

#include <types/short_types.h>
#include <psc.h>
#include <types/sbool.h>

#if defined (__TI_ARM_V7M3__)
#include <arch/barrier.h>
#endif

struct sleep_mode {
	char	*name;
	sbool	wake_sources;
	int	(*enter)(void);
	int	(*exit)(void);
};

void sleep_mode_update(u8 sleep_mode, sbool allow);

void sleep(void);

s32 sleep_modes_register(const struct sleep_mode *modes, u8 *block, size_t n);

#endif
