/*
 * System Firmware
 *
 * am62x lpm mcu_ctrl_mmr.h
 *
 * Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef LPM_MCU_CTRL_MMR_H_
#define LPM_MCU_CTRL_MMR_H_

#ifdef __cplusplus
extern "C" {
#endif

#define HFOSC0_CTRL			(0x00008010U)
#define MCU_PLL_CLKSEL			(0x00008050U)

/* HFOSC0_CTRL */
#define HFOSC0_CTRL_PD_C		BIT(7)

/* MCU_PLL_CLKSEL */
#define MCU_PLL_CLKSEL_CLKLOSS_SWTCH_EN	BIT(8)

#ifdef __cplusplus
}
#endif
#endif /* LPM_MCU_CTRL_MMR_H_ */
