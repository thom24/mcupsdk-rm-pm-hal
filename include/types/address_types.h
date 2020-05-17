/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */


/**
 * \file address_types.h
 *
 * \brief Include file to indicate various valid address types for System
 *	  firmware. These types are expected to be used to refer to addressing
 *	  schemes expected to access various entities.
 */

#ifndef ADDRESS_TYPES_H
#define ADDRESS_TYPES_H

#include <types/short_types.h>

/**
 * \brief Physical address representing SoC Bus level physical address.
 *
 * This may be used for register programming (example buffer addresses) OR be
 * used to map back to addresses visible to System Control Processor (such as
 * DMSC). See \ref mapped_addr_t for a remapped address
 */
typedef u64 soc_phys_addr_t;

/** Get the lower u32 from a \ref soc_phys_addr_t address */
static inline u32 soc_phys_low_u32(soc_phys_addr_t w)
{
	return (((u32) (w)) >> 0) & 0xFFFFFFFFU;
}

/** Get the Higher u32 from a \ref soc_phys_addr_t address */
static inline u32 soc_phys_high_u32(soc_phys_addr_t w)
{
	return ((u32) ((w) >> 32)) & 0xFFFFFFFFU;
}

/** Create soc_phys_addr_t address from 32-bit lo and hi portions */
static inline soc_phys_addr_t soc_phys_create(u32 l, u32 h)
{
	return (soc_phys_addr_t) (((u64) ((u64) (h) << 32)) | (u64) l);
}

/**
 * \brief Represents the local addressing type for System Control processor.
 *
 * This is expected to be usable without any remapping and indicates that this
 * address map belongs to local address map of System Control Processor (such
 * as DMSC).
 */
typedef u32 local_phys_addr_t;

/**
 * \brief Represents the remapped address for System Control processor.
 *
 * This address is used to represent a remapped address which is visible over
 * a remapping scheme implemented by System control processor. Typically this
 * may be implemented via RAT - See \ref soc_phys_addr_t for further details.
 */
typedef u32 mapped_addr_t;

#endif
