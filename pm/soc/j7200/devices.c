/*
 * Data version: 200505_131637
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#include <types/array_size.h>
#include <stddef.h>
#include <device_clk.h>
#include <config.h>
#include <resource.h>
#include <clk.h>
#include <device.h>
#include <build_assert.h>
#include <soc/device.h>
#include <soc/j7200/clk_ids.h>
#include <soc/j7200/clocks.h>
#include <soc/j7200/devices.h>
#include <soc/j7200/regs.h>
#include <soc/j7200/control.h>
#include <psc.h>

BUILD_ASSERT_GLOBAL(sizeof(dev_idx_t) == 2, dev_idx_t_is_16bit);

#define J7200_PSC_MULTIPLE_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_PBIST_WRAP 0
#define J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0 0
#define J7200_PSC_PD_GP_CORE_CTL 0
#define J7200_PSC_PD_PD_MCANSS 1
#define J7200_PSC_PD_PD_DSS 2
#define J7200_PSC_PD_PD_ICSS 3
#define J7200_PSC_PD_PD_9GSS 4
#define J7200_PSC_PD_PD_SERDES_0 5
#define J7200_PSC_PD_PD_SERDES_1 6
#define J7200_PSC_PD_PD_SERDES_2 7
#define J7200_PSC_PD_PD_SERDES_3 8
#define J7200_PSC_PD_PD_SERDES_4 9
#define J7200_PSC_PD_PD_SERDES_5 10
#define J7200_PSC_PD_PD_TIMER 11
#define J7200_PSC_PD_PD_C71X_0 12
#define J7200_PSC_PD_PD_C71X_1 13
#define J7200_PSC_PD_PD_A72_CLUSTER_0 14
#define J7200_PSC_PD_PD_A72_0 15
#define J7200_PSC_PD_PD_A72_1 16
#define J7200_PSC_PD_PD_A72_CLUSTER_1 17
#define J7200_PSC_PD_PD_A72_2 18
#define J7200_PSC_PD_PD_A72_3 19
#define J7200_PSC_PD_PD_GPUCOM 20
#define J7200_PSC_PD_PD_GPUCORE 21
#define J7200_PSC_PD_PD_C66X_0 22
#define J7200_PSC_PD_PD_C66X_1 23
#define J7200_PSC_PD_PD_PULSAR_0 24
#define J7200_PSC_PD_PD_PULSAR_1 25
#define J7200_PSC_PD_PD_DECODE_0 26
#define J7200_PSC_PD_PD_ENCODE_0 27
#define J7200_PSC_PD_PD_DMPAC 28
#define J7200_PSC_PD_PD_VPAC 29
#define J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON 0
#define J7200_PSC_LPSC_LPSC_MAIN_TEST 1
#define J7200_PSC_LPSC_LPSC_MAIN_PBIST 2
#define J7200_PSC_LPSC_LPSC_PER_AUDIO 3
#define J7200_PSC_LPSC_LPSC_PER_ATL 4
#define J7200_PSC_LPSC_LPSC_PER_MLB 5
#define J7200_PSC_LPSC_LPSC_PER_MOTOR 6
#define J7200_PSC_LPSC_LPSC_PER_MISCIO 7
#define J7200_PSC_LPSC_LPSC_PER_GPMC 8
#define J7200_PSC_LPSC_LPSC_PER_VPFE 9
#define J7200_PSC_LPSC_LPSC_PER_VPE 10
#define J7200_PSC_LPSC_LPSC_PER_SPARE0 11
#define J7200_PSC_LPSC_LPSC_PER_SPARE1 12
#define J7200_PSC_LPSC_LPSC_MAIN_DEBUG 13
#define J7200_PSC_LPSC_LPSC_EMIF_DATA_0 14
#define J7200_PSC_LPSC_LPSC_EMIF_CFG_0 15
#define J7200_PSC_LPSC_LPSC_EMIF_DATA_1 16
#define J7200_PSC_LPSC_LPSC_EMIF_CFG_1 17
#define J7200_PSC_LPSC_LPSC_PER_SPARE2 18
#define J7200_PSC_LPSC_LPSC_CC_TOP_PBIST 19
#define J7200_PSC_LPSC_LPSC_USB_0 20
#define J7200_PSC_LPSC_LPSC_USB_1 21
#define J7200_PSC_LPSC_LPSC_USB_2 22
#define J7200_PSC_LPSC_LPSC_MMC4B_0 23
#define J7200_PSC_LPSC_LPSC_MMC4B_1 24
#define J7200_PSC_LPSC_LPSC_MMC8B_0 25
#define J7200_PSC_LPSC_LPSC_UFS_0 26
#define J7200_PSC_LPSC_LPSC_UFS_1 27
#define J7200_PSC_LPSC_LPSC_PCIE_0 28
#define J7200_PSC_LPSC_LPSC_PCIE_1 29
#define J7200_PSC_LPSC_LPSC_PCIE_2 30
#define J7200_PSC_LPSC_LPSC_PCIE_3 31
#define J7200_PSC_LPSC_LPSC_SAUL 32
#define J7200_PSC_LPSC_LPSC_PER_I3C 33
#define J7200_PSC_LPSC_LPSC_MAIN_MCANSS_0 34
#define J7200_PSC_LPSC_LPSC_MAIN_MCANSS_1 35
#define J7200_PSC_LPSC_LPSC_MAIN_MCANSS_2 36
#define J7200_PSC_LPSC_LPSC_MAIN_MCANSS_3 37
#define J7200_PSC_LPSC_LPSC_MAIN_MCANSS_4 38
#define J7200_PSC_LPSC_LPSC_MAIN_MCANSS_5 39
#define J7200_PSC_LPSC_LPSC_MAIN_MCANSS_6 40
#define J7200_PSC_LPSC_LPSC_MAIN_MCANSS_7 41
#define J7200_PSC_LPSC_LPSC_MAIN_MCANSS_8 42
#define J7200_PSC_LPSC_LPSC_MAIN_MCANSS_9 43
#define J7200_PSC_LPSC_LPSC_MAIN_MCANSS_10 44
#define J7200_PSC_LPSC_LPSC_MAIN_MCANSS_11 45
#define J7200_PSC_LPSC_LPSC_MAIN_MCANSS_12 46
#define J7200_PSC_LPSC_LPSC_MAIN_MCANSS_13 47
#define J7200_PSC_LPSC_LPSC_DSS 48
#define J7200_PSC_LPSC_LPSC_DSS_PBIST 49
#define J7200_PSC_LPSC_LPSC_DSI 50
#define J7200_PSC_LPSC_LPSC_EDP_0 51
#define J7200_PSC_LPSC_LPSC_EDP_1 52
#define J7200_PSC_LPSC_LPSC_CSIRX_0 53
#define J7200_PSC_LPSC_LPSC_CSIRX_1 54
#define J7200_PSC_LPSC_LPSC_CSIRX_2 55
#define J7200_PSC_LPSC_LPSC_CSITX_0 56
#define J7200_PSC_LPSC_LPSC_TX_DPHY_0 57
#define J7200_PSC_LPSC_LPSC_CSIRX_PHY_0 58
#define J7200_PSC_LPSC_LPSC_CSIRX_PHY_1 59
#define J7200_PSC_LPSC_LPSC_CSIRX_PHY_2 60
#define J7200_PSC_LPSC_LPSC_ICSSG_0 61
#define J7200_PSC_LPSC_LPSC_ICSSG_1 62
#define J7200_PSC_LPSC_LPSC_9GSS 63
#define J7200_PSC_LPSC_LPSC_SERDES_0 64
#define J7200_PSC_LPSC_LPSC_SERDES_1 65
#define J7200_PSC_LPSC_LPSC_SERDES_2 66
#define J7200_PSC_LPSC_LPSC_SERDES_3 67
#define J7200_PSC_LPSC_LPSC_SERDES_4 68
#define J7200_PSC_LPSC_LPSC_SERDES_5 69
#define J7200_PSC_LPSC_LPSC_DMTIMER_0 70
#define J7200_PSC_LPSC_LPSC_DMTIMER_1 71
#define J7200_PSC_LPSC_LPSC_DMTIMER_2 72
#define J7200_PSC_LPSC_LPSC_DMTIMER_3 73
#define J7200_PSC_LPSC_LPSC_C71X_0 74
#define J7200_PSC_LPSC_LPSC_C71X_0_PBIST 75
#define J7200_PSC_LPSC_LPSC_C71X_1 76
#define J7200_PSC_LPSC_LPSC_C71X_1_PBIST 77
#define J7200_PSC_LPSC_LPSC_A72_CLUSTER_0 78
#define J7200_PSC_LPSC_LPSC_A72_CLUSTER_0_PBIST 79
#define J7200_PSC_LPSC_LPSC_A72_0 80
#define J7200_PSC_LPSC_LPSC_A72_1 81
#define J7200_PSC_LPSC_LPSC_A72_CLUSTER_1 82
#define J7200_PSC_LPSC_LPSC_A72_CLUSTER_1_PBIST 83
#define J7200_PSC_LPSC_LPSC_A72_2 84
#define J7200_PSC_LPSC_LPSC_A72_3 85
#define J7200_PSC_LPSC_LPSC_GPUCOM 86
#define J7200_PSC_LPSC_LPSC_GPUPBIST 87
#define J7200_PSC_LPSC_LPSC_GPUCORE 88
#define J7200_PSC_LPSC_LPSC_C66X_0 89
#define J7200_PSC_LPSC_LPSC_C66X_PBIST_0 90
#define J7200_PSC_LPSC_LPSC_C66X_1 91
#define J7200_PSC_LPSC_LPSC_C66X_PBIST_1 92
#define J7200_PSC_LPSC_LPSC_PULSAR_0_R5_0 93
#define J7200_PSC_LPSC_LPSC_PULSAR_0_R5_1 94
#define J7200_PSC_LPSC_LPSC_PULSAR_PBIST_0 95
#define J7200_PSC_LPSC_LPSC_PULSAR_1_R5_0 96
#define J7200_PSC_LPSC_LPSC_PULSAR_1_R5_1 97
#define J7200_PSC_LPSC_LPSC_PULSAR_PBIST_1 98
#define J7200_PSC_LPSC_LPSC_DECODE_0 99
#define J7200_PSC_LPSC_LPSC_DECODE_PBIST 100
#define J7200_PSC_LPSC_LPSC_ENCODE_0 101
#define J7200_PSC_LPSC_LPSC_ENCODE_PBIST 102
#define J7200_PSC_LPSC_LPSC_DMPAC 103
#define J7200_PSC_LPSC_LPSC_SDE 104
#define J7200_PSC_LPSC_LPSC_DMPAC_PBIST 105
#define J7200_PSC_LPSC_LPSC_VPAC 106
#define J7200_PSC_LPSC_LPSC_VPAC_PBIST 107
#define J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0 1
#define J7200_PSC_PD_PD_WKUP 0
#define J7200_PSC_PD_PD_MCU_PULSAR 1
#define J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON 0
#define J7200_PSC_LPSC_LPSC_DMSC 1
#define J7200_PSC_LPSC_LPSC_DEBUG2DMSC 2
#define J7200_PSC_LPSC_LPSC_WKUP_GPIO 3
#define J7200_PSC_LPSC_LPSC_WKUPMCU2MAIN 4
#define J7200_PSC_LPSC_LPSC_MAIN2WKUPMCU 5
#define J7200_PSC_LPSC_LPSC_MCU_TEST 6
#define J7200_PSC_LPSC_LPSC_MCU_DEBUG 7
#define J7200_PSC_LPSC_LPSC_MCU_MCAN_0 8
#define J7200_PSC_LPSC_LPSC_MCU_MCAN_1 9
#define J7200_PSC_LPSC_LPSC_MCU_OSPI_0 10
#define J7200_PSC_LPSC_LPSC_MCU_OSPI_1 11
#define J7200_PSC_LPSC_LPSC_MCU_HYPERBUS 12
#define J7200_PSC_LPSC_LPSC_MCU_I3C_0 13
#define J7200_PSC_LPSC_LPSC_MCU_I3C_1 14
#define J7200_PSC_LPSC_LPSC_MCU_ADC_0 15
#define J7200_PSC_LPSC_LPSC_MCU_ADC_1 16
#define J7200_PSC_LPSC_LPSC_WKUP_SPARE0 17
#define J7200_PSC_LPSC_LPSC_WKUP_SPARE1 18
#define J7200_PSC_LPSC_LPSC_MCU_R5_0 19
#define J7200_PSC_LPSC_LPSC_MCU_R5_1 20
#define J7200_PSC_LPSC_LPSC_MCU_PULSAR_PBIST_0 21

#define J7200_DEV_ADC12_CORE_MCU_0_CLOCKS 0
#define J7200_DEV_ADC12_CORE_MCU_1_CLOCKS 3
#define J7200_DEV_ATL_MAIN_0_CLOCKS 0
#define J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_CLOCKS 6
#define J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_P0_A72_DUAL_1MB_CLOCKS 13
#define J7200_DEV_DDR32V256SS_16FFC_EW_MAIN_0_CLOCKS 16
#define J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_PBIST_WRAP_CLOCKS 22
#define J7200_DEV_CPSW_2GUSS_MCU_0_CLOCKS 6
#define J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS 27
#define J7200_DEV_CPT2_AGGREGATOR32_MAIN_RC_0_CLOCKS 79
#define J7200_DEV_CPT2_AGGREGATOR32_MAIN_INFRA_0_CLOCKS 80
#define J7200_DEV_CPT2_AGGREGATOR32_MAIN_HC_0_CLOCKS 81
#define J7200_DEV_CPT2_AGGREGATOR32_MCU_0_CLOCKS 24
#define J7200_DEV_CPT2_AGGREGATOR32_MAIN_MV_0_CLOCKS 82
#define J7200_DEV_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_CLOCKS 83
#define J7200_DEV_CXSTM500SS_MAIN_0_CLOCKS 91
#define J7200_DEV_DCC2_MAIN_0_CLOCKS 94
#define J7200_DEV_DCC2_MAIN_1_CLOCKS 107
#define J7200_DEV_DCC2_MAIN_2_CLOCKS 120
#define J7200_DEV_DCC2_MAIN_3_CLOCKS 133
#define J7200_DEV_DCC2_MAIN_4_CLOCKS 146
#define J7200_DEV_DMTIMER_DMC1MS_MCU_0_CLOCKS 25
#define J7200_DEV_DCC2_MAIN_5_CLOCKS 159
#define J7200_DEV_DCC2_MAIN_6_CLOCKS 172
#define J7200_DEV_J7VC_WAKEUP_16FF_WKUP_0_CLOCKS 185
#define J7200_DEV_DCC2_MCU_0_CLOCKS 28
#define J7200_DEV_DCC2_MCU_1_CLOCKS 41
#define J7200_DEV_DCC2_MCU_2_CLOCKS 54
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_0_CLOCKS 188
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_1_CLOCKS 191
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_2_CLOCKS 193
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_3_CLOCKS 196
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_4_CLOCKS 198
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_5_CLOCKS 201
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_6_CLOCKS 203
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_7_CLOCKS 206
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_8_CLOCKS 208
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_9_CLOCKS 211
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_10_CLOCKS 213
#define J7200_DEV_GTC_R10_MAIN_0_CLOCKS 216
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_11_CLOCKS 218
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_12_CLOCKS 220
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_13_CLOCKS 223
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_14_CLOCKS 225
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_15_CLOCKS 228
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_16_CLOCKS 230
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_17_CLOCKS 233
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_18_CLOCKS 235
#define J7200_DEV_DMTIMER_DMC1MS_MAIN_19_CLOCKS 238
#define J7200_DEV_DMTIMER_DMC1MS_MCU_1_CLOCKS 67
#define J7200_DEV_DMTIMER_DMC1MS_MCU_2_CLOCKS 69
#define J7200_DEV_DMTIMER_DMC1MS_MCU_3_CLOCKS 72
#define J7200_DEV_DMTIMER_DMC1MS_MCU_4_CLOCKS 74
#define J7200_DEV_DMTIMER_DMC1MS_MCU_5_CLOCKS 77
#define J7200_DEV_DMTIMER_DMC1MS_MCU_6_CLOCKS 79
#define J7200_DEV_DMTIMER_DMC1MS_MCU_7_CLOCKS 82
#define J7200_DEV_DMTIMER_DMC1MS_MCU_8_CLOCKS 84
#define J7200_DEV_DMTIMER_DMC1MS_MCU_9_CLOCKS 87
#define J7200_DEV_ECAP_MAIN_0_CLOCKS 240
#define J7200_DEV_ECAP_MAIN_1_CLOCKS 241
#define J7200_DEV_ECAP_MAIN_2_CLOCKS 242
#define J7200_DEV_EHRPWM_MAIN_0_CLOCKS 243
#define J7200_DEV_EHRPWM_MAIN_1_CLOCKS 244
#define J7200_DEV_EHRPWM_MAIN_2_CLOCKS 245
#define J7200_DEV_EHRPWM_MAIN_3_CLOCKS 246
#define J7200_DEV_EHRPWM_MAIN_4_CLOCKS 247
#define J7200_DEV_EHRPWM_MAIN_5_CLOCKS 248
#define J7200_DEV_ELM_MAIN_0_CLOCKS 249
#define J7200_DEV_EMMC8SS_16FFC_MAIN_0_CLOCKS 250
#define J7200_DEV_EMMCSD4SS_MAIN_0_CLOCKS 254
#define J7200_DEV_EQEP_MAIN_0_CLOCKS 258
#define J7200_DEV_EQEP_MAIN_1_CLOCKS 259
#define J7200_DEV_EQEP_MAIN_2_CLOCKS 260
#define J7200_DEV_ESM_J7_MAIN_MAIN_0_CLOCKS 261
#define J7200_DEV_ESM_MCU_MCU_0_CLOCKS 89
#define J7200_DEV_ESM_J7VCL_WKUP_WKUP_0_CLOCKS 262
#define J7200_DEV_FSS_MCU_0_FSAS_0_CLOCKS 90
#define J7200_DEV_FSS_MCU_0_HYPERBUS1P0_0_CLOCKS 91
#define J7200_DEV_FSS_MCU_0_OSPI_0_CLOCKS 102
#define J7200_DEV_FSS_MCU_0_OSPI_1_CLOCKS 108
#define J7200_DEV_GPIO_144_MAIN_0_CLOCKS 263
#define J7200_DEV_GPIO_144_MAIN_2_CLOCKS 264
#define J7200_DEV_GPIO_144_MAIN_4_CLOCKS 265
#define J7200_DEV_GPIO_144_MAIN_6_CLOCKS 266
#define J7200_DEV_GPIO_144_WKUP_0_CLOCKS 113
#define J7200_DEV_GPIO_144_WKUP_1_CLOCKS 114
#define J7200_DEV_GPMC_MAIN_0_CLOCKS 267
#define J7200_DEV_I3C_MAIN_0_CLOCKS 271
#define J7200_DEV_I3C_MCU_0_CLOCKS 115
#define J7200_DEV_I3C_MCU_1_CLOCKS 120
#define J7200_DEV_J7VCL_CMP_EVENT_INTROUTER_MAIN_0_CLOCKS 276
#define J7200_DEV_J7_LED_MAIN_0_CLOCKS 277
#define J7200_DEV_J7VC_MAIN_GPIOMUX_INTROUTER_MAIN_0_CLOCKS 279
#define J7200_DEV_J7_MAIN_PORZ_SYNC_STRETCH_WKUP_0_CLOCKS 125
#define J7200_DEV_J7_MAIN_PSC_WRAP_MAIN_0_CLOCKS 280
#define J7200_DEV_J7_WKUP_PSC_WRAP_WKUP_0_CLOCKS 126
#define J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_0_CLOCKS 282
#define J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_1_CLOCKS 292
#define J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_PULSAR_0_CLOCKS 302
#define J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_0_CLOCKS 312
#define J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_1_CLOCKS 322
#define J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_PULSAR_0_CLOCKS 332
#define J7200_DEV_K3_DDPA_WKUP_0_CLOCKS 128
#define J7200_DEV_USART_MAIN_0_CLOCKS 342
#define J7200_DEV_USART_MCU_0_CLOCKS 129
#define J7200_DEV_MCANSS_MAIN_14_CLOCKS 346
#define J7200_DEV_MCANSS_MAIN_15_CLOCKS 349
#define J7200_DEV_MCANSS_MAIN_16_CLOCKS 352
#define J7200_DEV_MCANSS_MAIN_17_CLOCKS 355
#define J7200_DEV_K3VTM_N16FFC_WKUP_0_CLOCKS 133
#define J7200_DEV_MCANSS_MAIN_0_CLOCKS 358
#define J7200_DEV_BOARD_0_CLOCKS 135
#define J7200_DEV_MCANSS_MAIN_1_CLOCKS 361
#define J7200_DEV_MCANSS_MAIN_2_CLOCKS 364
#define J7200_DEV_MCANSS_MAIN_3_CLOCKS 367
#define J7200_DEV_MCANSS_MAIN_4_CLOCKS 370
#define J7200_DEV_MCANSS_MAIN_5_CLOCKS 373
#define J7200_DEV_MCANSS_MAIN_6_CLOCKS 376
#define J7200_DEV_MCANSS_MAIN_7_CLOCKS 379
#define J7200_DEV_MCANSS_MAIN_8_CLOCKS 382
#define J7200_DEV_MCANSS_MAIN_9_CLOCKS 385
#define J7200_DEV_MCANSS_MAIN_10_CLOCKS 388
#define J7200_DEV_MCANSS_MAIN_11_CLOCKS 391
#define J7200_DEV_MCANSS_MAIN_12_CLOCKS 394
#define J7200_DEV_MCANSS_MAIN_13_CLOCKS 397
#define J7200_DEV_MCANSS_MCU_0_CLOCKS 244
#define J7200_DEV_MCANSS_MCU_1_CLOCKS 247
#define J7200_DEV_MCASP_MAIN_0_CLOCKS 400
#define J7200_DEV_MCASP_MAIN_1_CLOCKS 412
#define J7200_DEV_MCASP_MAIN_2_CLOCKS 424
#define J7200_DEV_MSHSI2C_MAIN_0_CLOCKS 436
#define J7200_DEV_MSHSI2C_MAIN_1_CLOCKS 439
#define J7200_DEV_MSHSI2C_MAIN_2_CLOCKS 442
#define J7200_DEV_MSHSI2C_MAIN_3_CLOCKS 445
#define J7200_DEV_MSHSI2C_MAIN_4_CLOCKS 448
#define J7200_DEV_MSHSI2C_MAIN_5_CLOCKS 451
#define J7200_DEV_MSHSI2C_MAIN_6_CLOCKS 454
#define J7200_DEV_MSHSI2C_MCU_0_CLOCKS 250
#define J7200_DEV_MSHSI2C_MCU_1_CLOCKS 253
#define J7200_DEV_MSHSI2C_WKUP_0_CLOCKS 256
#define J7200_DEV_NAVSS256VCL_MAIN_0_CLOCKS 457
#define J7200_DEV_NAVSS256VCL_MAIN_0_CPTS_0_CLOCKS 460
#define J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_P0_A72_DUAL_1MB_0_CLOCKS 466
#define J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_P0_A72_DUAL_1MB_1_CLOCKS 469
#define J7200_DEV_NAVSS256VCL_MAIN_0_DTI_0_CLOCKS 470
#define J7200_DEV_NAVSS256VCL_MAIN_0_MODSS_INTA_0_CLOCKS 471
#define J7200_DEV_NAVSS256VCL_MAIN_0_MODSS_INTA_1_CLOCKS 472
#define J7200_DEV_NAVSS256VCL_MAIN_0_UDMASS_INTA_0_CLOCKS 473
#define J7200_DEV_NAVSS256VCL_MAIN_0_PROXY_0_CLOCKS 474
#define J7200_DEV_NAVSS256VCL_MAIN_0_RINGACC_0_CLOCKS 475
#define J7200_DEV_NAVSS256VCL_MAIN_0_UDMAP_0_CLOCKS 476
#define J7200_DEV_NAVSS256VCL_MAIN_0_INTR_0_CLOCKS 477
#define J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_0_CLOCKS 478
#define J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_1_CLOCKS 479
#define J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_2_CLOCKS 480
#define J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_3_CLOCKS 481
#define J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_4_CLOCKS 482
#define J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_5_CLOCKS 483
#define J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_6_CLOCKS 484
#define J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_7_CLOCKS 485
#define J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_8_CLOCKS 486
#define J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_9_CLOCKS 487
#define J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_10_CLOCKS 488
#define J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_11_CLOCKS 489
#define J7200_DEV_NAVSS256VCL_MAIN_0_SPINLOCK_0_CLOCKS 490
#define J7200_DEV_NAVSS256VCL_MAIN_0_MCRC_0_CLOCKS 491
#define J7200_DEV_NAVSS256VCL_MAIN_0_TBU_0_CLOCKS 492
#define J7200_DEV_NAVSS256VCL_MAIN_0_TIMERMGR_0_CLOCKS 493
#define J7200_DEV_NAVSS256VCL_MAIN_0_TIMERMGR_1_CLOCKS 495
#define J7200_DEV_NAVSS_MCU_J7_MCU_0_UDMASS_INTA_0_CLOCKS 260
#define J7200_DEV_NAVSS_MCU_J7_MCU_0_PROXY_0_CLOCKS 261
#define J7200_DEV_NAVSS_MCU_J7_MCU_0_RINGACC_0_CLOCKS 0
#define J7200_DEV_NAVSS_MCU_J7_MCU_0_UDMAP_0_CLOCKS 262
#define J7200_DEV_NAVSS_MCU_J7_MCU_0_INTR_0_CLOCKS 263
#define J7200_DEV_NAVSS_MCU_J7_MCU_0_MCRC_0_CLOCKS 264
#define J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS 497
#define J7200_DEV_PULSAR_SL_MAIN_0_R5_0_CLOCKS 525
#define J7200_DEV_PULSAR_SL_MAIN_0_R5_1_CLOCKS 528
#define J7200_DEV_PULSAR_SL_MCU_0_R5_0_CLOCKS 265
#define J7200_DEV_PULSAR_SL_MCU_0_R5_1_CLOCKS 268
#define J7200_DEV_RTI_CFG1_MAIN_A72_0_CLOCKS 531
#define J7200_DEV_RTI_CFG1_MAIN_A72_1_CLOCKS 533
#define J7200_DEV_RTI_CFG1_MAIN_R5_0_CLOCKS 535
#define J7200_DEV_RTI_CFG1_MAIN_R5_1_CLOCKS 537
#define J7200_DEV_RTI_CFG1_MCU_0_CLOCKS 271
#define J7200_DEV_RTI_CFG1_MCU_1_CLOCKS 273
#define J7200_DEV_SA2_UL_MCU_0_CLOCKS 275
#define J7200_DEV_SPI_MAIN_0_CLOCKS 539
#define J7200_DEV_SPI_MAIN_1_CLOCKS 543
#define J7200_DEV_SPI_MAIN_2_CLOCKS 547
#define J7200_DEV_SPI_MAIN_3_CLOCKS 551
#define J7200_DEV_SPI_MAIN_4_CLOCKS 555
#define J7200_DEV_SPI_MAIN_5_CLOCKS 559
#define J7200_DEV_SPI_MAIN_6_CLOCKS 563
#define J7200_DEV_SPI_MAIN_7_CLOCKS 567
#define J7200_DEV_SPI_MCU_0_CLOCKS 278
#define J7200_DEV_SPI_MCU_1_CLOCKS 282
#define J7200_DEV_SPI_MCU_2_CLOCKS 286
#define J7200_DEV_USART_MAIN_1_CLOCKS 571
#define J7200_DEV_USART_MAIN_2_CLOCKS 575
#define J7200_DEV_USART_MAIN_3_CLOCKS 579
#define J7200_DEV_USART_MAIN_4_CLOCKS 583
#define J7200_DEV_USART_MAIN_5_CLOCKS 587
#define J7200_DEV_USART_MAIN_6_CLOCKS 591
#define J7200_DEV_USART_MAIN_7_CLOCKS 595
#define J7200_DEV_USART_MAIN_8_CLOCKS 599
#define J7200_DEV_USART_MAIN_9_CLOCKS 603
#define J7200_DEV_USART_WKUP_0_CLOCKS 290
#define J7200_DEV_USB3P0SS_16FFC_MAIN_0_CLOCKS 607
#define J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS 621
#define J7200_DEV_NAVSS256VCL_MAIN_0_MODSS_0_CLOCKS 744
#define J7200_DEV_NAVSS256VCL_MAIN_0_UDMASS_0_CLOCKS 745
#define J7200_DEV_NAVSS256VCL_MAIN_0_VIRTSS_0_CLOCKS 746
#define J7200_DEV_NAVSS_MCU_J7_MCU_0_MODSS_0_CLOCKS 294
#define J7200_DEV_NAVSS_MCU_J7_MCU_0_UDMASS_0_CLOCKS 295
#define J7200_DEV_DEBUGSS_K3_WRAP_CV0_MAIN_0_CLOCKS 747

static const struct dev_data j7200_dev_adc12_core_mcu_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_MCU_ADC_0,
	},
	.dev_clk_idx		= J7200_DEV_ADC12_CORE_MCU_0_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_adc12_core_mcu_1 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.dev_clk_idx		= J7200_DEV_ADC12_CORE_MCU_1_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_atl_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_ATL,
	},
	.dev_clk_idx		= J7200_DEV_ATL_MAIN_0_CLOCKS,
	.n_clocks		= 6,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.dev_clk_idx		= J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_CLOCKS,
	.n_clocks		= 7,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_p0_a72_dual_1mb __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_A72_CLUSTER_0,
		.mod		= J7200_PSC_LPSC_LPSC_A72_CLUSTER_0_PBIST,
	},
	.dev_clk_idx		= J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_P0_A72_DUAL_1MB_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_cfg_wrap __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_clec __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_core_core __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_ddr32v256ss_16ffc_ew_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_EMIF_CFG_0,
	},
	.dev_clk_idx		= J7200_DEV_DDR32V256SS_16FFC_EW_MAIN_0_CLOCKS,
	.n_clocks		= 6,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_debug_wrap __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_divh2_divh0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_divp_tft0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_dmsc_wrap __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_en_msmc_domain __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_gic500ss __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct soc_device_data compute_cluster_j7vcl_tb_vdc_main_0_pbist_wrap_domains[] = {
	{
		.psc_idx = J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd = J7200_PSC_PD_GP_CORE_CTL,
		.mod = J7200_PSC_LPSC_LPSC_CC_TOP_PBIST,
	},
	{
		.psc_idx = J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd = J7200_PSC_PD_PD_A72_CLUSTER_0,
		.mod = J7200_PSC_LPSC_LPSC_A72_CLUSTER_0_PBIST,
	},
	{
		.psc_idx = PSC_DEV_NONE,
	},
};
static const struct dev_data j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_pbist_wrap __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_MULTIPLE,
		.mod		= J7200_PSC_MULTIPLE_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_PBIST_WRAP,
	},
	.dev_clk_idx		= J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_PBIST_WRAP_CLOCKS,
	.n_clocks		= 5,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_cpsw_2guss_mcu_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_CPSW_2GUSS_MCU_0_CLOCKS,
	.n_clocks		= 18,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_cpsw_5xuss_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_9GSS,
		.mod		= J7200_PSC_LPSC_LPSC_9GSS,
	},
	.dev_clk_idx		= J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,
	.n_clocks		= 52,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_cpt2_aggregator32_main_rc_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_CPT2_AGGREGATOR32_MAIN_RC_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_cpt2_aggregator32_main_infra_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_CPT2_AGGREGATOR32_MAIN_INFRA_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmsc_wkup_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_DMSC,
	},
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_cpt2_aggregator32_main_hc_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_CPT2_AGGREGATOR32_MAIN_HC_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_cpt2_aggregator32_mcu_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_CPT2_AGGREGATOR32_MCU_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_cpt2_aggregator32_main_mv_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_CPT2_AGGREGATOR32_MAIN_MV_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_j7vcl_cpsw_tx_rgmii_wrap_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.dev_clk_idx		= J7200_DEV_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_CLOCKS,
	.n_clocks		= 8,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_cxstm500ss_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_DEBUG,
	},
	.dev_clk_idx		= J7200_DEV_CXSTM500SS_MAIN_0_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dcc2_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DCC2_MAIN_0_CLOCKS,
	.n_clocks		= 13,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dcc2_main_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DCC2_MAIN_1_CLOCKS,
	.n_clocks		= 13,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dcc2_main_2 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DCC2_MAIN_2_CLOCKS,
	.n_clocks		= 13,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dcc2_main_3 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DCC2_MAIN_3_CLOCKS,
	.n_clocks		= 13,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dcc2_main_4 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DCC2_MAIN_4_CLOCKS,
	.n_clocks		= 13,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_mcu_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MCU_0_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_dcc2_main_5 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DCC2_MAIN_5_CLOCKS,
	.n_clocks		= 13,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dcc2_main_6 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DCC2_MAIN_6_CLOCKS,
	.n_clocks		= 13,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_j7vc_main_16ff_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_j7vc_wakeup_16ff_wkup_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.dev_clk_idx		= J7200_DEV_J7VC_WAKEUP_16FF_WKUP_0_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dcc2_mcu_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DCC2_MCU_0_CLOCKS,
	.n_clocks		= 13,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_dcc2_mcu_1 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DCC2_MCU_1_CLOCKS,
	.n_clocks		= 13,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_dcc2_mcu_2 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DCC2_MCU_2_CLOCKS,
	.n_clocks		= 13,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_TIMER,
		.mod		= J7200_PSC_LPSC_LPSC_DMTIMER_0,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_0_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_TIMER,
		.mod		= J7200_PSC_LPSC_LPSC_DMTIMER_1,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_1_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_2 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_TIMER,
		.mod		= J7200_PSC_LPSC_LPSC_DMTIMER_2,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_2_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_3 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_TIMER,
		.mod		= J7200_PSC_LPSC_LPSC_DMTIMER_3,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_3_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_4 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_4_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_5 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_5_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_6 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_6_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_7 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_7_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_8 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_SPARE0,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_8_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_9 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_SPARE0,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_9_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_10 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_SPARE0,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_10_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_gtc_r10_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_VPFE,
	},
	.dev_clk_idx		= J7200_DEV_GTC_R10_MAIN_0_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_11 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_SPARE0,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_11_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_12 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_SPARE0,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_12_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_13 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_SPARE0,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_13_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_14 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_SPARE0,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_14_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_15 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_SPARE0,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_15_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_16 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_SPARE0,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_16_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_17 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_SPARE0,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_17_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_18 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_SPARE0,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_18_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_main_19 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_SPARE0,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MAIN_19_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_mcu_1 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MCU_1_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_mcu_2 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MCU_2_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_mcu_3 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MCU_3_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_mcu_4 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MCU_4_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_mcu_5 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MCU_5_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_mcu_6 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MCU_6_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_mcu_7 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MCU_7_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_mcu_8 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MCU_8_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_dmtimer_dmc1ms_mcu_9 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_DMTIMER_DMC1MS_MCU_9_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_ecap_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_MOTOR,
	},
	.dev_clk_idx		= J7200_DEV_ECAP_MAIN_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_ecap_main_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_MOTOR,
	},
	.dev_clk_idx		= J7200_DEV_ECAP_MAIN_1_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_ecap_main_2 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_MOTOR,
	},
	.dev_clk_idx		= J7200_DEV_ECAP_MAIN_2_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_ehrpwm_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_MOTOR,
	},
	.dev_clk_idx		= J7200_DEV_EHRPWM_MAIN_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_ehrpwm_main_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_MOTOR,
	},
	.dev_clk_idx		= J7200_DEV_EHRPWM_MAIN_1_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_ehrpwm_main_2 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_MOTOR,
	},
	.dev_clk_idx		= J7200_DEV_EHRPWM_MAIN_2_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_ehrpwm_main_3 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_MOTOR,
	},
	.dev_clk_idx		= J7200_DEV_EHRPWM_MAIN_3_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_ehrpwm_main_4 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_MOTOR,
	},
	.dev_clk_idx		= J7200_DEV_EHRPWM_MAIN_4_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_ehrpwm_main_5 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_MOTOR,
	},
	.dev_clk_idx		= J7200_DEV_EHRPWM_MAIN_5_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_elm_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_GPMC,
	},
	.dev_clk_idx		= J7200_DEV_ELM_MAIN_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_emif_data_0_VD __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_EMIF_DATA_0,
	},
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_emmc8ss_16ffc_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MMC8B_0,
	},
	.dev_clk_idx		= J7200_DEV_EMMC8SS_16FFC_MAIN_0_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_emmcsd4ss_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MMC4B_0,
	},
	.dev_clk_idx		= J7200_DEV_EMMCSD4SS_MAIN_0_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_eqep_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_MOTOR,
	},
	.dev_clk_idx		= J7200_DEV_EQEP_MAIN_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_eqep_main_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_MOTOR,
	},
	.dev_clk_idx		= J7200_DEV_EQEP_MAIN_1_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_eqep_main_2 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_MOTOR,
	},
	.dev_clk_idx		= J7200_DEV_EQEP_MAIN_2_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_esm_j7_main_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_ESM_J7_MAIN_MAIN_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_esm_mcu_mcu_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_ESM_MCU_MCU_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_esm_j7vcl_wkup_wkup_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_ESM_J7VCL_WKUP_WKUP_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_fss_mcu_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_fss_mcu_0_fsas_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_FSS_MCU_0_FSAS_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_fss_mcu_0_hyperbus1p0_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_MCU_HYPERBUS,
	},
	.dev_clk_idx		= J7200_DEV_FSS_MCU_0_HYPERBUS1P0_0_CLOCKS,
	.n_clocks		= 11,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_fss_mcu_0_ospi_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_MCU_OSPI_0,
	},
	.dev_clk_idx		= J7200_DEV_FSS_MCU_0_OSPI_0_CLOCKS,
	.n_clocks		= 6,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_fss_mcu_0_ospi_1 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_MCU_OSPI_1,
	},
	.dev_clk_idx		= J7200_DEV_FSS_MCU_0_OSPI_1_CLOCKS,
	.n_clocks		= 5,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_gpio_144_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_GPIO_144_MAIN_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_gpio_144_main_2 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_VPFE,
	},
	.dev_clk_idx		= J7200_DEV_GPIO_144_MAIN_2_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_gpio_144_main_4 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_VPFE,
	},
	.dev_clk_idx		= J7200_DEV_GPIO_144_MAIN_4_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_gpio_144_main_6 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_VPFE,
	},
	.dev_clk_idx		= J7200_DEV_GPIO_144_MAIN_6_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_gpio_144_wkup_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_GPIO,
	},
	.dev_clk_idx		= J7200_DEV_GPIO_144_WKUP_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_gpio_144_wkup_1 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_GPIO,
	},
	.dev_clk_idx		= J7200_DEV_GPIO_144_WKUP_1_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_gpmc_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_GPMC,
	},
	.dev_clk_idx		= J7200_DEV_GPMC_MAIN_0_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_i3c_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_I3C,
	},
	.dev_clk_idx		= J7200_DEV_I3C_MAIN_0_CLOCKS,
	.n_clocks		= 5,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_i3c_mcu_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_MCU_I3C_0,
	},
	.dev_clk_idx		= J7200_DEV_I3C_MCU_0_CLOCKS,
	.n_clocks		= 5,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_i3c_mcu_1 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_MCU_I3C_1,
	},
	.dev_clk_idx		= J7200_DEV_I3C_MCU_1_CLOCKS,
	.n_clocks		= 5,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_j7vcl_cmp_event_introuter_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_VPFE,
	},
	.dev_clk_idx		= J7200_DEV_J7VCL_CMP_EVENT_INTROUTER_MAIN_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_j7_led_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.dev_clk_idx		= J7200_DEV_J7_LED_MAIN_0_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_j7_main2mcu_lvl_introuter_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_VPFE,
	},
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_j7_main2mcu_pls_introuter_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_VPFE,
	},
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_j7vc_main_gpiomux_introuter_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_VPFE,
	},
	.dev_clk_idx		= J7200_DEV_J7VC_MAIN_GPIOMUX_INTROUTER_MAIN_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_j7_main_porz_sync_stretch_wkup_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.dev_clk_idx		= J7200_DEV_J7_MAIN_PORZ_SYNC_STRETCH_WKUP_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_00,
};
static struct psc_data j7200_j7_main_psc_wrap_main_0_data __attribute__((__section__(".bss.devgroup.MAIN")));
static const struct psc_pd_data j7200_j7_main_psc_wrap_main_0_pd_data[] __attribute__((__section__(".const.devgroup.MAIN"))) = {
	[J7200_PSC_PD_GP_CORE_CTL] =	  {
		.flags	= PSC_PD_EXISTS,
	},
	[J7200_PSC_PD_PD_MCANSS] =	  {
		.flags	= PSC_PD_EXISTS | PSC_PD_ALWAYSON,
	},
	[J7200_PSC_PD_PD_DSS] =		  {
		.depends	= J7200_PSC_PD_GP_CORE_CTL,
		.flags		= PSC_PD_EXISTS | PSC_PD_ALWAYSON | PSC_PD_DEPENDS,
	},
	[J7200_PSC_PD_PD_ICSS] =	  {
		.flags	= PSC_PD_EXISTS | PSC_PD_ALWAYSON,
	},
	[J7200_PSC_PD_PD_9GSS] =	  {
		.flags	= PSC_PD_EXISTS | PSC_PD_ALWAYSON,
	},
	[J7200_PSC_PD_PD_SERDES_0] =	  {
		.flags	= PSC_PD_EXISTS | PSC_PD_ALWAYSON,
	},
	[J7200_PSC_PD_PD_SERDES_1] =	  {
		.flags	= PSC_PD_EXISTS | PSC_PD_ALWAYSON,
	},
	[J7200_PSC_PD_PD_SERDES_2] =	  {
		.flags	= PSC_PD_EXISTS | PSC_PD_ALWAYSON,
	},
	[J7200_PSC_PD_PD_SERDES_3] =	  {
		.flags	= PSC_PD_EXISTS | PSC_PD_ALWAYSON,
	},
	[J7200_PSC_PD_PD_SERDES_4] =	  {
		.flags	= PSC_PD_EXISTS | PSC_PD_ALWAYSON,
	},
	[J7200_PSC_PD_PD_SERDES_5] =	  {
		.flags	= PSC_PD_EXISTS | PSC_PD_ALWAYSON,
	},
	[J7200_PSC_PD_PD_TIMER] =	  {
		.depends	= J7200_PSC_PD_GP_CORE_CTL,
		.flags		= PSC_PD_EXISTS | PSC_PD_ALWAYSON | PSC_PD_DEPENDS,
	},
	[J7200_PSC_PD_PD_C71X_0] =	  {
		.flags	= PSC_PD_EXISTS,
	},
	[J7200_PSC_PD_PD_C71X_1] =	  {
		.flags	= PSC_PD_EXISTS,
	},
	[J7200_PSC_PD_PD_A72_CLUSTER_0] = {
		.flags	= PSC_PD_EXISTS,
	},
	[J7200_PSC_PD_PD_A72_0] =	  {
		.depends	= J7200_PSC_PD_PD_A72_CLUSTER_0,
		.flags		= PSC_PD_EXISTS | PSC_PD_DEPENDS,
	},
	[J7200_PSC_PD_PD_A72_1] =	  {
		.depends	= J7200_PSC_PD_PD_A72_CLUSTER_0,
		.flags		= PSC_PD_EXISTS | PSC_PD_DEPENDS,
	},
	[J7200_PSC_PD_PD_A72_CLUSTER_1] = {
		.flags	= PSC_PD_EXISTS,
	},
	[J7200_PSC_PD_PD_A72_2] =	  {
		.flags	= PSC_PD_EXISTS,
	},
	[J7200_PSC_PD_PD_A72_3] =	  {
		.flags	= PSC_PD_EXISTS,
	},
	[J7200_PSC_PD_PD_GPUCOM] =	  {
		.flags	= PSC_PD_EXISTS,
	},
	[J7200_PSC_PD_PD_GPUCORE] =	  {
		.flags	= PSC_PD_EXISTS,
	},
	[J7200_PSC_PD_PD_C66X_0] =	  {
		.flags	= PSC_PD_EXISTS,
	},
	[J7200_PSC_PD_PD_C66X_1] =	  {
		.flags	= PSC_PD_EXISTS,
	},
	[J7200_PSC_PD_PD_PULSAR_0] =	  {
		.flags	= PSC_PD_EXISTS,
	},
	[J7200_PSC_PD_PD_PULSAR_1] =	  {
		.flags	= PSC_PD_EXISTS,
	},
	[J7200_PSC_PD_PD_DECODE_0] =	  {
		.flags	= PSC_PD_EXISTS,
	},
	[J7200_PSC_PD_PD_ENCODE_0] =	  {
		.flags	= PSC_PD_EXISTS,
	},
	[J7200_PSC_PD_PD_DMPAC] =	  {
		.flags	= PSC_PD_EXISTS,
	},
	[J7200_PSC_PD_PD_VPAC] =	  {
		.flags	= PSC_PD_EXISTS,
	},
};
static struct psc_pd j7200_j7_main_psc_wrap_main_0_powerdomains[ARRAY_SIZE(j7200_j7_main_psc_wrap_main_0_pd_data)] __attribute__((__section__(".bss.devgroup.MAIN")));
static const dev_idx_t dev_list_LPSC_main_alwayson[] __attribute__((__section__(".const.devgroup.MAIN"))) = {
	J7200_DEV_COMPUTE_CLUSTER0_CORE_CORE,
	J7200_DEV_COMPUTE_CLUSTER0_EN_MSMC_DOMAIN,
	J7200_DEV_CPT2_AGGR2,
	J7200_DEV_CPT2_AGGR1,
	J7200_DEV_CPT2_AGGR3,
	J7200_DEV_CPT2_AGGR0,
	J7200_DEV_DCC0,
	J7200_DEV_DCC1,
	J7200_DEV_DCC2,
	J7200_DEV_DCC3,
	J7200_DEV_DCC4,
	J7200_DEV_DCC5,
	J7200_DEV_DCC6,
	J7200_DEV_TIMER4,
	J7200_DEV_TIMER5,
	J7200_DEV_TIMER6,
	J7200_DEV_TIMER7,
	J7200_DEV_ESM0,
	J7200_DEV_GPIO0,
	J7200_DEV_NAVSS0_CPTS_0,
	J7200_DEV_NAVSS0_DTI_0,
	J7200_DEV_NAVSS0_INTR_ROUTER_0,
	J7200_DEV_NAVSS0_MAILBOX_0,
	J7200_DEV_NAVSS0_MAILBOX_1,
	J7200_DEV_NAVSS0_MAILBOX_10,
	J7200_DEV_NAVSS0_MAILBOX_11,
	J7200_DEV_NAVSS0_MAILBOX_2,
	J7200_DEV_NAVSS0_MAILBOX_3,
	J7200_DEV_NAVSS0_MAILBOX_4,
	J7200_DEV_NAVSS0_MAILBOX_5,
	J7200_DEV_NAVSS0_MAILBOX_6,
	J7200_DEV_NAVSS0_MAILBOX_7,
	J7200_DEV_NAVSS0_MAILBOX_8,
	J7200_DEV_NAVSS0_MAILBOX_9,
	J7200_DEV_NAVSS0_MCRC_0,
	J7200_DEV_NAVSS0_MODSS,
	J7200_DEV_NAVSS0_MODSS_INTA_0,
	J7200_DEV_NAVSS0_MODSS_INTA_1,
	J7200_DEV_NAVSS0_PROXY_0,
	J7200_DEV_NAVSS0_RINGACC_0,
	J7200_DEV_NAVSS0_SPINLOCK_0,
	J7200_DEV_NAVSS0_TBU_0,
	J7200_DEV_NAVSS0_TIMERMGR_0,
	J7200_DEV_NAVSS0_TIMERMGR_1,
	J7200_DEV_NAVSS0_UDMAP_0,
	J7200_DEV_NAVSS0_UDMASS,
	J7200_DEV_NAVSS0_UDMASS_INTA_0,
	J7200_DEV_NAVSS0_VIRTSS,
	DEV_ID_NONE,
};
static const dev_idx_t dev_list_LPSC_PER_audio[] __attribute__((__section__(".const.devgroup.MAIN"))) = {
	J7200_DEV_MCASP0,
	J7200_DEV_MCASP1,
	J7200_DEV_MCASP2,
	DEV_ID_NONE,
};
static const dev_idx_t dev_list_LPSC_PER_motor[] __attribute__((__section__(".const.devgroup.MAIN"))) = {
	J7200_DEV_ECAP0,
	J7200_DEV_ECAP1,
	J7200_DEV_ECAP2,
	J7200_DEV_EHRPWM0,
	J7200_DEV_EHRPWM1,
	J7200_DEV_EHRPWM2,
	J7200_DEV_EHRPWM3,
	J7200_DEV_EHRPWM4,
	J7200_DEV_EHRPWM5,
	J7200_DEV_EQEP0,
	J7200_DEV_EQEP1,
	J7200_DEV_EQEP2,
	DEV_ID_NONE,
};
static const dev_idx_t dev_list_LPSC_PER_VPFE[] __attribute__((__section__(".const.devgroup.MAIN"))) = {
	J7200_DEV_GPIO2,
	J7200_DEV_GPIO4,
	J7200_DEV_GPIO6,
	J7200_DEV_GTC0,
	J7200_DEV_MAIN2MCU_LVL_INTRTR0,
	J7200_DEV_MAIN2MCU_PLS_INTRTR0,
	J7200_DEV_TIMESYNC_INTRTR0,
	J7200_DEV_GPIOMUX_INTRTR0,
	J7200_DEV_CMPEVENT_INTRTR0,
	DEV_ID_NONE,
};
static const dev_idx_t dev_list_LPSC_PER_spare0[] __attribute__((__section__(".const.devgroup.MAIN"))) = {
	J7200_DEV_TIMER10,
	J7200_DEV_TIMER11,
	J7200_DEV_TIMER12,
	J7200_DEV_TIMER13,
	J7200_DEV_TIMER14,
	J7200_DEV_TIMER15,
	J7200_DEV_TIMER16,
	J7200_DEV_TIMER17,
	J7200_DEV_TIMER18,
	J7200_DEV_TIMER19,
	J7200_DEV_TIMER8,
	J7200_DEV_TIMER9,
	DEV_ID_NONE,
};
static const dev_idx_t dev_list_LPSC_eDP_1[] __attribute__((__section__(".const.devgroup.MAIN"))) = {
	J7200_DEV_MCSPI0,
	J7200_DEV_MCSPI1,
	J7200_DEV_MCSPI2,
	J7200_DEV_MCSPI3,
	DEV_ID_NONE,
};
static const dev_idx_t dev_list_LPSC_CSIRX_0[] __attribute__((__section__(".const.devgroup.MAIN"))) = {
	J7200_DEV_MCSPI4,
	J7200_DEV_MCSPI5,
	J7200_DEV_MCSPI6,
	J7200_DEV_MCSPI7,
	DEV_ID_NONE,
};
static const dev_idx_t dev_list_LPSC_CSITX_0[] __attribute__((__section__(".const.devgroup.MAIN"))) = {
	J7200_DEV_UART4,
	J7200_DEV_UART5,
	J7200_DEV_UART6,
	J7200_DEV_UART7,
	J7200_DEV_UART8,
	J7200_DEV_UART9,
	DEV_ID_NONE,
};
static const dev_idx_t dev_list_LPSC_TX_DPHY_0[] __attribute__((__section__(".const.devgroup.MAIN"))) = {
	J7200_DEV_I2C1,
	J7200_DEV_I2C2,
	J7200_DEV_I2C3,
	DEV_ID_NONE,
};
static const dev_idx_t dev_list_LPSC_CSIRX_PHY_0[] __attribute__((__section__(".const.devgroup.MAIN"))) = {
	J7200_DEV_I2C4,
	J7200_DEV_I2C5,
	J7200_DEV_I2C6,
	DEV_ID_NONE,
};
static const struct lpsc_module_data j7200_j7_main_psc_wrap_main_0_mod_data[] __attribute__((__section__(".const.devgroup.MAIN"))) = {
	[J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON] =	    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_list	= dev_list_LPSC_main_alwayson,
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING | LPSC_NO_MODULE_RESET | LPSC_DEVICES_LIST,
	},
	[J7200_PSC_LPSC_LPSC_MAIN_TEST] =	    {
		.powerdomain		= J7200_PSC_PD_GP_CORE_CTL,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_PER_VPE,
		.dev_array		=	    {
			DEV_ID_NONE,
		},
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS | LPSC_HAS_LOCAL_RESET,
	},
	[J7200_PSC_LPSC_LPSC_MAIN_PBIST] =	    {
		.powerdomain		= J7200_PSC_PD_GP_CORE_CTL,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_PER_VPE,
		.dev_array		=	    {
			J7200_DEV_PBIST0,
			J7200_DEV_PBIST1,
		},
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS | LPSC_HAS_LOCAL_RESET,
	},
	[J7200_PSC_LPSC_LPSC_PER_AUDIO] =	    {
		.powerdomain		= J7200_PSC_PD_GP_CORE_CTL,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_USB_2,
		.dev_list		= dev_list_LPSC_PER_audio,
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS | LPSC_DEVICES_LIST,
	},
	[J7200_PSC_LPSC_LPSC_PER_ATL] =		    {
		.powerdomain		= J7200_PSC_PD_GP_CORE_CTL,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_USB_2,
		.dev_array		=	    {
			J7200_DEV_ATL0,
			DEV_ID_NONE,
		},
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS,
	},
	[J7200_PSC_LPSC_LPSC_PER_MLB] =		    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			J7200_DEV_NAVSS0,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_PER_MOTOR] =	    {
		.powerdomain		= J7200_PSC_PD_GP_CORE_CTL,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_USB_2,
		.dev_list		= dev_list_LPSC_PER_motor,
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS | LPSC_DEVICES_LIST,
	},
	[J7200_PSC_LPSC_LPSC_PER_MISCIO] =	    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			J7200_DEV_I2C0,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_PER_GPMC] =	    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			J7200_DEV_ELM0,
			J7200_DEV_GPMC0,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_PER_VPFE] =	    {
		.powerdomain		= J7200_PSC_PD_GP_CORE_CTL,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_PER_VPE,
		.dev_list		= dev_list_LPSC_PER_VPFE,
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS | LPSC_DEVICES_LIST,
	},
	[J7200_PSC_LPSC_LPSC_PER_VPE] =		    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_PER_SPARE0] =	    {
		.powerdomain		= J7200_PSC_PD_GP_CORE_CTL,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_USB_2,
		.dev_list		= dev_list_LPSC_PER_spare0,
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS | LPSC_DEVICES_LIST,
	},
	[J7200_PSC_LPSC_LPSC_PER_SPARE1] =	    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_MAIN_DEBUG] =	    {
		.powerdomain		= J7200_PSC_PD_GP_CORE_CTL,
		.depends_psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.depends		= J7200_PSC_LPSC_LPSC_MCU_DEBUG,
		.dev_array		=	    {
			J7200_DEV_STM0,
			J7200_DEV_DEBUGSS_WRAP0,
		},
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS,
	},
	[J7200_PSC_LPSC_LPSC_EMIF_DATA_0] =	    {
		.powerdomain		= J7200_PSC_PD_GP_CORE_CTL,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_EMIF_CFG_0,
		.dev_array		=	    {
			J7200_DEV_EMIF_DATA_0_VD,
			DEV_ID_NONE,
		},
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS,
	},
	[J7200_PSC_LPSC_LPSC_EMIF_CFG_0] =	    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			J7200_DEV_DDR0,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_EMIF_DATA_1] =	    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_EMIF_CFG_1] =	    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_PER_SPARE2] =	    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_CC_TOP_PBIST] =	    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			J7200_DEV_COMPUTE_CLUSTER0_PBIST_WRAP,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_USB_0] =		    {
		.powerdomain		= J7200_PSC_PD_GP_CORE_CTL,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_UFS_1,
		.dev_array		=	    {
			J7200_DEV_USB0,
			DEV_ID_NONE,
		},
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS,
	},
	[J7200_PSC_LPSC_LPSC_USB_1] =		    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_USB_2] =		    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			J7200_DEV_FFI_MAIN_IP_CBASS_VD,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MMC4B_0] =		    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			J7200_DEV_MMCSD1,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MMC4B_1] =		    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_MMC8B_0] =		    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			J7200_DEV_MMCSD0,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_UFS_0] =		    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_UFS_1] =		    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			J7200_DEV_FFI_MAIN_RC_CBASS_VD,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_PCIE_0] =		    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_PCIE_1] =		    {
		.powerdomain		= J7200_PSC_PD_GP_CORE_CTL,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_UFS_1,
		.dev_array		=	    {
			J7200_DEV_PCIE1,
			DEV_ID_NONE,
		},
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS,
	},
	[J7200_PSC_LPSC_LPSC_PCIE_2] =		    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_PCIE_3] =		    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_SAUL] =		    {
		.powerdomain	= J7200_PSC_PD_GP_CORE_CTL,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_PER_I3C] =		    {
		.powerdomain		= J7200_PSC_PD_GP_CORE_CTL,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_USB_2,
		.dev_array		=	    {
			J7200_DEV_I3C0,
			DEV_ID_NONE,
		},
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS,
	},
	[J7200_PSC_LPSC_LPSC_MAIN_MCANSS_0] =	    {
		.powerdomain	= J7200_PSC_PD_PD_MCANSS,
		.dev_array	=		    {
			J7200_DEV_MCAN0,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MAIN_MCANSS_1] =	    {
		.powerdomain	= J7200_PSC_PD_PD_MCANSS,
		.dev_array	=		    {
			J7200_DEV_MCAN1,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MAIN_MCANSS_2] =	    {
		.powerdomain	= J7200_PSC_PD_PD_MCANSS,
		.dev_array	=		    {
			J7200_DEV_MCAN2,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MAIN_MCANSS_3] =	    {
		.powerdomain	= J7200_PSC_PD_PD_MCANSS,
		.dev_array	=		    {
			J7200_DEV_MCAN3,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MAIN_MCANSS_4] =	    {
		.powerdomain	= J7200_PSC_PD_PD_MCANSS,
		.dev_array	=		    {
			J7200_DEV_MCAN4,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MAIN_MCANSS_5] =	    {
		.powerdomain	= J7200_PSC_PD_PD_MCANSS,
		.dev_array	=		    {
			J7200_DEV_MCAN5,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MAIN_MCANSS_6] =	    {
		.powerdomain	= J7200_PSC_PD_PD_MCANSS,
		.dev_array	=		    {
			J7200_DEV_MCAN6,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MAIN_MCANSS_7] =	    {
		.powerdomain	= J7200_PSC_PD_PD_MCANSS,
		.dev_array	=		    {
			J7200_DEV_MCAN7,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MAIN_MCANSS_8] =	    {
		.powerdomain	= J7200_PSC_PD_PD_MCANSS,
		.dev_array	=		    {
			J7200_DEV_MCAN8,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MAIN_MCANSS_9] =	    {
		.powerdomain	= J7200_PSC_PD_PD_MCANSS,
		.dev_array	=		    {
			J7200_DEV_MCAN9,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MAIN_MCANSS_10] =	    {
		.powerdomain	= J7200_PSC_PD_PD_MCANSS,
		.dev_array	=		    {
			J7200_DEV_MCAN10,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MAIN_MCANSS_11] =	    {
		.powerdomain	= J7200_PSC_PD_PD_MCANSS,
		.dev_array	=		    {
			J7200_DEV_MCAN11,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MAIN_MCANSS_12] =	    {
		.powerdomain	= J7200_PSC_PD_PD_MCANSS,
		.dev_array	=		    {
			J7200_DEV_MCAN12,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MAIN_MCANSS_13] =	    {
		.powerdomain	= J7200_PSC_PD_PD_MCANSS,
		.dev_array	=		    {
			J7200_DEV_MCAN13,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_DSS] =		    {
		.powerdomain	= J7200_PSC_PD_PD_DSS,
		.dev_array	=		    {
			J7200_DEV_MCAN14,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_DSS_PBIST] =	    {
		.powerdomain	= J7200_PSC_PD_PD_DSS,
		.dev_array	=		    {
			J7200_DEV_MCAN15,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_DSI] =		    {
		.powerdomain	= J7200_PSC_PD_PD_DSS,
		.dev_array	=		    {
			J7200_DEV_MCAN16,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_EDP_0] =		    {
		.powerdomain	= J7200_PSC_PD_PD_DSS,
		.dev_array	=		    {
			J7200_DEV_MCAN17,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_EDP_1] =		    {
		.powerdomain	= J7200_PSC_PD_PD_DSS,
		.dev_list	= dev_list_LPSC_eDP_1,
		.flags		= LPSC_MODULE_EXISTS | LPSC_DEVICES_LIST,
	},
	[J7200_PSC_LPSC_LPSC_CSIRX_0] =		    {
		.powerdomain		= J7200_PSC_PD_PD_DSS,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_USB_2,
		.dev_list		= dev_list_LPSC_CSIRX_0,
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS | LPSC_DEVICES_LIST,
	},
	[J7200_PSC_LPSC_LPSC_CSIRX_1] =		    {
		.powerdomain	= J7200_PSC_PD_PD_DSS,
		.dev_array	=		    {
			J7200_DEV_UART0,
			J7200_DEV_UART1,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_CSIRX_2] =		    {
		.powerdomain		= J7200_PSC_PD_PD_DSS,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_USB_2,
		.dev_array		=	    {
			J7200_DEV_UART2,
			J7200_DEV_UART3,
		},
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS,
	},
	[J7200_PSC_LPSC_LPSC_CSITX_0] =		    {
		.powerdomain	= J7200_PSC_PD_PD_DSS,
		.dev_list	= dev_list_LPSC_CSITX_0,
		.flags		= LPSC_MODULE_EXISTS | LPSC_DEVICES_LIST,
	},
	[J7200_PSC_LPSC_LPSC_TX_DPHY_0] =	    {
		.powerdomain	= J7200_PSC_PD_PD_DSS,
		.dev_list	= dev_list_LPSC_TX_DPHY_0,
		.flags		= LPSC_MODULE_EXISTS | LPSC_DEVICES_LIST,
	},
	[J7200_PSC_LPSC_LPSC_CSIRX_PHY_0] =	    {
		.powerdomain		= J7200_PSC_PD_PD_DSS,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_USB_2,
		.dev_list		= dev_list_LPSC_CSIRX_PHY_0,
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS | LPSC_DEVICES_LIST,
	},
	[J7200_PSC_LPSC_LPSC_CSIRX_PHY_1] =	    {
		.powerdomain	= J7200_PSC_PD_PD_DSS,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_CSIRX_PHY_2] =	    {
		.powerdomain	= J7200_PSC_PD_PD_DSS,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_ICSSG_0] =		    {
		.powerdomain	= J7200_PSC_PD_PD_ICSS,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_ICSSG_1] =		    {
		.powerdomain	= J7200_PSC_PD_PD_ICSS,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_9GSS] =		    {
		.powerdomain	= J7200_PSC_PD_PD_9GSS,
		.dev_array	=		    {
			J7200_DEV_CPSW0,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_SERDES_0] =	    {
		.powerdomain	= J7200_PSC_PD_PD_SERDES_0,
		.dev_array	=		    {
			J7200_DEV_SERDES_10G1,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_SERDES_1] =	    {
		.powerdomain	= J7200_PSC_PD_PD_SERDES_1,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_SERDES_2] =	    {
		.powerdomain	= J7200_PSC_PD_PD_SERDES_2,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_SERDES_3] =	    {
		.powerdomain	= J7200_PSC_PD_PD_SERDES_3,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_SERDES_4] =	    {
		.powerdomain	= J7200_PSC_PD_PD_SERDES_4,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_SERDES_5] =	    {
		.powerdomain	= J7200_PSC_PD_PD_SERDES_5,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_DMTIMER_0] =	    {
		.powerdomain		= J7200_PSC_PD_PD_TIMER,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_USB_2,
		.dev_array		=	    {
			J7200_DEV_TIMER0,
			DEV_ID_NONE,
		},
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS,
	},
	[J7200_PSC_LPSC_LPSC_DMTIMER_1] =	    {
		.powerdomain		= J7200_PSC_PD_PD_TIMER,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_USB_2,
		.dev_array		=	    {
			J7200_DEV_TIMER1,
			DEV_ID_NONE,
		},
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS,
	},
	[J7200_PSC_LPSC_LPSC_DMTIMER_2] =	    {
		.powerdomain		= J7200_PSC_PD_PD_TIMER,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_USB_2,
		.dev_array		=	    {
			J7200_DEV_TIMER2,
			DEV_ID_NONE,
		},
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS,
	},
	[J7200_PSC_LPSC_LPSC_DMTIMER_3] =	    {
		.powerdomain		= J7200_PSC_PD_PD_TIMER,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_USB_2,
		.dev_array		=	    {
			J7200_DEV_TIMER3,
			DEV_ID_NONE,
		},
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS,
	},
	[J7200_PSC_LPSC_LPSC_C71X_0] =		    {
		.powerdomain	= J7200_PSC_PD_PD_C71X_0,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_C71X_0_PBIST] =	    {
		.powerdomain	= J7200_PSC_PD_PD_C71X_0,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_C71X_1] =		    {
		.powerdomain	= J7200_PSC_PD_PD_C71X_1,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_C71X_1_PBIST] =	    {
		.powerdomain	= J7200_PSC_PD_PD_C71X_1,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_A72_CLUSTER_0] =	    {
		.powerdomain	= J7200_PSC_PD_PD_A72_CLUSTER_0,
		.dev_array	=		    {
			J7200_DEV_A72SS0,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_A72_CLUSTER_0_PBIST] = {
		.powerdomain		= J7200_PSC_PD_PD_A72_CLUSTER_0,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_A72_CLUSTER_0,
		.dev_array		=	    {
			J7200_DEV_A72SS0,
			J7200_DEV_COMPUTE_CLUSTER0_PBIST_WRAP,
		},
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS,
	},
	[J7200_PSC_LPSC_LPSC_A72_0] =		    {
		.powerdomain		= J7200_PSC_PD_PD_A72_0,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_A72_CLUSTER_0,
		.dev_array		=	    {
			J7200_DEV_A72SS0_CORE0,
			J7200_DEV_RTI0,
		},
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS | LPSC_HAS_LOCAL_RESET | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_A72_1] =		    {
		.powerdomain		= J7200_PSC_PD_PD_A72_1,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_A72_CLUSTER_0,
		.dev_array		=	    {
			J7200_DEV_A72SS0_CORE1,
			J7200_DEV_RTI1,
		},
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS | LPSC_HAS_LOCAL_RESET | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_A72_CLUSTER_1] =	    {
		.powerdomain	= J7200_PSC_PD_PD_A72_CLUSTER_1,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_A72_CLUSTER_1_PBIST] = {
		.powerdomain	= J7200_PSC_PD_PD_A72_CLUSTER_1,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_A72_2] =		    {
		.powerdomain	= J7200_PSC_PD_PD_A72_2,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_A72_3] =		    {
		.powerdomain	= J7200_PSC_PD_PD_A72_3,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_GPUCOM] =		    {
		.powerdomain	= J7200_PSC_PD_PD_GPUCOM,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_GPUPBIST] =	    {
		.powerdomain	= J7200_PSC_PD_PD_GPUCOM,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_GPUCORE] =		    {
		.powerdomain	= J7200_PSC_PD_PD_GPUCORE,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_C66X_0] =		    {
		.powerdomain	= J7200_PSC_PD_PD_C66X_0,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_C66X_PBIST_0] =	    {
		.powerdomain	= J7200_PSC_PD_PD_C66X_0,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_C66X_1] =		    {
		.powerdomain	= J7200_PSC_PD_PD_C66X_1,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_C66X_PBIST_1] =	    {
		.powerdomain	= J7200_PSC_PD_PD_C66X_1,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_PULSAR_0_R5_0] =	    {
		.powerdomain	= J7200_PSC_PD_PD_PULSAR_0,
		.dev_array	=		    {
			J7200_DEV_R5FSS0_CORE0,
			J7200_DEV_RTI28,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_HAS_LOCAL_RESET,
	},
	[J7200_PSC_LPSC_LPSC_PULSAR_0_R5_1] =	    {
		.powerdomain	= J7200_PSC_PD_PD_PULSAR_0,
		.dev_array	=		    {
			J7200_DEV_R5FSS0_CORE1,
			J7200_DEV_RTI29,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_HAS_LOCAL_RESET,
	},
	[J7200_PSC_LPSC_LPSC_PULSAR_PBIST_0] =	    {
		.powerdomain		= J7200_PSC_PD_PD_PULSAR_0,
		.depends_psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.depends		= J7200_PSC_LPSC_LPSC_PULSAR_0_R5_1,
		.dev_array		=	    {
			J7200_DEV_PBIST2,
			DEV_ID_NONE,
		},
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS,
	},
	[J7200_PSC_LPSC_LPSC_PULSAR_1_R5_0] =	    {
		.powerdomain	= J7200_PSC_PD_PD_PULSAR_1,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_PULSAR_1_R5_1] =	    {
		.powerdomain	= J7200_PSC_PD_PD_PULSAR_1,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_PULSAR_PBIST_1] =	    {
		.powerdomain	= J7200_PSC_PD_PD_PULSAR_1,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_DECODE_0] =	    {
		.powerdomain	= J7200_PSC_PD_PD_DECODE_0,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_DECODE_PBIST] =	    {
		.powerdomain	= J7200_PSC_PD_PD_DECODE_0,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_ENCODE_0] =	    {
		.powerdomain	= J7200_PSC_PD_PD_ENCODE_0,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_ENCODE_PBIST] =	    {
		.powerdomain	= J7200_PSC_PD_PD_ENCODE_0,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_DMPAC] =		    {
		.powerdomain	= J7200_PSC_PD_PD_DMPAC,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_SDE] =		    {
		.powerdomain	= J7200_PSC_PD_PD_DMPAC,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_DMPAC_PBIST] =	    {
		.powerdomain	= J7200_PSC_PD_PD_DMPAC,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_VPAC] =		    {
		.powerdomain	= J7200_PSC_PD_PD_VPAC,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_VPAC_PBIST] =	    {
		.powerdomain	= J7200_PSC_PD_PD_VPAC,
		.dev_array	=		    {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
};
static struct lpsc_module j7200_j7_main_psc_wrap_main_0_modules[ARRAY_SIZE(j7200_j7_main_psc_wrap_main_0_mod_data)] __attribute__((__section__(".bss.devgroup.MAIN")));
static const u8 j7200_dev_j7_main_psc_wrap_main_0_resources[] __attribute__((__section__(".const.devgroup.MAIN"))) = {
	RDAT_HDR(RESOURCE_MEM, 1, STRUE),
	RDAT_MEM(0x00400000),
};
static const struct psc_drv_data j7200_dev_j7_main_psc_wrap_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.data					= &j7200_j7_main_psc_wrap_main_0_data,
	.pd_data				= j7200_j7_main_psc_wrap_main_0_pd_data,
	.powerdomains				= j7200_j7_main_psc_wrap_main_0_powerdomains,
	.pd_count				= ARRAY_SIZE(j7200_j7_main_psc_wrap_main_0_pd_data),
	.mod_data				= j7200_j7_main_psc_wrap_main_0_mod_data,
	.modules				= j7200_j7_main_psc_wrap_main_0_modules,
	.module_count				= ARRAY_SIZE(j7200_j7_main_psc_wrap_main_0_mod_data),
	.psc_idx				= 0,
	.drv_data				= {
		.dev_data			= {
			.soc			= {
				.psc_idx	= PSC_DEV_NONE,
			},
			.dev_clk_idx		= J7200_DEV_J7_MAIN_PSC_WRAP_MAIN_0_CLOCKS,
			.n_clocks		= 2,
			.pm_devgrp		= PM_DEVGRP_01,
			.flags			= DEVD_FLAG_DO_INIT | DEVD_FLAG_DRV_DATA,
		},
		.drv				= &psc_drv,
		.r				= (const struct resource *) j7200_dev_j7_main_psc_wrap_main_0_resources,
	},
};
static const struct dev_data j7200_dev_j7_timesync_event_introuter_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_VPFE,
	},
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_j7_wkup_gpiomux_introuter_wkup_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.pm_devgrp		= PM_DEVGRP_00,
};
static struct psc_data j7200_j7_wkup_psc_wrap_wkup_0_data __attribute__((__section__(".bss.devgroup.MCU_WAKEUP")));
static const struct psc_pd_data j7200_j7_wkup_psc_wrap_wkup_0_pd_data[] __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	[J7200_PSC_PD_PD_WKUP] =       {
		.flags	= PSC_PD_EXISTS,
	},
	[J7200_PSC_PD_PD_MCU_PULSAR] = {
		.flags	= PSC_PD_EXISTS,
	},
};
static struct psc_pd j7200_j7_wkup_psc_wrap_wkup_0_powerdomains[ARRAY_SIZE(j7200_j7_wkup_psc_wrap_wkup_0_pd_data)] __attribute__((__section__(".bss.devgroup.MCU_WAKEUP")));
static const dev_idx_t dev_list_LPSC_wkup_alwayson[] __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	J7200_DEV_MCU_CPSW0,
	J7200_DEV_MCU_CPT2_AGGR0,
	J7200_DEV_MCU_DCC0,
	J7200_DEV_MCU_DCC1,
	J7200_DEV_MCU_DCC2,
	J7200_DEV_MCU_TIMER0,
	J7200_DEV_MCU_TIMER1,
	J7200_DEV_MCU_TIMER2,
	J7200_DEV_MCU_TIMER3,
	J7200_DEV_MCU_TIMER4,
	J7200_DEV_MCU_TIMER5,
	J7200_DEV_MCU_TIMER6,
	J7200_DEV_MCU_TIMER7,
	J7200_DEV_MCU_TIMER8,
	J7200_DEV_MCU_TIMER9,
	J7200_DEV_WKUP_ESM0,
	J7200_DEV_MCU_ESM0,
	J7200_DEV_MCU_FSS0_FSAS_0,
	J7200_DEV_MCU_FSS0_HYPERBUS1P0_0,
	J7200_DEV_MCU_FSS0_OSPI_0,
	J7200_DEV_MCU_FSS0_OSPI_1,
	J7200_DEV_WKUP_GPIOMUX_INTRTR0,
	J7200_DEV_WKUP_DDPA0,
	J7200_DEV_WKUP_VTM0,
	J7200_DEV_MCU_I2C0,
	J7200_DEV_MCU_I2C1,
	J7200_DEV_MCU_NAVSS0_INTR_0,
	J7200_DEV_MCU_NAVSS0_MCRC_0,
	J7200_DEV_MCU_NAVSS0_MODSS,
	J7200_DEV_MCU_NAVSS0_PROXY0,
	J7200_DEV_MCU_NAVSS0_RINGACC0,
	J7200_DEV_MCU_NAVSS0_UDMAP_0,
	J7200_DEV_MCU_NAVSS0_UDMASS,
	J7200_DEV_MCU_NAVSS0_UDMASS_INTA_0,
	J7200_DEV_MCU_SA2_UL0,
	J7200_DEV_MCU_MCSPI0,
	J7200_DEV_MCU_MCSPI1,
	J7200_DEV_MCU_MCSPI2,
	J7200_DEV_MCU_UART0,
	DEV_ID_NONE,
};
static const dev_idx_t dev_list_LPSC_wkup_gpio[] __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	J7200_DEV_WKUP_GPIO0,
	J7200_DEV_WKUP_GPIO1,
	J7200_DEV_WKUP_I2C0,
	J7200_DEV_WKUP_UART0,
	DEV_ID_NONE,
};
static const struct lpsc_module_data j7200_j7_wkup_psc_wrap_wkup_0_mod_data[] __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	[J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON] =	   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_list	= dev_list_LPSC_wkup_alwayson,
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING | LPSC_NO_MODULE_RESET | LPSC_DEVICES_LIST,
	},
	[J7200_PSC_LPSC_LPSC_DMSC] =		   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_array	=		   {
			J7200_DEV_WKUP_DMSC0,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_HAS_LOCAL_RESET,
	},
	[J7200_PSC_LPSC_LPSC_DEBUG2DMSC] =	   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_array	=		   {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING | LPSC_NO_MODULE_RESET,
	},
	[J7200_PSC_LPSC_LPSC_WKUP_GPIO] =	   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_list	= dev_list_LPSC_wkup_gpio,
		.flags		= LPSC_MODULE_EXISTS | LPSC_DEVICES_LIST,
	},
	[J7200_PSC_LPSC_LPSC_WKUPMCU2MAIN] =	   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_array	=		   {
			J7200_DEV_WKUPMCU2MAIN_VD,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING | LPSC_NO_MODULE_RESET,
	},
	[J7200_PSC_LPSC_LPSC_MAIN2WKUPMCU] =	   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_array	=		   {
			J7200_DEV_MAIN2WKUPMCU_VD,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING | LPSC_NO_MODULE_RESET,
	},
	[J7200_PSC_LPSC_LPSC_MCU_TEST] =	   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_array	=		   {
			J7200_DEV_MCU_PBIST0,
			J7200_DEV_MCU_PBIST1,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MCU_DEBUG] =	   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_array	=		   {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING | LPSC_NO_MODULE_RESET,
	},
	[J7200_PSC_LPSC_LPSC_MCU_MCAN_0] =	   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_array	=		   {
			J7200_DEV_MCU_MCAN0,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MCU_MCAN_1] =	   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_array	=		   {
			J7200_DEV_MCU_MCAN1,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MCU_OSPI_0] =	   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_array	=		   {
			J7200_DEV_MCU_FSS0_OSPI_0,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MCU_OSPI_1] =	   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_array	=		   {
			J7200_DEV_MCU_FSS0_OSPI_1,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_MCU_HYPERBUS] =	   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_array	=		   {
			J7200_DEV_MCU_FSS0_HYPERBUS1P0_0,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MCU_I3C_0] =	   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_array	=		   {
			J7200_DEV_MCU_I3C0,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MCU_I3C_1] =	   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_array	=		   {
			J7200_DEV_MCU_I3C1,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_MCU_ADC_0] =	   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_array	=		   {
			J7200_DEV_MCU_ADC0,
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS,
	},
	[J7200_PSC_LPSC_LPSC_MCU_ADC_1] =	   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_array	=		   {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_WKUP_SPARE0] =	   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_array	=		   {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_WKUP_SPARE1] =	   {
		.powerdomain	= J7200_PSC_PD_PD_WKUP,
		.dev_array	=		   {
			DEV_ID_NONE,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_NO_CLOCK_GATING,
	},
	[J7200_PSC_LPSC_LPSC_MCU_R5_0] =	   {
		.powerdomain	= J7200_PSC_PD_PD_MCU_PULSAR,
		.dev_array	=		   {
			J7200_DEV_MCU_R5FSS0_CORE0,
			J7200_DEV_MCU_RTI0,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_HAS_LOCAL_RESET,
	},
	[J7200_PSC_LPSC_LPSC_MCU_R5_1] =	   {
		.powerdomain	= J7200_PSC_PD_PD_MCU_PULSAR,
		.dev_array	=		   {
			J7200_DEV_MCU_R5FSS0_CORE1,
			J7200_DEV_MCU_RTI1,
		},
		.flags		= LPSC_MODULE_EXISTS | LPSC_HAS_LOCAL_RESET,
	},
	[J7200_PSC_LPSC_LPSC_MCU_PULSAR_PBIST_0] = {
		.powerdomain		= J7200_PSC_PD_PD_MCU_PULSAR,
		.depends_psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.depends		= J7200_PSC_LPSC_LPSC_MCU_R5_1,
		.dev_array		=	   {
			J7200_DEV_MCU_PBIST2,
			DEV_ID_NONE,
		},
		.flags			= LPSC_MODULE_EXISTS | LPSC_DEPENDS,
	},
};
static struct lpsc_module j7200_j7_wkup_psc_wrap_wkup_0_modules[ARRAY_SIZE(j7200_j7_wkup_psc_wrap_wkup_0_mod_data)] __attribute__((__section__(".bss.devgroup.MCU_WAKEUP")));
static const u8 j7200_dev_j7_wkup_psc_wrap_wkup_0_resources[] __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	RDAT_HDR(RESOURCE_MEM, 1, STRUE),
	RDAT_MEM(0x42000000),
};
static const struct psc_drv_data j7200_dev_j7_wkup_psc_wrap_wkup_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.data					= &j7200_j7_wkup_psc_wrap_wkup_0_data,
	.pd_data				= j7200_j7_wkup_psc_wrap_wkup_0_pd_data,
	.powerdomains				= j7200_j7_wkup_psc_wrap_wkup_0_powerdomains,
	.pd_count				= ARRAY_SIZE(j7200_j7_wkup_psc_wrap_wkup_0_pd_data),
	.mod_data				= j7200_j7_wkup_psc_wrap_wkup_0_mod_data,
	.modules				= j7200_j7_wkup_psc_wrap_wkup_0_modules,
	.module_count				= ARRAY_SIZE(j7200_j7_wkup_psc_wrap_wkup_0_mod_data),
	.psc_idx				= 1,
	.drv_data				= {
		.dev_data			= {
			.soc			= {
				.psc_idx	= PSC_DEV_NONE,
			},
			.dev_clk_idx		= J7200_DEV_J7_WKUP_PSC_WRAP_WKUP_0_CLOCKS,
			.n_clocks		= 2,
			.pm_devgrp		= PM_DEVGRP_00,
			.flags			= DEVD_FLAG_DO_INIT | DEVD_FLAG_DRV_DATA,
		},
		.drv				= &psc_drv,
		.r				= (const struct resource *) j7200_dev_j7_wkup_psc_wrap_wkup_0_resources,
	},
};
static const struct dev_data j7200_dev_k3_pbist_8c28p_wrap_main_infra_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_PBIST,
	},
	.dev_clk_idx		= J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_0_CLOCKS,
	.n_clocks		= 10,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_k3_pbist_8c28p_wrap_main_infra_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_PBIST,
	},
	.dev_clk_idx		= J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_1_CLOCKS,
	.n_clocks		= 10,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_k3_pbist_8c28p_wrap_main_pulsar_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_PULSAR_0,
		.mod		= J7200_PSC_LPSC_LPSC_PULSAR_PBIST_0,
	},
	.dev_clk_idx		= J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_PULSAR_0_CLOCKS,
	.n_clocks		= 10,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_k3_pbist_8c28p_wrap_mcu_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_MCU_TEST,
	},
	.dev_clk_idx		= J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_0_CLOCKS,
	.n_clocks		= 10,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_k3_pbist_8c28p_wrap_mcu_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_MCU_TEST,
	},
	.dev_clk_idx		= J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_1_CLOCKS,
	.n_clocks		= 10,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_k3_pbist_8c28p_wrap_mcu_pulsar_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_MCU_PULSAR,
		.mod		= J7200_PSC_LPSC_LPSC_MCU_PULSAR_PBIST_0,
	},
	.dev_clk_idx		= J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_PULSAR_0_CLOCKS,
	.n_clocks		= 10,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_k3_ddpa_wkup_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_K3_DDPA_WKUP_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_usart_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_CSIRX_1,
	},
	.dev_clk_idx		= J7200_DEV_USART_MAIN_0_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_usart_mcu_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_USART_MCU_0_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_mcanss_main_14 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_DSS,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MAIN_14_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mcanss_main_15 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_DSS_PBIST,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MAIN_15_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mcanss_main_16 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_DSI,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MAIN_16_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mcanss_main_17 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_EDP_0,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MAIN_17_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_k3vtm_n16ffc_wkup_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_K3VTM_N16FFC_WKUP_0_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_main2wkupmcu_VD __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN2WKUPMCU,
	},
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_mcanss_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_MCANSS,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_MCANSS_0,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MAIN_0_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_board_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.dev_clk_idx		= J7200_DEV_BOARD_0_CLOCKS,
	.n_clocks		= 109,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_mcanss_main_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_MCANSS,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_MCANSS_1,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MAIN_1_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mcanss_main_2 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_MCANSS,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_MCANSS_2,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MAIN_2_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mcanss_main_3 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_MCANSS,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_MCANSS_3,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MAIN_3_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mcanss_main_4 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_MCANSS,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_MCANSS_4,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MAIN_4_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mcanss_main_5 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_MCANSS,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_MCANSS_5,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MAIN_5_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mcanss_main_6 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_MCANSS,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_MCANSS_6,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MAIN_6_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mcanss_main_7 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_MCANSS,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_MCANSS_7,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MAIN_7_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mcanss_main_8 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_MCANSS,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_MCANSS_8,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MAIN_8_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mcanss_main_9 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_MCANSS,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_MCANSS_9,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MAIN_9_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mcanss_main_10 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_MCANSS,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_MCANSS_10,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MAIN_10_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mcanss_main_11 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_MCANSS,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_MCANSS_11,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MAIN_11_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mcanss_main_12 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_MCANSS,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_MCANSS_12,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MAIN_12_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mcanss_main_13 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_MCANSS,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_MCANSS_13,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MAIN_13_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mcanss_mcu_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_MCU_MCAN_0,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MCU_0_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_mcanss_mcu_1 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_MCU_MCAN_1,
	},
	.dev_clk_idx		= J7200_DEV_MCANSS_MCU_1_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_mcasp_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_AUDIO,
	},
	.dev_clk_idx		= J7200_DEV_MCASP_MAIN_0_CLOCKS,
	.n_clocks		= 12,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mcasp_main_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_AUDIO,
	},
	.dev_clk_idx		= J7200_DEV_MCASP_MAIN_1_CLOCKS,
	.n_clocks		= 12,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mcasp_main_2 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_AUDIO,
	},
	.dev_clk_idx		= J7200_DEV_MCASP_MAIN_2_CLOCKS,
	.n_clocks		= 12,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mshsi2c_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_MISCIO,
	},
	.dev_clk_idx		= J7200_DEV_MSHSI2C_MAIN_0_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mshsi2c_main_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_TX_DPHY_0,
	},
	.dev_clk_idx		= J7200_DEV_MSHSI2C_MAIN_1_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mshsi2c_main_2 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_TX_DPHY_0,
	},
	.dev_clk_idx		= J7200_DEV_MSHSI2C_MAIN_2_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mshsi2c_main_3 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_TX_DPHY_0,
	},
	.dev_clk_idx		= J7200_DEV_MSHSI2C_MAIN_3_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mshsi2c_main_4 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_CSIRX_PHY_0,
	},
	.dev_clk_idx		= J7200_DEV_MSHSI2C_MAIN_4_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mshsi2c_main_5 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_CSIRX_PHY_0,
	},
	.dev_clk_idx		= J7200_DEV_MSHSI2C_MAIN_5_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mshsi2c_main_6 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_CSIRX_PHY_0,
	},
	.dev_clk_idx		= J7200_DEV_MSHSI2C_MAIN_6_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_mshsi2c_mcu_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_MSHSI2C_MCU_0_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_mshsi2c_mcu_1 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_MSHSI2C_MCU_1_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_mshsi2c_wkup_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_GPIO,
	},
	.dev_clk_idx		= J7200_DEV_MSHSI2C_WKUP_0_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_navss256vcl_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PER_MLB,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_cpts_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_CPTS_0_CLOCKS,
	.n_clocks		= 6,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_p0_a72_dual_1mb_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_A72_0,
		.mod		= J7200_PSC_LPSC_LPSC_A72_0,
	},
	.dev_clk_idx		= J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_P0_A72_DUAL_1MB_0_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_p0_a72_dual_1mb_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_A72_1,
		.mod		= J7200_PSC_LPSC_LPSC_A72_1,
	},
	.dev_clk_idx		= J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_P0_A72_DUAL_1MB_1_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_dti_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_DTI_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_modss_inta_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_MODSS_INTA_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_modss_inta_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_MODSS_INTA_1_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_udmass_inta_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_UDMASS_INTA_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_proxy_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_PROXY_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_ringacc_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_RINGACC_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_udmap_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_UDMAP_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_intr_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_INTR_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_mailbox_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_mailbox_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_1_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_mailbox_2 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_2_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_mailbox_3 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_3_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_mailbox_4 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_4_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_mailbox_5 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_5_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_mailbox_6 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_6_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_mailbox_7 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_7_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_mailbox_8 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_8_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_mailbox_9 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_9_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_mailbox_10 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_10_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_mailbox_11 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_11_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_spinlock_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_SPINLOCK_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_mcrc_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_MCRC_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_tbu_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_TBU_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_timermgr_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_TIMERMGR_0_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_timermgr_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_TIMERMGR_1_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss_mcu_j7_mcu_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_navss_mcu_j7_mcu_0_udmass_inta_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS_MCU_J7_MCU_0_UDMASS_INTA_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_navss_mcu_j7_mcu_0_proxy_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS_MCU_J7_MCU_0_PROXY_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_navss_mcu_j7_mcu_0_ringacc_0 __attribute__((__section__(".const.devgroup.DMSC_INTERNAL"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS_MCU_J7_MCU_0_RINGACC_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_DMSC,
};
static const struct dev_data j7200_dev_navss_mcu_j7_mcu_0_udmap_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS_MCU_J7_MCU_0_UDMAP_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_navss_mcu_j7_mcu_0_intr_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS_MCU_J7_MCU_0_INTR_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_navss_mcu_j7_mcu_0_mcrc_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS_MCU_J7_MCU_0_MCRC_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_pcie_g3x4_128_main_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_PCIE_1,
	},
	.dev_clk_idx		= J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,
	.n_clocks		= 28,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_pulsar_sl_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_pulsar_sl_main_0_R5_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_PULSAR_0,
		.mod		= J7200_PSC_LPSC_LPSC_PULSAR_0_R5_0,
	},
	.dev_clk_idx		= J7200_DEV_PULSAR_SL_MAIN_0_R5_0_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_pulsar_sl_main_0_R5_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_PULSAR_0,
		.mod		= J7200_PSC_LPSC_LPSC_PULSAR_0_R5_1,
	},
	.dev_clk_idx		= J7200_DEV_PULSAR_SL_MAIN_0_R5_1_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_pulsar_sl_mcu_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_pulsar_sl_mcu_0_R5_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_MCU_PULSAR,
		.mod		= J7200_PSC_LPSC_LPSC_MCU_R5_0,
	},
	.dev_clk_idx		= J7200_DEV_PULSAR_SL_MCU_0_R5_0_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_pulsar_sl_mcu_0_R5_1 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_MCU_PULSAR,
		.mod		= J7200_PSC_LPSC_LPSC_MCU_R5_1,
	},
	.dev_clk_idx		= J7200_DEV_PULSAR_SL_MCU_0_R5_1_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_rti_cfg1_main_a72_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_A72_0,
		.mod		= J7200_PSC_LPSC_LPSC_A72_0,
	},
	.dev_clk_idx		= J7200_DEV_RTI_CFG1_MAIN_A72_0_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_rti_cfg1_main_a72_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_A72_1,
		.mod		= J7200_PSC_LPSC_LPSC_A72_1,
	},
	.dev_clk_idx		= J7200_DEV_RTI_CFG1_MAIN_A72_1_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_rti_cfg1_main_r5_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_PULSAR_0,
		.mod		= J7200_PSC_LPSC_LPSC_PULSAR_0_R5_0,
	},
	.dev_clk_idx		= J7200_DEV_RTI_CFG1_MAIN_R5_0_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_rti_cfg1_main_r5_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_PULSAR_0,
		.mod		= J7200_PSC_LPSC_LPSC_PULSAR_0_R5_1,
	},
	.dev_clk_idx		= J7200_DEV_RTI_CFG1_MAIN_R5_1_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_rti_cfg1_mcu_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_MCU_PULSAR,
		.mod		= J7200_PSC_LPSC_LPSC_MCU_R5_0,
	},
	.dev_clk_idx		= J7200_DEV_RTI_CFG1_MCU_0_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_rti_cfg1_mcu_1 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_MCU_PULSAR,
		.mod		= J7200_PSC_LPSC_LPSC_MCU_R5_1,
	},
	.dev_clk_idx		= J7200_DEV_RTI_CFG1_MCU_1_CLOCKS,
	.n_clocks		= 2,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_sa2_ul_mcu_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_SA2_UL_MCU_0_CLOCKS,
	.n_clocks		= 3,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_spi_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_EDP_1,
	},
	.dev_clk_idx		= J7200_DEV_SPI_MAIN_0_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_spi_main_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_EDP_1,
	},
	.dev_clk_idx		= J7200_DEV_SPI_MAIN_1_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_spi_main_2 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_EDP_1,
	},
	.dev_clk_idx		= J7200_DEV_SPI_MAIN_2_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_spi_main_3 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_EDP_1,
	},
	.dev_clk_idx		= J7200_DEV_SPI_MAIN_3_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_spi_main_4 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_CSIRX_0,
	},
	.dev_clk_idx		= J7200_DEV_SPI_MAIN_4_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_spi_main_5 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_CSIRX_0,
	},
	.dev_clk_idx		= J7200_DEV_SPI_MAIN_5_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_spi_main_6 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_CSIRX_0,
	},
	.dev_clk_idx		= J7200_DEV_SPI_MAIN_6_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_spi_main_7 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_CSIRX_0,
	},
	.dev_clk_idx		= J7200_DEV_SPI_MAIN_7_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_spi_mcu_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_SPI_MCU_0_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_spi_mcu_1 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_SPI_MCU_1_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_spi_mcu_2 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_SPI_MCU_2_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_usart_main_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_CSIRX_1,
	},
	.dev_clk_idx		= J7200_DEV_USART_MAIN_1_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_usart_main_2 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_CSIRX_2,
	},
	.dev_clk_idx		= J7200_DEV_USART_MAIN_2_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_usart_main_3 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_CSIRX_2,
	},
	.dev_clk_idx		= J7200_DEV_USART_MAIN_3_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_usart_main_4 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_CSITX_0,
	},
	.dev_clk_idx		= J7200_DEV_USART_MAIN_4_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_usart_main_5 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_CSITX_0,
	},
	.dev_clk_idx		= J7200_DEV_USART_MAIN_5_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_usart_main_6 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_CSITX_0,
	},
	.dev_clk_idx		= J7200_DEV_USART_MAIN_6_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_usart_main_7 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_CSITX_0,
	},
	.dev_clk_idx		= J7200_DEV_USART_MAIN_7_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_usart_main_8 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_CSITX_0,
	},
	.dev_clk_idx		= J7200_DEV_USART_MAIN_8_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_usart_main_9 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_DSS,
		.mod		= J7200_PSC_LPSC_LPSC_CSITX_0,
	},
	.dev_clk_idx		= J7200_DEV_USART_MAIN_9_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_usart_wkup_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_GPIO,
	},
	.dev_clk_idx		= J7200_DEV_USART_WKUP_0_CLOCKS,
	.n_clocks		= 4,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_usb3p0ss_16ffc_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_USB_0,
	},
	.dev_clk_idx		= J7200_DEV_USB3P0SS_16FFC_MAIN_0_CLOCKS,
	.n_clocks		= 14,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_wiz16b8m4ct2_main_1 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_PD_SERDES_0,
		.mod		= J7200_PSC_LPSC_LPSC_SERDES_0,
	},
	.dev_clk_idx		= J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,
	.n_clocks		= 123,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_wkupmcu2main_VD __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUPMCU2MAIN,
	},
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_modss_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_MODSS_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_udmass_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_UDMASS_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss256vcl_main_0_virtss_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS256VCL_MAIN_0_VIRTSS_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_navss_mcu_j7_mcu_0_modss_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS_MCU_J7_MCU_0_MODSS_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_navss_mcu_j7_mcu_0_udmass_0 __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_WKUP_PSC_WRAP_WKUP_0,
		.pd		= J7200_PSC_PD_PD_WKUP,
		.mod		= J7200_PSC_LPSC_LPSC_WKUP_ALWAYSON,
	},
	.dev_clk_idx		= J7200_DEV_NAVSS_MCU_J7_MCU_0_UDMASS_0_CLOCKS,
	.n_clocks		= 1,
	.pm_devgrp		= PM_DEVGRP_00,
};
static const struct dev_data j7200_dev_debugss_k3_wrap_cv0_main_0 __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_MAIN_DEBUG,
	},
	.dev_clk_idx		= J7200_DEV_DEBUGSS_K3_WRAP_CV0_MAIN_0_CLOCKS,
	.n_clocks		= 50,
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_ffi_main_infra_cbass_VD __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= PSC_DEV_NONE,
	},
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_ffi_main_ip_cbass_VD __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_USB_2,
	},
	.pm_devgrp		= PM_DEVGRP_01,
};
static const struct dev_data j7200_dev_ffi_main_rc_cbass_VD __attribute__((__section__(".const.devgroup.MAIN"))) = {
	.soc			= {
		.psc_idx	= J7200_PSC_INST_J7_MAIN_PSC_WRAP_MAIN_0,
		.pd		= J7200_PSC_PD_GP_CORE_CTL,
		.mod		= J7200_PSC_LPSC_LPSC_UFS_1,
	},
	.pm_devgrp		= PM_DEVGRP_01,
};

static const struct dev_clk_data MCU_WAKEUP_dev_clk_data[] __attribute__((__section__(".const.devgroup.MCU_WAKEUP"))) = {
	DEV_CLK(J7200_DEV_ADC12_CORE_MCU_0_CLOCKS,		   J7200_DEV_MCU_ADC0_ADC_CLK,			       CLK_J7200_MCU_ADC_CLK_SEL_OUT0,
		1),
	DEV_CLK(J7200_DEV_ADC12_CORE_MCU_0_CLOCKS,		   J7200_DEV_MCU_ADC0_SYS_CLK,			       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK(J7200_DEV_ADC12_CORE_MCU_0_CLOCKS,		   J7200_DEV_MCU_ADC0_VBUS_CLK,			       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		3),
	DEV_CLK(J7200_DEV_ADC12_CORE_MCU_1_CLOCKS,		   J7200_DEV_MCU_ADC1_ADC_CLK,			       CLK_J7200_MCU_ADC_CLK_SEL_OUT1,
		1),
	DEV_CLK(J7200_DEV_ADC12_CORE_MCU_1_CLOCKS,		   J7200_DEV_MCU_ADC1_SYS_CLK,			       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK(J7200_DEV_ADC12_CORE_MCU_1_CLOCKS,		   J7200_DEV_MCU_ADC1_VBUS_CLK,			       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		3),
	DEV_CLK(J7200_DEV_CPSW_2GUSS_MCU_0_CLOCKS,		   J7200_DEV_MCU_CPSW0_CPPI_CLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		3),
	DEV_CLK(J7200_DEV_CPSW_2GUSS_MCU_0_CLOCKS,		   J7200_DEV_MCU_CPSW0_CPTS_RFT_CLK,		       CLK_J7200_CPSW2G_CPTS_RCLK_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_CPSW_2GUSS_MCU_0_CLOCKS,		   J7200_DEV_MCU_CPSW0_GMII1_MR_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT0_CLK,
		10),
	DEV_CLK(J7200_DEV_CPSW_2GUSS_MCU_0_CLOCKS,		   J7200_DEV_MCU_CPSW0_GMII1_MT_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT0_CLK,
		10),
	DEV_CLK(J7200_DEV_CPSW_2GUSS_MCU_0_CLOCKS,		   J7200_DEV_MCU_CPSW0_GMII_RFT_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT0_CLK,
		2),
	DEV_CLK(J7200_DEV_CPSW_2GUSS_MCU_0_CLOCKS,		   J7200_DEV_MCU_CPSW0_RGMII1_RXC_I,		       CLK_J7200_BOARD_0_MCU_RGMII1_RXC_OUT,
		1),
	DEV_CLK(J7200_DEV_CPSW_2GUSS_MCU_0_CLOCKS,		   J7200_DEV_MCU_CPSW0_RGMII_MHZ_250_CLK,	       CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_2GUSS_MCU_0_CLOCKS,		   J7200_DEV_MCU_CPSW0_RGMII_MHZ_50_CLK,	       CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT0_CLK,
		5),
	DEV_CLK(J7200_DEV_CPSW_2GUSS_MCU_0_CLOCKS,		   J7200_DEV_MCU_CPSW0_RGMII_MHZ_5_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT0_CLK,
		50),
	DEV_CLK(J7200_DEV_CPSW_2GUSS_MCU_0_CLOCKS,		   J7200_DEV_MCU_CPSW0_RMII_MHZ_50_CLK,		       CLK_J7200_BOARD_0_MCU_RMII1_REF_CLK_OUT,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_CPSW_2GUSS_MCU_0_CLOCKS,	   J7200_DEV_MCU_CPSW0_CPTS_GENF0,		       CLK_J7200_CPSW_2GUSS_MCU_0_CPTS_GENF0),
	DEV_CLK_OUTPUT(J7200_DEV_CPSW_2GUSS_MCU_0_CLOCKS,	   J7200_DEV_MCU_CPSW0_MDIO_MDCLK_O,		       CLK_J7200_CPSW_2GUSS_MCU_0_MDIO_MDCLK_O),
	DEV_CLK_OUTPUT(J7200_DEV_CPSW_2GUSS_MCU_0_CLOCKS,	   J7200_DEV_MCU_CPSW0_RGMII1_TXC_O,		       CLK_J7200_CPSW_2GUSS_MCU_0_RGMII1_TXC_O),
	DEV_CLK(J7200_DEV_CPT2_AGGREGATOR32_MCU_0_CLOCKS,	   J7200_DEV_MCU_CPT2_AGGR0_VCLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		3),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_0_CLOCKS,		   J7200_DEV_MCU_TIMER0_TIMER_HCLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_0_CLOCKS,		   J7200_DEV_MCU_TIMER0_TIMER_TCLK_CLK,		       CLK_J7200_MCU_TIMER_CLKSEL_OUT0,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_DMTIMER_DMC1MS_MCU_0_CLOCKS,	   J7200_DEV_MCU_TIMER0_TIMER_PWM,		       CLK_J7200_DMTIMER_DMC1MS_MCU_0_TIMER_PWM),
	DEV_CLK(J7200_DEV_DCC2_MCU_0_CLOCKS,			   J7200_DEV_MCU_DCC0_DCC_CLKSRC0_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT0_CLK,
		2),
	DEV_CLK(J7200_DEV_DCC2_MCU_0_CLOCKS,			   J7200_DEV_MCU_DCC0_DCC_CLKSRC1_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT1_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_0_CLOCKS,			   J7200_DEV_MCU_DCC0_DCC_CLKSRC2_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT2_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_0_CLOCKS,			   J7200_DEV_MCU_DCC0_DCC_CLKSRC3_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT3_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_0_CLOCKS,			   J7200_DEV_MCU_DCC0_DCC_CLKSRC4_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT4_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_0_CLOCKS,			   J7200_DEV_MCU_DCC0_DCC_CLKSRC5_CLK,		       CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_32K_CLK,
		391),
	DEV_CLK(J7200_DEV_DCC2_MCU_0_CLOCKS,			   J7200_DEV_MCU_DCC0_DCC_CLKSRC6_CLK,		       CLK_J7200_BOARD_0_WKUP_LF_CLKIN_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_0_CLOCKS,			   J7200_DEV_MCU_DCC0_DCC_CLKSRC7_CLK,		       CLK_J7200_BOARD_0_MCU_EXT_REFCLK0_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_0_CLOCKS,			   J7200_DEV_MCU_DCC0_DCC_INPUT00_CLK,		       CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_0_CLOCKS,			   J7200_DEV_MCU_DCC0_DCC_INPUT01_CLK,		       CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_32K_CLK,
		391),
	DEV_CLK(J7200_DEV_DCC2_MCU_0_CLOCKS,			   J7200_DEV_MCU_DCC0_DCC_INPUT02_CLK,		       CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_0_CLOCKS,			   J7200_DEV_MCU_DCC0_DCC_INPUT10_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		3),
	DEV_CLK(J7200_DEV_DCC2_MCU_0_CLOCKS,			   J7200_DEV_MCU_DCC0_VBUS_CLK,			       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_DCC2_MCU_1_CLOCKS,			   J7200_DEV_MCU_DCC1_DCC_CLKSRC0_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT1_CLK,
		2),
	DEV_CLK(J7200_DEV_DCC2_MCU_1_CLOCKS,			   J7200_DEV_MCU_DCC1_DCC_CLKSRC1_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT2_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_1_CLOCKS,			   J7200_DEV_MCU_DCC1_DCC_CLKSRC2_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT3_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_1_CLOCKS,			   J7200_DEV_MCU_DCC1_DCC_CLKSRC3_CLK,		       CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT4_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_1_CLOCKS,			   J7200_DEV_MCU_DCC1_DCC_CLKSRC4_CLK,		       CLK_J7200_HSDIV1_16FFT_MCU_0_HSDIVOUT0_CLK,
		4),
	DEV_CLK(J7200_DEV_DCC2_MCU_1_CLOCKS,			   J7200_DEV_MCU_DCC1_DCC_CLKSRC5_CLK,		       CLK_J7200_HSDIV1_16FFT_MCU_0_HSDIVOUT1_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_1_CLOCKS,			   J7200_DEV_MCU_DCC1_DCC_CLKSRC6_CLK,		       CLK_J7200_BOARD_0_MCU_OSPI0_DQS_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_1_CLOCKS,			   J7200_DEV_MCU_DCC1_DCC_CLKSRC7_CLK,		       CLK_J7200_BOARD_0_MCU_CPTS0_RFT_CLK_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_1_CLOCKS,			   J7200_DEV_MCU_DCC1_DCC_INPUT00_CLK,		       CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_1_CLOCKS,			   J7200_DEV_MCU_DCC1_DCC_INPUT01_CLK,		       CLK_J7200_BOARD_0_WKUP_LF_CLKIN_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_1_CLOCKS,			   J7200_DEV_MCU_DCC1_DCC_INPUT02_CLK,		       CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_1_CLOCKS,			   J7200_DEV_MCU_DCC1_DCC_INPUT10_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_1_CLOCKS,			   J7200_DEV_MCU_DCC1_VBUS_CLK,			       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_DCC2_MCU_2_CLOCKS,			   J7200_DEV_MCU_DCC2_DCC_CLKSRC0_CLK,		       CLK_J7200_BOARD_0_MCU_RMII1_REF_CLK_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_2_CLOCKS,			   J7200_DEV_MCU_DCC2_DCC_CLKSRC1_CLK,		       CLK_J7200_BOARD_0_MCU_RGMII1_RXC_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_2_CLOCKS,			   J7200_DEV_MCU_DCC2_DCC_CLKSRC3_CLK,		       CLK_J7200_POSTDIV2_16FFT_MAIN_1_HSDIVOUT5_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_2_CLOCKS,			   J7200_DEV_MCU_DCC2_DCC_CLKSRC6_CLK,		       CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_2_CLOCKS,			   J7200_DEV_MCU_DCC2_DCC_CLKSRC7_CLK,		       CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_2_CLOCKS,			   J7200_DEV_MCU_DCC2_DCC_INPUT00_CLK,		       CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_2_CLOCKS,			   J7200_DEV_MCU_DCC2_DCC_INPUT01_CLK,		       CLK_J7200_BOARD_0_MCU_EXT_REFCLK0_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_2_CLOCKS,			   J7200_DEV_MCU_DCC2_DCC_INPUT02_CLK,		       CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MCU_2_CLOCKS,			   J7200_DEV_MCU_DCC2_DCC_INPUT10_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		3),
	DEV_CLK(J7200_DEV_DCC2_MCU_2_CLOCKS,			   J7200_DEV_MCU_DCC2_VBUS_CLK,			       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_1_CLOCKS,		   J7200_DEV_MCU_TIMER1_TIMER_HCLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_1_CLOCKS,		   J7200_DEV_MCU_TIMER1_TIMER_TCLK_CLK,		       CLK_J7200_MCU_TIMER1_CASCADE_OUT0,
		1),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_2_CLOCKS,		   J7200_DEV_MCU_TIMER2_TIMER_HCLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_2_CLOCKS,		   J7200_DEV_MCU_TIMER2_TIMER_TCLK_CLK,		       CLK_J7200_MCU_TIMER_CLKSEL_OUT2,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_DMTIMER_DMC1MS_MCU_2_CLOCKS,	   J7200_DEV_MCU_TIMER2_TIMER_PWM,		       CLK_J7200_DMTIMER_DMC1MS_MCU_2_TIMER_PWM),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_3_CLOCKS,		   J7200_DEV_MCU_TIMER3_TIMER_HCLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_3_CLOCKS,		   J7200_DEV_MCU_TIMER3_TIMER_TCLK_CLK,		       CLK_J7200_MCU_TIMER3_CASCADE_OUT0,
		1),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_4_CLOCKS,		   J7200_DEV_MCU_TIMER4_TIMER_HCLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_4_CLOCKS,		   J7200_DEV_MCU_TIMER4_TIMER_TCLK_CLK,		       CLK_J7200_MCU_TIMER_CLKSEL_OUT4,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_DMTIMER_DMC1MS_MCU_4_CLOCKS,	   J7200_DEV_MCU_TIMER4_TIMER_PWM,		       CLK_J7200_DMTIMER_DMC1MS_MCU_4_TIMER_PWM),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_5_CLOCKS,		   J7200_DEV_MCU_TIMER5_TIMER_HCLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_5_CLOCKS,		   J7200_DEV_MCU_TIMER5_TIMER_TCLK_CLK,		       CLK_J7200_MCU_TIMER5_CASCADE_OUT0,
		1),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_6_CLOCKS,		   J7200_DEV_MCU_TIMER6_TIMER_HCLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		3),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_6_CLOCKS,		   J7200_DEV_MCU_TIMER6_TIMER_TCLK_CLK,		       CLK_J7200_MCU_TIMER_CLKSEL_OUT6,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_DMTIMER_DMC1MS_MCU_6_CLOCKS,	   J7200_DEV_MCU_TIMER6_TIMER_PWM,		       CLK_J7200_DMTIMER_DMC1MS_MCU_6_TIMER_PWM),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_7_CLOCKS,		   J7200_DEV_MCU_TIMER7_TIMER_HCLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_7_CLOCKS,		   J7200_DEV_MCU_TIMER7_TIMER_TCLK_CLK,		       CLK_J7200_MCU_TIMER7_CASCADE_OUT0,
		1),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_8_CLOCKS,		   J7200_DEV_MCU_TIMER8_TIMER_HCLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_8_CLOCKS,		   J7200_DEV_MCU_TIMER8_TIMER_TCLK_CLK,		       CLK_J7200_MCU_TIMER_CLKSEL_OUT8,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_DMTIMER_DMC1MS_MCU_8_CLOCKS,	   J7200_DEV_MCU_TIMER8_TIMER_PWM,		       CLK_J7200_DMTIMER_DMC1MS_MCU_8_TIMER_PWM),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_9_CLOCKS,		   J7200_DEV_MCU_TIMER9_TIMER_HCLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MCU_9_CLOCKS,		   J7200_DEV_MCU_TIMER9_TIMER_TCLK_CLK,		       CLK_J7200_MCU_TIMER9_CASCADE_OUT0,
		1),
	DEV_CLK(J7200_DEV_ESM_MCU_MCU_0_CLOCKS,			   J7200_DEV_MCU_ESM0_CLK,			       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_FSS_MCU_0_FSAS_0_CLOCKS,		   J7200_DEV_MCU_FSS0_FSAS_0_GCLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_FSS_MCU_0_HYPERBUS1P0_0_CLOCKS,	   J7200_DEV_MCU_FSS0_HYPERBUS1P0_0_CBA_CLK,	       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_FSS_MCU_0_HYPERBUS1P0_0_CLOCKS,	   J7200_DEV_MCU_FSS0_HYPERBUS1P0_0_HPB_CLKX1_CLK,     CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT4_CLK,
		2),
	DEV_CLK(J7200_DEV_FSS_MCU_0_HYPERBUS1P0_0_CLOCKS,	   J7200_DEV_MCU_FSS0_HYPERBUS1P0_0_HPB_CLKX1_INV_CLK, CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT4_CLK,
		2),
	DEV_CLK(J7200_DEV_FSS_MCU_0_HYPERBUS1P0_0_CLOCKS,	   J7200_DEV_MCU_FSS0_HYPERBUS1P0_0_HPB_CLKX2_CLK,     CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT4_CLK,
		1),
	DEV_CLK(J7200_DEV_FSS_MCU_0_HYPERBUS1P0_0_CLOCKS,	   J7200_DEV_MCU_FSS0_HYPERBUS1P0_0_HPB_CLKX2_INV_CLK, CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT4_CLK,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_FSS_MCU_0_HYPERBUS1P0_0_CLOCKS,   J7200_DEV_MCU_FSS0_HYPERBUS1P0_0_HPB_OUT_CLK_N,     CLK_J7200_FSS_MCU_0_HYPERBUS1P0_0_HPB_OUT_CLK_N),
	DEV_CLK_OUTPUT(J7200_DEV_FSS_MCU_0_HYPERBUS1P0_0_CLOCKS,   J7200_DEV_MCU_FSS0_HYPERBUS1P0_0_HPB_OUT_CLK_P,     CLK_J7200_FSS_MCU_0_HYPERBUS1P0_0_HPB_OUT_CLK_P),
	DEV_CLK(J7200_DEV_FSS_MCU_0_OSPI_0_CLOCKS,		   J7200_DEV_MCU_FSS0_OSPI_0_OSPI_DQS_CLK,	       CLK_J7200_BOARD_0_MCU_OSPI0_DQS_OUT,
		1),
	DEV_CLK(J7200_DEV_FSS_MCU_0_OSPI_0_CLOCKS,		   J7200_DEV_MCU_FSS0_OSPI_0_OSPI_HCLK_CLK,	       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_FSS_MCU_0_OSPI_0_CLOCKS,		   J7200_DEV_MCU_FSS0_OSPI_0_OSPI_ICLK_CLK,	       CLK_J7200_MCU_OSPI0_ICLK_SEL_OUT0,
		1),
	DEV_CLK(J7200_DEV_FSS_MCU_0_OSPI_0_CLOCKS,		   J7200_DEV_MCU_FSS0_OSPI_0_OSPI_PCLK_CLK,	       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_FSS_MCU_0_OSPI_0_CLOCKS,		   J7200_DEV_MCU_FSS0_OSPI_0_OSPI_RCLK_CLK,	       CLK_J7200_MCU_OSPI_REF_CLK_SEL_OUT0,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_FSS_MCU_0_OSPI_0_CLOCKS,	   J7200_DEV_MCU_FSS0_OSPI_0_OSPI_OCLK_CLK,	       CLK_J7200_FSS_MCU_0_OSPI_0_OSPI_OCLK_CLK),
	DEV_CLK(J7200_DEV_FSS_MCU_0_OSPI_1_CLOCKS,		   J7200_DEV_MCU_FSS0_OSPI_1_OSPI_HCLK_CLK,	       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_FSS_MCU_0_OSPI_1_CLOCKS,		   J7200_DEV_MCU_FSS0_OSPI_1_OSPI_PCLK_CLK,	       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_FSS_MCU_0_OSPI_1_CLOCKS,		   J7200_DEV_MCU_FSS0_OSPI_1_OSPI_RCLK_CLK,	       CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT4_CLK,
		1),
	DEV_CLK(J7200_DEV_GPIO_144_WKUP_0_CLOCKS,		   J7200_DEV_WKUP_GPIO0_MMR_CLK,		       CLK_J7200_WKUP_GPIO0_CLKSEL_OUT0,
		1),
	DEV_CLK(J7200_DEV_GPIO_144_WKUP_1_CLOCKS,		   J7200_DEV_WKUP_GPIO1_MMR_CLK,		       CLK_J7200_WKUP_GPIO0_CLKSEL_OUT0,
		1),
	DEV_CLK(J7200_DEV_I3C_MCU_0_CLOCKS,			   J7200_DEV_MCU_I3C0_I3C_PCLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_I3C_MCU_0_CLOCKS,			   J7200_DEV_MCU_I3C0_I3C_SCL_DI,		       CLK_J7200_BOARD_0_MCU_I3C0_SCL_OUT,
		1),
	DEV_CLK(J7200_DEV_I3C_MCU_0_CLOCKS,			   J7200_DEV_MCU_I3C0_I3C_SCLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK_OUTPUT(J7200_DEV_I3C_MCU_0_CLOCKS,		   J7200_DEV_MCU_I3C0_I3C_SCL_DO,		       CLK_J7200_I3C_MCU_0_I3C_SCL_DO),
	DEV_CLK(J7200_DEV_I3C_MCU_1_CLOCKS,			   J7200_DEV_MCU_I3C1_I3C_PCLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_I3C_MCU_1_CLOCKS,			   J7200_DEV_MCU_I3C1_I3C_SCLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_J7_MAIN_PORZ_SYNC_STRETCH_WKUP_0_CLOCKS, J7200_DEV_WKUP_PORZ_SYNC0_CLK_12M_RC_CLK,	       CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1),
	DEV_CLK(J7200_DEV_J7_WKUP_PSC_WRAP_WKUP_0_CLOCKS,	   J7200_DEV_WKUP_PSC0_CLK,			       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_J7_WKUP_PSC_WRAP_WKUP_0_CLOCKS,	   J7200_DEV_WKUP_PSC0_SLOW_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		24),
	DEV_CLK(J7200_DEV_K3_DDPA_WKUP_0_CLOCKS,		   J7200_DEV_WKUP_DDPA0_DDPA_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_USART_MCU_0_CLOCKS,			   J7200_DEV_MCU_UART0_FCLK_CLK,		       CLK_J7200_MCUUSART_CLK_SEL_OUT0,
		1),
	DEV_CLK(J7200_DEV_USART_MCU_0_CLOCKS,			   J7200_DEV_MCU_UART0_VBUSP_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_K3VTM_N16FFC_WKUP_0_CLOCKS,		   J7200_DEV_WKUP_VTM0_FIX_REF2_CLK,		       CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1),
	DEV_CLK(J7200_DEV_K3VTM_N16FFC_WKUP_0_CLOCKS,		   J7200_DEV_WKUP_VTM0_VBUSP_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_AUDIO_EXT_REFCLK0_IN,	       CLK_J7200_AUDIO_REFCLKO_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_AUDIO_EXT_REFCLK1_IN,	       CLK_J7200_AUDIO_REFCLKO_MUX_OUT1,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_CLKOUT_IN,			       CLK_J7200_CLKOUT_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_GPMC0_CLKOUT_IN,		       CLK_J7200_GPMC_MAIN_0_PO_GPMC_DEV_CLK,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_GPMC0_CLK_IN,		       CLK_J7200_GPMC_MAIN_0_PO_GPMC_DEV_CLK,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_GPMC0_FCLK_MUX_IN,		       CLK_J7200_GPMC_FCLK_SEL_OUT0,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_I3C0_SCL_IN,		       CLK_J7200_I3C_MAIN_0_I3C_SCL_DO,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCASP0_ACLKR_IN,		       CLK_J7200_MCASP_MAIN_0_MCASP_ACLKR_POUT,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCASP0_ACLKX_IN,		       CLK_J7200_MCASP_MAIN_0_MCASP_ACLKX_POUT,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCASP1_ACLKR_IN,		       CLK_J7200_MCASP_MAIN_1_MCASP_ACLKR_POUT,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCASP1_ACLKX_IN,		       CLK_J7200_MCASP_MAIN_1_MCASP_ACLKX_POUT,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCASP2_ACLKR_IN,		       CLK_J7200_MCASP_MAIN_2_MCASP_ACLKR_POUT,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCASP2_ACLKX_IN,		       CLK_J7200_MCASP_MAIN_2_MCASP_ACLKX_POUT,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCU_CLKOUT0_IN,		       CLK_J7200_MCU_CLKOUT_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCU_HYPERBUS0_CKN_IN,	       CLK_J7200_FSS_MCU_0_HYPERBUS1P0_0_HPB_OUT_CLK_N,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCU_HYPERBUS0_CK_IN,	       CLK_J7200_FSS_MCU_0_HYPERBUS1P0_0_HPB_OUT_CLK_P,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCU_I2C0_SCL_IN,		       CLK_J7200_BOARD_0_MCU_I2C0_SCL_OUT,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCU_I3C0_SCL_IN,		       CLK_J7200_I3C_MCU_0_I3C_SCL_DO,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCU_MDIO0_MDC_IN,		       CLK_J7200_CPSW_2GUSS_MCU_0_MDIO_MDCLK_O,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCU_OBSCLK0_IN,		       CLK_J7200_MCU_OBSCLK_OUTMUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCU_OSPI0_CLK_IN,		       CLK_J7200_FSS_MCU_0_OSPI_0_OSPI_OCLK_CLK,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCU_OSPI0_LBCLKO_IN,	       CLK_J7200_FSS_MCU_0_OSPI_0_OSPI_OCLK_CLK,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCU_RGMII1_TXC_IN,		       CLK_J7200_CPSW_2GUSS_MCU_0_RGMII1_TXC_O,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCU_SPI0_CLK_IN,		       CLK_J7200_SPI_MCU_0_IO_CLKSPIO_CLK,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCU_SPI1_CLK_IN,		       CLK_J7200_SPI_MCU_1_IO_CLKSPIO_CLK,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MCU_SYSCLKOUT0_IN,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_SYSCLKOUT_CLK,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MDIO0_MDC_IN,		       CLK_J7200_CPSW_5XUSS_MAIN_0_MDIO_MDCLK_O,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_MMC1_CLK_IN,		       CLK_J7200_EMMCSD4SS_MAIN_0_EMMCSDSS_IO_CLK_O,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_OBSCLK0_IN,			       CLK_J7200_OSBCLK0_DIV_OUT0,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_OBSCLK1_IN,			       CLK_J7200_OSBCLK0_DIV_OUT0,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_OBSCLK2_IN,			       CLK_J7200_OSBCLK0_DIV_OUT0,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_RGMII1_TXC_IN,		       CLK_J7200_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII1_TXC__A,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_RGMII2_TXC_IN,		       CLK_J7200_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII2_TXC__A,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_RGMII3_TXC_IN,		       CLK_J7200_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII3_TXC__A,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_RGMII4_TXC_IN,		       CLK_J7200_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII4_TXC__A,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_SPI0_CLK_IN,		       CLK_J7200_SPI_MAIN_0_IO_CLKSPIO_CLK,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_SPI1_CLK_IN,		       CLK_J7200_SPI_MAIN_1_IO_CLKSPIO_CLK,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_SPI2_CLK_IN,		       CLK_J7200_SPI_MAIN_2_IO_CLKSPIO_CLK,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_SPI3_CLK_IN,		       CLK_J7200_SPI_MAIN_3_IO_CLKSPIO_CLK,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_SPI5_CLK_IN,		       CLK_J7200_SPI_MAIN_5_IO_CLKSPIO_CLK,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_SPI6_CLK_IN,		       CLK_J7200_SPI_MAIN_6_IO_CLKSPIO_CLK,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_SPI7_CLK_IN,		       CLK_J7200_SPI_MAIN_7_IO_CLKSPIO_CLK,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_SYSCLKOUT0_IN,		       CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_SYSCLKOUT_CLK,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_TRC_CLK_IN,			       CLK_J7200_DEBUGSS_K3_WRAP_CV0_MAIN_0_CSTPIU_TRACECLK,
		1),
	DEV_CLK(J7200_DEV_BOARD_0_CLOCKS,			   J7200_DEV_BOARD0_WKUP_I2C0_SCL_IN,		       CLK_J7200_MSHSI2C_WKUP_0_PORSCL,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_HFOSC1_CLK_OUT,		       CLK_J7200_BOARD_0_HFOSC1_CLK_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_AUDIO_EXT_REFCLK0_OUT,	       CLK_J7200_BOARD_0_AUDIO_EXT_REFCLK0_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_AUDIO_EXT_REFCLK1_OUT,	       CLK_J7200_BOARD_0_AUDIO_EXT_REFCLK1_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_CPTS0_RFT_CLK_OUT,		       CLK_J7200_BOARD_0_CPTS0_RFT_CLK_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_EXT_REFCLK1_OUT,		       CLK_J7200_BOARD_0_EXT_REFCLK1_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_GPMC0_CLK_OUT,		       CLK_J7200_BOARD_0_GPMC0_CLK_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_I2C0_SCL_OUT,		       CLK_J7200_BOARD_0_I2C0_SCL_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_I2C1_SCL_OUT,		       CLK_J7200_BOARD_0_I2C1_SCL_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_I2C2_SCL_OUT,		       CLK_J7200_BOARD_0_I2C2_SCL_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_I2C3_SCL_OUT,		       CLK_J7200_BOARD_0_I2C3_SCL_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_I2C4_SCL_OUT,		       CLK_J7200_BOARD_0_I2C4_SCL_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_I2C5_SCL_OUT,		       CLK_J7200_BOARD_0_I2C5_SCL_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_I2C6_SCL_OUT,		       CLK_J7200_BOARD_0_I2C6_SCL_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_I3C0_SCL_OUT,		       CLK_J7200_BOARD_0_I3C0_SCL_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_LED_CLK_OUT,		       CLK_J7200_BOARD_0_LED_CLK_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_MCASP0_ACLKR_OUT,		       CLK_J7200_BOARD_0_MCASP0_ACLKR_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_MCASP0_ACLKX_OUT,		       CLK_J7200_BOARD_0_MCASP0_ACLKX_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_MCASP1_ACLKR_OUT,		       CLK_J7200_BOARD_0_MCASP1_ACLKR_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_MCASP1_ACLKX_OUT,		       CLK_J7200_BOARD_0_MCASP1_ACLKX_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_MCASP2_ACLKR_OUT,		       CLK_J7200_BOARD_0_MCASP2_ACLKR_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_MCASP2_ACLKX_OUT,		       CLK_J7200_BOARD_0_MCASP2_ACLKX_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_MCU_CPTS0_RFT_CLK_OUT,	       CLK_J7200_BOARD_0_MCU_CPTS0_RFT_CLK_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_MCU_EXT_REFCLK0_OUT,	       CLK_J7200_BOARD_0_MCU_EXT_REFCLK0_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_MCU_I2C0_SCL_OUT,		       CLK_J7200_BOARD_0_MCU_I2C0_SCL_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_MCU_I2C1_SCL_OUT,		       CLK_J7200_BOARD_0_MCU_I2C1_SCL_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_MCU_I3C0_SCL_OUT,		       CLK_J7200_BOARD_0_MCU_I3C0_SCL_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_MCU_OSPI0_DQS_OUT,		       CLK_J7200_BOARD_0_MCU_OSPI0_DQS_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_MCU_RGMII1_RXC_OUT,		       CLK_J7200_BOARD_0_MCU_RGMII1_RXC_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_MCU_RMII1_REF_CLK_OUT,	       CLK_J7200_BOARD_0_MCU_RMII1_REF_CLK_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_RGMII1_RXC_OUT,		       CLK_J7200_BOARD_0_RGMII1_RXC_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_RGMII2_RXC_OUT,		       CLK_J7200_BOARD_0_RGMII2_RXC_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_RGMII3_RXC_OUT,		       CLK_J7200_BOARD_0_RGMII3_RXC_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_RGMII4_RXC_OUT,		       CLK_J7200_BOARD_0_RGMII4_RXC_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_RMII_REF_CLK_OUT,		       CLK_J7200_BOARD_0_RMII_REF_CLK_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_TCK_OUT,			       CLK_J7200_BOARD_0_TCK_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_WKUP_I2C0_SCL_OUT,		       CLK_J7200_BOARD_0_WKUP_I2C0_SCL_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_BOARD_0_CLOCKS,		   J7200_DEV_BOARD0_WKUP_LF_CLKIN_OUT,		       CLK_J7200_BOARD_0_WKUP_LF_CLKIN_OUT),
	DEV_CLK(J7200_DEV_MCANSS_MCU_0_CLOCKS,			   J7200_DEV_MCU_MCAN0_MCANSS_CCLK_CLK,		       CLK_J7200_MCU_MCAN_CLK_SEL_OUT0,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MCU_0_CLOCKS,			   J7200_DEV_MCU_MCAN0_MCANSS_HCLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_MCANSS_MCU_1_CLOCKS,			   J7200_DEV_MCU_MCAN1_MCANSS_CCLK_CLK,		       CLK_J7200_MCU_MCAN_CLK_SEL_OUT1,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MCU_1_CLOCKS,			   J7200_DEV_MCU_MCAN1_MCANSS_HCLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_MSHSI2C_MCU_0_CLOCKS,			   J7200_DEV_MCU_I2C0_CLK,			       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_MSHSI2C_MCU_0_CLOCKS,			   J7200_DEV_MCU_I2C0_PISCL,			       CLK_J7200_BOARD_0_MCU_I2C0_SCL_OUT,
		1),
	DEV_CLK(J7200_DEV_MSHSI2C_MCU_0_CLOCKS,			   J7200_DEV_MCU_I2C0_PISYS_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT3_CLK,
		1),
	DEV_CLK(J7200_DEV_MSHSI2C_MCU_1_CLOCKS,			   J7200_DEV_MCU_I2C1_CLK,			       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_MSHSI2C_MCU_1_CLOCKS,			   J7200_DEV_MCU_I2C1_PISCL,			       CLK_J7200_BOARD_0_MCU_I2C1_SCL_OUT,
		1),
	DEV_CLK(J7200_DEV_MSHSI2C_MCU_1_CLOCKS,			   J7200_DEV_MCU_I2C1_PISYS_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT3_CLK,
		1),
	DEV_CLK(J7200_DEV_MSHSI2C_WKUP_0_CLOCKS,		   J7200_DEV_WKUP_I2C0_CLK,			       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_MSHSI2C_WKUP_0_CLOCKS,		   J7200_DEV_WKUP_I2C0_PISCL,			       CLK_J7200_BOARD_0_WKUP_I2C0_SCL_OUT,
		1),
	DEV_CLK(J7200_DEV_MSHSI2C_WKUP_0_CLOCKS,		   J7200_DEV_WKUP_I2C0_PISYS_CLK,		       CLK_J7200_WKUP_I2C0_MCUPLL_BYPASS_CLKSEL_OUT0,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_MSHSI2C_WKUP_0_CLOCKS,		   J7200_DEV_WKUP_I2C0_PORSCL,			       CLK_J7200_MSHSI2C_WKUP_0_PORSCL),
	DEV_CLK(J7200_DEV_NAVSS_MCU_J7_MCU_0_UDMASS_INTA_0_CLOCKS, J7200_DEV_MCU_NAVSS0_UDMASS_INTA_0_SYS_CLK,	       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS_MCU_J7_MCU_0_PROXY_0_CLOCKS,	   J7200_DEV_MCU_NAVSS0_PROXY0_CLK_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS_MCU_J7_MCU_0_UDMAP_0_CLOCKS,	   J7200_DEV_MCU_NAVSS0_UDMAP_0_SYS_CLK,	       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS_MCU_J7_MCU_0_INTR_0_CLOCKS,	   J7200_DEV_MCU_NAVSS0_INTR_0_INTR_CLK,	       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS_MCU_J7_MCU_0_MCRC_0_CLOCKS,	   J7200_DEV_MCU_NAVSS0_MCRC_0_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_PULSAR_SL_MCU_0_R5_0_CLOCKS,		   J7200_DEV_MCU_R5FSS0_CORE0_CPU_CLK,		       CLK_J7200_MCU_R5_CORE0_CLKSEL_OUT0,
		1),
	DEV_CLK(J7200_DEV_PULSAR_SL_MCU_0_R5_0_CLOCKS,		   J7200_DEV_MCU_R5FSS0_CORE0_INTERFACE_CLK,	       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_PULSAR_SL_MCU_0_R5_0_CLOCKS,		   J7200_DEV_MCU_R5FSS0_CORE0_INTERFACE_PHASE,	       CLK_J7200_MCU_R5_PHASE0_CLKSEL_OUT0,
		1),
	DEV_CLK(J7200_DEV_PULSAR_SL_MCU_0_R5_1_CLOCKS,		   J7200_DEV_MCU_R5FSS0_CORE1_CPU_CLK,		       CLK_J7200_MCU_R5_CORE1_CLKSEL_OUT0,
		1),
	DEV_CLK(J7200_DEV_PULSAR_SL_MCU_0_R5_1_CLOCKS,		   J7200_DEV_MCU_R5FSS0_CORE1_INTERFACE_CLK,	       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_PULSAR_SL_MCU_0_R5_1_CLOCKS,		   J7200_DEV_MCU_R5FSS0_CORE1_INTERFACE_PHASE,	       CLK_J7200_MCU_R5_PHASE1_CLKSEL_OUT0,
		1),
	DEV_CLK(J7200_DEV_RTI_CFG1_MCU_0_CLOCKS,		   J7200_DEV_MCU_RTI0_RTI_CLK,			       CLK_J7200_MCU_WWD_CLKSEL_OUT0,
		1),
	DEV_CLK(J7200_DEV_RTI_CFG1_MCU_0_CLOCKS,		   J7200_DEV_MCU_RTI0_VBUSP_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_RTI_CFG1_MCU_1_CLOCKS,		   J7200_DEV_MCU_RTI1_RTI_CLK,			       CLK_J7200_MCU_WWD_CLKSEL_OUT1,
		1),
	DEV_CLK(J7200_DEV_RTI_CFG1_MCU_1_CLOCKS,		   J7200_DEV_MCU_RTI1_VBUSP_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_SA2_UL_MCU_0_CLOCKS,			   J7200_DEV_MCU_SA2_UL0_PKA_IN_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_SA2_UL_MCU_0_CLOCKS,			   J7200_DEV_MCU_SA2_UL0_X1_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_SA2_UL_MCU_0_CLOCKS,			   J7200_DEV_MCU_SA2_UL0_X2_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		3),
	DEV_CLK(J7200_DEV_SPI_MCU_0_CLOCKS,			   J7200_DEV_MCU_MCSPI0_CLKSPIREF_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT0_CLK,
		5),
	DEV_CLK(J7200_DEV_SPI_MCU_0_CLOCKS,			   J7200_DEV_MCU_MCSPI0_VBUSP_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK_OUTPUT(J7200_DEV_SPI_MCU_0_CLOCKS,		   J7200_DEV_MCU_MCSPI0_IO_CLKSPIO_CLK,		       CLK_J7200_SPI_MCU_0_IO_CLKSPIO_CLK),
	DEV_CLK(J7200_DEV_SPI_MCU_1_CLOCKS,			   J7200_DEV_MCU_MCSPI1_CLKSPIREF_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT0_CLK,
		5),
	DEV_CLK(J7200_DEV_SPI_MCU_1_CLOCKS,			   J7200_DEV_MCU_MCSPI1_IO_CLKSPII_CLK,		       CLK_J7200_MCU_SPI1_CLK_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_SPI_MCU_1_CLOCKS,			   J7200_DEV_MCU_MCSPI1_VBUSP_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK_OUTPUT(J7200_DEV_SPI_MCU_1_CLOCKS,		   J7200_DEV_MCU_MCSPI1_IO_CLKSPIO_CLK,		       CLK_J7200_SPI_MCU_1_IO_CLKSPIO_CLK),
	DEV_CLK(J7200_DEV_SPI_MCU_2_CLOCKS,			   J7200_DEV_MCU_MCSPI2_CLKSPIREF_CLK,		       CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT0_CLK,
		5),
	DEV_CLK(J7200_DEV_SPI_MCU_2_CLOCKS,			   J7200_DEV_MCU_MCSPI2_IO_CLKSPII_CLK,		       CLK_J7200_SPI_MCU_2_IO_CLKSPIO_CLK,
		1),
	DEV_CLK(J7200_DEV_SPI_MCU_2_CLOCKS,			   J7200_DEV_MCU_MCSPI2_VBUSP_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK_OUTPUT(J7200_DEV_SPI_MCU_2_CLOCKS,		   J7200_DEV_MCU_MCSPI2_IO_CLKSPIO_CLK,		       CLK_J7200_SPI_MCU_2_IO_CLKSPIO_CLK),
	DEV_CLK(J7200_DEV_USART_WKUP_0_CLOCKS,			   J7200_DEV_WKUP_UART0_FCLK_CLK,		       CLK_J7200_WKUP_USART_MCUPLL_BYPASS_CLKSEL_OUT0,
		1),
	DEV_CLK(J7200_DEV_USART_WKUP_0_CLOCKS,			   J7200_DEV_WKUP_UART0_VBUSP_CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_NAVSS_MCU_J7_MCU_0_MODSS_0_CLOCKS,	   J7200_DEV_MCU_NAVSS0_MODSS_VD2CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS_MCU_J7_MCU_0_UDMASS_0_CLOCKS,	   J7200_DEV_MCU_NAVSS0_UDMASS_VD2CLK,		       CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		1),
};
static struct dev_clk MCU_WAKEUP_dev_clk[ARRAY_SIZE(MCU_WAKEUP_dev_clk_data)] __attribute__((__section__(".bss.devgroup.MCU_WAKEUP")));
static const struct dev_clk_data MAIN_dev_clk_data[] __attribute__((__section__(".const.devgroup.MAIN"))) = {
	DEV_CLK(J7200_DEV_ATL_MAIN_0_CLOCKS,						J7200_DEV_ATL0_ATL_CLK,					 CLK_J7200_ATL_PCLKMUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_ATL_MAIN_0_CLOCKS,						J7200_DEV_ATL0_VBUS_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK_OUTPUT(J7200_DEV_ATL_MAIN_0_CLOCKS,					J7200_DEV_ATL0_ATL_IO_PORT_ATCLK_OUT,			 CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT),
	DEV_CLK_OUTPUT(J7200_DEV_ATL_MAIN_0_CLOCKS,					J7200_DEV_ATL0_ATL_IO_PORT_ATCLK_OUT_1,			 CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_1),
	DEV_CLK_OUTPUT(J7200_DEV_ATL_MAIN_0_CLOCKS,					J7200_DEV_ATL0_ATL_IO_PORT_ATCLK_OUT_2,			 CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_2),
	DEV_CLK_OUTPUT(J7200_DEV_ATL_MAIN_0_CLOCKS,					J7200_DEV_ATL0_ATL_IO_PORT_ATCLK_OUT_3,			 CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_3),
	DEV_CLK(J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_CLOCKS,			J7200_DEV_COMPUTE_CLUSTER0_DDR32SS_EMIF0_DDR_PLL_CLK,	 CLK_J7200_HSDIV0_16FFT_MAIN_12_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_CLOCKS,			J7200_DEV_COMPUTE_CLUSTER0_DDR32SS_EMIF0_PLL_CTRL_CLK,	 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_CLOCKS,			J7200_DEV_COMPUTE_CLUSTER0_TB_SOC_GIC_CLK,		 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK(J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_CLOCKS,			J7200_DEV_COMPUTE_CLUSTER0_TB_SOC_VBUSP_CFG_CLK,	 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_CLOCKS,			J7200_DEV_COMPUTE_CLUSTER0_TB_SOC_VBUSP_DBG_CLK,	 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK(J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_CLOCKS,			J7200_DEV_COMPUTE_CLUSTER0_TB_SOC_VBUSP_DMSC_CLK,	 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_P0_A72_DUAL_1MB_CLOCKS,	J7200_DEV_A72SS0_ARM_CLK_CLK,				 CLK_J7200_HSDIV0_16FFT_MAIN_8_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_P0_A72_DUAL_1MB_CLOCKS,	J7200_DEV_A72SS0_MSMC_CLK,				 CLK_J7200_HSDIV0_16FFT_MAIN_7_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_P0_A72_DUAL_1MB_CLOCKS,	J7200_DEV_A72SS0_PLL_CTRL_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_DDR32V256SS_16FFC_EW_MAIN_0_CLOCKS,				J7200_DEV_DDR0_DDRSS_DDR_PLL_CLK,			 CLK_J7200_HSDIV0_16FFT_MAIN_12_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_DDR32V256SS_16FFC_EW_MAIN_0_CLOCKS,				J7200_DEV_DDR0_PLL_CTRL_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_PBIST_WRAP_CLOCKS,	J7200_DEV_COMPUTE_CLUSTER0_PBIST_WRAP_DIVH_CLK4_CLK_CLK, CLK_J7200_HSDIV0_16FFT_MAIN_7_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_CPPI_CLK_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT1_CLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_CPTS_RFT_CLK,				 CLK_J7200_CPSW5X_CPTS_RFT_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_GMII1_MR_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT0_CLK,
		10),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_GMII1_MT_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT0_CLK,
		10),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_GMII2_MR_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT0_CLK,
		10),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_GMII2_MT_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT0_CLK,
		10),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_GMII3_MR_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT0_CLK,
		10),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_GMII3_MT_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT0_CLK,
		10),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_GMII4_MR_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT0_CLK,
		10),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_GMII4_MT_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT0_CLK,
		10),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_GMII_RFT_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT0_CLK,
		2),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_RGMII1_RXC_I,				 CLK_J7200_BOARD_0_RGMII1_RXC_OUT,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_RGMII2_RXC_I,				 CLK_J7200_BOARD_0_RGMII2_RXC_OUT,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_RGMII3_RXC_I,				 CLK_J7200_BOARD_0_RGMII3_RXC_OUT,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_RGMII4_RXC_I,				 CLK_J7200_BOARD_0_RGMII4_RXC_OUT,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_RGMII_MHZ_250_CLK,			 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_RGMII_MHZ_50_CLK,			 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT0_CLK,
		5),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_RGMII_MHZ_5_CLK,			 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT0_CLK,
		50),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_RMII_MHZ_50_CLK,			 CLK_J7200_BOARD_0_RMII_REF_CLK_OUT,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES1_REFCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN2_REFCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES1_RXCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN2_RXCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES1_RXFCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN2_RXFCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES1_TXFCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN2_TXFCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES1_TXMCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN2_TXMCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES2_REFCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN3_REFCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES2_RXCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN3_RXCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES2_RXFCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN3_RXFCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES2_TXFCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN3_TXFCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES2_TXMCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN3_TXMCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES3_REFCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN0_REFCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES3_RXCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN0_RXCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES3_RXFCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN0_RXFCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES3_TXFCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN0_TXFCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES3_TXMCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN0_TXMCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES4_REFCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN1_REFCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES4_RXCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN1_RXCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES4_RXFCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN1_RXFCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES4_TXFCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN1_TXFCLK,
		1),
	DEV_CLK(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,					J7200_DEV_CPSW0_SERDES4_TXMCLK,				 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN1_TXMCLK,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,				J7200_DEV_CPSW0_CPTS_GENF0,				 CLK_J7200_CPSW_5XUSS_MAIN_0_CPTS_GENF0),
	DEV_CLK_OUTPUT(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,				J7200_DEV_CPSW0_MDIO_MDCLK_O,				 CLK_J7200_CPSW_5XUSS_MAIN_0_MDIO_MDCLK_O),
	DEV_CLK_OUTPUT(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,				J7200_DEV_CPSW0_PRE_RGMII1_TCLK,			 CLK_J7200_CPSW_5XUSS_MAIN_0_PRE_RGMII1_TCLK),
	DEV_CLK_OUTPUT(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,				J7200_DEV_CPSW0_PRE_RGMII2_TCLK,			 CLK_J7200_CPSW_5XUSS_MAIN_0_PRE_RGMII2_TCLK),
	DEV_CLK_OUTPUT(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,				J7200_DEV_CPSW0_PRE_RGMII3_TCLK,			 CLK_J7200_CPSW_5XUSS_MAIN_0_PRE_RGMII3_TCLK),
	DEV_CLK_OUTPUT(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,				J7200_DEV_CPSW0_PRE_RGMII4_TCLK,			 CLK_J7200_CPSW_5XUSS_MAIN_0_PRE_RGMII4_TCLK),
	DEV_CLK_OUTPUT(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,				J7200_DEV_CPSW0_SERDES1_TXCLK,				 CLK_J7200_CPSW_5XUSS_MAIN_0_SERDES1_TXCLK),
	DEV_CLK_OUTPUT(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,				J7200_DEV_CPSW0_SERDES2_TXCLK,				 CLK_J7200_CPSW_5XUSS_MAIN_0_SERDES2_TXCLK),
	DEV_CLK_OUTPUT(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,				J7200_DEV_CPSW0_SERDES3_TXCLK,				 CLK_J7200_CPSW_5XUSS_MAIN_0_SERDES3_TXCLK),
	DEV_CLK_OUTPUT(J7200_DEV_CPSW_5XUSS_MAIN_0_CLOCKS,				J7200_DEV_CPSW0_SERDES4_TXCLK,				 CLK_J7200_CPSW_5XUSS_MAIN_0_SERDES4_TXCLK),
	DEV_CLK(J7200_DEV_CPT2_AGGREGATOR32_MAIN_RC_0_CLOCKS,				J7200_DEV_CPT2_AGGR0_VCLK_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_CPT2_AGGREGATOR32_MAIN_INFRA_0_CLOCKS,			J7200_DEV_CPT2_AGGR1_VCLK_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_CPT2_AGGREGATOR32_MAIN_HC_0_CLOCKS,				J7200_DEV_CPT2_AGGR2_VCLK_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK(J7200_DEV_CPT2_AGGREGATOR32_MAIN_MV_0_CLOCKS,				J7200_DEV_CPT2_AGGR3_VCLK_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_CLOCKS,			J7200_DEV_CPSW_TX_RGMII0_PRE_RGMII1_TCLK,		 CLK_J7200_CPSW_5XUSS_MAIN_0_PRE_RGMII1_TCLK,
		1),
	DEV_CLK(J7200_DEV_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_CLOCKS,			J7200_DEV_CPSW_TX_RGMII0_PRE_RGMII2_TCLK,		 CLK_J7200_CPSW_5XUSS_MAIN_0_PRE_RGMII2_TCLK,
		1),
	DEV_CLK(J7200_DEV_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_CLOCKS,			J7200_DEV_CPSW_TX_RGMII0_PRE_RGMII3_TCLK,		 CLK_J7200_CPSW_5XUSS_MAIN_0_PRE_RGMII3_TCLK,
		1),
	DEV_CLK(J7200_DEV_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_CLOCKS,			J7200_DEV_CPSW_TX_RGMII0_PRE_RGMII4_TCLK,		 CLK_J7200_CPSW_5XUSS_MAIN_0_PRE_RGMII4_TCLK,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_CLOCKS,		J7200_DEV_CPSW_TX_RGMII0_IO__RGMII1_TXC__A,
		       CLK_J7200_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII1_TXC__A),
	DEV_CLK_OUTPUT(J7200_DEV_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_CLOCKS,		J7200_DEV_CPSW_TX_RGMII0_IO__RGMII2_TXC__A,
		       CLK_J7200_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII2_TXC__A),
	DEV_CLK_OUTPUT(J7200_DEV_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_CLOCKS,		J7200_DEV_CPSW_TX_RGMII0_IO__RGMII3_TXC__A,
		       CLK_J7200_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII3_TXC__A),
	DEV_CLK_OUTPUT(J7200_DEV_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_CLOCKS,		J7200_DEV_CPSW_TX_RGMII0_IO__RGMII4_TXC__A,
		       CLK_J7200_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII4_TXC__A),
	DEV_CLK(J7200_DEV_CXSTM500SS_MAIN_0_CLOCKS,					J7200_DEV_STM0_ATB_CLK,					 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK(J7200_DEV_CXSTM500SS_MAIN_0_CLOCKS,					J7200_DEV_STM0_CORE_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK(J7200_DEV_CXSTM500SS_MAIN_0_CLOCKS,					J7200_DEV_STM0_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DCC2_MAIN_0_CLOCKS,						J7200_DEV_DCC0_DCC_CLKSRC0_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_0_HSDIVOUT1_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_0_CLOCKS,						J7200_DEV_DCC0_DCC_CLKSRC1_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_0_HSDIVOUT2_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_0_CLOCKS,						J7200_DEV_DCC0_DCC_CLKSRC2_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_0_HSDIVOUT3_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_0_CLOCKS,						J7200_DEV_DCC0_DCC_CLKSRC3_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_0_HSDIVOUT4_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_0_CLOCKS,						J7200_DEV_DCC0_DCC_CLKSRC4_CLK,				 CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_0_CLOCKS,						J7200_DEV_DCC0_DCC_CLKSRC5_CLK,				 CLK_J7200_BOARD_0_HFOSC1_CLK_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_0_CLOCKS,						J7200_DEV_DCC0_DCC_CLKSRC6_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_0_CLOCKS,						J7200_DEV_DCC0_DCC_INPUT00_CLK,				 CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_0_CLOCKS,						J7200_DEV_DCC0_DCC_INPUT01_CLK,				 CLK_J7200_BOARD_0_HFOSC1_CLK_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_0_CLOCKS,						J7200_DEV_DCC0_DCC_INPUT02_CLK,				 CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_0_CLOCKS,						J7200_DEV_DCC0_DCC_INPUT10_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK(J7200_DEV_DCC2_MAIN_0_CLOCKS,						J7200_DEV_DCC0_VBUS_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DCC2_MAIN_1_CLOCKS,						J7200_DEV_DCC1_DCC_CLKSRC0_CLK,				 CLK_J7200_POSTDIV2_16FFT_MAIN_0_HSDIVOUT5_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_1_CLOCKS,						J7200_DEV_DCC1_DCC_CLKSRC1_CLK,				 CLK_J7200_POSTDIV2_16FFT_MAIN_0_HSDIVOUT6_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_1_CLOCKS,						J7200_DEV_DCC1_DCC_CLKSRC2_CLK,				 CLK_J7200_POSTDIV2_16FFT_MAIN_0_HSDIVOUT7_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_1_CLOCKS,						J7200_DEV_DCC1_DCC_CLKSRC3_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_1_CLOCKS,						J7200_DEV_DCC1_DCC_CLKSRC4_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT1_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_1_CLOCKS,						J7200_DEV_DCC1_DCC_CLKSRC5_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT2_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_1_CLOCKS,						J7200_DEV_DCC1_DCC_CLKSRC6_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT3_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_1_CLOCKS,						J7200_DEV_DCC1_DCC_INPUT00_CLK,				 CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_1_CLOCKS,						J7200_DEV_DCC1_DCC_INPUT01_CLK,				 CLK_J7200_BOARD_0_HFOSC1_CLK_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_1_CLOCKS,						J7200_DEV_DCC1_DCC_INPUT02_CLK,				 CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_1_CLOCKS,						J7200_DEV_DCC1_DCC_INPUT10_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DCC2_MAIN_1_CLOCKS,						J7200_DEV_DCC1_VBUS_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DCC2_MAIN_2_CLOCKS,						J7200_DEV_DCC2_DCC_CLKSRC0_CLK,				 CLK_J7200_POSTDIV2_16FFT_MAIN_1_HSDIVOUT7_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_2_CLOCKS,						J7200_DEV_DCC2_DCC_CLKSRC2_CLK,				 CLK_J7200_CPSW5X_CPTS_RFT_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_2_CLOCKS,						J7200_DEV_DCC2_DCC_CLKSRC3_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_2_HSDIVOUT4_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_2_CLOCKS,						J7200_DEV_DCC2_DCC_CLKSRC4_CLK,				 CLK_J7200_POSTDIV2_16FFT_MAIN_2_HSDIVOUT6_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_2_CLOCKS,						J7200_DEV_DCC2_DCC_CLKSRC5_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_2_HSDIVOUT1_CLK,
		2),
	DEV_CLK(J7200_DEV_DCC2_MAIN_2_CLOCKS,						J7200_DEV_DCC2_DCC_CLKSRC6_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_2_HSDIVOUT2_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_2_CLOCKS,						J7200_DEV_DCC2_DCC_CLKSRC7_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_2_CLOCKS,						J7200_DEV_DCC2_DCC_INPUT00_CLK,				 CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_2_CLOCKS,						J7200_DEV_DCC2_DCC_INPUT01_CLK,				 CLK_J7200_BOARD_0_HFOSC1_CLK_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_2_CLOCKS,						J7200_DEV_DCC2_DCC_INPUT02_CLK,				 CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_2_CLOCKS,						J7200_DEV_DCC2_DCC_INPUT10_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DCC2_MAIN_2_CLOCKS,						J7200_DEV_DCC2_VBUS_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DCC2_MAIN_3_CLOCKS,						J7200_DEV_DCC3_DCC_CLKSRC0_CLK,				 CLK_J7200_HSDIV2_16FFT_MAIN_4_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_3_CLOCKS,						J7200_DEV_DCC3_DCC_CLKSRC3_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT3_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_3_CLOCKS,						J7200_DEV_DCC3_DCC_CLKSRC4_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT4_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_3_CLOCKS,						J7200_DEV_DCC3_DCC_CLKSRC5_CLK,				 CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_32K_CLK,
		391),
	DEV_CLK(J7200_DEV_DCC2_MAIN_3_CLOCKS,						J7200_DEV_DCC3_DCC_CLKSRC6_CLK,				 CLK_J7200_HSDIV0_16FFT_MAIN_7_HSDIVOUT0_CLK,
		4),
	DEV_CLK(J7200_DEV_DCC2_MAIN_3_CLOCKS,						J7200_DEV_DCC3_DCC_CLKSRC7_CLK,				 CLK_J7200_HSDIV0_16FFT_MAIN_8_HSDIVOUT0_CLK,
		8),
	DEV_CLK(J7200_DEV_DCC2_MAIN_3_CLOCKS,						J7200_DEV_DCC3_DCC_INPUT00_CLK,				 CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_3_CLOCKS,						J7200_DEV_DCC3_DCC_INPUT01_CLK,				 CLK_J7200_BOARD_0_HFOSC1_CLK_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_3_CLOCKS,						J7200_DEV_DCC3_DCC_INPUT02_CLK,				 CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_3_CLOCKS,						J7200_DEV_DCC3_DCC_INPUT10_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DCC2_MAIN_3_CLOCKS,						J7200_DEV_DCC3_VBUS_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DCC2_MAIN_4_CLOCKS,						J7200_DEV_DCC4_DCC_CLKSRC0_CLK,				 CLK_J7200_BOARD_0_AUDIO_EXT_REFCLK0_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_4_CLOCKS,						J7200_DEV_DCC4_DCC_CLKSRC1_CLK,				 CLK_J7200_BOARD_0_AUDIO_EXT_REFCLK1_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_4_CLOCKS,						J7200_DEV_DCC4_DCC_CLKSRC2_CLK,				 CLK_J7200_HSDIV0_16FFT_MAIN_12_HSDIVOUT0_CLK,
		4),
	DEV_CLK(J7200_DEV_DCC2_MAIN_4_CLOCKS,						J7200_DEV_DCC4_DCC_CLKSRC3_CLK,				 CLK_J7200_BOARD_0_WKUP_LF_CLKIN_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_4_CLOCKS,						J7200_DEV_DCC4_DCC_CLKSRC4_CLK,				 CLK_J7200_HSDIV1_16FFT_MAIN_14_HSDIVOUT0_CLK,
		4),
	DEV_CLK(J7200_DEV_DCC2_MAIN_4_CLOCKS,						J7200_DEV_DCC4_DCC_CLKSRC5_CLK,				 CLK_J7200_BOARD_0_MCU_EXT_REFCLK0_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_4_CLOCKS,						J7200_DEV_DCC4_DCC_CLKSRC6_CLK,				 CLK_J7200_BOARD_0_RGMII1_RXC_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_4_CLOCKS,						J7200_DEV_DCC4_DCC_CLKSRC7_CLK,				 CLK_J7200_BOARD_0_RGMII2_RXC_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_4_CLOCKS,						J7200_DEV_DCC4_DCC_INPUT00_CLK,				 CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_4_CLOCKS,						J7200_DEV_DCC4_DCC_INPUT01_CLK,				 CLK_J7200_BOARD_0_HFOSC1_CLK_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_4_CLOCKS,						J7200_DEV_DCC4_DCC_INPUT02_CLK,				 CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_4_CLOCKS,						J7200_DEV_DCC4_DCC_INPUT10_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK(J7200_DEV_DCC2_MAIN_4_CLOCKS,						J7200_DEV_DCC4_VBUS_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DCC2_MAIN_5_CLOCKS,						J7200_DEV_DCC5_DCC_CLKSRC0_CLK,				 CLK_J7200_BOARD_0_RGMII3_RXC_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_5_CLOCKS,						J7200_DEV_DCC5_DCC_CLKSRC1_CLK,				 CLK_J7200_BOARD_0_RGMII4_RXC_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_5_CLOCKS,						J7200_DEV_DCC5_DCC_CLKSRC4_CLK,				 CLK_J7200_BOARD_0_RMII_REF_CLK_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_5_CLOCKS,						J7200_DEV_DCC5_DCC_CLKSRC6_CLK,				 CLK_J7200_BOARD_0_GPMC0_CLK_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_5_CLOCKS,						J7200_DEV_DCC5_DCC_INPUT00_CLK,				 CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_5_CLOCKS,						J7200_DEV_DCC5_DCC_INPUT01_CLK,				 CLK_J7200_BOARD_0_HFOSC1_CLK_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_5_CLOCKS,						J7200_DEV_DCC5_DCC_INPUT02_CLK,				 CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_5_CLOCKS,						J7200_DEV_DCC5_DCC_INPUT10_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_5_CLOCKS,						J7200_DEV_DCC5_VBUS_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DCC2_MAIN_6_CLOCKS,						J7200_DEV_DCC6_DCC_CLKSRC0_CLK,				 CLK_J7200_BOARD_0_MCASP0_ACLKX_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_6_CLOCKS,						J7200_DEV_DCC6_DCC_CLKSRC1_CLK,				 CLK_J7200_BOARD_0_MCASP0_ACLKR_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_6_CLOCKS,						J7200_DEV_DCC6_DCC_CLKSRC2_CLK,				 CLK_J7200_BOARD_0_MCASP1_ACLKX_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_6_CLOCKS,						J7200_DEV_DCC6_DCC_CLKSRC3_CLK,				 CLK_J7200_BOARD_0_MCASP1_ACLKR_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_6_CLOCKS,						J7200_DEV_DCC6_DCC_CLKSRC4_CLK,				 CLK_J7200_BOARD_0_MCASP2_ACLKX_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_6_CLOCKS,						J7200_DEV_DCC6_DCC_CLKSRC5_CLK,				 CLK_J7200_BOARD_0_MCASP2_ACLKR_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_6_CLOCKS,						J7200_DEV_DCC6_DCC_CLKSRC6_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT1_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_6_CLOCKS,						J7200_DEV_DCC6_DCC_CLKSRC7_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT2_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_6_CLOCKS,						J7200_DEV_DCC6_DCC_INPUT00_CLK,				 CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_6_CLOCKS,						J7200_DEV_DCC6_DCC_INPUT01_CLK,				 CLK_J7200_BOARD_0_HFOSC1_CLK_OUT,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_6_CLOCKS,						J7200_DEV_DCC6_DCC_INPUT02_CLK,				 CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1),
	DEV_CLK(J7200_DEV_DCC2_MAIN_6_CLOCKS,						J7200_DEV_DCC6_DCC_INPUT10_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DCC2_MAIN_6_CLOCKS,						J7200_DEV_DCC6_VBUS_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_J7VC_WAKEUP_16FF_WKUP_0_CLOCKS,				J7200_DEV_WKUP_WAKEUP0_PLL_CTRL_WKUP_CLK24_CLK,		 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV24_CLK_CLK,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_J7VC_WAKEUP_16FF_WKUP_0_CLOCKS,			J7200_DEV_WKUP_WAKEUP0_WKUP_RCOSC_12P5M_CLK,		 CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK),
	DEV_CLK_OUTPUT(J7200_DEV_J7VC_WAKEUP_16FF_WKUP_0_CLOCKS,			J7200_DEV_WKUP_WAKEUP0_WKUP_RCOSC_32K_CLK,		 CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_32K_CLK),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_0_CLOCKS,					J7200_DEV_TIMER0_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_0_CLOCKS,					J7200_DEV_TIMER0_TIMER_TCLK_CLK,			 CLK_J7200_MAIN_TIMER_CLKSEL_OUT0,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_DMTIMER_DMC1MS_MAIN_0_CLOCKS,				J7200_DEV_TIMER0_TIMER_PWM,				 CLK_J7200_DMTIMER_DMC1MS_MAIN_0_TIMER_PWM),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_1_CLOCKS,					J7200_DEV_TIMER1_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_1_CLOCKS,					J7200_DEV_TIMER1_TIMER_TCLK_CLK,			 CLK_J7200_TIMER1_CASCADE_OUT0,
		1),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_2_CLOCKS,					J7200_DEV_TIMER2_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_2_CLOCKS,					J7200_DEV_TIMER2_TIMER_TCLK_CLK,			 CLK_J7200_MAIN_TIMER_CLKSEL_OUT2,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_DMTIMER_DMC1MS_MAIN_2_CLOCKS,				J7200_DEV_TIMER2_TIMER_PWM,				 CLK_J7200_DMTIMER_DMC1MS_MAIN_2_TIMER_PWM),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_3_CLOCKS,					J7200_DEV_TIMER3_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_3_CLOCKS,					J7200_DEV_TIMER3_TIMER_TCLK_CLK,			 CLK_J7200_TIMER3_CASCADE_OUT0,
		1),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_4_CLOCKS,					J7200_DEV_TIMER4_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_4_CLOCKS,					J7200_DEV_TIMER4_TIMER_TCLK_CLK,			 CLK_J7200_MAIN_TIMER_CLKSEL_OUT4,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_DMTIMER_DMC1MS_MAIN_4_CLOCKS,				J7200_DEV_TIMER4_TIMER_PWM,				 CLK_J7200_DMTIMER_DMC1MS_MAIN_4_TIMER_PWM),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_5_CLOCKS,					J7200_DEV_TIMER5_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_5_CLOCKS,					J7200_DEV_TIMER5_TIMER_TCLK_CLK,			 CLK_J7200_TIMER5_CASCADE_OUT0,
		1),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_6_CLOCKS,					J7200_DEV_TIMER6_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_6_CLOCKS,					J7200_DEV_TIMER6_TIMER_TCLK_CLK,			 CLK_J7200_MAIN_TIMER_CLKSEL_OUT6,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_DMTIMER_DMC1MS_MAIN_6_CLOCKS,				J7200_DEV_TIMER6_TIMER_PWM,				 CLK_J7200_DMTIMER_DMC1MS_MAIN_6_TIMER_PWM),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_7_CLOCKS,					J7200_DEV_TIMER7_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_7_CLOCKS,					J7200_DEV_TIMER7_TIMER_TCLK_CLK,			 CLK_J7200_TIMER7_CASCADE_OUT0,
		1),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_8_CLOCKS,					J7200_DEV_TIMER8_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_8_CLOCKS,					J7200_DEV_TIMER8_TIMER_TCLK_CLK,			 CLK_J7200_MAIN_TIMER_CLKSEL_OUT8,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_DMTIMER_DMC1MS_MAIN_8_CLOCKS,				J7200_DEV_TIMER8_TIMER_PWM,				 CLK_J7200_DMTIMER_DMC1MS_MAIN_8_TIMER_PWM),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_9_CLOCKS,					J7200_DEV_TIMER9_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_9_CLOCKS,					J7200_DEV_TIMER9_TIMER_TCLK_CLK,			 CLK_J7200_TIMER9_CASCADE_OUT0,
		1),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_10_CLOCKS,				J7200_DEV_TIMER10_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_10_CLOCKS,				J7200_DEV_TIMER10_TIMER_TCLK_CLK,			 CLK_J7200_MAIN_TIMER_CLKSEL_OUT10,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_DMTIMER_DMC1MS_MAIN_10_CLOCKS,				J7200_DEV_TIMER10_TIMER_PWM,				 CLK_J7200_DMTIMER_DMC1MS_MAIN_10_TIMER_PWM),
	DEV_CLK(J7200_DEV_GTC_R10_MAIN_0_CLOCKS,					J7200_DEV_GTC0_GTC_CLK,					 CLK_J7200_GTC_CLK_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_GTC_R10_MAIN_0_CLOCKS,					J7200_DEV_GTC0_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_11_CLOCKS,				J7200_DEV_TIMER11_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_11_CLOCKS,				J7200_DEV_TIMER11_TIMER_TCLK_CLK,			 CLK_J7200_TIMER11_CASCADE_OUT0,
		1),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_12_CLOCKS,				J7200_DEV_TIMER12_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_12_CLOCKS,				J7200_DEV_TIMER12_TIMER_TCLK_CLK,			 CLK_J7200_MAIN_TIMER_CLKSEL_OUT12,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_DMTIMER_DMC1MS_MAIN_12_CLOCKS,				J7200_DEV_TIMER12_TIMER_PWM,				 CLK_J7200_DMTIMER_DMC1MS_MAIN_12_TIMER_PWM),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_13_CLOCKS,				J7200_DEV_TIMER13_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_13_CLOCKS,				J7200_DEV_TIMER13_TIMER_TCLK_CLK,			 CLK_J7200_TIMER13_CASCADE_OUT0,
		1),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_14_CLOCKS,				J7200_DEV_TIMER14_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_14_CLOCKS,				J7200_DEV_TIMER14_TIMER_TCLK_CLK,			 CLK_J7200_MAIN_TIMER_CLKSEL_OUT14,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_DMTIMER_DMC1MS_MAIN_14_CLOCKS,				J7200_DEV_TIMER14_TIMER_PWM,				 CLK_J7200_DMTIMER_DMC1MS_MAIN_14_TIMER_PWM),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_15_CLOCKS,				J7200_DEV_TIMER15_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_15_CLOCKS,				J7200_DEV_TIMER15_TIMER_TCLK_CLK,			 CLK_J7200_TIMER15_CASCADE_OUT0,
		1),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_16_CLOCKS,				J7200_DEV_TIMER16_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_16_CLOCKS,				J7200_DEV_TIMER16_TIMER_TCLK_CLK,			 CLK_J7200_MAIN_TIMER_CLKSEL_OUT16,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_DMTIMER_DMC1MS_MAIN_16_CLOCKS,				J7200_DEV_TIMER16_TIMER_PWM,				 CLK_J7200_DMTIMER_DMC1MS_MAIN_16_TIMER_PWM),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_17_CLOCKS,				J7200_DEV_TIMER17_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_17_CLOCKS,				J7200_DEV_TIMER17_TIMER_TCLK_CLK,			 CLK_J7200_TIMER17_CASCADE_OUT0,
		1),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_18_CLOCKS,				J7200_DEV_TIMER18_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_18_CLOCKS,				J7200_DEV_TIMER18_TIMER_TCLK_CLK,			 CLK_J7200_MAIN_TIMER_CLKSEL_OUT18,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_DMTIMER_DMC1MS_MAIN_18_CLOCKS,				J7200_DEV_TIMER18_TIMER_PWM,				 CLK_J7200_DMTIMER_DMC1MS_MAIN_18_TIMER_PWM),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_19_CLOCKS,				J7200_DEV_TIMER19_TIMER_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DMTIMER_DMC1MS_MAIN_19_CLOCKS,				J7200_DEV_TIMER19_TIMER_TCLK_CLK,			 CLK_J7200_TIMER19_CASCADE_OUT0,
		1),
	DEV_CLK(J7200_DEV_ECAP_MAIN_0_CLOCKS,						J7200_DEV_ECAP0_VBUS_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_ECAP_MAIN_1_CLOCKS,						J7200_DEV_ECAP1_VBUS_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_ECAP_MAIN_2_CLOCKS,						J7200_DEV_ECAP2_VBUS_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_EHRPWM_MAIN_0_CLOCKS,						J7200_DEV_EHRPWM0_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_EHRPWM_MAIN_1_CLOCKS,						J7200_DEV_EHRPWM1_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_EHRPWM_MAIN_2_CLOCKS,						J7200_DEV_EHRPWM2_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_EHRPWM_MAIN_3_CLOCKS,						J7200_DEV_EHRPWM3_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_EHRPWM_MAIN_4_CLOCKS,						J7200_DEV_EHRPWM4_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_EHRPWM_MAIN_5_CLOCKS,						J7200_DEV_EHRPWM5_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_ELM_MAIN_0_CLOCKS,						J7200_DEV_ELM0_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_EMMC8SS_16FFC_MAIN_0_CLOCKS,					J7200_DEV_MMCSD0_EMMCSS_VBUS_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK(J7200_DEV_EMMC8SS_16FFC_MAIN_0_CLOCKS,					J7200_DEV_MMCSD0_EMMCSS_XIN_CLK,			 CLK_J7200_EMMCSD_REFCLK_SEL_OUT0,
		1),
	DEV_CLK(J7200_DEV_EMMCSD4SS_MAIN_0_CLOCKS,					J7200_DEV_MMCSD1_EMMCSDSS_IO_CLK_I,			 CLK_J7200_EMMCSD4SS_MAIN_0_EMMCSDSS_IO_CLK_O,
		1),
	DEV_CLK(J7200_DEV_EMMCSD4SS_MAIN_0_CLOCKS,					J7200_DEV_MMCSD1_EMMCSDSS_VBUS_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK(J7200_DEV_EMMCSD4SS_MAIN_0_CLOCKS,					J7200_DEV_MMCSD1_EMMCSDSS_XIN_CLK,			 CLK_J7200_EMMCSD_REFCLK_SEL_OUT1,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_EMMCSD4SS_MAIN_0_CLOCKS,				J7200_DEV_MMCSD1_EMMCSDSS_IO_CLK_O,			 CLK_J7200_EMMCSD4SS_MAIN_0_EMMCSDSS_IO_CLK_O),
	DEV_CLK(J7200_DEV_EQEP_MAIN_0_CLOCKS,						J7200_DEV_EQEP0_VBUS_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_EQEP_MAIN_1_CLOCKS,						J7200_DEV_EQEP1_VBUS_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_EQEP_MAIN_2_CLOCKS,						J7200_DEV_EQEP2_VBUS_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_ESM_J7_MAIN_MAIN_0_CLOCKS,					J7200_DEV_ESM0_CLK,					 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_ESM_J7VCL_WKUP_WKUP_0_CLOCKS,					J7200_DEV_WKUP_ESM0_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_GPIO_144_MAIN_0_CLOCKS,					J7200_DEV_GPIO0_MMR_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_GPIO_144_MAIN_2_CLOCKS,					J7200_DEV_GPIO2_MMR_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_GPIO_144_MAIN_4_CLOCKS,					J7200_DEV_GPIO4_MMR_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_GPIO_144_MAIN_6_CLOCKS,					J7200_DEV_GPIO6_MMR_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_GPMC_MAIN_0_CLOCKS,						J7200_DEV_GPMC0_FUNC_CLK,				 CLK_J7200_GPMC_FCLK_SEL_OUT0,
		1),
	DEV_CLK(J7200_DEV_GPMC_MAIN_0_CLOCKS,						J7200_DEV_GPMC0_PI_GPMC_RET_CLK,			 CLK_J7200_BOARD_0_GPMC0_CLK_OUT,
		1),
	DEV_CLK(J7200_DEV_GPMC_MAIN_0_CLOCKS,						J7200_DEV_GPMC0_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK_OUTPUT(J7200_DEV_GPMC_MAIN_0_CLOCKS,					J7200_DEV_GPMC0_PO_GPMC_DEV_CLK,			 CLK_J7200_GPMC_MAIN_0_PO_GPMC_DEV_CLK),
	DEV_CLK(J7200_DEV_I3C_MAIN_0_CLOCKS,						J7200_DEV_I3C0_I3C_PCLK_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_I3C_MAIN_0_CLOCKS,						J7200_DEV_I3C0_I3C_SCL_DI,				 CLK_J7200_BOARD_0_I3C0_SCL_OUT,
		1),
	DEV_CLK(J7200_DEV_I3C_MAIN_0_CLOCKS,						J7200_DEV_I3C0_I3C_SCLK_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK_OUTPUT(J7200_DEV_I3C_MAIN_0_CLOCKS,					J7200_DEV_I3C0_I3C_SCL_DO,				 CLK_J7200_I3C_MAIN_0_I3C_SCL_DO),
	DEV_CLK(J7200_DEV_J7VCL_CMP_EVENT_INTROUTER_MAIN_0_CLOCKS,			J7200_DEV_CMPEVENT_INTRTR0_INTR_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_J7_LED_MAIN_0_CLOCKS,						J7200_DEV_LED0_LED_CLK,					 CLK_J7200_BOARD_0_LED_CLK_OUT,
		1),
	DEV_CLK(J7200_DEV_J7_LED_MAIN_0_CLOCKS,						J7200_DEV_LED0_VBUS_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK(J7200_DEV_J7VC_MAIN_GPIOMUX_INTROUTER_MAIN_0_CLOCKS,			J7200_DEV_GPIOMUX_INTRTR0_INTR_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_J7_MAIN_PSC_WRAP_MAIN_0_CLOCKS,				J7200_DEV_PSC0_CLK,					 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_J7_MAIN_PSC_WRAP_MAIN_0_CLOCKS,				J7200_DEV_PSC0_SLOW_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		24),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_0_CLOCKS,			J7200_DEV_PBIST0_CLK1_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_0_CLOCKS,			J7200_DEV_PBIST0_CLK2_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_0_CLOCKS,			J7200_DEV_PBIST0_CLK3_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_0_CLOCKS,			J7200_DEV_PBIST0_CLK4_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_0_CLOCKS,			J7200_DEV_PBIST0_CLK5_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_0_CLOCKS,			J7200_DEV_PBIST0_CLK6_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_0_CLOCKS,			J7200_DEV_PBIST0_CLK7_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_0_CLOCKS,			J7200_DEV_PBIST0_CLK8_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_1_CLOCKS,			J7200_DEV_PBIST1_CLK1_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_1_CLOCKS,			J7200_DEV_PBIST1_CLK2_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_1_CLOCKS,			J7200_DEV_PBIST1_CLK3_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_1_CLOCKS,			J7200_DEV_PBIST1_CLK4_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_1_CLOCKS,			J7200_DEV_PBIST1_CLK5_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_1_CLOCKS,			J7200_DEV_PBIST1_CLK6_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_1_CLOCKS,			J7200_DEV_PBIST1_CLK7_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_INFRA_1_CLOCKS,			J7200_DEV_PBIST1_CLK8_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_PULSAR_0_CLOCKS,			J7200_DEV_PBIST2_CLK1_CLK,				 CLK_J7200_HSDIV1_16FFT_MAIN_14_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_PULSAR_0_CLOCKS,			J7200_DEV_PBIST2_CLK2_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_PULSAR_0_CLOCKS,			J7200_DEV_PBIST2_CLK3_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_PULSAR_0_CLOCKS,			J7200_DEV_PBIST2_CLK4_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_PULSAR_0_CLOCKS,			J7200_DEV_PBIST2_CLK5_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_PULSAR_0_CLOCKS,			J7200_DEV_PBIST2_CLK6_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_PULSAR_0_CLOCKS,			J7200_DEV_PBIST2_CLK7_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MAIN_PULSAR_0_CLOCKS,			J7200_DEV_PBIST2_CLK8_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_0_CLOCKS,				J7200_DEV_MCU_PBIST0_CLK1_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_0_CLOCKS,				J7200_DEV_MCU_PBIST0_CLK2_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		3),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_0_CLOCKS,				J7200_DEV_MCU_PBIST0_CLK3_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_0_CLOCKS,				J7200_DEV_MCU_PBIST0_CLK4_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		12),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_0_CLOCKS,				J7200_DEV_MCU_PBIST0_CLK5_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		12),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_0_CLOCKS,				J7200_DEV_MCU_PBIST0_CLK6_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		12),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_0_CLOCKS,				J7200_DEV_MCU_PBIST0_CLK7_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		12),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_0_CLOCKS,				J7200_DEV_MCU_PBIST0_CLK8_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		12),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_1_CLOCKS,				J7200_DEV_MCU_PBIST1_CLK1_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_1_CLOCKS,				J7200_DEV_MCU_PBIST1_CLK2_CLK,				 CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_1_CLOCKS,				J7200_DEV_MCU_PBIST1_CLK3_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT4_CLK,
		2),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_1_CLOCKS,				J7200_DEV_MCU_PBIST1_CLK4_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		3),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_1_CLOCKS,				J7200_DEV_MCU_PBIST1_CLK5_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_1_CLOCKS,				J7200_DEV_MCU_PBIST1_CLK6_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		12),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_1_CLOCKS,				J7200_DEV_MCU_PBIST1_CLK7_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		12),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_1_CLOCKS,				J7200_DEV_MCU_PBIST1_CLK8_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		12),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_PULSAR_0_CLOCKS,			J7200_DEV_MCU_PBIST2_CLK1_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_PULSAR_0_CLOCKS,			J7200_DEV_MCU_PBIST2_CLK2_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		12),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_PULSAR_0_CLOCKS,			J7200_DEV_MCU_PBIST2_CLK3_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		12),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_PULSAR_0_CLOCKS,			J7200_DEV_MCU_PBIST2_CLK4_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		12),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_PULSAR_0_CLOCKS,			J7200_DEV_MCU_PBIST2_CLK5_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		12),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_PULSAR_0_CLOCKS,			J7200_DEV_MCU_PBIST2_CLK6_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		12),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_PULSAR_0_CLOCKS,			J7200_DEV_MCU_PBIST2_CLK7_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		12),
	DEV_CLK(J7200_DEV_K3_PBIST_8C28P_WRAP_MCU_PULSAR_0_CLOCKS,			J7200_DEV_MCU_PBIST2_CLK8_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		12),
	DEV_CLK(J7200_DEV_USART_MAIN_0_CLOCKS,						J7200_DEV_UART0_FCLK_CLK,				 CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT0,
		1),
	DEV_CLK(J7200_DEV_USART_MAIN_0_CLOCKS,						J7200_DEV_UART0_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_14_CLOCKS,					J7200_DEV_MCAN14_MCANSS_CCLK_CLK,			 CLK_J7200_MCAN_CLK_MUX_OUT14_0,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_14_CLOCKS,					J7200_DEV_MCAN14_MCANSS_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_15_CLOCKS,					J7200_DEV_MCAN15_MCANSS_CCLK_CLK,			 CLK_J7200_MCAN_CLK_MUX_OUT15_0,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_15_CLOCKS,					J7200_DEV_MCAN15_MCANSS_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_16_CLOCKS,					J7200_DEV_MCAN16_MCANSS_CCLK_CLK,			 CLK_J7200_MCAN_CLK_MUX_OUT16_0,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_16_CLOCKS,					J7200_DEV_MCAN16_MCANSS_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_17_CLOCKS,					J7200_DEV_MCAN17_MCANSS_CCLK_CLK,			 CLK_J7200_MCAN_CLK_MUX_OUT17_0,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_17_CLOCKS,					J7200_DEV_MCAN17_MCANSS_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_0_CLOCKS,						J7200_DEV_MCAN0_MCANSS_CCLK_CLK,			 CLK_J7200_MCAN_CLK_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_0_CLOCKS,						J7200_DEV_MCAN0_MCANSS_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_1_CLOCKS,						J7200_DEV_MCAN1_MCANSS_CCLK_CLK,			 CLK_J7200_MCAN_CLK_MUX_OUT1,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_1_CLOCKS,						J7200_DEV_MCAN1_MCANSS_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_2_CLOCKS,						J7200_DEV_MCAN2_MCANSS_CCLK_CLK,			 CLK_J7200_MCAN_CLK_MUX_OUT2,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_2_CLOCKS,						J7200_DEV_MCAN2_MCANSS_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_3_CLOCKS,						J7200_DEV_MCAN3_MCANSS_CCLK_CLK,			 CLK_J7200_MCAN_CLK_MUX_OUT3,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_3_CLOCKS,						J7200_DEV_MCAN3_MCANSS_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_4_CLOCKS,						J7200_DEV_MCAN4_MCANSS_CCLK_CLK,			 CLK_J7200_MCAN_CLK_MUX_OUT4,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_4_CLOCKS,						J7200_DEV_MCAN4_MCANSS_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_5_CLOCKS,						J7200_DEV_MCAN5_MCANSS_CCLK_CLK,			 CLK_J7200_MCAN_CLK_MUX_OUT5,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_5_CLOCKS,						J7200_DEV_MCAN5_MCANSS_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_6_CLOCKS,						J7200_DEV_MCAN6_MCANSS_CCLK_CLK,			 CLK_J7200_MCAN_CLK_MUX_OUT6,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_6_CLOCKS,						J7200_DEV_MCAN6_MCANSS_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_7_CLOCKS,						J7200_DEV_MCAN7_MCANSS_CCLK_CLK,			 CLK_J7200_MCAN_CLK_MUX_OUT7,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_7_CLOCKS,						J7200_DEV_MCAN7_MCANSS_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_8_CLOCKS,						J7200_DEV_MCAN8_MCANSS_CCLK_CLK,			 CLK_J7200_MCAN_CLK_MUX_OUT8,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_8_CLOCKS,						J7200_DEV_MCAN8_MCANSS_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_9_CLOCKS,						J7200_DEV_MCAN9_MCANSS_CCLK_CLK,			 CLK_J7200_MCAN_CLK_MUX_OUT9,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_9_CLOCKS,						J7200_DEV_MCAN9_MCANSS_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_10_CLOCKS,					J7200_DEV_MCAN10_MCANSS_CCLK_CLK,			 CLK_J7200_MCAN_CLK_MUX_OUT10,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_10_CLOCKS,					J7200_DEV_MCAN10_MCANSS_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_11_CLOCKS,					J7200_DEV_MCAN11_MCANSS_CCLK_CLK,			 CLK_J7200_MCAN_CLK_MUX_OUT11,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_11_CLOCKS,					J7200_DEV_MCAN11_MCANSS_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_12_CLOCKS,					J7200_DEV_MCAN12_MCANSS_CCLK_CLK,			 CLK_J7200_MCAN_CLK_MUX_OUT12,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_12_CLOCKS,					J7200_DEV_MCAN12_MCANSS_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_13_CLOCKS,					J7200_DEV_MCAN13_MCANSS_CCLK_CLK,			 CLK_J7200_MCAN_CLK_MUX_OUT13,
		1),
	DEV_CLK(J7200_DEV_MCANSS_MAIN_13_CLOCKS,					J7200_DEV_MCAN13_MCANSS_HCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MCASP_MAIN_0_CLOCKS,						J7200_DEV_MCASP0_AUX_CLK,				 CLK_J7200_MCASP_AUXCLK_SEL_OUT0,
		1),
	DEV_CLK(J7200_DEV_MCASP_MAIN_0_CLOCKS,						J7200_DEV_MCASP0_MCASP_ACLKR_PIN,			 CLK_J7200_BOARD_0_MCASP0_ACLKR_OUT,
		1),
	DEV_CLK(J7200_DEV_MCASP_MAIN_0_CLOCKS,						J7200_DEV_MCASP0_MCASP_ACLKX_PIN,			 CLK_J7200_BOARD_0_MCASP0_ACLKX_OUT,
		1),
	DEV_CLK(J7200_DEV_MCASP_MAIN_0_CLOCKS,						J7200_DEV_MCASP0_MCASP_AHCLKR_PIN,			 CLK_J7200_MCASP_AHCLKR_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_MCASP_MAIN_0_CLOCKS,						J7200_DEV_MCASP0_MCASP_AHCLKX_PIN,			 CLK_J7200_MCASP_AHCLKX_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_MCASP_MAIN_0_CLOCKS,						J7200_DEV_MCASP0_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK_OUTPUT(J7200_DEV_MCASP_MAIN_0_CLOCKS,					J7200_DEV_MCASP0_MCASP_ACLKR_POUT,			 CLK_J7200_MCASP_MAIN_0_MCASP_ACLKR_POUT),
	DEV_CLK_OUTPUT(J7200_DEV_MCASP_MAIN_0_CLOCKS,					J7200_DEV_MCASP0_MCASP_ACLKX_POUT,			 CLK_J7200_MCASP_MAIN_0_MCASP_ACLKX_POUT),
	DEV_CLK_OUTPUT(J7200_DEV_MCASP_MAIN_0_CLOCKS,					J7200_DEV_MCASP0_MCASP_AHCLKR_POUT,			 CLK_J7200_MCASP_MAIN_0_MCASP_AHCLKR_POUT),
	DEV_CLK_OUTPUT(J7200_DEV_MCASP_MAIN_0_CLOCKS,					J7200_DEV_MCASP0_MCASP_AHCLKX_POUT,			 CLK_J7200_MCASP_MAIN_0_MCASP_AHCLKX_POUT),
	DEV_CLK(J7200_DEV_MCASP_MAIN_1_CLOCKS,						J7200_DEV_MCASP1_AUX_CLK,				 CLK_J7200_MCASP_AUXCLK_SEL_OUT1,
		1),
	DEV_CLK(J7200_DEV_MCASP_MAIN_1_CLOCKS,						J7200_DEV_MCASP1_MCASP_ACLKR_PIN,			 CLK_J7200_BOARD_0_MCASP1_ACLKR_OUT,
		1),
	DEV_CLK(J7200_DEV_MCASP_MAIN_1_CLOCKS,						J7200_DEV_MCASP1_MCASP_ACLKX_PIN,			 CLK_J7200_BOARD_0_MCASP1_ACLKX_OUT,
		1),
	DEV_CLK(J7200_DEV_MCASP_MAIN_1_CLOCKS,						J7200_DEV_MCASP1_MCASP_AHCLKR_PIN,			 CLK_J7200_MCASP_AHCLKR_MUX_OUT1,
		1),
	DEV_CLK(J7200_DEV_MCASP_MAIN_1_CLOCKS,						J7200_DEV_MCASP1_MCASP_AHCLKX_PIN,			 CLK_J7200_MCASP_AHCLKX_MUX_OUT1,
		1),
	DEV_CLK(J7200_DEV_MCASP_MAIN_1_CLOCKS,						J7200_DEV_MCASP1_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK_OUTPUT(J7200_DEV_MCASP_MAIN_1_CLOCKS,					J7200_DEV_MCASP1_MCASP_ACLKR_POUT,			 CLK_J7200_MCASP_MAIN_1_MCASP_ACLKR_POUT),
	DEV_CLK_OUTPUT(J7200_DEV_MCASP_MAIN_1_CLOCKS,					J7200_DEV_MCASP1_MCASP_ACLKX_POUT,			 CLK_J7200_MCASP_MAIN_1_MCASP_ACLKX_POUT),
	DEV_CLK_OUTPUT(J7200_DEV_MCASP_MAIN_1_CLOCKS,					J7200_DEV_MCASP1_MCASP_AHCLKR_POUT,			 CLK_J7200_MCASP_MAIN_1_MCASP_AHCLKR_POUT),
	DEV_CLK_OUTPUT(J7200_DEV_MCASP_MAIN_1_CLOCKS,					J7200_DEV_MCASP1_MCASP_AHCLKX_POUT,			 CLK_J7200_MCASP_MAIN_1_MCASP_AHCLKX_POUT),
	DEV_CLK(J7200_DEV_MCASP_MAIN_2_CLOCKS,						J7200_DEV_MCASP2_AUX_CLK,				 CLK_J7200_MCASP_AUXCLK_SEL_OUT2,
		1),
	DEV_CLK(J7200_DEV_MCASP_MAIN_2_CLOCKS,						J7200_DEV_MCASP2_MCASP_ACLKR_PIN,			 CLK_J7200_BOARD_0_MCASP2_ACLKR_OUT,
		1),
	DEV_CLK(J7200_DEV_MCASP_MAIN_2_CLOCKS,						J7200_DEV_MCASP2_MCASP_ACLKX_PIN,			 CLK_J7200_BOARD_0_MCASP2_ACLKX_OUT,
		1),
	DEV_CLK(J7200_DEV_MCASP_MAIN_2_CLOCKS,						J7200_DEV_MCASP2_MCASP_AHCLKR_PIN,			 CLK_J7200_MCASP_AHCLKR_MUX_OUT2,
		1),
	DEV_CLK(J7200_DEV_MCASP_MAIN_2_CLOCKS,						J7200_DEV_MCASP2_MCASP_AHCLKX_PIN,			 CLK_J7200_MCASP_AHCLKX_MUX_OUT2,
		1),
	DEV_CLK(J7200_DEV_MCASP_MAIN_2_CLOCKS,						J7200_DEV_MCASP2_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK_OUTPUT(J7200_DEV_MCASP_MAIN_2_CLOCKS,					J7200_DEV_MCASP2_MCASP_ACLKR_POUT,			 CLK_J7200_MCASP_MAIN_2_MCASP_ACLKR_POUT),
	DEV_CLK_OUTPUT(J7200_DEV_MCASP_MAIN_2_CLOCKS,					J7200_DEV_MCASP2_MCASP_ACLKX_POUT,			 CLK_J7200_MCASP_MAIN_2_MCASP_ACLKX_POUT),
	DEV_CLK_OUTPUT(J7200_DEV_MCASP_MAIN_2_CLOCKS,					J7200_DEV_MCASP2_MCASP_AHCLKR_POUT,			 CLK_J7200_MCASP_MAIN_2_MCASP_AHCLKR_POUT),
	DEV_CLK_OUTPUT(J7200_DEV_MCASP_MAIN_2_CLOCKS,					J7200_DEV_MCASP2_MCASP_AHCLKX_POUT,			 CLK_J7200_MCASP_MAIN_2_MCASP_AHCLKX_POUT),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_0_CLOCKS,					J7200_DEV_I2C0_CLK,					 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_0_CLOCKS,					J7200_DEV_I2C0_PISCL,					 CLK_J7200_BOARD_0_I2C0_SCL_OUT,
		1),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_0_CLOCKS,					J7200_DEV_I2C0_PISYS_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
		2),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_1_CLOCKS,					J7200_DEV_I2C1_CLK,					 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_1_CLOCKS,					J7200_DEV_I2C1_PISCL,					 CLK_J7200_BOARD_0_I2C1_SCL_OUT,
		1),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_1_CLOCKS,					J7200_DEV_I2C1_PISYS_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
		2),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_2_CLOCKS,					J7200_DEV_I2C2_CLK,					 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_2_CLOCKS,					J7200_DEV_I2C2_PISCL,					 CLK_J7200_BOARD_0_I2C2_SCL_OUT,
		1),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_2_CLOCKS,					J7200_DEV_I2C2_PISYS_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
		2),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_3_CLOCKS,					J7200_DEV_I2C3_CLK,					 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_3_CLOCKS,					J7200_DEV_I2C3_PISCL,					 CLK_J7200_BOARD_0_I2C3_SCL_OUT,
		1),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_3_CLOCKS,					J7200_DEV_I2C3_PISYS_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
		2),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_4_CLOCKS,					J7200_DEV_I2C4_CLK,					 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_4_CLOCKS,					J7200_DEV_I2C4_PISCL,					 CLK_J7200_BOARD_0_I2C4_SCL_OUT,
		1),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_4_CLOCKS,					J7200_DEV_I2C4_PISYS_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
		2),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_5_CLOCKS,					J7200_DEV_I2C5_CLK,					 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_5_CLOCKS,					J7200_DEV_I2C5_PISCL,					 CLK_J7200_BOARD_0_I2C5_SCL_OUT,
		1),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_5_CLOCKS,					J7200_DEV_I2C5_PISYS_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
		2),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_6_CLOCKS,					J7200_DEV_I2C6_CLK,					 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_6_CLOCKS,					J7200_DEV_I2C6_PISCL,					 CLK_J7200_BOARD_0_I2C6_SCL_OUT,
		1),
	DEV_CLK(J7200_DEV_MSHSI2C_MAIN_6_CLOCKS,					J7200_DEV_I2C6_PISYS_CLK,				 CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
		2),
	DEV_CLK_OUTPUT(J7200_DEV_NAVSS256VCL_MAIN_0_CLOCKS,				J7200_DEV_NAVSS0_CPTS0_GENF2,				 CLK_J7200_NAVSS256VCL_MAIN_0_CPTS0_GENF2),
	DEV_CLK_OUTPUT(J7200_DEV_NAVSS256VCL_MAIN_0_CLOCKS,				J7200_DEV_NAVSS0_CPTS0_GENF3,				 CLK_J7200_NAVSS256VCL_MAIN_0_CPTS0_GENF3),
	DEV_CLK_OUTPUT(J7200_DEV_NAVSS256VCL_MAIN_0_CLOCKS,				J7200_DEV_NAVSS0_CPTS0_GENF4,				 CLK_J7200_NAVSS256VCL_MAIN_0_CPTS0_GENF4),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_CPTS_0_CLOCKS,				J7200_DEV_NAVSS0_CPTS_0_RCLK,				 CLK_J7200_NAVSS_CPTS_RCLK_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_CPTS_0_CLOCKS,				J7200_DEV_NAVSS0_CPTS_0_VBUSP_GCLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_NAVSS256VCL_MAIN_0_CPTS_0_CLOCKS,			J7200_DEV_NAVSS0_CPTS_0_TS_GENF0,			 CLK_J7200_NAVSS256VCL_MAIN_0_CPTS_0_TS_GENF0),
	DEV_CLK_OUTPUT(J7200_DEV_NAVSS256VCL_MAIN_0_CPTS_0_CLOCKS,			J7200_DEV_NAVSS0_CPTS_0_TS_GENF1,			 CLK_J7200_NAVSS256VCL_MAIN_0_CPTS_0_TS_GENF1),
	DEV_CLK(J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_P0_A72_DUAL_1MB_0_CLOCKS, J7200_DEV_A72SS0_CORE0_ARM_CLK_CLK,			 CLK_J7200_HSDIV0_16FFT_MAIN_8_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_P0_A72_DUAL_1MB_1_CLOCKS, J7200_DEV_A72SS0_CORE1_ARM_CLK_CLK,			 CLK_J7200_HSDIV0_16FFT_MAIN_8_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_DTI_0_CLOCKS,				J7200_DEV_NAVSS0_DTI_0_CLK_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_MODSS_INTA_0_CLOCKS,			J7200_DEV_NAVSS0_MODSS_INTA_0_SYS_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_MODSS_INTA_1_CLOCKS,			J7200_DEV_NAVSS0_MODSS_INTA_1_SYS_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_UDMASS_INTA_0_CLOCKS,			J7200_DEV_NAVSS0_UDMASS_INTA_0_SYS_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_PROXY_0_CLOCKS,				J7200_DEV_NAVSS0_PROXY_0_CLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_RINGACC_0_CLOCKS,				J7200_DEV_NAVSS0_RINGACC_0_SYS_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_UDMAP_0_CLOCKS,				J7200_DEV_NAVSS0_UDMAP_0_SYS_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_INTR_0_CLOCKS,				J7200_DEV_NAVSS0_INTR_ROUTER_0_INTR_CLK,		 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_0_CLOCKS,				J7200_DEV_NAVSS0_MAILBOX_0_VCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_1_CLOCKS,				J7200_DEV_NAVSS0_MAILBOX_1_VCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_2_CLOCKS,				J7200_DEV_NAVSS0_MAILBOX_2_VCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_3_CLOCKS,				J7200_DEV_NAVSS0_MAILBOX_3_VCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_4_CLOCKS,				J7200_DEV_NAVSS0_MAILBOX_4_VCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_5_CLOCKS,				J7200_DEV_NAVSS0_MAILBOX_5_VCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_6_CLOCKS,				J7200_DEV_NAVSS0_MAILBOX_6_VCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_7_CLOCKS,				J7200_DEV_NAVSS0_MAILBOX_7_VCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_8_CLOCKS,				J7200_DEV_NAVSS0_MAILBOX_8_VCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_9_CLOCKS,				J7200_DEV_NAVSS0_MAILBOX_9_VCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_10_CLOCKS,				J7200_DEV_NAVSS0_MAILBOX_10_VCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_MAILBOX_11_CLOCKS,				J7200_DEV_NAVSS0_MAILBOX_11_VCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_SPINLOCK_0_CLOCKS,				J7200_DEV_NAVSS0_SPINLOCK_0_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_MCRC_0_CLOCKS,				J7200_DEV_NAVSS0_MCRC_0_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_TBU_0_CLOCKS,				J7200_DEV_NAVSS0_TBU_0_CLK_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_TIMERMGR_0_CLOCKS,				J7200_DEV_NAVSS0_TIMERMGR_0_EON_TICK_EVT,		 CLK_J7200_NAVSS256VCL_MAIN_0_CPTS_0_TS_GENF0,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_TIMERMGR_0_CLOCKS,				J7200_DEV_NAVSS0_TIMERMGR_0_VCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_TIMERMGR_1_CLOCKS,				J7200_DEV_NAVSS0_TIMERMGR_1_EON_TICK_EVT,		 CLK_J7200_NAVSS256VCL_MAIN_0_CPTS_0_TS_GENF1,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_TIMERMGR_1_CLOCKS,				J7200_DEV_NAVSS0_TIMERMGR_1_VCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_CBA_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_CPTS_RCLK_CLK,			 CLK_J7200_PCIE1_CPTS_RCLK_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE0_REFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN0_REFCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE0_RXCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN0_RXCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE0_RXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN0_RXFCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE0_TXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN0_TXFCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE0_TXMCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN0_TXMCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE1_REFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN1_REFCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE1_RXCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN1_RXCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE1_RXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN1_RXFCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE1_TXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN1_TXFCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE1_TXMCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN1_TXMCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE2_REFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN2_REFCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE2_RXCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN2_RXCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE2_RXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN2_RXFCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE2_TXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN2_TXFCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE2_TXMCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN2_TXMCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE3_REFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN3_REFCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE3_RXCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN3_RXCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE3_RXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN3_RXFCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE3_TXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN3_TXFCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_LANE3_TXMCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN3_TXMCLK,
		1),
	DEV_CLK(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,					J7200_DEV_PCIE1_PCIE_PM_CLK,				 CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,				J7200_DEV_PCIE1_PCIE_LANE0_TXCLK,			 CLK_J7200_PCIE_G3X4_128_MAIN_1_PCIE_LANE0_TXCLK),
	DEV_CLK_OUTPUT(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,				J7200_DEV_PCIE1_PCIE_LANE1_TXCLK,			 CLK_J7200_PCIE_G3X4_128_MAIN_1_PCIE_LANE1_TXCLK),
	DEV_CLK_OUTPUT(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,				J7200_DEV_PCIE1_PCIE_LANE2_TXCLK,			 CLK_J7200_PCIE_G3X4_128_MAIN_1_PCIE_LANE2_TXCLK),
	DEV_CLK_OUTPUT(J7200_DEV_PCIE_G3X4_128_MAIN_1_CLOCKS,				J7200_DEV_PCIE1_PCIE_LANE3_TXCLK,			 CLK_J7200_PCIE_G3X4_128_MAIN_1_PCIE_LANE3_TXCLK),
	DEV_CLK(J7200_DEV_PULSAR_SL_MAIN_0_R5_0_CLOCKS,					J7200_DEV_R5FSS0_CORE0_CPU_CLK,				 CLK_J7200_HSDIV1_16FFT_MAIN_14_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_PULSAR_SL_MAIN_0_R5_0_CLOCKS,					J7200_DEV_R5FSS0_CORE0_INTERFACE_CLK,			 CLK_J7200_HSDIV1_16FFT_MAIN_14_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_PULSAR_SL_MAIN_0_R5_0_CLOCKS,					J7200_DEV_R5FSS0_CORE0_INTERFACE_PHASE,			 CLK_J7200_HSDIV1_16FFT_MAIN_14_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_PULSAR_SL_MAIN_0_R5_1_CLOCKS,					J7200_DEV_R5FSS0_CORE1_CPU_CLK,				 CLK_J7200_HSDIV1_16FFT_MAIN_14_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_PULSAR_SL_MAIN_0_R5_1_CLOCKS,					J7200_DEV_R5FSS0_CORE1_INTERFACE_CLK,			 CLK_J7200_HSDIV1_16FFT_MAIN_14_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_PULSAR_SL_MAIN_0_R5_1_CLOCKS,					J7200_DEV_R5FSS0_CORE1_INTERFACE_PHASE,			 CLK_J7200_HSDIV1_16FFT_MAIN_14_HSDIVOUT0_CLK,
		1),
	DEV_CLK(J7200_DEV_RTI_CFG1_MAIN_A72_0_CLOCKS,					J7200_DEV_RTI0_RTI_CLK,					 CLK_J7200_MAIN_WWDT_CLKSEL_OUT0,
		1),
	DEV_CLK(J7200_DEV_RTI_CFG1_MAIN_A72_0_CLOCKS,					J7200_DEV_RTI0_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_RTI_CFG1_MAIN_A72_1_CLOCKS,					J7200_DEV_RTI1_RTI_CLK,					 CLK_J7200_MAIN_WWDT_CLKSEL_OUT1,
		1),
	DEV_CLK(J7200_DEV_RTI_CFG1_MAIN_A72_1_CLOCKS,					J7200_DEV_RTI1_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_RTI_CFG1_MAIN_R5_0_CLOCKS,					J7200_DEV_RTI28_RTI_CLK,				 CLK_J7200_MAIN_WWDT_CLKSEL_OUT6,
		1),
	DEV_CLK(J7200_DEV_RTI_CFG1_MAIN_R5_0_CLOCKS,					J7200_DEV_RTI28_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_RTI_CFG1_MAIN_R5_1_CLOCKS,					J7200_DEV_RTI29_RTI_CLK,				 CLK_J7200_MAIN_WWDT_CLKSEL_OUT7,
		1),
	DEV_CLK(J7200_DEV_RTI_CFG1_MAIN_R5_1_CLOCKS,					J7200_DEV_RTI29_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_SPI_MAIN_0_CLOCKS,						J7200_DEV_MCSPI0_CLKSPIREF_CLK,				 CLK_J7200_POSTDIV2_16FFT_MAIN_0_HSDIVOUT5_CLK,
		1),
	DEV_CLK(J7200_DEV_SPI_MAIN_0_CLOCKS,						J7200_DEV_MCSPI0_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK_OUTPUT(J7200_DEV_SPI_MAIN_0_CLOCKS,					J7200_DEV_MCSPI0_IO_CLKSPIO_CLK,			 CLK_J7200_SPI_MAIN_0_IO_CLKSPIO_CLK),
	DEV_CLK(J7200_DEV_SPI_MAIN_1_CLOCKS,						J7200_DEV_MCSPI1_CLKSPIREF_CLK,				 CLK_J7200_POSTDIV2_16FFT_MAIN_0_HSDIVOUT5_CLK,
		1),
	DEV_CLK(J7200_DEV_SPI_MAIN_1_CLOCKS,						J7200_DEV_MCSPI1_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK_OUTPUT(J7200_DEV_SPI_MAIN_1_CLOCKS,					J7200_DEV_MCSPI1_IO_CLKSPIO_CLK,			 CLK_J7200_SPI_MAIN_1_IO_CLKSPIO_CLK),
	DEV_CLK(J7200_DEV_SPI_MAIN_2_CLOCKS,						J7200_DEV_MCSPI2_CLKSPIREF_CLK,				 CLK_J7200_POSTDIV2_16FFT_MAIN_0_HSDIVOUT5_CLK,
		1),
	DEV_CLK(J7200_DEV_SPI_MAIN_2_CLOCKS,						J7200_DEV_MCSPI2_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK_OUTPUT(J7200_DEV_SPI_MAIN_2_CLOCKS,					J7200_DEV_MCSPI2_IO_CLKSPIO_CLK,			 CLK_J7200_SPI_MAIN_2_IO_CLKSPIO_CLK),
	DEV_CLK(J7200_DEV_SPI_MAIN_3_CLOCKS,						J7200_DEV_MCSPI3_CLKSPIREF_CLK,				 CLK_J7200_POSTDIV2_16FFT_MAIN_0_HSDIVOUT5_CLK,
		1),
	DEV_CLK(J7200_DEV_SPI_MAIN_3_CLOCKS,						J7200_DEV_MCSPI3_IO_CLKSPII_CLK,			 CLK_J7200_SPI3_CLK_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_SPI_MAIN_3_CLOCKS,						J7200_DEV_MCSPI3_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK_OUTPUT(J7200_DEV_SPI_MAIN_3_CLOCKS,					J7200_DEV_MCSPI3_IO_CLKSPIO_CLK,			 CLK_J7200_SPI_MAIN_3_IO_CLKSPIO_CLK),
	DEV_CLK(J7200_DEV_SPI_MAIN_4_CLOCKS,						J7200_DEV_MCSPI4_CLKSPIREF_CLK,				 CLK_J7200_POSTDIV2_16FFT_MAIN_0_HSDIVOUT5_CLK,
		1),
	DEV_CLK(J7200_DEV_SPI_MAIN_4_CLOCKS,						J7200_DEV_MCSPI4_IO_CLKSPII_CLK,			 CLK_J7200_SPI_MAIN_4_IO_CLKSPIO_CLK,
		1),
	DEV_CLK(J7200_DEV_SPI_MAIN_4_CLOCKS,						J7200_DEV_MCSPI4_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK_OUTPUT(J7200_DEV_SPI_MAIN_4_CLOCKS,					J7200_DEV_MCSPI4_IO_CLKSPIO_CLK,			 CLK_J7200_SPI_MAIN_4_IO_CLKSPIO_CLK),
	DEV_CLK(J7200_DEV_SPI_MAIN_5_CLOCKS,						J7200_DEV_MCSPI5_CLKSPIREF_CLK,				 CLK_J7200_POSTDIV2_16FFT_MAIN_0_HSDIVOUT5_CLK,
		1),
	DEV_CLK(J7200_DEV_SPI_MAIN_5_CLOCKS,						J7200_DEV_MCSPI5_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK_OUTPUT(J7200_DEV_SPI_MAIN_5_CLOCKS,					J7200_DEV_MCSPI5_IO_CLKSPIO_CLK,			 CLK_J7200_SPI_MAIN_5_IO_CLKSPIO_CLK),
	DEV_CLK(J7200_DEV_SPI_MAIN_6_CLOCKS,						J7200_DEV_MCSPI6_CLKSPIREF_CLK,				 CLK_J7200_POSTDIV2_16FFT_MAIN_0_HSDIVOUT5_CLK,
		1),
	DEV_CLK(J7200_DEV_SPI_MAIN_6_CLOCKS,						J7200_DEV_MCSPI6_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK_OUTPUT(J7200_DEV_SPI_MAIN_6_CLOCKS,					J7200_DEV_MCSPI6_IO_CLKSPIO_CLK,			 CLK_J7200_SPI_MAIN_6_IO_CLKSPIO_CLK),
	DEV_CLK(J7200_DEV_SPI_MAIN_7_CLOCKS,						J7200_DEV_MCSPI7_CLKSPIREF_CLK,				 CLK_J7200_POSTDIV2_16FFT_MAIN_0_HSDIVOUT5_CLK,
		1),
	DEV_CLK(J7200_DEV_SPI_MAIN_7_CLOCKS,						J7200_DEV_MCSPI7_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK_OUTPUT(J7200_DEV_SPI_MAIN_7_CLOCKS,					J7200_DEV_MCSPI7_IO_CLKSPIO_CLK,			 CLK_J7200_SPI_MAIN_7_IO_CLKSPIO_CLK),
	DEV_CLK(J7200_DEV_USART_MAIN_1_CLOCKS,						J7200_DEV_UART1_FCLK_CLK,				 CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT1,
		1),
	DEV_CLK(J7200_DEV_USART_MAIN_1_CLOCKS,						J7200_DEV_UART1_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_USART_MAIN_2_CLOCKS,						J7200_DEV_UART2_FCLK_CLK,				 CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT2,
		1),
	DEV_CLK(J7200_DEV_USART_MAIN_2_CLOCKS,						J7200_DEV_UART2_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_USART_MAIN_3_CLOCKS,						J7200_DEV_UART3_FCLK_CLK,				 CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT3,
		1),
	DEV_CLK(J7200_DEV_USART_MAIN_3_CLOCKS,						J7200_DEV_UART3_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_USART_MAIN_4_CLOCKS,						J7200_DEV_UART4_FCLK_CLK,				 CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT4,
		1),
	DEV_CLK(J7200_DEV_USART_MAIN_4_CLOCKS,						J7200_DEV_UART4_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_USART_MAIN_5_CLOCKS,						J7200_DEV_UART5_FCLK_CLK,				 CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT5,
		1),
	DEV_CLK(J7200_DEV_USART_MAIN_5_CLOCKS,						J7200_DEV_UART5_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_USART_MAIN_6_CLOCKS,						J7200_DEV_UART6_FCLK_CLK,				 CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT6,
		1),
	DEV_CLK(J7200_DEV_USART_MAIN_6_CLOCKS,						J7200_DEV_UART6_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_USART_MAIN_7_CLOCKS,						J7200_DEV_UART7_FCLK_CLK,				 CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT7,
		1),
	DEV_CLK(J7200_DEV_USART_MAIN_7_CLOCKS,						J7200_DEV_UART7_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_USART_MAIN_8_CLOCKS,						J7200_DEV_UART8_FCLK_CLK,				 CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT8,
		1),
	DEV_CLK(J7200_DEV_USART_MAIN_8_CLOCKS,						J7200_DEV_UART8_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_USART_MAIN_9_CLOCKS,						J7200_DEV_UART9_FCLK_CLK,				 CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT9,
		1),
	DEV_CLK(J7200_DEV_USART_MAIN_9_CLOCKS,						J7200_DEV_UART9_VBUSP_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_USB3P0SS_16FFC_MAIN_0_CLOCKS,					J7200_DEV_USB0_ACLK_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_USB3P0SS_16FFC_MAIN_0_CLOCKS,					J7200_DEV_USB0_BUF_CLK,					 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK(J7200_DEV_USB3P0SS_16FFC_MAIN_0_CLOCKS,					J7200_DEV_USB0_CLK_LPM_CLK,				 CLK_J7200_POSTDIV2_16FFT_MAIN_1_HSDIVOUT7_CLK,
		1),
	DEV_CLK(J7200_DEV_USB3P0SS_16FFC_MAIN_0_CLOCKS,					J7200_DEV_USB0_PCLK_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_USB3P0SS_16FFC_MAIN_0_CLOCKS,					J7200_DEV_USB0_PIPE_REFCLK,				 CLK_J7200_USB0_SERDES_REFCLK_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_USB3P0SS_16FFC_MAIN_0_CLOCKS,					J7200_DEV_USB0_PIPE_RXCLK,				 CLK_J7200_USB0_SERDES_RXCLK_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_USB3P0SS_16FFC_MAIN_0_CLOCKS,					J7200_DEV_USB0_PIPE_RXFCLK,				 CLK_J7200_USB0_SERDES_RXFCLK_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_USB3P0SS_16FFC_MAIN_0_CLOCKS,					J7200_DEV_USB0_PIPE_TXFCLK,				 CLK_J7200_USB0_SERDES_TXFCLK_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_USB3P0SS_16FFC_MAIN_0_CLOCKS,					J7200_DEV_USB0_PIPE_TXMCLK,				 CLK_J7200_USB0_SERDES_TXMCLK_MUX_OUT0,
		1),
	DEV_CLK(J7200_DEV_USB3P0SS_16FFC_MAIN_0_CLOCKS,					J7200_DEV_USB0_USB2_APB_PCLK_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_USB3P0SS_16FFC_MAIN_0_CLOCKS,					J7200_DEV_USB0_USB2_REFCLOCK_CLK,			 CLK_J7200_USB0_REFCLK_SEL_OUT0,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_USB3P0SS_16FFC_MAIN_0_CLOCKS,				J7200_DEV_USB0_PIPE_TXCLK,				 CLK_J7200_USB3P0SS_16FFC_MAIN_0_PIPE_TXCLK),
	DEV_CLK(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,					J7200_DEV_SERDES_10G1_CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,					J7200_DEV_SERDES_10G1_CORE_REF_CLK,			 CLK_J7200_SERDES0_CORE_REFCLK_OUT0,
		1),
	DEV_CLK(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,					J7200_DEV_SERDES_10G1_IP1_LN0_TXCLK,			 CLK_J7200_CPSW_5XUSS_MAIN_0_SERDES3_TXCLK,
		1),
	DEV_CLK(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,					J7200_DEV_SERDES_10G1_IP1_LN1_TXCLK,			 CLK_J7200_CPSW_5XUSS_MAIN_0_SERDES4_TXCLK,
		1),
	DEV_CLK(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,					J7200_DEV_SERDES_10G1_IP1_LN2_TXCLK,			 CLK_J7200_CPSW_5XUSS_MAIN_0_SERDES1_TXCLK,
		1),
	DEV_CLK(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,					J7200_DEV_SERDES_10G1_IP1_LN3_TXCLK,			 CLK_J7200_CPSW_5XUSS_MAIN_0_SERDES2_TXCLK,
		1),
	DEV_CLK(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,					J7200_DEV_SERDES_10G1_IP2_LN0_TXCLK,			 CLK_J7200_PCIE_G3X4_128_MAIN_1_PCIE_LANE0_TXCLK,
		1),
	DEV_CLK(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,					J7200_DEV_SERDES_10G1_IP2_LN1_TXCLK,			 CLK_J7200_PCIE_G3X4_128_MAIN_1_PCIE_LANE1_TXCLK,
		1),
	DEV_CLK(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,					J7200_DEV_SERDES_10G1_IP2_LN2_TXCLK,			 CLK_J7200_PCIE_G3X4_128_MAIN_1_PCIE_LANE2_TXCLK,
		1),
	DEV_CLK(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,					J7200_DEV_SERDES_10G1_IP2_LN3_TXCLK,			 CLK_J7200_PCIE_G3X4_128_MAIN_1_PCIE_LANE3_TXCLK,
		1),
	DEV_CLK(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,					J7200_DEV_SERDES_10G1_IP3_LN1_TXCLK,			 CLK_J7200_USB3P0SS_16FFC_MAIN_0_PIPE_TXCLK,
		1),
	DEV_CLK(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,					J7200_DEV_SERDES_10G1_IP3_LN3_TXCLK,			 CLK_J7200_USB3P0SS_16FFC_MAIN_0_PIPE_TXCLK,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN0_REFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN0_REFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN0_RXCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN0_RXCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN0_RXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN0_RXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN0_TXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN0_TXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN0_TXMCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN0_TXMCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN1_REFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN1_REFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN1_RXCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN1_RXCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN1_RXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN1_RXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN1_TXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN1_TXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN1_TXMCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN1_TXMCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN2_REFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN2_REFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN2_RXCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN2_RXCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN2_RXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN2_RXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN2_TXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN2_TXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN2_TXMCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN2_TXMCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN3_REFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN3_REFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN3_RXCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN3_RXCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN3_RXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN3_RXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN3_TXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN3_TXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP1_LN3_TXMCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN3_TXMCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN0_REFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN0_REFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN0_RXCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN0_RXCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN0_RXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN0_RXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN0_TXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN0_TXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN0_TXMCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN0_TXMCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN1_REFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN1_REFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN1_RXCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN1_RXCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN1_RXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN1_RXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN1_TXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN1_TXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN1_TXMCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN1_TXMCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN2_REFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN2_REFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN2_RXCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN2_RXCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN2_RXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN2_RXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN2_TXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN2_TXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN2_TXMCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN2_TXMCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN3_REFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN3_REFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN3_RXCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN3_RXCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN3_RXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN3_RXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN3_TXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN3_TXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP2_LN3_TXMCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN3_TXMCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP3_LN1_REFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN1_REFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP3_LN1_RXCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN1_RXCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP3_LN1_RXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN1_RXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP3_LN1_TXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN1_TXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP3_LN1_TXMCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN1_TXMCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP3_LN3_REFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN3_REFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP3_LN3_RXCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN3_RXCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP3_LN3_RXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN3_RXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP3_LN3_TXFCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN3_TXFCLK),
	DEV_CLK_OUTPUT(J7200_DEV_WIZ16B8M4CT2_MAIN_1_CLOCKS,				J7200_DEV_SERDES_10G1_IP3_LN3_TXMCLK,			 CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN3_TXMCLK),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_MODSS_0_CLOCKS,				J7200_DEV_NAVSS0_MODSS_VD2CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_UDMASS_0_CLOCKS,				J7200_DEV_NAVSS0_UDMASS_VD2CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_NAVSS256VCL_MAIN_0_VIRTSS_0_CLOCKS,				J7200_DEV_NAVSS0_VIRTSS_VD2CLK,				 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1),
	DEV_CLK(J7200_DEV_DEBUGSS_K3_WRAP_CV0_MAIN_0_CLOCKS,				J7200_DEV_DEBUGSS_WRAP0_ATB_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		2),
	DEV_CLK(J7200_DEV_DEBUGSS_K3_WRAP_CV0_MAIN_0_CLOCKS,				J7200_DEV_DEBUGSS_WRAP0_CORE_CLK,			 CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4),
	DEV_CLK(J7200_DEV_DEBUGSS_K3_WRAP_CV0_MAIN_0_CLOCKS,				J7200_DEV_DEBUGSS_WRAP0_JTAG_TCK,			 CLK_J7200_BOARD_0_TCK_OUT,
		1),
	DEV_CLK(J7200_DEV_DEBUGSS_K3_WRAP_CV0_MAIN_0_CLOCKS,				J7200_DEV_DEBUGSS_WRAP0_TREXPT_CLK,			 CLK_J7200_HSDIV4_16FFT_MAIN_2_HSDIVOUT3_CLK,
		1),
	DEV_CLK_OUTPUT(J7200_DEV_DEBUGSS_K3_WRAP_CV0_MAIN_0_CLOCKS,			J7200_DEV_DEBUGSS_WRAP0_CSTPIU_TRACECLK,		 CLK_J7200_DEBUGSS_K3_WRAP_CV0_MAIN_0_CSTPIU_TRACECLK),
};
static struct dev_clk MAIN_dev_clk[ARRAY_SIZE(MAIN_dev_clk_data)] __attribute__((__section__(".bss.devgroup.MAIN")));
static const struct dev_clk_data DMSC_INTERNAL_dev_clk_data[] __attribute__((__section__(".const.devgroup.DMSC_INTERNAL"))) = {
	DEV_CLK(J7200_DEV_NAVSS_MCU_J7_MCU_0_RINGACC_0_CLOCKS, J7200_DEV_MCU_NAVSS0_RINGACC0_SYS_CLK, CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK, 1),
};
static struct dev_clk DMSC_INTERNAL_dev_clk[ARRAY_SIZE(DMSC_INTERNAL_dev_clk_data)] __attribute__((__section__(".bss.devgroup.DMSC_INTERNAL")));

const struct devgroup soc_devgroups[] = {
	[PM_DEVGRP_00] =   {
		.dev_clk_data	= MCU_WAKEUP_dev_clk_data,
		.dev_clk	= MCU_WAKEUP_dev_clk,
		.clk_idx	= 8U,
	},
	[PM_DEVGRP_01] =   {
		.dev_clk_data	= MAIN_dev_clk_data,
		.dev_clk	= MAIN_dev_clk,
		.clk_idx	= 193U,
	},
	[PM_DEVGRP_DMSC] = {
		.dev_clk_data	= DMSC_INTERNAL_dev_clk_data,
		.dev_clk	= DMSC_INTERNAL_dev_clk,
		.clk_idx	= 1U,
	},
};
const size_t soc_devgroup_count = ARRAY_SIZE(soc_devgroups);

const struct soc_device_data *const soc_psc_multiple_domains[] = {
	[J7200_PSC_MULTIPLE_COMPUTE_CLUSTER_J7VCL_TB_VDC_MAIN_0_PBIST_WRAP] = compute_cluster_j7vcl_tb_vdc_main_0_pbist_wrap_domains,
};

const struct dev_data *const soc_device_data[] = {
	[J7200_DEV_MCU_ADC0] = &j7200_dev_adc12_core_mcu_0,
	[J7200_DEV_MCU_ADC1] = &j7200_dev_adc12_core_mcu_1,
	[J7200_DEV_ATL0] = &j7200_dev_atl_main_0,
	[J7200_DEV_COMPUTE_CLUSTER0] = &j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0,
	[J7200_DEV_A72SS0] = &j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_p0_a72_dual_1mb,
	[J7200_DEV_COMPUTE_CLUSTER0_CFG_WRAP] = &j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_cfg_wrap,
	[J7200_DEV_COMPUTE_CLUSTER0_CLEC] = &j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_clec,
	[J7200_DEV_COMPUTE_CLUSTER0_CORE_CORE] = &j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_core_core,
	[J7200_DEV_DDR0] = &j7200_dev_ddr32v256ss_16ffc_ew_main_0,
	[J7200_DEV_COMPUTE_CLUSTER0_DEBUG_WRAP] = &j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_debug_wrap,
	[J7200_DEV_COMPUTE_CLUSTER0_DIVH2_DIVH0] = &j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_divh2_divh0,
	[J7200_DEV_COMPUTE_CLUSTER0_DIVP_TFT0] = &j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_divp_tft0,
	[J7200_DEV_COMPUTE_CLUSTER0_DMSC_WRAP] = &j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_dmsc_wrap,
	[J7200_DEV_COMPUTE_CLUSTER0_EN_MSMC_DOMAIN] = &j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_en_msmc_domain,
	[J7200_DEV_COMPUTE_CLUSTER0_GIC500SS] = &j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_gic500ss,
	[J7200_DEV_COMPUTE_CLUSTER0_PBIST_WRAP] = &j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_pbist_wrap,
	[J7200_DEV_MCU_CPSW0] = &j7200_dev_cpsw_2guss_mcu_0,
	[J7200_DEV_CPSW0] = &j7200_dev_cpsw_5xuss_main_0,
	[J7200_DEV_CPT2_AGGR0] = &j7200_dev_cpt2_aggregator32_main_rc_0,
	[J7200_DEV_CPT2_AGGR1] = &j7200_dev_cpt2_aggregator32_main_infra_0,
	[J7200_DEV_WKUP_DMSC0] = &j7200_dev_dmsc_wkup_0,
	[J7200_DEV_CPT2_AGGR2] = &j7200_dev_cpt2_aggregator32_main_hc_0,
	[J7200_DEV_MCU_CPT2_AGGR0] = &j7200_dev_cpt2_aggregator32_mcu_0,
	[J7200_DEV_CPT2_AGGR3] = &j7200_dev_cpt2_aggregator32_main_mv_0,
	[J7200_DEV_CPSW_TX_RGMII0] = &j7200_dev_j7vcl_cpsw_tx_rgmii_wrap_main_0,
	[J7200_DEV_STM0] = &j7200_dev_cxstm500ss_main_0,
	[J7200_DEV_DCC0] = &j7200_dev_dcc2_main_0,
	[J7200_DEV_DCC1] = &j7200_dev_dcc2_main_1,
	[J7200_DEV_DCC2] = &j7200_dev_dcc2_main_2,
	[J7200_DEV_DCC3] = &j7200_dev_dcc2_main_3,
	[J7200_DEV_DCC4] = &j7200_dev_dcc2_main_4,
	[J7200_DEV_MCU_TIMER0] = &j7200_dev_dmtimer_dmc1ms_mcu_0,
	[J7200_DEV_DCC5] = &j7200_dev_dcc2_main_5,
	[J7200_DEV_DCC6] = &j7200_dev_dcc2_main_6,
	[J7200_DEV_MAIN0] = &j7200_dev_j7vc_main_16ff_main_0,
	[J7200_DEV_WKUP_WAKEUP0] = &j7200_dev_j7vc_wakeup_16ff_wkup_0,
	[J7200_DEV_MCU_DCC0] = &j7200_dev_dcc2_mcu_0,
	[J7200_DEV_MCU_DCC1] = &j7200_dev_dcc2_mcu_1,
	[J7200_DEV_MCU_DCC2] = &j7200_dev_dcc2_mcu_2,
	[J7200_DEV_TIMER0] = &j7200_dev_dmtimer_dmc1ms_main_0,
	[J7200_DEV_TIMER1] = &j7200_dev_dmtimer_dmc1ms_main_1,
	[J7200_DEV_TIMER2] = &j7200_dev_dmtimer_dmc1ms_main_2,
	[J7200_DEV_TIMER3] = &j7200_dev_dmtimer_dmc1ms_main_3,
	[J7200_DEV_TIMER4] = &j7200_dev_dmtimer_dmc1ms_main_4,
	[J7200_DEV_TIMER5] = &j7200_dev_dmtimer_dmc1ms_main_5,
	[J7200_DEV_TIMER6] = &j7200_dev_dmtimer_dmc1ms_main_6,
	[J7200_DEV_TIMER7] = &j7200_dev_dmtimer_dmc1ms_main_7,
	[J7200_DEV_TIMER8] = &j7200_dev_dmtimer_dmc1ms_main_8,
	[J7200_DEV_TIMER9] = &j7200_dev_dmtimer_dmc1ms_main_9,
	[J7200_DEV_TIMER10] = &j7200_dev_dmtimer_dmc1ms_main_10,
	[J7200_DEV_GTC0] = &j7200_dev_gtc_r10_main_0,
	[J7200_DEV_TIMER11] = &j7200_dev_dmtimer_dmc1ms_main_11,
	[J7200_DEV_TIMER12] = &j7200_dev_dmtimer_dmc1ms_main_12,
	[J7200_DEV_TIMER13] = &j7200_dev_dmtimer_dmc1ms_main_13,
	[J7200_DEV_TIMER14] = &j7200_dev_dmtimer_dmc1ms_main_14,
	[J7200_DEV_TIMER15] = &j7200_dev_dmtimer_dmc1ms_main_15,
	[J7200_DEV_TIMER16] = &j7200_dev_dmtimer_dmc1ms_main_16,
	[J7200_DEV_TIMER17] = &j7200_dev_dmtimer_dmc1ms_main_17,
	[J7200_DEV_TIMER18] = &j7200_dev_dmtimer_dmc1ms_main_18,
	[J7200_DEV_TIMER19] = &j7200_dev_dmtimer_dmc1ms_main_19,
	[J7200_DEV_MCU_TIMER1] = &j7200_dev_dmtimer_dmc1ms_mcu_1,
	[J7200_DEV_MCU_TIMER2] = &j7200_dev_dmtimer_dmc1ms_mcu_2,
	[J7200_DEV_MCU_TIMER3] = &j7200_dev_dmtimer_dmc1ms_mcu_3,
	[J7200_DEV_MCU_TIMER4] = &j7200_dev_dmtimer_dmc1ms_mcu_4,
	[J7200_DEV_MCU_TIMER5] = &j7200_dev_dmtimer_dmc1ms_mcu_5,
	[J7200_DEV_MCU_TIMER6] = &j7200_dev_dmtimer_dmc1ms_mcu_6,
	[J7200_DEV_MCU_TIMER7] = &j7200_dev_dmtimer_dmc1ms_mcu_7,
	[J7200_DEV_MCU_TIMER8] = &j7200_dev_dmtimer_dmc1ms_mcu_8,
	[J7200_DEV_MCU_TIMER9] = &j7200_dev_dmtimer_dmc1ms_mcu_9,
	[J7200_DEV_ECAP0] = &j7200_dev_ecap_main_0,
	[J7200_DEV_ECAP1] = &j7200_dev_ecap_main_1,
	[J7200_DEV_ECAP2] = &j7200_dev_ecap_main_2,
	[J7200_DEV_EHRPWM0] = &j7200_dev_ehrpwm_main_0,
	[J7200_DEV_EHRPWM1] = &j7200_dev_ehrpwm_main_1,
	[J7200_DEV_EHRPWM2] = &j7200_dev_ehrpwm_main_2,
	[J7200_DEV_EHRPWM3] = &j7200_dev_ehrpwm_main_3,
	[J7200_DEV_EHRPWM4] = &j7200_dev_ehrpwm_main_4,
	[J7200_DEV_EHRPWM5] = &j7200_dev_ehrpwm_main_5,
	[J7200_DEV_ELM0] = &j7200_dev_elm_main_0,
	[J7200_DEV_EMIF_DATA_0_VD] = &j7200_dev_emif_data_0_VD,
	[J7200_DEV_MMCSD0] = &j7200_dev_emmc8ss_16ffc_main_0,
	[J7200_DEV_MMCSD1] = &j7200_dev_emmcsd4ss_main_0,
	[J7200_DEV_EQEP0] = &j7200_dev_eqep_main_0,
	[J7200_DEV_EQEP1] = &j7200_dev_eqep_main_1,
	[J7200_DEV_EQEP2] = &j7200_dev_eqep_main_2,
	[J7200_DEV_ESM0] = &j7200_dev_esm_j7_main_main_0,
	[J7200_DEV_MCU_ESM0] = &j7200_dev_esm_mcu_mcu_0,
	[J7200_DEV_WKUP_ESM0] = &j7200_dev_esm_j7vcl_wkup_wkup_0,
	[J7200_DEV_MCU_FSS0] = &j7200_dev_fss_mcu_0,
	[J7200_DEV_MCU_FSS0_FSAS_0] = &j7200_dev_fss_mcu_0_fsas_0,
	[J7200_DEV_MCU_FSS0_HYPERBUS1P0_0] = &j7200_dev_fss_mcu_0_hyperbus1p0_0,
	[J7200_DEV_MCU_FSS0_OSPI_0] = &j7200_dev_fss_mcu_0_ospi_0,
	[J7200_DEV_MCU_FSS0_OSPI_1] = &j7200_dev_fss_mcu_0_ospi_1,
	[J7200_DEV_GPIO0] = &j7200_dev_gpio_144_main_0,
	[J7200_DEV_GPIO2] = &j7200_dev_gpio_144_main_2,
	[J7200_DEV_GPIO4] = &j7200_dev_gpio_144_main_4,
	[J7200_DEV_GPIO6] = &j7200_dev_gpio_144_main_6,
	[J7200_DEV_WKUP_GPIO0] = &j7200_dev_gpio_144_wkup_0,
	[J7200_DEV_WKUP_GPIO1] = &j7200_dev_gpio_144_wkup_1,
	[J7200_DEV_GPMC0] = &j7200_dev_gpmc_main_0,
	[J7200_DEV_I3C0] = &j7200_dev_i3c_main_0,
	[J7200_DEV_MCU_I3C0] = &j7200_dev_i3c_mcu_0,
	[J7200_DEV_MCU_I3C1] = &j7200_dev_i3c_mcu_1,
	[J7200_DEV_CMPEVENT_INTRTR0] = &j7200_dev_j7vcl_cmp_event_introuter_main_0,
	[J7200_DEV_LED0] = &j7200_dev_j7_led_main_0,
	[J7200_DEV_MAIN2MCU_LVL_INTRTR0] = &j7200_dev_j7_main2mcu_lvl_introuter_main_0,
	[J7200_DEV_MAIN2MCU_PLS_INTRTR0] = &j7200_dev_j7_main2mcu_pls_introuter_main_0,
	[J7200_DEV_GPIOMUX_INTRTR0] = &j7200_dev_j7vc_main_gpiomux_introuter_main_0,
	[J7200_DEV_WKUP_PORZ_SYNC0] = &j7200_dev_j7_main_porz_sync_stretch_wkup_0,
	[J7200_DEV_PSC0] = &j7200_dev_j7_main_psc_wrap_main_0.drv_data.dev_data,
	[J7200_DEV_TIMESYNC_INTRTR0] = &j7200_dev_j7_timesync_event_introuter_main_0,
	[J7200_DEV_WKUP_GPIOMUX_INTRTR0] = &j7200_dev_j7_wkup_gpiomux_introuter_wkup_0,
	[J7200_DEV_WKUP_PSC0] = &j7200_dev_j7_wkup_psc_wrap_wkup_0.drv_data.dev_data,
	[J7200_DEV_PBIST0] = &j7200_dev_k3_pbist_8c28p_wrap_main_infra_0,
	[J7200_DEV_PBIST1] = &j7200_dev_k3_pbist_8c28p_wrap_main_infra_1,
	[J7200_DEV_PBIST2] = &j7200_dev_k3_pbist_8c28p_wrap_main_pulsar_0,
	[J7200_DEV_MCU_PBIST0] = &j7200_dev_k3_pbist_8c28p_wrap_mcu_0,
	[J7200_DEV_MCU_PBIST1] = &j7200_dev_k3_pbist_8c28p_wrap_mcu_1,
	[J7200_DEV_MCU_PBIST2] = &j7200_dev_k3_pbist_8c28p_wrap_mcu_pulsar_0,
	[J7200_DEV_WKUP_DDPA0] = &j7200_dev_k3_ddpa_wkup_0,
	[J7200_DEV_UART0] = &j7200_dev_usart_main_0,
	[J7200_DEV_MCU_UART0] = &j7200_dev_usart_mcu_0,
	[J7200_DEV_MCAN14] = &j7200_dev_mcanss_main_14,
	[J7200_DEV_MCAN15] = &j7200_dev_mcanss_main_15,
	[J7200_DEV_MCAN16] = &j7200_dev_mcanss_main_16,
	[J7200_DEV_MCAN17] = &j7200_dev_mcanss_main_17,
	[J7200_DEV_WKUP_VTM0] = &j7200_dev_k3vtm_n16ffc_wkup_0,
	[J7200_DEV_MAIN2WKUPMCU_VD] = &j7200_dev_main2wkupmcu_VD,
	[J7200_DEV_MCAN0] = &j7200_dev_mcanss_main_0,
	[J7200_DEV_BOARD0] = &j7200_dev_board_0,
	[J7200_DEV_MCAN1] = &j7200_dev_mcanss_main_1,
	[J7200_DEV_MCAN2] = &j7200_dev_mcanss_main_2,
	[J7200_DEV_MCAN3] = &j7200_dev_mcanss_main_3,
	[J7200_DEV_MCAN4] = &j7200_dev_mcanss_main_4,
	[J7200_DEV_MCAN5] = &j7200_dev_mcanss_main_5,
	[J7200_DEV_MCAN6] = &j7200_dev_mcanss_main_6,
	[J7200_DEV_MCAN7] = &j7200_dev_mcanss_main_7,
	[J7200_DEV_MCAN8] = &j7200_dev_mcanss_main_8,
	[J7200_DEV_MCAN9] = &j7200_dev_mcanss_main_9,
	[J7200_DEV_MCAN10] = &j7200_dev_mcanss_main_10,
	[J7200_DEV_MCAN11] = &j7200_dev_mcanss_main_11,
	[J7200_DEV_MCAN12] = &j7200_dev_mcanss_main_12,
	[J7200_DEV_MCAN13] = &j7200_dev_mcanss_main_13,
	[J7200_DEV_MCU_MCAN0] = &j7200_dev_mcanss_mcu_0,
	[J7200_DEV_MCU_MCAN1] = &j7200_dev_mcanss_mcu_1,
	[J7200_DEV_MCASP0] = &j7200_dev_mcasp_main_0,
	[J7200_DEV_MCASP1] = &j7200_dev_mcasp_main_1,
	[J7200_DEV_MCASP2] = &j7200_dev_mcasp_main_2,
	[J7200_DEV_I2C0] = &j7200_dev_mshsi2c_main_0,
	[J7200_DEV_I2C1] = &j7200_dev_mshsi2c_main_1,
	[J7200_DEV_I2C2] = &j7200_dev_mshsi2c_main_2,
	[J7200_DEV_I2C3] = &j7200_dev_mshsi2c_main_3,
	[J7200_DEV_I2C4] = &j7200_dev_mshsi2c_main_4,
	[J7200_DEV_I2C5] = &j7200_dev_mshsi2c_main_5,
	[J7200_DEV_I2C6] = &j7200_dev_mshsi2c_main_6,
	[J7200_DEV_MCU_I2C0] = &j7200_dev_mshsi2c_mcu_0,
	[J7200_DEV_MCU_I2C1] = &j7200_dev_mshsi2c_mcu_1,
	[J7200_DEV_WKUP_I2C0] = &j7200_dev_mshsi2c_wkup_0,
	[J7200_DEV_NAVSS0] = &j7200_dev_navss256vcl_main_0,
	[J7200_DEV_NAVSS0_CPTS_0] = &j7200_dev_navss256vcl_main_0_cpts_0,
	[J7200_DEV_A72SS0_CORE0] = &j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_p0_a72_dual_1mb_0,
	[J7200_DEV_A72SS0_CORE1] = &j7200_dev_compute_cluster_j7vcl_tb_vdc_main_0_p0_a72_dual_1mb_1,
	[J7200_DEV_NAVSS0_DTI_0] = &j7200_dev_navss256vcl_main_0_dti_0,
	[J7200_DEV_NAVSS0_MODSS_INTA_0] = &j7200_dev_navss256vcl_main_0_modss_inta_0,
	[J7200_DEV_NAVSS0_MODSS_INTA_1] = &j7200_dev_navss256vcl_main_0_modss_inta_1,
	[J7200_DEV_NAVSS0_UDMASS_INTA_0] = &j7200_dev_navss256vcl_main_0_udmass_inta_0,
	[J7200_DEV_NAVSS0_PROXY_0] = &j7200_dev_navss256vcl_main_0_proxy_0,
	[J7200_DEV_NAVSS0_RINGACC_0] = &j7200_dev_navss256vcl_main_0_ringacc_0,
	[J7200_DEV_NAVSS0_UDMAP_0] = &j7200_dev_navss256vcl_main_0_udmap_0,
	[J7200_DEV_NAVSS0_INTR_ROUTER_0] = &j7200_dev_navss256vcl_main_0_intr_0,
	[J7200_DEV_NAVSS0_MAILBOX_0] = &j7200_dev_navss256vcl_main_0_mailbox_0,
	[J7200_DEV_NAVSS0_MAILBOX_1] = &j7200_dev_navss256vcl_main_0_mailbox_1,
	[J7200_DEV_NAVSS0_MAILBOX_2] = &j7200_dev_navss256vcl_main_0_mailbox_2,
	[J7200_DEV_NAVSS0_MAILBOX_3] = &j7200_dev_navss256vcl_main_0_mailbox_3,
	[J7200_DEV_NAVSS0_MAILBOX_4] = &j7200_dev_navss256vcl_main_0_mailbox_4,
	[J7200_DEV_NAVSS0_MAILBOX_5] = &j7200_dev_navss256vcl_main_0_mailbox_5,
	[J7200_DEV_NAVSS0_MAILBOX_6] = &j7200_dev_navss256vcl_main_0_mailbox_6,
	[J7200_DEV_NAVSS0_MAILBOX_7] = &j7200_dev_navss256vcl_main_0_mailbox_7,
	[J7200_DEV_NAVSS0_MAILBOX_8] = &j7200_dev_navss256vcl_main_0_mailbox_8,
	[J7200_DEV_NAVSS0_MAILBOX_9] = &j7200_dev_navss256vcl_main_0_mailbox_9,
	[J7200_DEV_NAVSS0_MAILBOX_10] = &j7200_dev_navss256vcl_main_0_mailbox_10,
	[J7200_DEV_NAVSS0_MAILBOX_11] = &j7200_dev_navss256vcl_main_0_mailbox_11,
	[J7200_DEV_NAVSS0_SPINLOCK_0] = &j7200_dev_navss256vcl_main_0_spinlock_0,
	[J7200_DEV_NAVSS0_MCRC_0] = &j7200_dev_navss256vcl_main_0_mcrc_0,
	[J7200_DEV_NAVSS0_TBU_0] = &j7200_dev_navss256vcl_main_0_tbu_0,
	[J7200_DEV_NAVSS0_TIMERMGR_0] = &j7200_dev_navss256vcl_main_0_timermgr_0,
	[J7200_DEV_NAVSS0_TIMERMGR_1] = &j7200_dev_navss256vcl_main_0_timermgr_1,
	[J7200_DEV_MCU_NAVSS0] = &j7200_dev_navss_mcu_j7_mcu_0,
	[J7200_DEV_MCU_NAVSS0_UDMASS_INTA_0] = &j7200_dev_navss_mcu_j7_mcu_0_udmass_inta_0,
	[J7200_DEV_MCU_NAVSS0_PROXY0] = &j7200_dev_navss_mcu_j7_mcu_0_proxy_0,
	[J7200_DEV_MCU_NAVSS0_RINGACC0] = &j7200_dev_navss_mcu_j7_mcu_0_ringacc_0,
	[J7200_DEV_MCU_NAVSS0_UDMAP_0] = &j7200_dev_navss_mcu_j7_mcu_0_udmap_0,
	[J7200_DEV_MCU_NAVSS0_INTR_0] = &j7200_dev_navss_mcu_j7_mcu_0_intr_0,
	[J7200_DEV_MCU_NAVSS0_MCRC_0] = &j7200_dev_navss_mcu_j7_mcu_0_mcrc_0,
	[J7200_DEV_PCIE1] = &j7200_dev_pcie_g3x4_128_main_1,
	[J7200_DEV_R5FSS0] = &j7200_dev_pulsar_sl_main_0,
	[J7200_DEV_R5FSS0_CORE0] = &j7200_dev_pulsar_sl_main_0_R5_0,
	[J7200_DEV_R5FSS0_CORE1] = &j7200_dev_pulsar_sl_main_0_R5_1,
	[J7200_DEV_MCU_R5FSS0] = &j7200_dev_pulsar_sl_mcu_0,
	[J7200_DEV_MCU_R5FSS0_CORE0] = &j7200_dev_pulsar_sl_mcu_0_R5_0,
	[J7200_DEV_MCU_R5FSS0_CORE1] = &j7200_dev_pulsar_sl_mcu_0_R5_1,
	[J7200_DEV_RTI0] = &j7200_dev_rti_cfg1_main_a72_0,
	[J7200_DEV_RTI1] = &j7200_dev_rti_cfg1_main_a72_1,
	[J7200_DEV_RTI28] = &j7200_dev_rti_cfg1_main_r5_0,
	[J7200_DEV_RTI29] = &j7200_dev_rti_cfg1_main_r5_1,
	[J7200_DEV_MCU_RTI0] = &j7200_dev_rti_cfg1_mcu_0,
	[J7200_DEV_MCU_RTI1] = &j7200_dev_rti_cfg1_mcu_1,
	[J7200_DEV_MCU_SA2_UL0] = &j7200_dev_sa2_ul_mcu_0,
	[J7200_DEV_MCSPI0] = &j7200_dev_spi_main_0,
	[J7200_DEV_MCSPI1] = &j7200_dev_spi_main_1,
	[J7200_DEV_MCSPI2] = &j7200_dev_spi_main_2,
	[J7200_DEV_MCSPI3] = &j7200_dev_spi_main_3,
	[J7200_DEV_MCSPI4] = &j7200_dev_spi_main_4,
	[J7200_DEV_MCSPI5] = &j7200_dev_spi_main_5,
	[J7200_DEV_MCSPI6] = &j7200_dev_spi_main_6,
	[J7200_DEV_MCSPI7] = &j7200_dev_spi_main_7,
	[J7200_DEV_MCU_MCSPI0] = &j7200_dev_spi_mcu_0,
	[J7200_DEV_MCU_MCSPI1] = &j7200_dev_spi_mcu_1,
	[J7200_DEV_MCU_MCSPI2] = &j7200_dev_spi_mcu_2,
	[J7200_DEV_UART1] = &j7200_dev_usart_main_1,
	[J7200_DEV_UART2] = &j7200_dev_usart_main_2,
	[J7200_DEV_UART3] = &j7200_dev_usart_main_3,
	[J7200_DEV_UART4] = &j7200_dev_usart_main_4,
	[J7200_DEV_UART5] = &j7200_dev_usart_main_5,
	[J7200_DEV_UART6] = &j7200_dev_usart_main_6,
	[J7200_DEV_UART7] = &j7200_dev_usart_main_7,
	[J7200_DEV_UART8] = &j7200_dev_usart_main_8,
	[J7200_DEV_UART9] = &j7200_dev_usart_main_9,
	[J7200_DEV_WKUP_UART0] = &j7200_dev_usart_wkup_0,
	[J7200_DEV_USB0] = &j7200_dev_usb3p0ss_16ffc_main_0,
	[J7200_DEV_SERDES_10G1] = &j7200_dev_wiz16b8m4ct2_main_1,
	[J7200_DEV_WKUPMCU2MAIN_VD] = &j7200_dev_wkupmcu2main_VD,
	[J7200_DEV_NAVSS0_MODSS] = &j7200_dev_navss256vcl_main_0_modss_0,
	[J7200_DEV_NAVSS0_UDMASS] = &j7200_dev_navss256vcl_main_0_udmass_0,
	[J7200_DEV_NAVSS0_VIRTSS] = &j7200_dev_navss256vcl_main_0_virtss_0,
	[J7200_DEV_MCU_NAVSS0_MODSS] = &j7200_dev_navss_mcu_j7_mcu_0_modss_0,
	[J7200_DEV_MCU_NAVSS0_UDMASS] = &j7200_dev_navss_mcu_j7_mcu_0_udmass_0,
	[J7200_DEV_DEBUGSS_WRAP0] = &j7200_dev_debugss_k3_wrap_cv0_main_0,
	[J7200_DEV_FFI_MAIN_INFRA_CBASS_VD] = &j7200_dev_ffi_main_infra_cbass_VD,
	[J7200_DEV_FFI_MAIN_IP_CBASS_VD] = &j7200_dev_ffi_main_ip_cbass_VD,
	[J7200_DEV_FFI_MAIN_RC_CBASS_VD] = &j7200_dev_ffi_main_rc_cbass_VD,
};

struct device soc_devices[ARRAY_SIZE(soc_device_data)];
const size_t soc_device_count = ARRAY_SIZE(soc_device_data);

struct device *const this_dev = soc_devices + J7200_DEV_WKUP_DMSC0;
