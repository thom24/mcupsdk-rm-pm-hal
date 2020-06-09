/*
 * System Firmware Source File
 *
 * Static IA IRQ maps for Processing Entities for AM64X device
 *
 * Data version: 200505_104840
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
		 * For: MAIN_0_R5_0 response
		 */
		.id		= AM64X_DEV_DMASS0_INTAGGR_0,
		.event_id	= 0x0000U,
		.vint		= 0x0028U,
	},
	[1] =  {
		/*
		 * For: MAIN_0_R5_1 response
		 */
		.id		= AM64X_DEV_DMASS0_INTAGGR_0,
		.event_id	= 0x0001U,
		.vint		= 0x0029U,
	},
	[2] =  {
		/*
		 * For: MAIN_0_R5_2 response
		 */
		.id		= AM64X_DEV_DMASS0_INTAGGR_0,
		.event_id	= 0x0002U,
		.vint		= 0x002AU,
	},
	[3] =  {
		/*
		 * For: MAIN_0_R5_3 response
		 */
		.id		= AM64X_DEV_DMASS0_INTAGGR_0,
		.event_id	= 0x0003U,
		.vint		= 0x002BU,
	},
	[4] =  {
		/*
		 * For: A53_0 response
		 */
		.id		= AM64X_DEV_DMASS0_INTAGGR_0,
		.event_id	= 0x0004U,
		.vint		= 0x0000U,
	},
	[5] =  {
		/*
		 * For: A53_1 response
		 */
		.id		= AM64X_DEV_DMASS0_INTAGGR_0,
		.event_id	= 0x0005U,
		.vint		= 0x0001U,
	},
	[6] =  {
		/*
		 * For: A53_2 response
		 */
		.id		= AM64X_DEV_DMASS0_INTAGGR_0,
		.event_id	= 0x0006U,
		.vint		= 0x0002U,
	},
	[7] =  {
		/*
		 * For: A53_3 response
		 */
		.id		= AM64X_DEV_DMASS0_INTAGGR_0,
		.event_id	= 0x0007U,
		.vint		= 0x0003U,
	},
	[8] =  {
		/*
		 * For: MAIN_1_R5_0 response
		 */
		.id		= AM64X_DEV_DMASS0_INTAGGR_0,
		.event_id	= 0x0008U,
		.vint		= 0x0058U,
	},
	[9] =  {
		/*
		 * For: MAIN_1_R5_1 response
		 */
		.id		= AM64X_DEV_DMASS0_INTAGGR_0,
		.event_id	= 0x0009U,
		.vint		= 0x0059U,
	},
	[10] = {
		/*
		 * For: MAIN_1_R5_2 response
		 */
		.id		= AM64X_DEV_DMASS0_INTAGGR_0,
		.event_id	= 0x000AU,
		.vint		= 0x005AU,
	},
	[11] = {
		/*
		 * For: MAIN_1_R5_3 response
		 */
		.id		= AM64X_DEV_DMASS0_INTAGGR_0,
		.event_id	= 0x000BU,
		.vint		= 0x005BU,
	},
};
