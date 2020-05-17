/*
 * DMSC firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef SOC_DEVICE_H
#define SOC_DEVICE_H

#include <psc_soc_device.h>

/**
 * This index defines the device ID assigned to a given piece of IP. Device
 * IDs are assigned statically and are exported as part of the ABI.
 *
 * This value has a 1-to-1 correspondence with the device field in the TISCI
 * PM messages.
 */
typedef u8 dev_idx_t;

#endif
