/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <lib/strncpy.h>

char *lib_strncpy(char *a, const char *b, size_t n)
{
	char *_a = a;

	while (b[0]) {
		if (!(n--)) {
			n = 0;
			break;
		}
		*a++ = *b++;
	}

	while (n--) {
		*a++ = '\0';
	}
	return _a;
}
