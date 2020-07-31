/*
 * Interrupt Router
 *
 * Interrupt router driver instance data definition
 *
 * Data version: 200730_091422
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/short_types.h>
#include <types/array_size.h>
#include <types/sbool.h>
#include <soc/rm_mmr.h>
#include <devices.h>
#include <soc/j7200/resasg_types.h>
#include <soc/j7200/soc_devgrps.h>

#include "../../include/ir_inst.h"
#include "ir_cfg.h"

static const struct rm_mmr mmr_MAIN2MCU_LVL_INTRTR0_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0xa10000U,
};

static struct ir_used_mapping rom_usage_MAIN2MCU_LVL_INTRTR0[2U] = {
	{
		.inp_start = 28U,
		.outp_start = 32U,
		.length = 2U,
		.cleared = SFALSE,
	},
	{
		.inp_start = 128U,
		.outp_start = 34U,
		.length = 16U,
		.cleared = SFALSE,
	},
};

static const struct rm_mmr mmr_MAIN2MCU_PLS_INTRTR0_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0xa20000U,
};

static const struct rm_mmr mmr_TIMESYNC_INTRTR0_INTR_ROUTER_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0xa40000U,
};

static const struct rm_mmr mmr_WKUP_GPIOMUX_INTRTR0_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x42200000U,
};

static const struct rm_mmr mmr_GPIOMUX_INTRTR0_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0xa00000U,
};

static const struct rm_mmr mmr_CMPEVENT_INTRTR0_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0xa30000U,
};

static const struct rm_mmr mmr_NAVSS0_INTR_ROUTER_0_INTR0_INTR_ROUTER_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x310e0000U,
};

static const struct rm_mmr mmr_MCU_NAVSS0_INTR_0_INTR0_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x28540000U,
};

static struct ir_used_mapping rom_usage_MCU_NAVSS0_INTR_0[1U] = {
	{
		.inp_start = 1U,
		.outp_start = 0U,
		.length = 2U,
		.cleared = SFALSE,
	},
};

struct ir_instance ir_inst[IR_INST_COUNT] = {
	{
		.id = J7200_DEV_MAIN2MCU_LVL_INTRTR0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J7200_MAIN,
		.int_enable = STRUE,
		.cfg = &mmr_MAIN2MCU_LVL_INTRTR0_CFG,
		.n_inp = 320U,
		.n_outp = 64U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(J7200_DEV_MAIN2MCU_LVL_INTRTR0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = &rom_usage_MAIN2MCU_LVL_INTRTR0[0U],
		.n_rom_usage = ARRAY_SIZE(rom_usage_MAIN2MCU_LVL_INTRTR0),
	},
	{
		.id = J7200_DEV_MAIN2MCU_PLS_INTRTR0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J7200_MAIN,
		.int_enable = STRUE,
		.cfg = &mmr_MAIN2MCU_PLS_INTRTR0_CFG,
		.n_inp = 112U,
		.n_outp = 48U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(J7200_DEV_MAIN2MCU_PLS_INTRTR0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = J7200_DEV_TIMESYNC_INTRTR0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J7200_MAIN,
		.int_enable = STRUE,
		.cfg = &mmr_TIMESYNC_INTRTR0_INTR_ROUTER_CFG,
		.n_inp = 56U,
		.n_outp = 48U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(J7200_DEV_TIMESYNC_INTRTR0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = J7200_DEV_WKUP_GPIOMUX_INTRTR0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J7200_MCU_WAKEUP,
		.int_enable = STRUE,
		.cfg = &mmr_WKUP_GPIOMUX_INTRTR0_CFG,
		.n_inp = 120U,
		.n_outp = 32U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(J7200_DEV_WKUP_GPIOMUX_INTRTR0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = J7200_DEV_GPIOMUX_INTRTR0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J7200_MAIN,
		.int_enable = STRUE,
		.cfg = &mmr_GPIOMUX_INTRTR0_CFG,
		.n_inp = 180U,
		.n_outp = 64U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(J7200_DEV_GPIOMUX_INTRTR0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = J7200_DEV_CMPEVENT_INTRTR0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J7200_MAIN,
		.int_enable = STRUE,
		.cfg = &mmr_CMPEVENT_INTRTR0_CFG,
		.n_inp = 16U,
		.n_outp = 16U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(J7200_DEV_CMPEVENT_INTRTR0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J7200_MAIN,
		.int_enable = STRUE,
		.cfg = &mmr_NAVSS0_INTR_ROUTER_0_INTR0_INTR_ROUTER_CFG,
		.n_inp = 442U,
		.n_outp = 512U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(J7200_DEV_NAVSS0_INTR_ROUTER_0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = J7200_DEV_MCU_NAVSS0_INTR_0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J7200_MCU_WAKEUP,
		.int_enable = STRUE,
		.cfg = &mmr_MCU_NAVSS0_INTR_0_INTR0_CFG,
		.n_inp = 261U,
		.n_outp = 64U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(J7200_DEV_MCU_NAVSS0_INTR_0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = &rom_usage_MCU_NAVSS0_INTR_0[0U],
		.n_rom_usage = ARRAY_SIZE(rom_usage_MCU_NAVSS0_INTR_0),
	},
};
