/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef PUTS_H
#define PUTS_H

#include <types.h>

/*
 * Some output types operate more efficiently when they can queue characters
 * rather than operating on a character at a time. To make this work
 * efficiently with out printf implementation, we need some method to
 * notify the character driver that it needs to flush current output
 */
#define PUTCHAR_FLUSH   -1

s32 set_putchar(int (*pc)(int));
s32 putchar(s32 c);
s32 puts(const char *str);
s32 putsn(const char *s, size_t maxlen);

#endif
