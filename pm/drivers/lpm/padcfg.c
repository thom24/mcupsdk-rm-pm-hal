/*
 * Device Manager - Manage PADCFG Ctrl MMR during Suspend/Resume
 *
 * Copyright (C) 2021-2024, Texas Instruments Incorporated
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

#include <lib/ioremap.h>
#include <lib/mmr_lock.h>
#include <types/errno.h>
#include "soc_ctrl_mmr.h"
#include "padcfg.h"

static u32 main_padcfg_data[MAIN_PADCFG_SIZE];
static u32 mcu_padcfg_data[MCU_PADCFG_SIZE];

s32 lpm_sleep_save_main_padconf(sbool *wkup_en)
{
	u32 p = MAIN_PADCFG_CTRL_BASE + PADCFG_OFFSET;
	u32 i;

	for (i = 0; i < MAIN_PADCFG_SIZE; i++) {
		main_padcfg_data[i] = readl(p);
		p += 4U;

		if ((main_padcfg_data[i] & PADCFG_WAKE_EN_BIT) == PADCFG_WAKE_EN_BIT) {
			*wkup_en = STRUE;
		}
	}

	return SUCCESS;
}

s32 lpm_sleep_save_mcu_padconf(sbool *wkup_en)
{
	u32 p = MCU_PADCFG_CTRL_BASE + PADCFG_OFFSET;
	u32 i;

	for (i = 0; i < MCU_PADCFG_SIZE; i++) {
		mcu_padcfg_data[i] = readl(p);
		p += 4U;

		if ((mcu_padcfg_data[i] & PADCFG_WAKE_EN_BIT) == PADCFG_WAKE_EN_BIT) {
			*wkup_en = STRUE;
		}
	}

	return SUCCESS;
}

s32 lpm_resume_restore_main_padconf(void)
{
	u32 p = MAIN_PADCFG_CTRL_BASE + PADCFG_OFFSET;
	u32 i;

	mmr_unlock(MAIN_PADCFG_CTRL_BASE, 1);

	for (i = 0; i < MAIN_PADCFG_SIZE; i++) {
		writel(main_padcfg_data[i], p);
		p += 4U;
	}

	return SUCCESS;
}

s32 lpm_resume_restore_mcu_padconf(void)
{
	u32 p = MCU_PADCFG_CTRL_BASE + PADCFG_OFFSET;
	u32 i;

	mmr_unlock(MCU_PADCFG_CTRL_BASE, 1);
	for (i = 0; i < MCU_PADCFG_SIZE; i++) {
		writel(mcu_padcfg_data[i], p);
		p += 4U;
	}

	return SUCCESS;
}
