/*
 * System Firmware Source File
 *
 * Static IR IRQ maps for Processing Entities for J7200 device
 *
 * Data version: 200730_091422
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <devices.h>

#include "../../include/ir_init.h"
#include "ir_pe_conf.h"

const struct ir_init ir_soc_pe_init_list[IR_SOC_PE_INIT_NUM] = {
	/*
	 * For: A72_0 notify: COMPUTE_CLUSTER0_GIC500SS/spi_64,
	 * COMPUTE_CLUSTER0_MSMC_1MB/gic_spi_64, COMPUTE_CLUSTER0_MSMC_EN/gic_spi_64
	 */
	[0] =  {
		.id	= J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.inp	= 0x00U,
		.outp	= 0x0000U,
	},
	/*
	 * For: A72_0 response: COMPUTE_CLUSTER0_GIC500SS/spi_65,
	 * COMPUTE_CLUSTER0_MSMC_1MB/gic_spi_65, COMPUTE_CLUSTER0_MSMC_EN/gic_spi_65
	 */
	[1] =  {
		.id	= J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.inp	= 0x01U,
		.outp	= 0x0001U,
	},
	/*
	 * For: A72_1 notify: COMPUTE_CLUSTER0_GIC500SS/spi_66,
	 * COMPUTE_CLUSTER0_MSMC_1MB/gic_spi_66, COMPUTE_CLUSTER0_MSMC_EN/gic_spi_66
	 */
	[2] =  {
		.id	= J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.inp	= 0x02U,
		.outp	= 0x0002U,
	},
	/*
	 * For: A72_1 response: COMPUTE_CLUSTER0_GIC500SS/spi_67,
	 * COMPUTE_CLUSTER0_MSMC_1MB/gic_spi_67, COMPUTE_CLUSTER0_MSMC_EN/gic_spi_67
	 */
	[3] =  {
		.id	= J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.inp	= 0x03U,
		.outp	= 0x0003U,
	},
	/*
	 * For: A72_2 notify: COMPUTE_CLUSTER0_GIC500SS/spi_68,
	 * COMPUTE_CLUSTER0_MSMC_1MB/gic_spi_68, COMPUTE_CLUSTER0_MSMC_EN/gic_spi_68
	 */
	[4] =  {
		.id	= J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.inp	= 0x04U,
		.outp	= 0x0004U,
	},
	/*
	 * For: A72_2 response: COMPUTE_CLUSTER0_GIC500SS/spi_69,
	 * COMPUTE_CLUSTER0_MSMC_1MB/gic_spi_69, COMPUTE_CLUSTER0_MSMC_EN/gic_spi_69
	 */
	[5] =  {
		.id	= J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.inp	= 0x05U,
		.outp	= 0x0005U,
	},
	/*
	 * For: A72_3 notify: COMPUTE_CLUSTER0_GIC500SS/spi_70,
	 * COMPUTE_CLUSTER0_MSMC_1MB/gic_spi_70, COMPUTE_CLUSTER0_MSMC_EN/gic_spi_70
	 */
	[6] =  {
		.id	= J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.inp	= 0x06U,
		.outp	= 0x0006U,
	},
	/*
	 * For: A72_3 response: COMPUTE_CLUSTER0_GIC500SS/spi_71,
	 * COMPUTE_CLUSTER0_MSMC_1MB/gic_spi_71, COMPUTE_CLUSTER0_MSMC_EN/gic_spi_71
	 */
	[7] =  {
		.id	= J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.inp	= 0x07U,
		.outp	= 0x0007U,
	},
	/*
	 * For: A72_4 notify: COMPUTE_CLUSTER0_GIC500SS/spi_72,
	 * COMPUTE_CLUSTER0_MSMC_1MB/gic_spi_72, COMPUTE_CLUSTER0_MSMC_EN/gic_spi_72
	 */
	[8] =  {
		.id	= J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.inp	= 0x08U,
		.outp	= 0x0008U,
	},
	/*
	 * For: A72_4 response: COMPUTE_CLUSTER0_GIC500SS/spi_73,
	 * COMPUTE_CLUSTER0_MSMC_1MB/gic_spi_73, COMPUTE_CLUSTER0_MSMC_EN/gic_spi_73
	 */
	[9] =  {
		.id	= J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.inp	= 0x09U,
		.outp	= 0x0009U,
	},
	/*
	 * For: MAIN_0_R5_0 notify: R5FSS0_CORE0/intr_224
	 */
	[10] = {
		.id	= J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.inp	= 0x0AU,
		.outp	= 0x00C0U,
	},
	/*
	 * For: MAIN_0_R5_0 response: R5FSS0_CORE0/intr_225
	 */
	[11] = {
		.id	= J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.inp	= 0x0BU,
		.outp	= 0x00C1U,
	},
	/*
	 * For: MAIN_0_R5_1 notify: R5FSS0_CORE0/intr_226
	 */
	[12] = {
		.id	= J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.inp	= 0x0CU,
		.outp	= 0x00C2U,
	},
	/*
	 * For: MAIN_0_R5_1 response: R5FSS0_CORE0/intr_227
	 */
	[13] = {
		.id	= J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.inp	= 0x0DU,
		.outp	= 0x00C3U,
	},
	/*
	 * For: MAIN_0_R5_2 notify: R5FSS0_CORE1/intr_224
	 */
	[14] = {
		.id	= J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.inp	= 0x0EU,
		.outp	= 0x00E0U,
	},
	/*
	 * For: MAIN_0_R5_2 response: R5FSS0_CORE1/intr_225
	 */
	[15] = {
		.id	= J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.inp	= 0x0FU,
		.outp	= 0x00E1U,
	},
	/*
	 * For: MAIN_0_R5_3 notify: R5FSS0_CORE1/intr_226
	 */
	[16] = {
		.id	= J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.inp	= 0x10U,
		.outp	= 0x00E2U,
	},
	/*
	 * For: MAIN_0_R5_3 response: R5FSS0_CORE1/intr_227
	 */
	[17] = {
		.id	= J7200_DEV_NAVSS0_INTR_ROUTER_0,
		.inp	= 0x11U,
		.outp	= 0x00E3U,
	},
	/*
	 * For: MCU_0_R5_0 notify: MCU_R5FSS0_CORE0/intr_64
	 */
	[18] = {
		.id	= J7200_DEV_MCU_NAVSS0_INTR_0,
		.inp	= 0x00U,
		.outp	= 0x0000U,
	},
	/*
	 * For: MCU_0_R5_0 response: MCU_R5FSS0_CORE0/intr_65
	 */
	[19] = {
		.id	= J7200_DEV_MCU_NAVSS0_INTR_0,
		.inp	= 0x01U,
		.outp	= 0x0001U,
	},
	/*
	 * For: MCU_0_R5_1 notify: MCU_R5FSS0_CORE0/intr_66
	 */
	[20] = {
		.id	= J7200_DEV_MCU_NAVSS0_INTR_0,
		.inp	= 0x02U,
		.outp	= 0x0002U,
	},
	/*
	 * For: MCU_0_R5_1 response: MCU_R5FSS0_CORE0/intr_67
	 */
	[21] = {
		.id	= J7200_DEV_MCU_NAVSS0_INTR_0,
		.inp	= 0x03U,
		.outp	= 0x0003U,
	},
	/*
	 * For: MCU_0_R5_2 notify: MCU_R5FSS0_CORE1/intr_64
	 */
	[22] = {
		.id	= J7200_DEV_MCU_NAVSS0_INTR_0,
		.inp	= 0x04U,
		.outp	= 0x0020U,
	},
	/*
	 * For: MCU_0_R5_2 response: MCU_R5FSS0_CORE1/intr_65
	 */
	[23] = {
		.id	= J7200_DEV_MCU_NAVSS0_INTR_0,
		.inp	= 0x05U,
		.outp	= 0x0021U,
	},
	/*
	 * For: MCU_0_R5_3 notify: MCU_R5FSS0_CORE1/intr_66
	 */
	[24] = {
		.id	= J7200_DEV_MCU_NAVSS0_INTR_0,
		.inp	= 0x06U,
		.outp	= 0x0022U,
	},
	/*
	 * For: MCU_0_R5_3 response: MCU_R5FSS0_CORE1/intr_67
	 */
	[25] = {
		.id	= J7200_DEV_MCU_NAVSS0_INTR_0,
		.inp	= 0x07U,
		.outp	= 0x0023U,
	},
};
