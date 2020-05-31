/*
 * PSI-L
 *
 * PSI-L driver instance data definition
 *
 * Data version: 000000_000000
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <config.h>
#include <types/short_types.h>
#include <types/sbool.h>
#include <types/array_size.h>
#include <soc/rm_mmr.h>
#include <devices.h>
#include <devices_internal.h>
#include <soc/am65x_sr2/soc_devgrps.h>

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
		.end = 0x1077U,
		.dev_id = AM6_DEV_NAVSS0_UDMAP0,
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
		.end = 0x4304U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4400U,
		.end = 0x4400U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4401U,
		.end = 0x4401U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4402U,
		.end = 0x4402U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4500U,
		.end = 0x4503U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4504U,
		.end = 0x4507U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4508U,
		.end = 0x450BU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x450CU,
		.end = 0x450FU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4510U,
		.end = 0x4513U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4514U,
		.end = 0x4514U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4515U,
		.end = 0x4515U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4516U,
		.end = 0x4516U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4600U,
		.end = 0x4600U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4601U,
		.end = 0x4601U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4602U,
		.end = 0x4602U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4700U,
		.end = 0x4707U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x4800U,
		.end = 0x481FU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x6000U,
		.end = 0x602FU,
		.dev_id = AM6_DEV_MCU_NAVSS0_UDMAP0,
	},
	{
		.start = 0x7000U,
		.end = 0x7000U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x7100U,
		.end = 0x7103U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x7200U,
		.end = 0x7203U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x7204U,
		.end = 0x7207U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x7208U,
		.end = 0x720BU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x720CU,
		.end = 0x720EU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x720FU,
		.end = 0x7211U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0x7212U,
		.end = 0x7212U,
		.dev_id = SOC_DEV_NONE,
	},
};

static const struct psil_thread_type dst_thread_types[] = {
	{
		.start = 0x9000U,
		.end = 0x9095U,
		.dev_id = AM6_DEV_NAVSS0_UDMAP0,
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
		.start = 0xC300U,
		.end = 0xC308U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC400U,
		.end = 0xC400U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC401U,
		.end = 0xC401U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC402U,
		.end = 0xC402U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC500U,
		.end = 0xC503U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC504U,
		.end = 0xC507U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC508U,
		.end = 0xC50BU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC50CU,
		.end = 0xC50FU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC510U,
		.end = 0xC513U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC514U,
		.end = 0xC514U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC515U,
		.end = 0xC515U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC516U,
		.end = 0xC516U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xC800U,
		.end = 0xC81FU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xE000U,
		.end = 0xE02FU,
		.dev_id = AM6_DEV_MCU_NAVSS0_UDMAP0,
	},
	{
		.start = 0xF000U,
		.end = 0xF007U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xF100U,
		.end = 0xF103U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xF200U,
		.end = 0xF203U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xF204U,
		.end = 0xF207U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xF208U,
		.end = 0xF20BU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xF20CU,
		.end = 0xF20EU,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xF20FU,
		.end = 0xF211U,
		.dev_id = SOC_DEV_NONE,
	},
	{
		.start = 0xF212U,
		.end = 0xF212U,
		.dev_id = SOC_DEV_NONE,
	},
};

struct psil_instance psil_inst[] = {
	{
		.id = AM6_DEV_NAVSS0,
		.devgrp = SOC_DEVGRP_AM6_MAIN,
		.proxy = &mmr_NAVSS0_PSILCFG_0_UDMASS_PSILCFG0_CFG_PROXY,
		.src_thread_types = &src_thread_types[0],
		.dst_thread_types = &dst_thread_types[0],
		.n_src_thread_type = ARRAY_SIZE(src_thread_types),
		.n_dst_thread_type = ARRAY_SIZE(dst_thread_types),
		.dru_ch0_dst_thread_offset = 0xc800U,
	},
	{
		.id = AM6_DEV_MCU_NAVSS0,
		.devgrp = SOC_DEVGRP_AM6_MCU_WAKEUP,
		.proxy = &mmr_MCU_NAVSS0_PSILCFG_0_UDMASS_PSILSS_CFG0_PROXY,
		.src_thread_types = &src_thread_types[0],
		.dst_thread_types = &dst_thread_types[0],
		.n_src_thread_type = ARRAY_SIZE(src_thread_types),
		.n_dst_thread_type = ARRAY_SIZE(dst_thread_types),
		.dru_ch0_dst_thread_offset = 0xc800U,
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
