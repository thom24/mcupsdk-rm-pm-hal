/*
 * System Firmware Source File
 *
 * Software defined Device groups (devgrps) for J7200 device.
 *
 * Data version: 190425_000000
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef SOC_J7200_DOMGRPS_H
#define SOC_J7200_DOMGRPS_H

#include <types/domgrps.h>

/**
 * identifier for system reset. It's for backward compatibility of the sys_reset().
   It will reset the WKUP, MCU, MAIN domain.
 */
#define SOC_DOMGRP_J7200_SYSTEM DOMGRP_COMPATIBILITY

/**
 * identifier for MCU_RESETz reset. It affects all domains (WKUP, MCU, MAIN).
 */
#define SOC_DOMGRP_J7200_MCU DOMGRP_00

/**
 * identifier for RESET_REQz reset. It affects the MAIN domain
 */
#define SOC_DOMGRP_J7200_MAIN DOMGRP_01


#endif /* SOC_J7200_DOMGRPS_H */
