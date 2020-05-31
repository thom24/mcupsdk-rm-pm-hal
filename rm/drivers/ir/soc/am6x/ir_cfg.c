/*
 * IRQ Interrupt Router
 *
 * IRQ Interrupt Router SoC data for AM6
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/short_types.h>
#include <types/array_size.h>
#include <types/sbool.h>
#include <soc/rm_mmr.h>
#include <devices.h>
#include <soc/am6x/resasg_types.h>
#include <soc/am6x/soc_devgrps.h>

#include "../../include/ir_inst.h"
#include "ir_cfg.h"

/* Start of MAIN2MCU_LVL_INTRTR0 instance definition */
static const struct rm_mmr mmr_MAIN2MCU_LVL_INTRTR0_CFG = {
	.fwl_id = RM_MMR_FWL_INVALID,
	.base	= 0xa10000,
};

static struct ir_used_mapping rom_usage_MAIN2MCU_LVL_INTRTR0_CFG[2U] = {
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

/* Start of MAIN2MCU_PLS_INTRTR0 instance definition */
static const struct rm_mmr mmr_MAIN2MCU_PLS_INTRTR0_CFG = {
	.fwl_id = RM_MMR_FWL_INVALID,
	.base	= 0xa20000,
};

/* Start of main_gpiomux_introuter_main_gpiomux_introuter_main_0 instance
 *definition */
static const struct rm_mmr
	mmr_main_gpiomux_introuter_main_gpiomux_introuter_main_0_intr_router_cfg
	= {
	.fwl_id = RM_MMR_FWL_INVALID,
	.base	= 0xa00000,
	};

/* Start of WKUP_GPIOMUX_INTRTR0 instance definition */
static const struct rm_mmr mmr_WKUP_GPIOMUX_INTRTR0_CFG = {
	.fwl_id = RM_MMR_FWL_INVALID,
	.base	= 0x42200000,
};

/* Start of cmp_event_introuter_cmp_event_introuter_main_0 instance definition
 **/
static const struct rm_mmr
	mmr_cmp_event_introuter_cmp_event_introuter_main_0_intr_router_cfg = {
	.fwl_id = RM_MMR_FWL_INVALID,
	.base	= 0xa30000,
};

/* Start of TIMESYNC_INTRTR0 instance definition */
static const struct rm_mmr mmr_TIMESYNC_INTRTR0_intr_router_cfg = {
	.fwl_id = RM_MMR_FWL_INVALID,
	.base	= 0xa40000,
};

/* Start of NAVSS0_INTR_ROUTER_0 instance definition */
static const struct rm_mmr mmr_NAVSS0_INTR_ROUTER_0_intr_router_cfg = {
	.fwl_id = RM_MMR_FWL_INVALID,
	.base	= 0x310e0000,
};

/* Start of MCU_NAVSS0_INTR_ROUTER_0 instance definition */
static const struct rm_mmr mmr_MCU_NAVSS0_INTR_ROUTER_0_intr_router_cfg = {
	.fwl_id = RM_MMR_FWL_INVALID,
	.base	= 0x28540000,
};

static struct ir_used_mapping rom_usage_MCU_NAVSS0_INTR_ROUTER_0_intr_router_cfg[1U] = {
	{
		.inp_start = 1U,
		.outp_start = 0U,
		.length = 2U,
		.cleared = SFALSE,
	},
};


struct ir_instance ir_inst[IR_INST_COUNT] = {
	{
		/* MAIN2MCU_LVL_INTRTR0 */
		.id = AM6_DEV_MAIN2MCU_LVL_INTRTR0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM6_MAIN,
		.int_enable = SFALSE,
		.cfg = &mmr_MAIN2MCU_LVL_INTRTR0_CFG,
		.n_inp = 192u,
		.n_outp = 64u,
		.inp0_mapping = 0u,
		.outp_utype = RESASG_UTYPE(AM6_DEV_MAIN2MCU_LVL_INTRTR0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = &rom_usage_MAIN2MCU_LVL_INTRTR0_CFG[0U],
		.n_rom_usage = 2U,
	},
	{
		/* MAIN2MCU_PLS_INTRTR0 */
		.id = AM6_DEV_MAIN2MCU_PLS_INTRTR0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM6_MAIN,
		.int_enable = SFALSE,
		.cfg = &mmr_MAIN2MCU_PLS_INTRTR0_CFG,
		.n_inp = 32U,
		.n_outp = 48u,
		.inp0_mapping = 0u,
		.outp_utype = RESASG_UTYPE(AM6_DEV_MAIN2MCU_PLS_INTRTR0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0u,
	},
	{
		/* main_gpiomux_introuter_main_gpiomux_introuter_main_0 */
		.id = AM6_DEV_GPIOMUX_INTRTR0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM6_MAIN,
		.int_enable = SFALSE,
		.cfg = &mmr_main_gpiomux_introuter_main_gpiomux_introuter_main_0_intr_router_cfg,
		.n_inp = 208u,
		.n_outp = 32u,
		.inp0_mapping = 0u,
		.outp_utype = RESASG_UTYPE(AM6_DEV_GPIOMUX_INTRTR0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0u,
	},
	{
		/* WKUP_GPIOMUX_INTRTR0 */
		.id = AM6_DEV_WKUP_GPIOMUX_INTRTR0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM6_MCU_WAKEUP,
		.int_enable = SFALSE,
		.cfg = &mmr_WKUP_GPIOMUX_INTRTR0_CFG,
		.n_inp = 64u,
		.n_outp = 16u,
		.inp0_mapping = 0u,
		.outp_utype = RESASG_UTYPE(AM6_DEV_WKUP_GPIOMUX_INTRTR0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0u,
	},
	{
		/* cmp_event_introuter_cmp_event_introuter_main_0 */
		.id = AM6_DEV_CMPEVENT_INTRTR0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM6_MAIN,
		.int_enable = SFALSE,
		.cfg = &mmr_cmp_event_introuter_cmp_event_introuter_main_0_intr_router_cfg,
		.n_inp = 128u,
		.n_outp = 32u,
		.inp0_mapping = 0u,
		.outp_utype = RESASG_UTYPE(AM6_DEV_CMPEVENT_INTRTR0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0u,
	},
	{
		/* TIMESYNC_INTRTR0 */
		.id = AM6_DEV_TIMESYNC_INTRTR0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM6_MAIN,
		.int_enable = SFALSE,
		.cfg = &mmr_TIMESYNC_INTRTR0_intr_router_cfg,
		.n_inp = 48u,
		.n_outp = 40u,
		.inp0_mapping = 0u,
		.outp_utype = RESASG_UTYPE(AM6_DEV_TIMESYNC_INTRTR0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0u,
	},
	{
		/* NAVSS0_INTR_ROUTER */
		.id = AM6_DEV_NAVSS0_INTR_ROUTER_0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM6_MAIN,
		.int_enable = SFALSE,
		.cfg = &mmr_NAVSS0_INTR_ROUTER_0_intr_router_cfg,
		.n_inp = 440u,
		.n_outp = 152u,
		.inp0_mapping = 0u,
		.outp_utype = RESASG_UTYPE(AM6_DEV_NAVSS0_INTR_ROUTER_0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = NULL,
		.n_rom_usage = 0u,
	},
	{
		/* MCU_NAVSS0_INTR_ROUTER */
		.id = AM6_DEV_MCU_NAVSS0_INTR_ROUTER_0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM6_MCU_WAKEUP,
		.int_enable = SFALSE,
		.cfg = &mmr_MCU_NAVSS0_INTR_ROUTER_0_intr_router_cfg,
		.n_inp = 261u,
		.n_outp = 64u,
		.inp0_mapping = 0u,
		.outp_utype = RESASG_UTYPE(AM6_DEV_MCU_NAVSS0_INTR_ROUTER_0, RESASG_SUBTYPE_IR_OUTPUT),
		.rom_usage = &rom_usage_MCU_NAVSS0_INTR_ROUTER_0_intr_router_cfg[0U],
		.n_rom_usage = 1u,
	},
};
