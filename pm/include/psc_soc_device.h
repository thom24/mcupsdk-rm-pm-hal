/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef PSC_SOC_DEVICE_H
#define PSC_SOC_DEVICE_H

#include <types/short_types.h>
#include <pm_types.h>

/**
 * \brief SoC specific const device data.
 *
 * This stores the SoC specific const data for each device.
 */
struct soc_device_data {
	u8		psc_idx : 3;

	/** The PSC powerdomain that this device is part of. */
	u8		pd : 5;

	/** The PSC module that this device is part of. */
	lpsc_idx_t	mod;
};

#endif
