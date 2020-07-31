/*
 * PSI-L
 *
 * PSI-L SoC data for AM6
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <config.h>
#include <types/short_types.h>
#include <types/sbool.h>
#include <types/array_size.h>
#include <soc/rm_mmr.h>
#include <devices.h>
#include <devices_internal.h>
#include <soc/am6x/soc_devgrps.h>

#include "../../include/psil_inst.h"
#include <psil_cfg.h>

/* Start of NAVSS0 PSI-L instance definition */
static const struct rm_mmr mmr_NAVSS0_PSIL_CFG_PROXY = {
	.fwl_id = RM_MMR_FWL_INVALID,
	.base	= 0x31F78000u,
};

/* Start of MCU_NAVSS0 PSI-L instance definition */
static const struct rm_mmr mmr_MCU_NAVSS0_PSIL_CFG_PROXY = {
	.fwl_id = RM_MMR_FWL_INVALID,
	.base	= 0x2A268000u,
};

/* Thread type configuration common amongst all instances */
static const struct psil_thread_type src_thread_types_AM6[] = {
	{
		.start = 0x1000u,
		.end = 0x1077u,
		.dev_id = AM6_DEV_NAVSS0_UDMAP0,
	},
	{
		.start = 0x4000u,
		.end = 0x4003u,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4100u,
		.end = 0x4113u,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4200u,
		.end = 0x4213u,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4300u,
		.end = 0x4313u,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4400u,
		.end = 0x443Fu,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4500u,
		.end = 0x453Fu,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4600u,
		.end = 0x463Fu,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4700u,
		.end = 0x4707u,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4800u,
		.end = 0x483Fu,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x6000u,
		.end = 0x602Fu,
		.dev_id = AM6_DEV_MCU_NAVSS0_UDMAP0,
	},
	{
		.start = 0x7000u,
		.end = 0x7000u,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x7100u,
		.end = 0x713Fu,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x7200u,
		.end = 0x723Fu,
		.dev_id = SOC_DEV_NONE,
	},
};
static const struct psil_thread_type dst_thread_types_AM6[] = {
	{
		.start = 0x9000u,
		.end = 0x9095u,
		.dev_id = AM6_DEV_NAVSS0_UDMAP0,
	},
	{
		.start = 0xC000u,
		.end = 0xC001u,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC100u,
		.end = 0xC10Fu,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC200u,
		.end = 0xC20Fu,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC300u,
		.end = 0xC30Fu,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC400u,
		.end = 0xC43Fu,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC500u,
		.end = 0xC53Fu,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC600u,
		.end = 0xC63Fu,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC800u,
		.end = 0xC83Fu,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xE000u,
		.end = 0xE02Fu,
		.dev_id = AM6_DEV_MCU_NAVSS0_UDMAP0,
	},
	{
		.start = 0xF000u,
		.end = 0xF007u,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xF100u,
		.end = 0xF13Fu,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xF200u,
		.end = 0xF23Fu,
		.dev_id = SOC_DEV_NONE,
	},
};


struct psil_instance psil_inst[] = {
	{
		/* NAVSS0 PSI-L */
		.id = AM6_DEV_NAVSS0,
		.devgrp = SOC_DEVGRP_AM6_MAIN,
		.proxy = &mmr_NAVSS0_PSIL_CFG_PROXY,
		.src_thread_types = &src_thread_types_AM6[0],
		.dst_thread_types = &dst_thread_types_AM6[0],
		.n_src_thread_type = ARRAY_SIZE(src_thread_types_AM6),
		.n_dst_thread_type = ARRAY_SIZE(dst_thread_types_AM6),
	},
	{
		/* MCU_NAVSS0 PSI-L */
		.id = AM6_DEV_MCU_NAVSS0,
		.devgrp = SOC_DEVGRP_AM6_MCU_WAKEUP,
		.proxy = &mmr_MCU_NAVSS0_PSIL_CFG_PROXY,
		.src_thread_types = &src_thread_types_AM6[0],
		.dst_thread_types = &dst_thread_types_AM6[0],
		.n_src_thread_type = ARRAY_SIZE(src_thread_types_AM6),
		.n_dst_thread_type = ARRAY_SIZE(dst_thread_types_AM6),
	},
};

const u32 psil_inst_count = ARRAY_SIZE(psil_inst);

/*
 * Threads used by ROM which must be disabled prior to reuse
 */
#if !defined(CONFIG_DEVICE_TYPE_HS)
struct psil_used_thread psil_rom_usage[PSIL_ROM_USAGE_CNT] = {
	{
		.thread = 0x4001U,
		.disabled = SFALSE,
	},
	{
		.thread = 0x6000U,
		.disabled = SFALSE,
	},
	{
		.thread = 0x7000U,
		.disabled = SFALSE,
	},
	{
		.thread = 0xe000U,
		.disabled = SFALSE,
	},
	{
		.thread = 0xf000U,
		.disabled = SFALSE,
	},
	/*
	 * Threads used on devices other than HS device
	 */
	{
		.thread = 0x4000U,
		.disabled = SFALSE,
	},
	{
		.thread = 0xc000U,
		.disabled = SFALSE,
	},
};
#else
struct psil_used_thread psil_rom_usage[PSIL_ROM_USAGE_CNT] = {
	{
		.thread = 0x4001U,
		.disabled = SFALSE,
	},
	{
		.thread = 0x6000U,
		.disabled = SFALSE,
	},
	{
		.thread = 0x7000U,
		.disabled = SFALSE,
	},
	{
		.thread = 0xe000U,
		.disabled = SFALSE,
	},
	{
		.thread = 0xf000U,
		.disabled = SFALSE,
	},
};
#endif
