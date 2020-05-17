/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <startup.h>

/* This is invoked only if PM is disabled - Essentially does nothing ... */
s32 pm_init(void)
{
	return 0;
}
