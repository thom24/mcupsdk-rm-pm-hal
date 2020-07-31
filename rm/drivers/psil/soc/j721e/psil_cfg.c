/*
 * PSI-L
 *
 * PSI-L driver instance data definition
 *
 * Data version: 200529_213657
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
#include <soc/j721e/soc_devgrps.h>

#include "../../include/psil_inst.h"
#include "psil_cfg.h"

static const struct rm_mmr mmr_NAVSS0_PSILCFG_0_UDMASS_PSILCFG0_CFG_PROXY = {
	.fwl_id = RM_MMR_FWL_INVALID,
	.base	= 0x31F78000U,
};

static const struct rm_mmr mmr_MCU_NAVSS0_PSILCFG_0_UDMASS_PSILSS_CFG0_PROXY = {
	.fwl_id = RM_MMR_FWL_INVALID,
	.base	= 0x2A268000U,
};

static const struct psil_thread_type src_thread_types[] = {
	{
		.start = 0x8U,
		.end = 0x8U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x20U,
		.end = 0x20U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x1000U,
		.end = 0x108BU,
		.dev_id = J721E_DEV_NAVSS0_UDMAP_0,
	},
	{
		.start = 0x4000U,
		.end = 0x4003U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4100U,
		.end = 0x4104U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4200U,
		.end = 0x4204U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4300U,
		.end = 0x4302U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4304U,
		.end = 0x4305U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4400U,
		.end = 0x4402U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4404U,
		.end = 0x440BU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4500U,
		.end = 0x4508U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4600U,
		.end = 0x460AU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x460CU,
		.end = 0x4616U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4618U,
		.end = 0x4622U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4624U,
		.end = 0x462EU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4700U,
		.end = 0x4701U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4702U,
		.end = 0x4703U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4704U,
		.end = 0x4709U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x470CU,
		.end = 0x4729U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4800U,
		.end = 0x481FU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4820U,
		.end = 0x483FU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4840U,
		.end = 0x487FU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4880U,
		.end = 0x489FU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4900U,
		.end = 0x49FFU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4A00U,
		.end = 0x4A00U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x6000U,
		.end = 0x602FU,
		.dev_id = J721E_DEV_MCU_NAVSS0_UDMAP_0,
	},
	{
		.start = 0x7000U,
		.end = 0x7000U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x7100U,
		.end = 0x7106U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x7200U,
		.end = 0x7207U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x7300U,
		.end = 0x7303U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x7400U,
		.end = 0x7403U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x7500U,
		.end = 0x7503U,
		.dev_id = SOC_DEV_NONE,
	},
};

static const struct psil_thread_type dst_thread_types[] = {
	{
		.start = 0x9000U,
		.end = 0x908BU,
		.dev_id = J721E_DEV_NAVSS0_UDMAP_0,
	},
	{
		.start = 0xC000U,
		.end = 0xC001U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC100U,
		.end = 0xC108U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC200U,
		.end = 0xC208U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC400U,
		.end = 0xC402U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC404U,
		.end = 0xC40BU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC500U,
		.end = 0xC508U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC600U,
		.end = 0xC60AU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC60CU,
		.end = 0xC616U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC618U,
		.end = 0xC622U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC624U,
		.end = 0xC62EU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC700U,
		.end = 0xC701U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC702U,
		.end = 0xC703U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC704U,
		.end = 0xC709U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC70CU,
		.end = 0xC729U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC800U,
		.end = 0xC81FU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC820U,
		.end = 0xC83FU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC840U,
		.end = 0xC87FU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC880U,
		.end = 0xC89FU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC900U,
		.end = 0xC9FFU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xCA00U,
		.end = 0xCA07U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xE000U,
		.end = 0xE02FU,
		.dev_id = J721E_DEV_MCU_NAVSS0_UDMAP_0,
	},
	{
		.start = 0xF000U,
		.end = 0xF007U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xF100U,
		.end = 0xF106U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xF200U,
		.end = 0xF207U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xF300U,
		.end = 0xF303U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xF400U,
		.end = 0xF3FFU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xF500U,
		.end = 0xF501U,
		.dev_id = SOC_DEV_NONE,
	},
};

struct psil_instance psil_inst[] = {
	{
		.id = J721E_DEV_NAVSS0,
		.devgrp = SOC_DEVGRP_J721E_MAIN,
		.proxy = &mmr_NAVSS0_PSILCFG_0_UDMASS_PSILCFG0_CFG_PROXY,
		.src_thread_types = &src_thread_types[0],
		.dst_thread_types = &dst_thread_types[0],
		.n_src_thread_type = ARRAY_SIZE(src_thread_types),
		.n_dst_thread_type = ARRAY_SIZE(dst_thread_types),
	},
	{
		.id = J721E_DEV_MCU_NAVSS0,
		.devgrp = SOC_DEVGRP_J721E_MCU_WAKEUP,
		.proxy = &mmr_MCU_NAVSS0_PSILCFG_0_UDMASS_PSILSS_CFG0_PROXY,
		.src_thread_types = &src_thread_types[0],
		.dst_thread_types = &dst_thread_types[0],
		.n_src_thread_type = ARRAY_SIZE(src_thread_types),
		.n_dst_thread_type = ARRAY_SIZE(dst_thread_types),
	},
};

const u32 psil_inst_count = ARRAY_SIZE(psil_inst);

/*
 * Threads used by ROM which must be disabled prior to reuse
 */
#if !defined(CONFIG_DEVICE_TYPE_HS)
struct psil_used_thread psil_rom_usage[PSIL_ROM_USAGE_CNT] = {
	{
		.thread = 0x6000U,
		.disabled = SFALSE,
	},
	{
		.thread = 0x6004U,
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
		.thread = 0xe004U,
		.disabled = SFALSE,
	},
	{
		.thread = 0xe005U,
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
		.thread = 0x7500U,
		.disabled = SFALSE,
	},
	{
		.thread = 0x7501U,
		.disabled = SFALSE,
	},
	{
		.thread = 0xf500U,
		.disabled = SFALSE,
	},
};
#else
struct psil_used_thread psil_rom_usage[PSIL_ROM_USAGE_CNT] = {
	{
		.thread = 0x6000U,
		.disabled = SFALSE,
	},
	{
		.thread = 0x6004U,
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
		.thread = 0xe004U,
		.disabled = SFALSE,
	},
	{
		.thread = 0xe005U,
		.disabled = SFALSE,
	},
	{
		.thread = 0xf000U,
		.disabled = SFALSE,
	},
};
#endif
