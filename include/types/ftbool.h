/*
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

/**
 * \file ftbool.h
 *
 * \brief Fault tolerant boolean types and checks
 *
 */
#ifndef FTBOOL_H
#define FTBOOL_H

#include <types/short_types.h>
#include <types/sbool.h>

/**
 * Fault tolerant boolean type
 */
typedef u8 ftbool;

/*
 * function prototypes
 */
static inline sbool ft_is_true(ftbool val);
static inline sbool ft_is_false(ftbool val);
static inline sbool ft_s_is_true(u32 val);

/**
 * Fault tolerant "STRUE" value
 */
#define FT_TRUE         0x5AU
/**
 * Fault tolerant "SFALSE" value
 */
#define FT_FALSE        0xA5U

/**
 * Fault tolerant check for "STRUE"
 */
static inline sbool ft_is_true(ftbool val)
{
	return (val) == FT_TRUE;
}

/**
 * Fault tolerant check for "SFALSE"
 */
static inline sbool ft_is_false(ftbool val)
{
	return (val) == FT_FALSE;
}

/**
 * Short fault tolerant "STRUE" value (4-bits) used in H/W registers
 */
#define FT_S_TRUE       0xAU

/**
 * Short fault tolerant "SFALSE" value
 */
#define FT_S_FALSE        0x5U

/**
 * Fault tolerant check for "STRUE" (short value)
 */
static inline sbool ft_s_is_true(u32 val)
{
	return (val) == FT_S_TRUE;
}

#endif /* FTBOOL */
