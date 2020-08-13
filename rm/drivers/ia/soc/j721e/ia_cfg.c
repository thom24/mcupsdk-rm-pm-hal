/*
 * Interrupt Aggregator
 *
 * Interrupt aggregator driver instance data definition
 *
 * Data version: 200529_213657
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/short_types.h>
#include <types/array_size.h>
#include <types/sbool.h>
#include <soc/rm_mmr.h>
#include <devices.h>
#include <soc/j721e/resasg_types.h>
#include <soc/j721e/soc_devgrps.h>

#include "../../include/ia_inst.h"
#include "ia_cfg.h"

static const struct rm_mmr mmr_NAVSS0_MODSS_INTAGGR_0_MODSS_INTA0_CFG_IMAP = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x30900000U,
};

static const struct rm_mmr mmr_NAVSS0_MODSS_INTAGGR_0_MODSS_INTA0_CFG_INTR = {
	.fwl_id		= 4644U,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 63U,
	.base		= 0x33c00000U,
};

static u8 vint_usage_count_NAVSS0_MODSS_INTAGGR_0[64U];

static const struct rm_mmr mmr_NAVSS0_MODSS_INTAGGR_1_MODSS_INTA1_CFG_IMAP = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x30908000U,
};

static const struct rm_mmr mmr_NAVSS0_MODSS_INTAGGR_1_MODSS_INTA1_CFG_INTR = {
	.fwl_id		= 4652U,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 63U,
	.base		= 0x33c40000U,
};

static u8 vint_usage_count_NAVSS0_MODSS_INTAGGR_1[64U];

static const struct rm_mmr mmr_NAVSS0_UDMASS_INTAGGR_0_UDMASS_INTA0_IMAP = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x30940000U,
};

static const struct rm_mmr mmr_NAVSS0_UDMASS_INTAGGR_0_UDMASS_INTA0_CFG_INTR = {
	.fwl_id		= 4320U,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 255U,
	.base		= 0x33d00000U,
};

static const struct rm_mmr mmr_NAVSS0_UDMASS_INTAGGR_0_UDMASS_INTA0_CFG_GCNTRTI = {
	.fwl_id		= 4320U,
	.fwl_ch_start	= 256U,
	.fwl_ch_end	= 767U,
	.base		= 0x33800000U,
};

static u8 vint_usage_count_NAVSS0_UDMASS_INTAGGR_0[256U];

static const struct rm_mmr mmr_MCU_NAVSS0_UDMASS_INTA_0_UDMASS_INTA0_IMAP = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x28560000U,
};

static const struct rm_mmr mmr_MCU_NAVSS0_UDMASS_INTA_0_UDMASS_INTA0_INTR = {
	.fwl_id		= 6208U,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 255U,
	.base		= 0x2a700000U,
};

static const struct rm_mmr mmr_MCU_NAVSS0_UDMASS_INTA_0_UDMASS_INTA0_GCNTRTI = {
	.fwl_id		= 6208U,
	.fwl_ch_start	= 256U,
	.fwl_ch_end	= 511U,
	.base		= 0x2a600000U,
};

static u8 vint_usage_count_MCU_NAVSS0_UDMASS_INTA_0[256U];

struct ia_instance ia_inst[IA_INST_COUNT] = {
	{
		.id = J721E_DEV_NAVSS0_MODSS_INTAGGR_0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J721E_MAIN,
		.imap = &mmr_NAVSS0_MODSS_INTAGGR_0_MODSS_INTA0_CFG_IMAP,
		.intr = &mmr_NAVSS0_MODSS_INTAGGR_0_MODSS_INTA0_CFG_INTR,
		.gcntrti = NULL,
		.unmap = NULL,
		.sevt_offset = 20480U,
		.n_sevt = 1024U,
		.vint_utype = RESASG_UTYPE(J721E_DEV_NAVSS0_MODSS_INTAGGR_0, RESASG_SUBTYPE_IA_VINT),
		.n_vint = 64U,
		.vint_usage_count = &vint_usage_count_NAVSS0_MODSS_INTAGGR_0[0U],
		.v0_b0_evt = 0U,
		.unmapped_events = NULL,
		.n_unmapped_events = 0U,
	},
	{
		.id = J721E_DEV_NAVSS0_MODSS_INTAGGR_1,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J721E_MAIN,
		.imap = &mmr_NAVSS0_MODSS_INTAGGR_1_MODSS_INTA1_CFG_IMAP,
		.intr = &mmr_NAVSS0_MODSS_INTAGGR_1_MODSS_INTA1_CFG_INTR,
		.gcntrti = NULL,
		.unmap = NULL,
		.sevt_offset = 22528U,
		.n_sevt = 1024U,
		.vint_utype = RESASG_UTYPE(J721E_DEV_NAVSS0_MODSS_INTAGGR_1, RESASG_SUBTYPE_IA_VINT),
		.n_vint = 64U,
		.vint_usage_count = &vint_usage_count_NAVSS0_MODSS_INTAGGR_1[0U],
		.v0_b0_evt = 0U,
		.unmapped_events = NULL,
		.n_unmapped_events = 0U,
	},
	{
		.id = J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J721E_MAIN,
		.imap = &mmr_NAVSS0_UDMASS_INTAGGR_0_UDMASS_INTA0_IMAP,
		.intr = &mmr_NAVSS0_UDMASS_INTAGGR_0_UDMASS_INTA0_CFG_INTR,
		.gcntrti = &mmr_NAVSS0_UDMASS_INTAGGR_0_UDMASS_INTA0_CFG_GCNTRTI,
		.unmap = NULL,
		.sevt_offset = 0U,
		.n_sevt = 4608U,
		.vint_utype = RESASG_UTYPE(J721E_DEV_NAVSS0_UDMASS_INTAGGR_0, RESASG_SUBTYPE_IA_VINT),
		.n_vint = 256U,
		.vint_usage_count = &vint_usage_count_NAVSS0_UDMASS_INTAGGR_0[0U],
		.v0_b0_evt = 0U,
		.unmapped_events = NULL,
		.n_unmapped_events = 0U,
	},
	{
		.id = J721E_DEV_MCU_NAVSS0_UDMASS_INTA_0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J721E_MCU_WAKEUP,
		.imap = &mmr_MCU_NAVSS0_UDMASS_INTA_0_UDMASS_INTA0_IMAP,
		.intr = &mmr_MCU_NAVSS0_UDMASS_INTA_0_UDMASS_INTA0_INTR,
		.gcntrti = &mmr_MCU_NAVSS0_UDMASS_INTA_0_UDMASS_INTA0_GCNTRTI,
		.unmap = NULL,
		.sevt_offset = 16384U,
		.n_sevt = 1536U,
		.vint_utype = RESASG_UTYPE(J721E_DEV_MCU_NAVSS0_UDMASS_INTA_0, RESASG_SUBTYPE_IA_VINT),
		.n_vint = 256U,
		.vint_usage_count = &vint_usage_count_MCU_NAVSS0_UDMASS_INTA_0[0U],
		.v0_b0_evt = 0U,
		.unmapped_events = NULL,
		.n_unmapped_events = 0U,
	},
};
