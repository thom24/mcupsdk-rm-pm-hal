/*
 * System Firmware Source File
 *
 * Static IA IRQ maps for Processing Entities for J721E device
 *
 * Data version: 190425_000000
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <devices.h>

#include "../../include/ia_init.h"
#include "ia_pe_conf.h"

const struct ia_init ia_soc_pe_init_list[IA_SOC_PE_INIT_NUM] = {
	[0] =  {
		/*
		 * For: A72_0 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0000U,
		.vint		= 0x0000U,
	},
	[1] =  {
		/*
		 * For: A72_0 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0001U,
		.vint		= 0x0001U,
	},
	[2] =  {
		/*
		 * For: A72_1 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0002U,
		.vint		= 0x0002U,
	},
	[3] =  {
		/*
		 * For: A72_1 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0003U,
		.vint		= 0x0003U,
	},
	[4] =  {
		/*
		 * For: A72_2 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0004U,
		.vint		= 0x0004U,
	},
	[5] =  {
		/*
		 * For: A72_2 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0005U,
		.vint		= 0x0005U,
	},
	[6] =  {
		/*
		 * For: A72_3 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0006U,
		.vint		= 0x0006U,
	},
	[7] =  {
		/*
		 * For: A72_3 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0007U,
		.vint		= 0x0007U,
	},
	[8] =  {
		/*
		 * For: A72_4 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0008U,
		.vint		= 0x0008U,
	},
	[9] =  {
		/*
		 * For: A72_4 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0009U,
		.vint		= 0x0009U,
	},
	[10] = {
		/*
		 * For: C7X_0 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x000AU,
		.vint		= 0x000AU,
	},
	[11] = {
		/*
		 * For: C7X_0 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x000BU,
		.vint		= 0x000BU,
	},
	[12] = {
		/*
		 * For: C7X_1 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x000CU,
		.vint		= 0x000CU,
	},
	[13] = {
		/*
		 * For: C7X_1 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x000DU,
		.vint		= 0x000DU,
	},
	[14] = {
		/*
		 * For: C6X_0_0 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x000EU,
		.vint		= 0x000EU,
	},
	[15] = {
		/*
		 * For: C6X_0_0 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x000FU,
		.vint		= 0x000FU,
	},
	[16] = {
		/*
		 * For: C6X_0_1 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0010U,
		.vint		= 0x0010U,
	},
	[17] = {
		/*
		 * For: C6X_0_1 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0011U,
		.vint		= 0x0011U,
	},
	[18] = {
		/*
		 * For: C6X_1_0 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0012U,
		.vint		= 0x0012U,
	},
	[19] = {
		/*
		 * For: C6X_1_0 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0013U,
		.vint		= 0x0013U,
	},
	[20] = {
		/*
		 * For: C6X_1_1 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0014U,
		.vint		= 0x0014U,
	},
	[21] = {
		/*
		 * For: C6X_1_1 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0015U,
		.vint		= 0x0015U,
	},
	[22] = {
		/*
		 * For: MAIN_0_R5_0 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0016U,
		.vint		= 0x0016U,
	},
	[23] = {
		/*
		 * For: MAIN_0_R5_0 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0017U,
		.vint		= 0x0017U,
	},
	[24] = {
		/*
		 * For: MAIN_0_R5_1 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0018U,
		.vint		= 0x0018U,
	},
	[25] = {
		/*
		 * For: MAIN_0_R5_1 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0019U,
		.vint		= 0x0019U,
	},
	[26] = {
		/*
		 * For: MAIN_0_R5_2 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x001AU,
		.vint		= 0x001AU,
	},
	[27] = {
		/*
		 * For: MAIN_0_R5_2 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x001BU,
		.vint		= 0x001BU,
	},
	[28] = {
		/*
		 * For: MAIN_0_R5_3 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x001CU,
		.vint		= 0x001CU,
	},
	[29] = {
		/*
		 * For: MAIN_0_R5_3 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x001DU,
		.vint		= 0x001DU,
	},
	[30] = {
		/*
		 * For: MAIN_1_R5_0 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x001EU,
		.vint		= 0x001EU,
	},
	[31] = {
		/*
		 * For: MAIN_1_R5_0 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x001FU,
		.vint		= 0x001FU,
	},
	[32] = {
		/*
		 * For: MAIN_1_R5_1 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0020U,
		.vint		= 0x0020U,
	},
	[33] = {
		/*
		 * For: MAIN_1_R5_1 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0021U,
		.vint		= 0x0021U,
	},
	[34] = {
		/*
		 * For: MAIN_1_R5_2 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0022U,
		.vint		= 0x0022U,
	},
	[35] = {
		/*
		 * For: MAIN_1_R5_2 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0023U,
		.vint		= 0x0023U,
	},
	[36] = {
		/*
		 * For: MAIN_1_R5_3 notify
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0024U,
		.vint		= 0x0024U,
	},
	[37] = {
		/*
		 * For: MAIN_1_R5_3 response
		 */
		.id		= J721E_DEV_NAVSS0_UDMASS_INTAGGR_0,
		.event_id	= 0x0025U,
		.vint		= 0x0025U,
	},
	[38] = {
		/*
		 * For: MCU_0_R5_0 notify
		 */
		.id		= J721E_DEV_MCU_NAVSS0_INTAGGR_0,
		.event_id	= 0x4000U,
		.vint		= 0x0000U,
	},
	[39] = {
		/*
		 * For: MCU_0_R5_0 response
		 */
		.id		= J721E_DEV_MCU_NAVSS0_INTAGGR_0,
		.event_id	= 0x4001U,
		.vint		= 0x0001U,
	},
	[40] = {
		/*
		 * For: MCU_0_R5_1 notify
		 */
		.id		= J721E_DEV_MCU_NAVSS0_INTAGGR_0,
		.event_id	= 0x4002U,
		.vint		= 0x0002U,
	},
	[41] = {
		/*
		 * For: MCU_0_R5_1 response
		 */
		.id		= J721E_DEV_MCU_NAVSS0_INTAGGR_0,
		.event_id	= 0x4003U,
		.vint		= 0x0003U,
	},
	[42] = {
		/*
		 * For: MCU_0_R5_2 notify
		 */
		.id		= J721E_DEV_MCU_NAVSS0_INTAGGR_0,
		.event_id	= 0x4004U,
		.vint		= 0x0004U,
	},
	[43] = {
		/*
		 * For: MCU_0_R5_2 response
		 */
		.id		= J721E_DEV_MCU_NAVSS0_INTAGGR_0,
		.event_id	= 0x4005U,
		.vint		= 0x0005U,
	},
	[44] = {
		/*
		 * For: MCU_0_R5_3 notify
		 */
		.id		= J721E_DEV_MCU_NAVSS0_INTAGGR_0,
		.event_id	= 0x4006U,
		.vint		= 0x0006U,
	},
	[45] = {
		/*
		 * For: MCU_0_R5_3 response
		 */
		.id		= J721E_DEV_MCU_NAVSS0_INTAGGR_0,
		.event_id	= 0x4007U,
		.vint		= 0x0007U,
	},
};
