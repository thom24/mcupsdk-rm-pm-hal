/*
 * System Firmware Source File
 *
 * Software defined Device groups (devgrps) for AM64X device.
 *
 * Data version: 200505_104840
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef SOC_AM64X_DEVGRPS_H
#define SOC_AM64X_DEVGRPS_H

#include <types/devgrps.h>

/**
 * Set of MCU domain peripherals to initialize at boot and use during runtime.
 */
#define SOC_DEVGRP_AM64X_MCU_WAKEUP DEVGRP_00

/**
 * Set of Main domain peripherals to initialize at boot and use during
 * runtime.
 */
#define SOC_DEVGRP_AM64X_MAIN DEVGRP_01

/**
 * Set of peripherals to initialize for System Firmware internal usage
 */
#define SOC_DEVGRP_AM64X_DMSC_INTERNAL DEVGRP_DMSC


#endif /* SOC_AM64X_DEVGRPS_H */
