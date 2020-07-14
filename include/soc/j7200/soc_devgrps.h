/*
 * System Firmware Source File
 *
 * Software defined Device groups (devgrps) for J7200 device.
 *
 * Data version: 200717_093321
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef SOC_J7200_DEVGRPS_H
#define SOC_J7200_DEVGRPS_H

#include <types/devgrps.h>

/**
 * Set of MCU domain peripherals to initialize at boot and use during runtime.
 * Utilize this device group of MCU/Wakeup domain peripherals to achieve a
 * faster boot sequence
 */
#define SOC_DEVGRP_J7200_MCU_WAKEUP DEVGRP_00

/**
 * Set of Main domain peripherals to initialize at boot and use during
 * runtime.  Utilize this device group of non-critical peripherals for
 * advanced use cases.
 */
#define SOC_DEVGRP_J7200_MAIN DEVGRP_01

/**
 * Set of peripherals to initialize for System Firmware internal usage
 */
#define SOC_DEVGRP_J7200_DMSC_INTERNAL DEVGRP_DMSC


#endif /* SOC_J7200_DEVGRPS_H */
