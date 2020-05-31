/*
 * Interrupt Router
 *
 * Interrupt router driver instance data definition
 *
 * Data version: 000000_000000
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/short_types.h>
#include <types/array_size.h>
#include <types/sbool.h>
#include <soc/rm_mmr.h>
#include <devices.h>
#include <soc/am65x_sr2/resasg_types.h>
#include <soc/am65x_sr2/soc_devgrps.h>

#include "../../include/ir_inst.h"
#include "ir_cfg.h"

static const struct rm_mmr mmr_CMPEVENT_INTRTR0_INTR_ROUTER_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0xa30000U,
};

static const struct rm_mmr mmr_MAIN2MCU_LVL_INTRTR0_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0xa10000U,
};

static struct ir_used_mapping rom_usage_MAIN2MCU_LVL_INTRTR0[2U] = {
	{
		.inp_start = 64U,
		.outp_start = 0U,
		.length = 32U,
		.cleared = SFALSE,
	},
	{
		.inp_start = 28U,
		.outp_start = 32U,
		.length = 2U,
		.cleared = SFALSE,
	},
};

static const struct rm_mmr mmr_MAIN2MCU_PLS_INTRTR0_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0xa20000U,
};

static const struct rm_mmr mmr_GPIOMUX_INTRTR0_INTR_ROUTER_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0xa00000U,
};

static const struct rm_mmr mmr_navss0_intr_router_0_INTR0_INTR_ROUTER_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x310e0000U,
};

static const struct rm_mmr mmr_mcu_navss0_intr_router_0_INTR0_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x28540000U,
};

static struct ir_used_mapping rom_usage_mcu_navss0_intr_router_0[1U] = {
	{
		.inp_start = 1U,
		.outp_start = 0U,
		.length = 2U,
		.cleared = SFALSE,
	},
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

struct ir_instance ir_inst[IR_INST_COUNT] = {
	{
		.id = AM6_DEV_CMPEVENT_INTRTR0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM6_MAIN,
		.int_enable = SFALSE,
		.cfg = &mmr_CMPEVENT_INTRTR0_INTR_ROUTER_CFG,
		.n_inp = 128U,
		.n_outp = 32U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(AM6_DEV_CMPEVENT_INTRTR0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = AM6_DEV_MAIN2MCU_LVL_INTRTR0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM6_MAIN,
		.int_enable = SFALSE,
		.cfg = &mmr_MAIN2MCU_LVL_INTRTR0_CFG,
		.n_inp = 192U,
		.n_outp = 64U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(AM6_DEV_MAIN2MCU_LVL_INTRTR0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = &rom_usage_MAIN2MCU_LVL_INTRTR0[0U],
		.n_rom_usage = ARRAY_SIZE(rom_usage_MAIN2MCU_LVL_INTRTR0),
	},
	{
		.id = AM6_DEV_MAIN2MCU_PLS_INTRTR0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM6_MAIN,
		.int_enable = SFALSE,
		.cfg = &mmr_MAIN2MCU_PLS_INTRTR0_CFG,
		.n_inp = 32U,
		.n_outp = 48U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(AM6_DEV_MAIN2MCU_PLS_INTRTR0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = AM6_DEV_GPIOMUX_INTRTR0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM6_MAIN,
		.int_enable = SFALSE,
		.cfg = &mmr_GPIOMUX_INTRTR0_INTR_ROUTER_CFG,
		.n_inp = 208U,
		.n_outp = 32U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(AM6_DEV_GPIOMUX_INTRTR0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = AM6_DEV_NAVSS0_INTR_ROUTER_0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM6_MAIN,
		.int_enable = STRUE,
		.cfg = &mmr_navss0_intr_router_0_INTR0_INTR_ROUTER_CFG,
		.n_inp = 440U,
		.n_outp = 152U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(AM6_DEV_NAVSS0_INTR_ROUTER_0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = AM6_DEV_MCU_NAVSS0_INTR_ROUTER_0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM6_MCU_WAKEUP,
		.int_enable = STRUE,
		.cfg = &mmr_mcu_navss0_intr_router_0_INTR0_CFG,
		.n_inp = 261U,
		.n_outp = 64U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(AM6_DEV_MCU_NAVSS0_INTR_ROUTER_0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = &rom_usage_mcu_navss0_intr_router_0[0U],
		.n_rom_usage = ARRAY_SIZE(rom_usage_mcu_navss0_intr_router_0),
	},
	{
		.id = AM6_DEV_TIMESYNC_INTRTR0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM6_MAIN,
		.int_enable = SFALSE,
		.cfg = &mmr_TIMESYNC_INTRTR0_INTR_ROUTER_CFG,
		.n_inp = 48U,
		.n_outp = 40U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(AM6_DEV_TIMESYNC_INTRTR0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = AM6_DEV_WKUP_GPIOMUX_INTRTR0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM6_MCU_WAKEUP,
		.int_enable = SFALSE,
		.cfg = &mmr_WKUP_GPIOMUX_INTRTR0_CFG,
		.n_inp = 64U,
		.n_outp = 16U,
		.inp0_mapping = 0U,
		.outp_utype = RESASG_UTYPE(AM6_DEV_WKUP_GPIOMUX_INTRTR0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
};
