/*
 * System Firmware Multiplication Utilities
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef MUL_H
#define MUL_H

#include <types/sbool.h>
#include <types/short_types.h>

/*
 * \brief Multiply and return overflow status.
 *
 * Multiply two 32-bit numbers and return true if the value did not fit in
 * the 32-bit result.
 *
 * Note that ARM does not provide a flag on multiplication overflow. We
 * instead use umull to produce a 64-bit result from two 32-bit operands.
 * umull just takes a couple extra cycles vs a 32-bit umul. We create
 * this as an inline to allow the compiler to optimize it properly.
 *
 * \param a
 * First operand.
 *
 * \param b
 * Second operand.
 *
 * \param c
 * Pointer to location to store result.
 *
 * \return
 * True if overflow occurred, false otherwise
 */
static inline sbool mul32_check_overflow(u32 a, u32 b, u32 *ret)
{
	u64 d = (u64) a * b;

	*ret = (u32) d;
	return d > 0xffffffffULL;
}

#endif
