/*
 * System Firmware
 *
 * am62x soc pll.c
 *
 * Copyright (C) 2023, Texas Instruments Incorporated
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

#include <pll.h>

/* MCU PLL to be saved and restored */
struct pll_raw_data mcu_pll = 
{ .base = MCU_PLL_MMR_BASE, };

/* Main PLL to be saved and restored */
struct pll_raw_data main_pll0 =
{ .base = MAIN_PLL_MMR_BASE + PLLOFFSET(0), };

struct pll_raw_data main_pll1 =
{ .base = MAIN_PLL_MMR_BASE + PLLOFFSET(1), };

struct pll_raw_data main_pll2 =
{ .base = MAIN_PLL_MMR_BASE + PLLOFFSET(2), };

struct pll_raw_data main_pll8 =
{ .base = MAIN_PLL_MMR_BASE + PLLOFFSET(8), };

struct pll_raw_data main_pll12 =
{ .base = MAIN_PLL_MMR_BASE + PLLOFFSET(12), };

struct pll_raw_data main_pll16 =
{ .base = MAIN_PLL_MMR_BASE + PLLOFFSET(16), };

struct pll_raw_data main_pll17 =
{ .base = MAIN_PLL_MMR_BASE + PLLOFFSET(17), };

/* Base addresses of main PLL structures to be saved and restored */
u32 main_plls_save_rstr[] = {(u32)(&main_pll0), (u32)(&main_pll1), (u32)(&main_pll2), (u32)(&main_pll8), (u32)(&main_pll12), (u32)(&main_pll16), (u32)(&main_pll17)};

u8 num_main_plls_save_rstr = (sizeof(main_plls_save_rstr))/ (sizeof(u32));

/* Base addresses of main PLL structures to be disabled */
u32 main_plls_dis[] = {(u32)(&main_pll1), (u32)(&main_pll2), (u32)(&main_pll8), (u32)(&main_pll12), (u32)(&main_pll16), (u32)(&main_pll17)};

u8 num_main_plls_dis = (sizeof(main_plls_dis))/ (sizeof(u32));
