/*
 * System Firmware
 *
 * LPM DDR driver
 *
 * Copyright (C) 2021-2023, Texas Instruments Incorporated
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

#include <lib/bitops.h>
#include <lib/io.h>
#include <types/errno.h>
#include <types/short_types.h>
#include <types/sbool.h>
#include <baseaddress.h>
#include <wkup_ctrl_mmr.h>
#include "ddr.h"

#define DDR_RETRAIN_TIMEOUT 10000000U

/* Cadence DDR registers */
#define CDNS_DENALI_PHY_1333                                    0x54d4U
#define CDNS_DENALI_PHY_1333_PHY_CAL_START_0                    0x01000000U

#define CDNS_DENALI_PHY_1336                                    0x54e0U
#define CDNS_DENALI_PHY_1336_PHY_CAL_RESULT_OBS_0               (BIT(23))

#define CDNS_DENALI_PHY_1364                                    0x5550U
#define CDNS_DENALI_PHY_1364_PHY_INIT_UPDATE_CONFIG_MASK        0x7U
#define CDNS_DENALI_PHY_1364_PHY_INIT_UPDATE_CONFIG_SHIFT       0x8U

#define CDNS_DENALI_PHY_1369                                    0x5564U
#define CDNS_DENALI_PHY_1369_PHY_UPDATE_MASK                    0x1U

#define CDNS_DENALI_PI_23                                       0x205CU
#define CDNS_DENALI_PI_23_WRLVL_REQ                             0x01000000U

#define CDNS_DENALI_PI_24                                       0x2060U
#define CDNS_DENALI_PI_24_WRLVL_CS                              0x00000100U

#define CDNS_DENALI_PI_33                                       0x2084U
#define CDNS_DENALI_PI_33_RDLVL_GATE_REQ                        0x01000000U
#define CDNS_DENALI_PI_33_RDLVL_REQ                             0x00010000U

#define CDNS_DENALI_PI_34                                       0x2088U
#define CDNS_DENALI_PI_34_RDLVL_CS                              0x00000100U

#define CDNS_DENALI_PI_83                                       0x214CU
#define CDNS_DENALI_PI_83_LVL_DONE_BIT                          0x2000U

#define CDNS_DENALI_PI_84                                       0x2150U
#define CDNS_DENALI_PI_84_INT_ACK_REG_MASK                      0x1FFFFFFFU

#define CDNS_DENALI_CTL_0                                       0x0000U
#define CDNS_DENALI_CTL_0_DRAM_CLASS_MASK                       0x00000F00U
#define CDNS_DENALI_CTL_0_DRAM_CLASS_SHIFT                      0x00000008U

#define CDNS_DENALI_CTL_0_DRAM_CLASS_DDR4                       0xAU
#define CDNS_DENALI_CTL_0_DRAM_CLASS_LPDDR4                     0xBU

/**
 * \brief Return type of DRAM class from DDR registers
 */
static u32 ddr_read_ddr_type(void)
{
	u32 dram_class, val;

	val = readl(DDR_CTRL_BASE + CDNS_DENALI_CTL_0);
	dram_class = (val & CDNS_DENALI_CTL_0_DRAM_CLASS_MASK) >>
		     CDNS_DENALI_CTL_0_DRAM_CLASS_SHIFT;

	return dram_class;
}

s32 ddr_enter_low_power_mode(void)
{
	u32 val;
	s32 ret = SUCCESS;

	switch (ddr_read_ddr_type()) {
	case CDNS_DENALI_CTL_0_DRAM_CLASS_DDR4:

		/* Set CDNS_DENALI_PHY_1369:PHY UPDATE MASK */
		val = readl(DDR_CTRL_BASE + CDNS_DENALI_PHY_1369);
		val |= CDNS_DENALI_PHY_1369_PHY_UPDATE_MASK;
		writel(val, DDR_CTRL_BASE + CDNS_DENALI_PHY_1369);

		/* Clear 0x7 in CDNS_DENALI_PHY_1364:PHY_INIT_UPDATE_CONFIG */
		val = readl(DDR_CTRL_BASE + CDNS_DENALI_PHY_1364);
		val &= ~(CDNS_DENALI_PHY_1364_PHY_INIT_UPDATE_CONFIG_MASK <<
			 CDNS_DENALI_PHY_1364_PHY_INIT_UPDATE_CONFIG_SHIFT);
		writel(val, DDR_CTRL_BASE + CDNS_DENALI_PHY_1364);

		break;
	default:
		ret = -EFAIL;
		break;
	}

	return ret;
}

