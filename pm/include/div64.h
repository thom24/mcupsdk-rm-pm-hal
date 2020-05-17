/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef DIV64_H
#define DIV64_H

#include <types/short_types.h>
#include <compiler.h>

/**
 * 64-bit division/modulo.
 *
 * Perform a 64-bit division/modulo operation. This divides a 64-bit numerator
 * by a 32-bit denominator and provides the result and remainder. Note that
 * passing the value 0 for denominator will result in an exception.
 *
 * @param rem The numerator should be passed in this memory location. The
 * remainder is returned in this memory location.
 *
 * @param b The denominator.
 *
 * @return The result of the division.
 */
u64 pm_div64(u64 *rem, u32 b);

/**
 * 64-bit division.
 *
 * Perform a 64-bit division operation. This divides a 64-bit numerator
 * by a 32-bit denominator and provides the result. Note that passing
 * the value 0 for denominator will result in an exception.
 *
 * @param a The numerator.
 *
 * @param b The denominator.
 *
 * @return The result of the division.
 */
static inline u64 div64(u64 a, u32 b)
{
	return pm_div64(&a, b);
}

/**
 * 64-bit modulo.
 *
 * Perform a 64-bit division operation. This divides a 64-bit numerator
 * by a 32-bit denominator and provides the remainder. Note that passing
 * the value 0 for denominator will result in an exception.
 *
 * @param a The numerator.
 *
 * @param b The denominator.
 *
 * @return The remainder of the division.
 */
static inline u64 mod64(u64 a, u32 b)
{
	u64 temp UNUSED;

	temp = pm_div64(&a, b);
	return a;
}


#endif
