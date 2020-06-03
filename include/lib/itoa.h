/*
 * System Firmware Trace Layer
 *
 * Utility itoa function for number to string conversion
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef ITOA_H
#define ITOA_H

#include <types/short_types.h>

/**
 * \brief Integer to alphanumberic conversion.
 *
 * \param value Number to convert to string.
 * \param str Pointer to buffer large enough to hold number.
 * \param base Base to convert number to.
 *
 * \returns Pointer to str.
 */
u8 *lib_itoa(u32 value, u8 *str, s32 base);

#endif /* ITOA_H */
