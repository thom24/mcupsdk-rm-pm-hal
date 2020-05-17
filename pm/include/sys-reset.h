/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef SYS_RESET_H
#define SYS_RESET_H

#include <types.h>
#include <types/sbool.h>
#include <stddef.h>
#include <config.h>
#include <types/short_types.h>

void system_reset(void);
void sys_reset_handler_register(void (*handler)(void));

#endif
