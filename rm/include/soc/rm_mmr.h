/*
 * DMSC RM Driver MMR Definition
 *
 * Resource Manager internal driver's MMR structure definition
 *
 * Copyright (C) 2017-2019 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef RM_MMR_H
#define RM_MMR_H

#include <types/short_types.h>
#include <types/address_types.h>

/**
 * Used to define an MMR as not having a channelized firewall.
 */
#define RM_MMR_FWL_INVALID 0xFFFFu

/**
 * \struct rm_mmr
 *
 * \brief MMR info for SoC device
 *
 * MMR info for a device within the SoC.
 *
 * \param base
 * Base address of the MMR region
 *
 * \param fwl_id
 * ID of channelized firewall which controls access to the MMR region.  Set to
 * @ref RM_MMR_FWL_INVALID if a channelized firewall does not protect the MMR
 * block.
 *
 * \param fwl_ch_start
 * Starting offset of channelized firewall channels within the firewall group
 *
 * \param fwl_ch_end
 * Ending offset of channelized firewall channels within the firewall group
 */
struct rm_mmr {
	soc_phys_addr_t base;
	u16		fwl_id;
	u16		fwl_ch_start;
	u16		fwl_ch_end;
};

#endif /* RM_MMR_H */
