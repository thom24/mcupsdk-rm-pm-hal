/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <div64.h>

u64 pm_div64(u64 *remainder64, u32 b32)
{
	u32 ah32, al32;
	u64 a64;
	u64 b64;
	u64 bit64;
	u64 result64;

	if (*remainder64 == 0ULL) {
		result64 = 0ULL;
	} else {
		if (b32 == 0U) {
			/* Generate exception */
			result64 = (u64) (1U / b32);
		} else {
			a64 = *remainder64;

			ah32 = (u32) (a64 >> 32U);
			al32 = (u32) (a64 & 0xffffffffULL);

			result64 = 0ULL;

			/* Check if b * 2^32 fits at least once */
			if (ah32 >= b32) {
				/* Divide out b * 2^32 */
				ah32 /= b32;
				result64 = ((u64) ah32) << 32U;
				a64 -= result64 * b32;
			}

			/* 32 bit division possible */
			if (ah32 == 0U) {
				a64 = (u64) (al32 % b32);
				result64 += (u64) (al32 / b32);
			} else {
				/* Time for long division */
				b64 = ((u64) b32) << 32U;
				bit64 = 1ULL << 32;

				/* Shift divisor up to line up with remaining dividend */
				while (b64 < a64) {
					b64 <<= 1U;
					bit64 <<= 1U;
				}

				/* Long division loop */
				do {
					if (b64 <= a64) {
						a64 -= b64;
						result64 += bit64;
					}
					b64 >>= 1U;
					bit64 >>= 1U;
				} while (bit64 != 0ULL);
			}

			*remainder64 = a64;
		}
	}

	return result64;
}
