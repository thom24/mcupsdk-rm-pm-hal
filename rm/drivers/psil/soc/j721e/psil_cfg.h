/*
 * PSI-L
 *
 * PSI-L SoC-specific configuration definitions
 *
 * Data version: 190425_000000
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef PSIL_CFG_H
#define PSIL_CFG_H

#include <config.h>

/**
 * Number of threads used by ROM during boot
 */
#if !defined(CONFIG_DEVICE_TYPE_HS)
#define PSIL_ROM_USAGE_CNT (10U)
#else
#define PSIL_ROM_USAGE_CNT (7U)
#endif


#endif /* PSIL_CFG_H */
