/*
 * System Firmware Source File
 *
 * Host IDs for J721E device
 *
 * Data version: 200529_213657
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef J721E_HOSTS_H
#define J721E_HOSTS_H

/** DMSC(Secure): Device Management and Security Control */
#define HOST_ID_DMSC (0U)
/** MCU_0_R5_0(Non Secure): Cortex R5 context 0 on MCU island */
#define HOST_ID_MCU_0_R5_0 (3U)
/** MCU_0_R5_1(Secure): Cortex R5 context 1 on MCU island(Boot) */
#define HOST_ID_MCU_0_R5_1 (4U)
/** MCU_0_R5_2(Non Secure): Cortex R5 context 2 on MCU island */
#define HOST_ID_MCU_0_R5_2 (5U)
/** MCU_0_R5_3(Secure): Cortex R5 context 3 on MCU island */
#define HOST_ID_MCU_0_R5_3 (6U)
/** A72_0(Secure): Cortex A72 context 0 on Main island */
#define HOST_ID_A72_0 (10U)
/** A72_1(Secure): Cortex A72 context 1 on Main island */
#define HOST_ID_A72_1 (11U)
/** A72_2(Non Secure): Cortex A72 context 2 on Main island */
#define HOST_ID_A72_2 (12U)
/** A72_3(Non Secure): Cortex A72 context 3 on Main island */
#define HOST_ID_A72_3 (13U)
/** A72_4(Non Secure): Cortex A72 context 4 on Main island */
#define HOST_ID_A72_4 (14U)
/** C7X_0(Secure): C7x Context 0 on Main island */
#define HOST_ID_C7X_0 (20U)
/** C7X_1(Non Secure): C7x context 1 on Main island */
#define HOST_ID_C7X_1 (21U)
/** C6X_0_0(Secure): C6x_0 Context 0 on Main island */
#define HOST_ID_C6X_0_0 (25U)
/** C6X_0_1(Non Secure): C6x_0 context 1 on Main island */
#define HOST_ID_C6X_0_1 (26U)
/** C6X_1_0(Secure): C6x_1 Context 0 on Main island */
#define HOST_ID_C6X_1_0 (27U)
/** C6X_1_1(Non Secure): C6x_1 context 1 on Main island */
#define HOST_ID_C6X_1_1 (28U)
/** GPU_0(Non Secure): RGX context 0 on Main island */
#define HOST_ID_GPU_0 (30U)
/** MAIN_0_R5_0(Non Secure): Cortex R5_0 context 0 on Main island */
#define HOST_ID_MAIN_0_R5_0 (35U)
/** MAIN_0_R5_1(Secure): Cortex R5_0 context 1 on Main island */
#define HOST_ID_MAIN_0_R5_1 (36U)
/** MAIN_0_R5_2(Non Secure): Cortex R5_0 context 2 on Main island */
#define HOST_ID_MAIN_0_R5_2 (37U)
/** MAIN_0_R5_3(Secure): Cortex R5_0 context 3 on MCU island */
#define HOST_ID_MAIN_0_R5_3 (38U)
/** MAIN_1_R5_0(Non Secure): Cortex R5_1 context 0 on Main island */
#define HOST_ID_MAIN_1_R5_0 (40U)
/** MAIN_1_R5_1(Secure): Cortex R5_1 context 1 on Main island */
#define HOST_ID_MAIN_1_R5_1 (41U)
/** MAIN_1_R5_2(Non Secure): Cortex R5_1 context 2 on Main island */
#define HOST_ID_MAIN_1_R5_2 (42U)
/** MAIN_1_R5_3(Secure): Cortex R5_1 context 3 on MCU island */
#define HOST_ID_MAIN_1_R5_3 (43U)
/** ICSSG_0(Non Secure): ICSSG context 0 on Main island */
#define HOST_ID_ICSSG_0 (50U)

/**
 * Host catch all. Used in board configuration resource assignments to define
 * resource ranges useable by all hosts. Cannot be used
 */
#define HOST_ID_ALL (128U)

/** Number of unique hosts on the SoC */
#define HOST_ID_CNT (26U)

#endif /* J721E_HOSTS_H */
