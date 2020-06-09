/*
 * System Firmware Source File
 *
 * Host IDs for AM64X device
 *
 * Data version: 200505_104840
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef AM64X_HOSTS_H
#define AM64X_HOSTS_H

/** DMSC(Secure): Device Management and Security Control */
#define HOST_ID_DMSC (0U)
/** MAIN_0_R5_0(Secure): Cortex R5_0 context 0 on Main island(BOOT) */
#define HOST_ID_MAIN_0_R5_0 (35U)
/** MAIN_0_R5_1(Non Secure): Cortex R5_0 context 1 on Main island */
#define HOST_ID_MAIN_0_R5_1 (36U)
/** MAIN_0_R5_2(Secure): Cortex R5_0 context 2 on Main island */
#define HOST_ID_MAIN_0_R5_2 (37U)
/** MAIN_0_R5_3(Non Secure): Cortex R5_0 context 3 on Main island */
#define HOST_ID_MAIN_0_R5_3 (38U)
/** A53_0(Secure): Cortex a53 context 0 on Main islana - ATF */
#define HOST_ID_A53_0 (10U)
/** A53_1(Non Secure): Cortex A53 context 1 on Main island - EL2/Hyp */
#define HOST_ID_A53_1 (11U)
/** A53_2(Non Secure): Cortex A53 context 2 on Main island - VM/OS1 */
#define HOST_ID_A53_2 (12U)
/** A53_3(Non Secure): Cortex A53 context 3 on Main island - VM2/OS2 */
#define HOST_ID_A53_3 (13U)
/** M4_0(Non Secure): M4 */
#define HOST_ID_M4_0 (30U)
/** MAIN_1_R5_0(Secure): Cortex R5_1 context 0 on Main island */
#define HOST_ID_MAIN_1_R5_0 (40U)
/** MAIN_1_R5_1(Non Secure): Cortex R5_1 context 1 on Main island */
#define HOST_ID_MAIN_1_R5_1 (41U)
/** MAIN_1_R5_2(Secure): Cortex R5_1 context 2 on Main island */
#define HOST_ID_MAIN_1_R5_2 (42U)
/** MAIN_1_R5_3(Non Secure): Cortex R5_1 context 3 on Main island */
#define HOST_ID_MAIN_1_R5_3 (43U)
/** ICSSG_0(Non Secure): ICSSG context 0 on Main island */
#define HOST_ID_ICSSG_0 (50U)

/**
 * Host catch all. Used in board configuration resource assignments to define
 * resource ranges useable by all hosts. Cannot be used
 */
#define HOST_ID_ALL (128U)

/** Number of unique hosts on the SoC */
#define HOST_ID_CNT (15U)

#endif /* AM64X_HOSTS_H */
