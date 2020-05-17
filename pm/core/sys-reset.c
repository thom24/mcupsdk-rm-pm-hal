/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <sys-reset.h>
#include <types/short_types.h>

static void (*sys_reset_handler)(void);

void system_reset(void)
{
	if (sys_reset_handler) {
		sys_reset_handler();
	}
}

void sys_reset_handler_register(void (*handler)(void))
{
	sys_reset_handler = handler;
}
