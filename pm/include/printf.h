/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef PRINTF_H
#define PRINTF_H

#include <stdarg.h>
#include <types.h>

s32 vprintf(char const *fmt, va_list ap);
s32 printf(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

#endif
