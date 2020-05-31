/*
 * PSI-L
 *
 * PSI-L driver instance definition
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef PSIL_INST_H
#define PSIL_INST_H

#include <types/short_types.h>
#include <types/sbool.h>
#include <types/devgrps.h>
#include <soc/rm_mmr.h>
#include <psil_cfg.h>

/**
 * \brief
 * Describes the PSI-L threads used by ROM and if they've been disabled
 *
 * \param thread
 * Thread used by ROM
 *
 * \param disabled
 * Boolean storing whether or not the thread has been disabled
 */
struct psil_used_thread {
	u16	thread;
	sbool	disabled;
};

/**
 * \brief
 * PSI-L thread type information
 *
 * \param start
 * Thread type start index
 *
 * \param end
 * Thread type end index
 *
 * \param dev_id
 * SoC device ID of subsystem needing additional programming when thread
 * type is paired.  Currently only applies to UDMAP.
 */
struct psil_thread_type {
	const u32	start;
	const u32	end;
	const u16	dev_id;
};

/**
 * \brief
 * PSI-L instance containing all data required to manage all SoC PSI-L threads
 * via a Navigator Subsystem's PSI-L proxy
 *
 * \param id
 * Device ID of NavSS containing the PSI-L proxy
 *
 * \param devgrp
 * Device group to which instance belongs
 *
 * \param proxy
 * NavSS subsystem's PSI-L proxy MMR region
 *
 * \param src_thread_types
 * Pointer to array of PSI-L source thread types
 *
 * \param dst_thread_types
 * Pointer to array of PSI-L destination thread types
 *
 * \param n_src_thread_type
 * Number of PSI-L source thread types
 *
 * \param n_dst_thread_type
 * Number of PSI-L destination thread types
 *
 * \param dru_ch0_dst_thread_offset
 * Thread offset for DRU channel zero.  Needed for UDMA UTC configuration.
 */
struct psil_instance {
	const u16				id;
	const devgrp_t				devgrp;
	const struct rm_mmr *const		proxy;
	const struct psil_thread_type *const	src_thread_types;
	const struct psil_thread_type *const	dst_thread_types;
	const u8				n_src_thread_type;
	const u8				n_dst_thread_type;
	const u16				dru_ch0_dst_thread_offset;
};

/**
 * Extern for PSI-L subsystem instances array
 */
extern struct psil_instance psil_inst[];

/**
 * Extern for number of PSI-L subsystem instances
 */
extern const u32 psil_inst_count;

/**
 * Extern for PSI-L ROM usage threads array
 */
extern struct psil_used_thread psil_rom_usage[PSIL_ROM_USAGE_CNT];


#endif /* PSIL_INST_H */
