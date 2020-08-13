/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <sleep.h>
#include <stddef.h>
#include <types/errno.h>
#include <types/array_size.h>
#include <wake.h>
#include <lib/trace.h>

static const struct sleep_mode *sleep_modes __attribute__((unused));
static u8 *sleep_modes_block __attribute__((unused));
static size_t sleep_mode_count __attribute__((unused));

void sleep_mode_update(u8 sleep_mode __attribute__((unused)), sbool allow __attribute__((unused)))
{
}

void sleep(void)
{
}

s32 sleep_modes_register(const struct sleep_mode *modes, u8 *block, size_t n)
{
	s32 ret = 0;

	if (sleep_modes && modes != sleep_modes) {
		ret = -EBUSY;
	} else {
		sleep_mode_count = n;
		sleep_modes_block = block;
		sleep_modes = modes;
	}

	return ret;
}
