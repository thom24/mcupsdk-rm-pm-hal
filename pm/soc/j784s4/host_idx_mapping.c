/*
 * Data version: 230112_095811
 *
 * Copyright (C) 2019-2023, Texas Instruments Incorporated
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
#include <soc/host_idx_mapping.h>
#include <soc/j784s4/hosts.h>

const u8 soc_host_indexes[254] = {
	[HOST_ID_TIFS] = 0U,
	[HOST_ID_MCU_0_R5_0] = 1U,
	[HOST_ID_MCU_0_R5_1] = 2U,
	[HOST_ID_MCU_0_R5_2] = 3U,
	[HOST_ID_MCU_0_R5_3] = 4U,
	[HOST_ID_A72_0] = 5U,
	[HOST_ID_A72_1] = 6U,
	[HOST_ID_A72_2] = 7U,
	[HOST_ID_A72_3] = 8U,
	[HOST_ID_A72_4] = 9U,
	[HOST_ID_A72_5] = 10U,
	[HOST_ID_A72_6] = 11U,
	[HOST_ID_A72_7] = 12U,
	[HOST_ID_C7X_0_0] = 13U,
	[HOST_ID_C7X_0_1] = 14U,
	[HOST_ID_C7X_1_0] = 15U,
	[HOST_ID_C7X_1_1] = 16U,
	[HOST_ID_C7X_2_0] = 17U,
	[HOST_ID_C7X_2_1] = 18U,
	[HOST_ID_C7X_3_0] = 19U,
	[HOST_ID_C7X_3_1] = 20U,
	[HOST_ID_GPU_0] = 21U,
	[HOST_ID_MAIN_0_R5_0] = 22U,
	[HOST_ID_MAIN_0_R5_1] = 23U,
	[HOST_ID_MAIN_0_R5_2] = 24U,
	[HOST_ID_MAIN_0_R5_3] = 25U,
	[HOST_ID_MAIN_1_R5_0] = 26U,
	[HOST_ID_MAIN_1_R5_1] = 27U,
	[HOST_ID_MAIN_1_R5_2] = 28U,
	[HOST_ID_MAIN_1_R5_3] = 29U,
	[HOST_ID_MAIN_2_R5_0] = 30U,
	[HOST_ID_MAIN_2_R5_1] = 31U,
	[HOST_ID_MAIN_2_R5_2] = 32U,
	[HOST_ID_MAIN_2_R5_3] = 33U,
	[HOST_ID_DM2TIFS] = 34U,
	[HOST_ID_TIFS2DM] = 35U,
	[HOST_ID_HSM] = 36U,
	[1U] = HOST_IDX_NONE,
	[2U] = HOST_IDX_NONE,
	[7U] = HOST_IDX_NONE,
	[8U] = HOST_IDX_NONE,
	[9U] = HOST_IDX_NONE,
	[18U] = HOST_IDX_NONE,
	[19U] = HOST_IDX_NONE,
	[28U] = HOST_IDX_NONE,
	[29U] = HOST_IDX_NONE,
	[31U] = HOST_IDX_NONE,
	[32U] = HOST_IDX_NONE,
	[33U] = HOST_IDX_NONE,
	[34U] = HOST_IDX_NONE,
	[39U] = HOST_IDX_NONE,
	[44U] = HOST_IDX_NONE,
	[49U] = HOST_IDX_NONE,
	[50U] = HOST_IDX_NONE,
	[51U] = HOST_IDX_NONE,
	[52U] = HOST_IDX_NONE,
	[53U] = HOST_IDX_NONE,
	[54U] = HOST_IDX_NONE,
	[55U] = HOST_IDX_NONE,
	[56U] = HOST_IDX_NONE,
	[57U] = HOST_IDX_NONE,
	[58U] = HOST_IDX_NONE,
	[59U] = HOST_IDX_NONE,
	[60U] = HOST_IDX_NONE,
	[61U] = HOST_IDX_NONE,
	[62U] = HOST_IDX_NONE,
	[63U] = HOST_IDX_NONE,
	[64U] = HOST_IDX_NONE,
	[65U] = HOST_IDX_NONE,
	[66U] = HOST_IDX_NONE,
	[67U] = HOST_IDX_NONE,
	[68U] = HOST_IDX_NONE,
	[69U] = HOST_IDX_NONE,
	[70U] = HOST_IDX_NONE,
	[71U] = HOST_IDX_NONE,
	[72U] = HOST_IDX_NONE,
	[73U] = HOST_IDX_NONE,
	[74U] = HOST_IDX_NONE,
	[75U] = HOST_IDX_NONE,
	[76U] = HOST_IDX_NONE,
	[77U] = HOST_IDX_NONE,
	[78U] = HOST_IDX_NONE,
	[79U] = HOST_IDX_NONE,
	[80U] = HOST_IDX_NONE,
	[81U] = HOST_IDX_NONE,
	[82U] = HOST_IDX_NONE,
	[83U] = HOST_IDX_NONE,
	[84U] = HOST_IDX_NONE,
	[85U] = HOST_IDX_NONE,
	[86U] = HOST_IDX_NONE,
	[87U] = HOST_IDX_NONE,
	[88U] = HOST_IDX_NONE,
	[89U] = HOST_IDX_NONE,
	[90U] = HOST_IDX_NONE,
	[91U] = HOST_IDX_NONE,
	[92U] = HOST_IDX_NONE,
	[93U] = HOST_IDX_NONE,
	[94U] = HOST_IDX_NONE,
	[95U] = HOST_IDX_NONE,
	[96U] = HOST_IDX_NONE,
	[97U] = HOST_IDX_NONE,
	[98U] = HOST_IDX_NONE,
	[99U] = HOST_IDX_NONE,
	[100U] = HOST_IDX_NONE,
	[101U] = HOST_IDX_NONE,
	[102U] = HOST_IDX_NONE,
	[103U] = HOST_IDX_NONE,
	[104U] = HOST_IDX_NONE,
	[105U] = HOST_IDX_NONE,
	[106U] = HOST_IDX_NONE,
	[107U] = HOST_IDX_NONE,
	[108U] = HOST_IDX_NONE,
	[109U] = HOST_IDX_NONE,
	[110U] = HOST_IDX_NONE,
	[111U] = HOST_IDX_NONE,
	[112U] = HOST_IDX_NONE,
	[113U] = HOST_IDX_NONE,
	[114U] = HOST_IDX_NONE,
	[115U] = HOST_IDX_NONE,
	[116U] = HOST_IDX_NONE,
	[117U] = HOST_IDX_NONE,
	[118U] = HOST_IDX_NONE,
	[119U] = HOST_IDX_NONE,
	[120U] = HOST_IDX_NONE,
	[121U] = HOST_IDX_NONE,
	[122U] = HOST_IDX_NONE,
	[123U] = HOST_IDX_NONE,
	[124U] = HOST_IDX_NONE,
	[125U] = HOST_IDX_NONE,
	[126U] = HOST_IDX_NONE,
	[127U] = HOST_IDX_NONE,
	[128U] = HOST_IDX_NONE,
	[129U] = HOST_IDX_NONE,
	[130U] = HOST_IDX_NONE,
	[131U] = HOST_IDX_NONE,
	[132U] = HOST_IDX_NONE,
	[133U] = HOST_IDX_NONE,
	[134U] = HOST_IDX_NONE,
	[135U] = HOST_IDX_NONE,
	[136U] = HOST_IDX_NONE,
	[137U] = HOST_IDX_NONE,
	[138U] = HOST_IDX_NONE,
	[139U] = HOST_IDX_NONE,
	[140U] = HOST_IDX_NONE,
	[141U] = HOST_IDX_NONE,
	[142U] = HOST_IDX_NONE,
	[143U] = HOST_IDX_NONE,
	[144U] = HOST_IDX_NONE,
	[145U] = HOST_IDX_NONE,
	[146U] = HOST_IDX_NONE,
	[147U] = HOST_IDX_NONE,
	[148U] = HOST_IDX_NONE,
	[149U] = HOST_IDX_NONE,
	[150U] = HOST_IDX_NONE,
	[151U] = HOST_IDX_NONE,
	[152U] = HOST_IDX_NONE,
	[153U] = HOST_IDX_NONE,
	[154U] = HOST_IDX_NONE,
	[155U] = HOST_IDX_NONE,
	[156U] = HOST_IDX_NONE,
	[157U] = HOST_IDX_NONE,
	[158U] = HOST_IDX_NONE,
	[159U] = HOST_IDX_NONE,
	[160U] = HOST_IDX_NONE,
	[161U] = HOST_IDX_NONE,
	[162U] = HOST_IDX_NONE,
	[163U] = HOST_IDX_NONE,
	[164U] = HOST_IDX_NONE,
	[165U] = HOST_IDX_NONE,
	[166U] = HOST_IDX_NONE,
	[167U] = HOST_IDX_NONE,
	[168U] = HOST_IDX_NONE,
	[169U] = HOST_IDX_NONE,
	[170U] = HOST_IDX_NONE,
	[171U] = HOST_IDX_NONE,
	[172U] = HOST_IDX_NONE,
	[173U] = HOST_IDX_NONE,
	[174U] = HOST_IDX_NONE,
	[175U] = HOST_IDX_NONE,
	[176U] = HOST_IDX_NONE,
	[177U] = HOST_IDX_NONE,
	[178U] = HOST_IDX_NONE,
	[179U] = HOST_IDX_NONE,
	[180U] = HOST_IDX_NONE,
	[181U] = HOST_IDX_NONE,
	[182U] = HOST_IDX_NONE,
	[183U] = HOST_IDX_NONE,
	[184U] = HOST_IDX_NONE,
	[185U] = HOST_IDX_NONE,
	[186U] = HOST_IDX_NONE,
	[187U] = HOST_IDX_NONE,
	[188U] = HOST_IDX_NONE,
	[189U] = HOST_IDX_NONE,
	[190U] = HOST_IDX_NONE,
	[191U] = HOST_IDX_NONE,
	[192U] = HOST_IDX_NONE,
	[193U] = HOST_IDX_NONE,
	[194U] = HOST_IDX_NONE,
	[195U] = HOST_IDX_NONE,
	[196U] = HOST_IDX_NONE,
	[197U] = HOST_IDX_NONE,
	[198U] = HOST_IDX_NONE,
	[199U] = HOST_IDX_NONE,
	[200U] = HOST_IDX_NONE,
	[201U] = HOST_IDX_NONE,
	[202U] = HOST_IDX_NONE,
	[203U] = HOST_IDX_NONE,
	[204U] = HOST_IDX_NONE,
	[205U] = HOST_IDX_NONE,
	[206U] = HOST_IDX_NONE,
	[207U] = HOST_IDX_NONE,
	[208U] = HOST_IDX_NONE,
	[209U] = HOST_IDX_NONE,
	[210U] = HOST_IDX_NONE,
	[211U] = HOST_IDX_NONE,
	[212U] = HOST_IDX_NONE,
	[213U] = HOST_IDX_NONE,
	[214U] = HOST_IDX_NONE,
	[215U] = HOST_IDX_NONE,
	[216U] = HOST_IDX_NONE,
	[217U] = HOST_IDX_NONE,
	[218U] = HOST_IDX_NONE,
	[219U] = HOST_IDX_NONE,
	[220U] = HOST_IDX_NONE,
	[221U] = HOST_IDX_NONE,
	[222U] = HOST_IDX_NONE,
	[223U] = HOST_IDX_NONE,
	[224U] = HOST_IDX_NONE,
	[225U] = HOST_IDX_NONE,
	[226U] = HOST_IDX_NONE,
	[227U] = HOST_IDX_NONE,
	[228U] = HOST_IDX_NONE,
	[229U] = HOST_IDX_NONE,
	[230U] = HOST_IDX_NONE,
	[231U] = HOST_IDX_NONE,
	[232U] = HOST_IDX_NONE,
	[233U] = HOST_IDX_NONE,
	[234U] = HOST_IDX_NONE,
	[235U] = HOST_IDX_NONE,
	[236U] = HOST_IDX_NONE,
	[237U] = HOST_IDX_NONE,
	[238U] = HOST_IDX_NONE,
	[239U] = HOST_IDX_NONE,
	[240U] = HOST_IDX_NONE,
	[241U] = HOST_IDX_NONE,
	[242U] = HOST_IDX_NONE,
	[243U] = HOST_IDX_NONE,
	[244U] = HOST_IDX_NONE,
	[245U] = HOST_IDX_NONE,
	[246U] = HOST_IDX_NONE,
	[247U] = HOST_IDX_NONE,
	[248U] = HOST_IDX_NONE,
	[249U] = HOST_IDX_NONE,
	[252U] = HOST_IDX_NONE,
};
const u8 soc_host_indexes_sz = (u8) sizeof(soc_host_indexes);
