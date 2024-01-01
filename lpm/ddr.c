/*
 * System Firmware
 *
 * LPM DDR driver
 *
 * Copyright (C) 2021-2022, Texas Instruments Incorporated
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
#include <types/short_types.h>
#include <baseaddress.h>
#include <wkup_ctrl_mmr.h>
#include "ddr.h"

#include "lpm_trace.h"

/* Cadence DDR registers */
#define CDNS_DENALI_PHY_1364					0x5550
#define CDNS_DENALI_PHY_1364_PHY_INIT_UPDATE_CONFIG_MASK	0x7
#define CDNS_DENALI_PHY_1364_PHY_INIT_UPDATE_CONFIG_SHIFT	0x8

#define CDNS_DENALI_PHY_1369			0x5564
#define CDNS_DENALI_PHY_1369_PHY_UPDATE_MASK	0x1

void ddr_enter_low_power_mode(void)
{
	u32 val;

	/*
	 * - Set CDNS_DENALI_PHY_1369:PHY UPDATE MASK
	 * - Clear 0x7 in CDNS_DENALI_PHY_1364:PHY_INIT_UPDATE_CONFIG
	 */

	val = readl(DDR_CTRL_BASE + CDNS_DENALI_PHY_1369);
	val |= CDNS_DENALI_PHY_1369_PHY_UPDATE_MASK;
	writel(val, DDR_CTRL_BASE + CDNS_DENALI_PHY_1369);

	val = readl(DDR_CTRL_BASE + CDNS_DENALI_PHY_1364);
	val &= ~(CDNS_DENALI_PHY_1364_PHY_INIT_UPDATE_CONFIG_MASK <<
		 CDNS_DENALI_PHY_1364_PHY_INIT_UPDATE_CONFIG_SHIFT);
	writel(val, DDR_CTRL_BASE + CDNS_DENALI_PHY_1364);
}

void ddr_exit_low_power_mode(void)
{
	u32 val;

	/*
	 * - Clear CDNS_DENALI_PHY_1369:PHY UPDATE MASK
	 * - Set 0x7 in CDNS_DENALI_PHY_1364:PHY_INIT_UPDATE_CONFIG
	 */

	val = readl(DDR_CTRL_BASE + CDNS_DENALI_PHY_1369);
	val &= ~CDNS_DENALI_PHY_1369_PHY_UPDATE_MASK;
	writel(val, DDR_CTRL_BASE + CDNS_DENALI_PHY_1369);

	val = readl(DDR_CTRL_BASE + CDNS_DENALI_PHY_1364);
	val |= (CDNS_DENALI_PHY_1364_PHY_INIT_UPDATE_CONFIG_MASK <<
		CDNS_DENALI_PHY_1364_PHY_INIT_UPDATE_CONFIG_SHIFT);
	writel(val, DDR_CTRL_BASE + CDNS_DENALI_PHY_1364);
}

void ddr_enable_retention(void)
{
	/* TODO finish the sequence once it is consolidated */

	writel(DDR16SS_RETENTION_EN, WKUP_CTRL_MMR_BASE + DDR16SS_PMCTRL);
}

s32 ddr_disable_retention(void)
{

	writel(DDR16SS_RETENTION_DIS, WKUP_CTRL_MMR_BASE + DDR16SS_PMCTRL);

	return 0;
}
