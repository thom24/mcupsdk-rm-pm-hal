/*
 * Interrupt Router
 *
 * Interrupt router driver instance data definition
 *
 * Data version: 200505_104840
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/short_types.h>
#include <types/array_size.h>
#include <types/sbool.h>
#include <soc/rm_mmr.h>
#include <devices.h>
#include <soc/am64x/resasg_types.h>
#include <soc/am64x/soc_devgrps.h>

#include "../../include/ir_inst.h"
#include "ir_cfg.h"

static const struct rm_mmr mmr_CMP_EVENT_INTROUTER0_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0xa30000U,
};

static const struct rm_mmr mmr_MAIN_GPIOMUX_INTROUTER0_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0xa00000U,
};

static const struct rm_mmr mmr_MCU_MCU_GPIOMUX_INTROUTER0_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x4210000U,
};

static const struct rm_mmr mmr_TIMESYNC_EVENT_INTROUTER0_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0xa40000U,
};

struct ir_instance ir_inst[IR_INST_COUNT] = {
	{
		.id = AM64X_DEV_CMP_EVENT_INTROUTER0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM64X_MAIN,
		.int_enable = STRUE,
		.cfg = &mmr_CMP_EVENT_INTROUTER0_CFG,
		.n_inp = 87U,
		.n_outp = 43U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(AM64X_DEV_CMP_EVENT_INTROUTER0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = AM64X_DEV_MAIN_GPIOMUX_INTROUTER0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM64X_MAIN,
		.int_enable = STRUE,
		.cfg = &mmr_MAIN_GPIOMUX_INTROUTER0_CFG,
		.n_inp = 200U,
		.n_outp = 54U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(AM64X_DEV_MAIN_GPIOMUX_INTROUTER0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = AM64X_DEV_MCU_MCU_GPIOMUX_INTROUTER0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM64X_MCU_WAKEUP,
		.int_enable = STRUE,
		.cfg = &mmr_MCU_MCU_GPIOMUX_INTROUTER0_CFG,
		.n_inp = 32U,
		.n_outp = 12U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(AM64X_DEV_MCU_MCU_GPIOMUX_INTROUTER0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = AM64X_DEV_TIMESYNC_EVENT_INTROUTER0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM64X_MAIN,
		.int_enable = STRUE,
		.cfg = &mmr_TIMESYNC_EVENT_INTROUTER0_CFG,
		.n_inp = 43U,
		.n_outp = 41U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(AM64X_DEV_TIMESYNC_EVENT_INTROUTER0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
};
