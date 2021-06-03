/*
 * Ring Accelerator
 *
 * Ring accelerator driver instance data definition
 *
 * Data version: 201208_205323
 *
 * Copyright (C) 2019-2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <types/short_types.h>
#include <types/array_size.h>
#include <types/sbool.h>
#include <soc/rm_mmr.h>
#include <devices.h>
#include <soc/am64x/resasg_types.h>
#include <soc/am64x/soc_devgrps.h>

#include "../../include/ra_inst.h"
#include "ra_cfg.h"

static const struct rm_mmr mmr_DMASS0_BCDMA_0_BCDMA_GCFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x485c0100U,
};

static const struct rm_mmr mmr_DMASS0_BCDMA_0_BCDMA_RING = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x48600000U,
};

static const struct rm_mmr mmr_DMASS0_BCDMA_0_BCDMA_RINGRT = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x4bc00000U,
};

static const struct ra_ring_type ring_types_DMASS0_BCDMA_0[3] = {
	{
		.start = 0U,
		.end = 27U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_BCDMA_0, RESASG_SUBTYPE_BCDMA_RING_BLOCK_COPY_CHAN),
	},
	{
		.start = 28U,
		.end = 47U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_BCDMA_0, RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_TX_CHAN),
	},
	{
		.start = 48U,
		.end = 67U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_BCDMA_0, RESASG_SUBTYPE_BCDMA_RING_SPLIT_TR_RX_CHAN),
	},
};

static const struct rm_mmr mmr_DMASS0_PKTDMA_0_PKTDMA_GCFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x485c0000U,
};

static const struct rm_mmr mmr_DMASS0_PKTDMA_0_PKTDMA_RING = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x485e0000U,
};

static const struct rm_mmr mmr_DMASS0_PKTDMA_0_PKTDMA_RINGRT = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x4b800000U,
};

static const struct ra_ring_type ring_types_DMASS0_PKTDMA_0[14] = {
	{
		.start = 0U,
		.end = 15U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_TX_CHAN),
	},
	{
		.start = 16U,
		.end = 79U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_CPSW_TX_CHAN),
	},
	{
		.start = 80U,
		.end = 87U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_SAUL_TX_0_CHAN),
	},
	{
		.start = 88U,
		.end = 95U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_SAUL_TX_1_CHAN),
	},
	{
		.start = 96U,
		.end = 103U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_ICSSG_0_TX_CHAN),
	},
	{
		.start = 104U,
		.end = 111U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_ICSSG_1_TX_CHAN),
	},
	{
		.start = 112U,
		.end = 127U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_UNMAPPED_RX_CHAN),
	},
	{
		.start = 128U,
		.end = 143U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_CPSW_RX_CHAN),
	},
	{
		.start = 144U,
		.end = 151U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_0_CHAN),
	},
	{
		.start = 144U,
		.end = 151U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_1_CHAN),
	},
	{
		.start = 152U,
		.end = 159U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_2_CHAN),
	},
	{
		.start = 152U,
		.end = 159U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_SAUL_RX_3_CHAN),
	},
	{
		.start = 160U,
		.end = 223U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_ICSSG_0_RX_CHAN),
	},
	{
		.start = 224U,
		.end = 287U,
		.type = RA_DMSS_RING,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_PKTDMA_0, RESASG_SUBTYPE_PKTDMA_RING_ICSSG_1_RX_CHAN),
	},
};

static const struct rm_mmr mmr_DMASS0_RINGACC_0_RINGACC_GCFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x48240000U,
};

static const struct rm_mmr mmr_DMASS0_RINGACC_0_RINGACC_SRC_FIFOS = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x4e000000U,
};

static const struct rm_mmr mmr_DMASS0_RINGACC_0_RINGACC_CFG = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x49800000U,
};

static const struct rm_mmr mmr_DMASS0_RINGACC_0_RINGACC_RT = {
	.fwl_id		= RM_MMR_FWL_INVALID,
	.fwl_ch_start	= 0U,
	.fwl_ch_end	= 0U,
	.base		= 0x49000000U,
};

static const struct ra_ring_type ring_types_DMASS0_RINGACC_0[1] = {
	{
		.start = 20U,
		.end = 31U,
		.type = RA_STANDARD_RING,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_RINGACC_0, RESASG_SUBTYPE_RA_GENERIC_IPC),
	},
};

struct ra_instance ra_inst[] = {
	{
		.id = AM64X_DEV_DMASS0_BCDMA_0,
		.root_id = AM64X_DEV_DMASS0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM64X_MAIN,
		.gcfg = &mmr_DMASS0_BCDMA_0_BCDMA_GCFG,
		.cfg = &mmr_DMASS0_BCDMA_0_BCDMA_RING,
		.rt = &mmr_DMASS0_BCDMA_0_BCDMA_RINGRT,
		.mon = NULL,
		.fifos = NULL,
		.n_ring = 0U,
		.ring_oes_offset = 0U,
		.ring_types = &ring_types_DMASS0_BCDMA_0[0U],
		.n_ring_type = ARRAY_SIZE(ring_types_DMASS0_BCDMA_0),
		.err_evt_index = RA_GCFG_ERROR_EVT_INDEX,
		.err_evt_utype = RESASG_UTYPE(AM64X_DEV_DMASS0_BCDMA_0, RESASG_SUBTYPE_RA_ERROR_OES),
		.virtid_utype = 0U,
		.n_ring_mon = 0U,
		.ring_mon_utype = 0U,
		.ring_mon_oes_offset = 0U,
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = AM64X_DEV_DMASS0_PKTDMA_0,
		.root_id = AM64X_DEV_DMASS0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM64X_MAIN,
		.gcfg = &mmr_DMASS0_PKTDMA_0_PKTDMA_GCFG,
		.cfg = &mmr_DMASS0_PKTDMA_0_PKTDMA_RING,
		.rt = &mmr_DMASS0_PKTDMA_0_PKTDMA_RINGRT,
		.mon = NULL,
		.fifos = NULL,
		.n_ring = 0U,
		.ring_oes_offset = 0U,
		.ring_types = &ring_types_DMASS0_PKTDMA_0[0U],
		.n_ring_type = ARRAY_SIZE(ring_types_DMASS0_PKTDMA_0),
		.err_evt_index = RA_GCFG_ERROR_EVT_INDEX,
		.err_evt_utype = RESASG_UTYPE(AM64X_DEV_DMASS0_PKTDMA_0, RESASG_SUBTYPE_RA_ERROR_OES),
		.virtid_utype = 0U,
		.n_ring_mon = 0U,
		.ring_mon_utype = 0U,
		.ring_mon_oes_offset = 0U,
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
	{
		.id = AM64X_DEV_DMASS0_RINGACC_0,
		.root_id = AM64X_DEV_DMASS0,
		.initialized = SFALSE,
		.devgrp = SOC_DEVGRP_AM64X_MAIN | SOC_DEVGRP_AM64X_DMSC_INTERNAL,
		.gcfg = &mmr_DMASS0_RINGACC_0_RINGACC_GCFG,
		.cfg = &mmr_DMASS0_RINGACC_0_RINGACC_CFG,
		.rt = &mmr_DMASS0_RINGACC_0_RINGACC_RT,
		.mon = NULL,
		.fifos = &mmr_DMASS0_RINGACC_0_RINGACC_SRC_FIFOS,
		.n_ring = RA_DMASS0_RINGACC_0_MAX_INDEX,
		.ring_oes_offset = RA_DMASS0_RINGACC_0_RING_OES_EVT_INDEX_OFFSET,
		.ring_types = &ring_types_DMASS0_RINGACC_0[0U],
		.n_ring_type = ARRAY_SIZE(ring_types_DMASS0_RINGACC_0),
		.err_evt_index = RA_GCFG_ERROR_EVT_INDEX,
		.err_evt_utype = RESASG_UTYPE(AM64X_DEV_DMASS0_RINGACC_0, RESASG_SUBTYPE_RA_ERROR_OES),
		.virtid_utype = RESASG_UTYPE(AM64X_DEV_DMASS0_RINGACC_0, RESASG_SUBTYPE_RA_VIRTID),
		.n_ring_mon = 0U,
		.ring_mon_utype = 0U,
		.ring_mon_oes_offset = 0U,
		.rom_usage = NULL,
		.n_rom_usage = 0U,
	},
};

const u32 ra_inst_count = ARRAY_SIZE(ra_inst);