s32 ddr_exit_low_power_mode(void)
{
	u32 val;
	s32 ret = SUCCESS;

	switch (ddr_read_ddr_type()) {
	case CDNS_DENALI_CTL_0_DRAM_CLASS_DDR4:

		/* Clear CDNS_DENALI_PHY_1369:PHY UPDATE MASK */
		val = readl(DDR_CTRL_BASE + CDNS_DENALI_PHY_1369);
		val &= ~CDNS_DENALI_PHY_1369_PHY_UPDATE_MASK;
		writel(val, DDR_CTRL_BASE + CDNS_DENALI_PHY_1369);

		/* Set 0x7 in CDNS_DENALI_PHY_1364:PHY_INIT_UPDATE_CONFIG */
		val = readl(DDR_CTRL_BASE + CDNS_DENALI_PHY_1364);
		val |= (CDNS_DENALI_PHY_1364_PHY_INIT_UPDATE_CONFIG_MASK <<
			CDNS_DENALI_PHY_1364_PHY_INIT_UPDATE_CONFIG_SHIFT);
		writel(val, DDR_CTRL_BASE + CDNS_DENALI_PHY_1364);

		break;
	default:
		ret = -EFAIL;
		break;
	}

	return ret;
}

s32 ddr_deepsleep_exit_training(void)
{
	s32 ret = SUCCESS;

	switch (ddr_read_ddr_type()) {
	case CDNS_DENALI_CTL_0_DRAM_CLASS_DDR4:
	{
		u32 timeout = DDR_RETRAIN_TIMEOUT;
		u32 val;

		/* Write phy_cal_start_0 = 1 */
		val = readl(DDR_CTRL_BASE + CDNS_DENALI_PHY_1333);
		val |= CDNS_DENALI_PHY_1333_PHY_CAL_START_0;
		writel(val, DDR_CTRL_BASE + CDNS_DENALI_PHY_1333);

		/* Poll on phy_cal_result_obs_0 bit 23 = 1 */
		while (((timeout > 0U) && ((readl(DDR_CTRL_BASE + CDNS_DENALI_PHY_1336) &
					    (CDNS_DENALI_PHY_1336_PHY_CAL_RESULT_OBS_0)) == CDNS_DENALI_PHY_1336_PHY_CAL_RESULT_OBS_0)) == SFALSE) {
			--timeout;
		}
		if (timeout == 0U) {
			ret = -EFAIL;
		}

		/* Program PI_INT_ACK={`ddr32_ew_PI_NUM_INT_SOURCES{1'b1}} */
		writel(CDNS_DENALI_PI_84_INT_ACK_REG_MASK, DDR_CTRL_BASE + CDNS_DENALI_PI_84);

		/* Software trigger read gate level training */
		if (ret == 0) {
			/* Program PI_RDLVL_CS=0 */
			val = readl(DDR_CTRL_BASE + CDNS_DENALI_PI_34);
			val &= ~CDNS_DENALI_PI_34_RDLVL_CS;
			writel(val, DDR_CTRL_BASE + CDNS_DENALI_PI_34);

			/* Program PI_RDLVL_GATE_REQ=1 */
			val = readl(DDR_CTRL_BASE + CDNS_DENALI_PI_33);
			val |= CDNS_DENALI_PI_33_RDLVL_GATE_REQ;
			writel(val, DDR_CTRL_BASE + CDNS_DENALI_PI_33);

			/* Polling PI_INT_STATUS[`ddr32_ew_PI_LVL_DONE_BIT]=1 */
			timeout = DDR_RETRAIN_TIMEOUT;
			while (((timeout > 0U) && ((readl(DDR_CTRL_BASE + CDNS_DENALI_PI_83) &
						    (CDNS_DENALI_PI_83_LVL_DONE_BIT)) == CDNS_DENALI_PI_83_LVL_DONE_BIT)) == SFALSE) {
				--timeout;
			}
			if (timeout == 0U) {
				ret = -EFAIL;
			}

			/* Program PI_INT_ACK={`ddr32_ew_PI_NUM_INT_SOURCES{1'b1}} */
			writel(CDNS_DENALI_PI_84_INT_ACK_REG_MASK, DDR_CTRL_BASE + CDNS_DENALI_PI_84);
		}

		/* Software trigger read level training */
		if (ret == 0) {
			/* Program PI_RDLVL_CS=0 */
			val = readl(DDR_CTRL_BASE + CDNS_DENALI_PI_34);
			val &= ~CDNS_DENALI_PI_34_RDLVL_CS;
			writel(val, DDR_CTRL_BASE + CDNS_DENALI_PI_34);

			/* Program PI_RDLVL_REQ=1 */
			val = readl(DDR_CTRL_BASE + CDNS_DENALI_PI_33);
			val |= CDNS_DENALI_PI_33_RDLVL_REQ;
			writel(val, DDR_CTRL_BASE + CDNS_DENALI_PI_33);

			/* Polling PI_INT_STATUS[`ddr32_ew_PI_LVL_DONE_BIT]=1 */
			timeout = DDR_RETRAIN_TIMEOUT;
			while (((timeout > 0U) && ((readl(DDR_CTRL_BASE + CDNS_DENALI_PI_83) &
						    (CDNS_DENALI_PI_83_LVL_DONE_BIT)) == CDNS_DENALI_PI_83_LVL_DONE_BIT)) == SFALSE) {
				--timeout;
			}
			if (timeout == 0U) {
				ret = -EFAIL;
			}

			/* Program PI_INT_ACK={`ddr32_ew_PI_NUM_INT_SOURCES{1'b1}} */
			writel(CDNS_DENALI_PI_84_INT_ACK_REG_MASK, DDR_CTRL_BASE + CDNS_DENALI_PI_84);
		}

		/* Software trigger write level training */
		if (ret == 0) {
			/* Program PI_WRLVL_CS=0 */
			val = readl(DDR_CTRL_BASE + CDNS_DENALI_PI_24);
			val &= ~CDNS_DENALI_PI_24_WRLVL_CS;
			writel(val, DDR_CTRL_BASE + CDNS_DENALI_PI_24);

			/* Program PI_WRLVL_REQ=1 */
			val = readl(DDR_CTRL_BASE + CDNS_DENALI_PI_23);
			val |= CDNS_DENALI_PI_23_WRLVL_REQ;
			writel(val, DDR_CTRL_BASE + CDNS_DENALI_PI_23);

			/* Polling PI_INT_STATUS[`ddr32_ew_PI_LVL_DONE_BIT]=1 */
			timeout = DDR_RETRAIN_TIMEOUT;
			while (((timeout > 0U) && ((readl(DDR_CTRL_BASE + CDNS_DENALI_PI_83) &
						    (CDNS_DENALI_PI_83_LVL_DONE_BIT)) == CDNS_DENALI_PI_83_LVL_DONE_BIT)) == SFALSE) {
				--timeout;
			}
			if (timeout == 0U) {
				ret = -EFAIL;
			}

			/* Program PI_INT_ACK={`ddr32_ew_PI_NUM_INT_SOURCES{1'b1}} */
			writel(CDNS_DENALI_PI_84_INT_ACK_REG_MASK, DDR_CTRL_BASE + CDNS_DENALI_PI_84);
		}

		break;
	}
	default:
		ret = -EFAIL;
		break;
	}

	return ret;
}

void ddr_enable_retention(void)
{
	writel(DDR16SS_RETENTION_EN, WKUP_CTRL_MMR_BASE + DDR16SS_PMCTRL);
}

void ddr_disable_retention(void)
{
	writel(DDR16SS_RETENTION_DIS, WKUP_CTRL_MMR_BASE + DDR16SS_PMCTRL);
}
