/*
 * Interrupt Router
 *
 * Interrupt router driver instance definition
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef IR_INST_H
#define IR_INST_H

#include <types/short_types.h>
#include <types/sbool.h>
#include <types/devgrps.h>
#include <soc/rm_mmr.h>
#include <ir_cfg.h>

/**
 * \brief
 * Describes a range of IR input to output mappings used by ROM and if they've
 * been cleared back to hardware reset values
 *
 * \param inp_start
 * Start of IR input range
 *
 * \param outp_start
 * Start of IR output range
 *
 * \param length
 * Length of the mapping range
 *
 * \param cleared
 * Boolean storing whether or not the mapped range has been cleared
 */
struct ir_used_mapping {
	u16	inp_start;
	u16	outp_start;
	u16	length;
	sbool	cleared;
};

/**
 * \brief
 * Interrupt router instance containing all data required to manage a SoC
 * interrupt router
 *
 * \param id
 * Device ID of IR
 *
 * \param initialized
 * Instance initialization flag
 *
 * \param devgrp
 * Device group to which instance belongs
 *
 * \param int_enable
 * Interrupt output enable bit support flag
 *
 * \param cfg
 * IR subsystem's config MMR region
 *
 * \param n_inp
 * Number of IR inputs
 *
 * \param n_outp
 * Number of IR outputs
 *
 * \param inp0_mapping
 * A standalone element is needed to track usage of IR input 0.  The CONTROL
 * registers are read to determine IR input and output usage.  The default
 * state for the output CONTROL registers is 0x0000 which translates to use of
 * IR input zero.  This field allows the IR driver to determine which IR
 * output input zero has been mapped to.
 *
 * \param outp_utype
 * Resource assignment type mapped to IR outputs
 *
 * \param rom_usage
 * IR inputs and outputs used by ROM during boot that need to be reset to defaults
 *
 * \param n_rom_usage
 * Number of entries in the rom_usage array
 */
struct ir_instance {
	const u16			id;
	sbool				initialized;
	const devgrp_t			devgrp;
	sbool				int_enable;
	const struct rm_mmr *const	cfg;
	const u16			n_inp;
	const u16			n_outp;
	u16				inp0_mapping;
	const u16			outp_utype;
	struct ir_used_mapping *const	rom_usage;
	const u8			n_rom_usage;
};

/**
 * Extern for IR subsystem instances array
 */
extern struct ir_instance ir_inst[IR_INST_COUNT];


#endif /* IR_INST_H */
