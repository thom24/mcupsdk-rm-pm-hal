/*
 * System Firmware
 *
 * Deinfitions for various sysfw devgrps
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef SYSFW_DEVGRPS_H
#define SYSFW_DEVGRPS_H

#include <types/errno.h>
#include <types/short_types.h>

/**
 * \brief Defines the sysfw DEVGRP type. This is meant to be used in code
 * or data structures that require distinction of devgrps.
 */
typedef u8 devgrp_t;

/* External definitions */

/**
 * SoC SYSFW devgrp any: NOT TO BE used for SoC data.
 * This implies that specific sequenced devgrp is NOT used
 */
#define DEVGRP_ALL              (0x00U)

/** SoC defined SYSFW devgrp 00 */
#define DEVGRP_00               ((0x01U) << 0U)
/** SoC defined SYSFW devgrp 01 */
#define DEVGRP_01               ((0x01U) << 1U)
/** SoC defined SYSFW devgrp 02 */
#define DEVGRP_02               ((0x01U) << 2U)
/** SoC defined SYSFW devgrp 03 */
#define DEVGRP_03               ((0x01U) << 3U)
/** SoC defined SYSFW devgrp 04 */
#define DEVGRP_04               ((0x01U) << 4U)
/** SoC defined SYSFW devgrp 05 */
#define DEVGRP_05               ((0x01U) << 5U)
/** SoC defined SYSFW devgrp 06 */
#define DEVGRP_06               ((0x01U) << 6U)

/** SYSFW internal usage ONLY */

/** Module belonging solely to DMSC operations */
#define DEVGRP_DMSC             ((0x01U) << 7U)
/** Match everything - STRICTLY INTERNAL USAGE ONLY */
#define DEVGRP_DMSC_ALL         (0xFFU)

/**
 * Maximum number of devgrps that are supported by SYSFW.
 * Derived from the above definitions
 */
#define MAX_NUM_DEVGRPS (8U)

/**
 * \brief respond if the requested module devgrp is valid as requested devgrp
 *
 * \param module_devgrp  Domain defined for the module (to verify)
 * \param requested_devgrp Requested devgrp to check against
 *
 * \return SUCCESS if:
 *  - requested_devgrp is DEVGRP_DMSC_ALL
 *  - requested_devgrp is DEVGRP_ALL and module_devgrp is not DEVGRP_DMSC
 *  - module_devgrp matches requested devgrp.
 *  Else return -EINVAL
 */
static inline s32 is_devgrp(devgrp_t module_devgrp, devgrp_t requested_devgrp)
{
	s32 ret = -EINVAL;

	if (requested_devgrp == DEVGRP_DMSC_ALL) {
		ret = SUCCESS;
	}
	if ((requested_devgrp == DEVGRP_ALL) && (module_devgrp != DEVGRP_DMSC)) {
		ret = SUCCESS;
	}
	if ((requested_devgrp & module_devgrp) != 0U) {
		ret = SUCCESS;
	}

	return ret;
}

#endif /* SYSFW_DEVGRPS_H */
