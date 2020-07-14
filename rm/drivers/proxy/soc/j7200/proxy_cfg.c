/*
 * Proxy
 *
 * Proxy driver instance data definition
 *
 * Data version: 200717_093321
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/short_types.h>
#include <types/array_size.h>
#include <types/sbool.h>
#include <soc/rm_mmr.h>
#include <devices.h>
#include <soc/j7200/resasg_types.h>
#include <soc/j7200/soc_devgrps.h>

#include "../../include/proxy_inst.h"
#include "proxy_cfg.h"

static const struct rm_mmr mmr_NAVSS0_PROXY_0_PROXY0_BUF_CFG = {
	.fwl_id		= 4660U,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 63U,
	.base		= 0x33400000U,
};

static const struct rm_mmr mmr_NAVSS0_PROXY_0_PROXY_TARGET0_DATA = {
	.fwl_id		= 4684U,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 63U,
	.base		= 0x33000000U,
};

static const struct rm_mmr mmr_MCU_NAVSS0_PROXY0_PROXY0_BUF_CFG = {
	.fwl_id		= 6146U,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 63U,
	.base		= 0x2a580000U,
};

static const struct rm_mmr mmr_MCU_NAVSS0_PROXY0_PROXY0_TARGET0_DATA = {
	.fwl_id		= 6256U,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 63U,
	.base		= 0x2a500000U,
};

struct proxy_instance proxy_inst[PROXY_INST_COUNT] = {
	{
		.id = J7200_DEV_NAVSS0_PROXY_0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J7200_MAIN,
		.cfg = &mmr_NAVSS0_PROXY_0_PROXY0_BUF_CFG,
		.target0_data = &mmr_NAVSS0_PROXY_0_PROXY_TARGET0_DATA,
		.n_proxies = PROXY_NAVSS0_PROXY_0_PROXY_MAX_INDEX,
		.proxy_utype = RESASG_UTYPE(J7200_DEV_NAVSS0_PROXY_0, RESASG_SUBTYPE_PROXY_PROXIES),
	},
	{
		.id = J7200_DEV_MCU_NAVSS0_PROXY0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_J7200_MCU_WAKEUP,
		.cfg = &mmr_MCU_NAVSS0_PROXY0_PROXY0_BUF_CFG,
		.target0_data = &mmr_MCU_NAVSS0_PROXY0_PROXY0_TARGET0_DATA,
		.n_proxies = PROXY_MCU_NAVSS0_PROXY0_PROXY_MAX_INDEX,
		.proxy_utype = RESASG_UTYPE(J7200_DEV_MCU_NAVSS0_PROXY0, RESASG_SUBTYPE_PROXY_PROXIES),
	},
};
