/*
 * System Firmware Source File
 *
 * Software defined Device groups (devgrps) for AM6 device.
 *
 * Data version: 190425_000000
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef SOC_AM6_DEVGRPS_H
#define SOC_AM6_DEVGRPS_H

#include <types/devgrps.h>

/**
 * Set of MCU domain peripherals to initialize at boot and use during runtime.
 * Utilize this device group of MCU/Wakeup domain peripherals to achieve a
 * faster boot sequence
 */
#define SOC_DEVGRP_AM6_MCU_WAKEUP DEVGRP_00

/**
 * Set of Main domain peripherals to initialize at boot and use during
 * runtime.  Utilize this device group of non-critical peripherals for
 * advanced use cases.
 */
#define SOC_DEVGRP_AM6_MAIN DEVGRP_01

/**
 * Set of peripherals to initialize for System Firmware internal usage
 */
#define SOC_DEVGRP_AM6_DMSC_INTERNAL DEVGRP_DMSC


#endif /* SOC_AM6_DEVGRPS_H */
