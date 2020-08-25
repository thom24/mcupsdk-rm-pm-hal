/*
 * System Firmware Trace Layer
 *
 * Utility itoa function for number to string conversion
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/short_types.h>

u8 *lib_itoa(u32 value, u8 *str, s32 base)
{
	u32 idx = 0;
	u32 val;
	u32 i;

	if (value == 0) {
		str[0] = '0';
		idx++;
	}

	while (value > 0) {
		val = value % base;
		if (val < 10) {
			str[idx] = val + '0';
		} else {
			str[idx] = (val - 10) + 'A';
		}

		idx++;
		value /= base;
	}

	str[idx] = '\0';

	if (idx > 1) {
		/* Get length of string - NULL terminator*/
		idx--;

		/* Reverse the string as we converted from low digit to high */
		for (i = 0; i <= (idx / 2); i++) {
			val = str[idx - i];
			str[idx - i] = str[i];
			str[i] = val;
		}
	}

	return str;
}
