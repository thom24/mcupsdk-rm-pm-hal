/*
 * System Firmware Boolean Type definition
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef BOOL_H
#define BOOL_H

#include <types/short_types.h>

/**
 * Internal definition of boolean type
 */
#ifndef __cplusplus
typedef _Bool sbool;
#else
typedef bool sbool;
#endif

#define STRUE           ((sbool) 1U)
#define SFALSE          ((sbool) 0U)

#endif /* BOOL_H */
