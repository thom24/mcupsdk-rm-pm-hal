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
#define CDNS_DENALI_CTL_158     0x278
#define CDNS_DENALI_CTL_167     0x29c
#define CDNS_DENALI_CTL_345     0x564

#define CDNS_DENALI_PHY_1333	0x54d4
#define CDNS_DENALI_PHY_1368	0x5560

#define CDNS_LP_CMD_SHIFT       8
#define CDNS_LP_STATE_MASK      0xF << CDNS_LP_CMD_SHIFT
#define CDNS_LP_STATE_VALID     BIT(14)


#define CDNS_LP_CMD_SR_SHORT    0x1
#define CDNS_LP_CMD_SR_LONG     0x51
#define CDNS_LP_CMD_SR_EXIT     0x2

#define CDNS_DENALI_PHY_1368_DFI_INIT_COMPLETE	BIT(8)

#define DDR_COUNT_TIMEOUT	10000

#define CDNS_DENALI_PHY_1313	0x5484
#define CDNS_DENALI_PHY_1316	0x5490

void ddr_enter_self_refesh(void)
{
	u32 val;

	/* Enable LP For DDR */
	val = readl(0xF308294);
	val |= 0xf << 8;
	writel(val, 0xF308294);

}

void ddr_exit_self_refresh(void)
{
	u32 val;

	/*
	 * Disable LP For DDR, leaving this enabled in active increases
	 * DDR access latency
	 */
	val = readl(0xF308294);
	val &= ~(0xf << 8);
	writel(val, 0xF308294);
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
