/*
 * System Firmware Source File
 *
 * Static IA IRQ maps for Processing Entities for J7200 device
 *
 * Data version: 200505_131637
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
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
		.id		= J7200_DEV_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x0000U,
		.vint		= 0x0000U,
	},
	[1] =  {
		/*
		 * For: A72_0 response
		 */
		.id		= J7200_DEV_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x0001U,
		.vint		= 0x0001U,
	},
	[2] =  {
		/*
		 * For: A72_1 notify
		 */
		.id		= J7200_DEV_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x0002U,
		.vint		= 0x0002U,
	},
	[3] =  {
		/*
		 * For: A72_1 response
		 */
		.id		= J7200_DEV_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x0003U,
		.vint		= 0x0003U,
	},
	[4] =  {
		/*
		 * For: A72_2 notify
		 */
		.id		= J7200_DEV_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x0004U,
		.vint		= 0x0004U,
	},
	[5] =  {
		/*
		 * For: A72_2 response
		 */
		.id		= J7200_DEV_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x0005U,
		.vint		= 0x0005U,
	},
	[6] =  {
		/*
		 * For: A72_3 notify
		 */
		.id		= J7200_DEV_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x0006U,
		.vint		= 0x0006U,
	},
	[7] =  {
		/*
		 * For: A72_3 response
		 */
		.id		= J7200_DEV_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x0007U,
		.vint		= 0x0007U,
	},
	[8] =  {
		/*
		 * For: A72_4 notify
		 */
		.id		= J7200_DEV_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x0008U,
		.vint		= 0x0008U,
	},
	[9] =  {
		/*
		 * For: A72_4 response
		 */
		.id		= J7200_DEV_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x0009U,
		.vint		= 0x0009U,
	},
	[10] = {
		/*
		 * For: MAIN_0_R5_0 notify
		 */
		.id		= J7200_DEV_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x000AU,
		.vint		= 0x000AU,
	},
	[11] = {
		/*
		 * For: MAIN_0_R5_0 response
		 */
		.id		= J7200_DEV_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x000BU,
		.vint		= 0x000BU,
	},
	[12] = {
		/*
		 * For: MAIN_0_R5_1 notify
		 */
		.id		= J7200_DEV_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x000CU,
		.vint		= 0x000CU,
	},
	[13] = {
		/*
		 * For: MAIN_0_R5_1 response
		 */
		.id		= J7200_DEV_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x000DU,
		.vint		= 0x000DU,
	},
	[14] = {
		/*
		 * For: MAIN_0_R5_2 notify
		 */
		.id		= J7200_DEV_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x000EU,
		.vint		= 0x000EU,
	},
	[15] = {
		/*
		 * For: MAIN_0_R5_2 response
		 */
		.id		= J7200_DEV_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x000FU,
		.vint		= 0x000FU,
	},
	[16] = {
		/*
		 * For: MAIN_0_R5_3 notify
		 */
		.id		= J7200_DEV_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x0010U,
		.vint		= 0x0010U,
	},
	[17] = {
		/*
		 * For: MAIN_0_R5_3 response
		 */
		.id		= J7200_DEV_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x0011U,
		.vint		= 0x0011U,
	},
	[18] = {
		/*
		 * For: MCU_0_R5_0 notify
		 */
		.id		= J7200_DEV_MCU_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x4000U,
		.vint		= 0x0000U,
	},
	[19] = {
		/*
		 * For: MCU_0_R5_0 response
		 */
		.id		= J7200_DEV_MCU_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x4001U,
		.vint		= 0x0001U,
	},
	[20] = {
		/*
		 * For: MCU_0_R5_1 notify
		 */
		.id		= J7200_DEV_MCU_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x4002U,
		.vint		= 0x0002U,
	},
	[21] = {
		/*
		 * For: MCU_0_R5_1 response
		 */
		.id		= J7200_DEV_MCU_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x4003U,
		.vint		= 0x0003U,
	},
	[22] = {
		/*
		 * For: MCU_0_R5_2 notify
		 */
		.id		= J7200_DEV_MCU_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x4004U,
		.vint		= 0x0004U,
	},
	[23] = {
		/*
		 * For: MCU_0_R5_2 response
		 */
		.id		= J7200_DEV_MCU_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x4005U,
		.vint		= 0x0005U,
	},
	[24] = {
		/*
		 * For: MCU_0_R5_3 notify
		 */
		.id		= J7200_DEV_MCU_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x4006U,
		.vint		= 0x0006U,
	},
	[25] = {
		/*
		 * For: MCU_0_R5_3 response
		 */
		.id		= J7200_DEV_MCU_NAVSS0_UDMASS_INTA_0,
		.event_id	= 0x4007U,
		.vint		= 0x0007U,
	},
};
