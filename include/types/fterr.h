/*
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

/**
 * \file types/fterr.h
 *
 * \brief Fault tolerant error codes, types and checks
 *
 */
#ifndef FTERR_H
#define FTERR_H

#include <types/short_types.h>
#include <types/errno.h>
#include <types/sbool.h>

/**
 * Fault tolerant non-boolean return type
 */
typedef s32 fterr;

/*
 * Function prototypes
 */
static inline sbool ft_is_ok(fterr val);
static inline fterr fterr_from_common(s32 e);
static inline s32 fterr_to_common(fterr e);

/**
 * No error (Not using zero for success for fault tolerance). Must be returned
 * as a positive value. (Not as -EFTOK)
 */
#define EFTOK           ((fterr) 0x5A)

/**
 * Translate from common error to fterr, only the success value is different
 * Other error codes are common to allow for easy translation. Does not impact
 * fault tolerance.
 */
static inline fterr fterr_from_common(s32 e)
{
	return (fterr) (((e) == 0) ? EFTOK : (e));
}

/**
 * Translate to common error from fterr, only the success value is different
 * Other error codes are common to allow for easy translation. Does not impact
 * fault tolerance.
 */
static inline s32 fterr_to_common(fterr e)
{
	return (s32) (((e) == EFTOK) ? 0 : (e));
}


/**
 * Check of EFTOK
 */
static inline sbool ft_is_ok(fterr val)
{
	return (val) == EFTOK;
}


#endif /* FTERR_H */
