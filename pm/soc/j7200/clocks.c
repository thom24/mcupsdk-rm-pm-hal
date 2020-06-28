/*
 * Data version: 200505_131637
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#include <clk.h>
#include <clk_mux.h>
#include <clk_dev.h>
#include <clk_div.h>
#include <clk_pll.h>
#include <types/array_size.h>
#include <types/devgrps.h>
#include <soc/j7200/control.h>
#include <soc/j7200/clk_ids.h>
#include <soc/j7200/devices.h>
#include <soc/j7200/clocks.h>
#include <soc/j7200/clk_soc_hfosc0.h>
#include <clk_fixed.h>
#include <clk_div.h>
#include <clk_pllctrl.h>
#include <clk_pll_16fft.h>


enum {
	J7200_FREQ_VALUE_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT,
	J7200_FREQ_VALUE_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_1,
	J7200_FREQ_VALUE_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_2,
	J7200_FREQ_VALUE_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_3,
	J7200_FREQ_VALUE_BOARD_0_AUDIO_EXT_REFCLK0_OUT,
	J7200_FREQ_VALUE_BOARD_0_AUDIO_EXT_REFCLK1_OUT,
	J7200_FREQ_VALUE_BOARD_0_CPTS0_RFT_CLK_OUT,
	J7200_FREQ_VALUE_BOARD_0_EXT_REFCLK1_OUT,
	J7200_FREQ_VALUE_BOARD_0_GPMC0_CLK_OUT,
	J7200_FREQ_VALUE_BOARD_0_HFOSC1_CLK_OUT,
	J7200_FREQ_VALUE_BOARD_0_I2C0_SCL_OUT,
	J7200_FREQ_VALUE_BOARD_0_I2C1_SCL_OUT,
	J7200_FREQ_VALUE_BOARD_0_I2C2_SCL_OUT,
	J7200_FREQ_VALUE_BOARD_0_I2C3_SCL_OUT,
	J7200_FREQ_VALUE_BOARD_0_I2C4_SCL_OUT,
	J7200_FREQ_VALUE_BOARD_0_I2C5_SCL_OUT,
	J7200_FREQ_VALUE_BOARD_0_I2C6_SCL_OUT,
	J7200_FREQ_VALUE_BOARD_0_I3C0_SCL_OUT,
	J7200_FREQ_VALUE_BOARD_0_LED_CLK_OUT,
	J7200_FREQ_VALUE_BOARD_0_MCASP0_ACLKR_OUT,
	J7200_FREQ_VALUE_BOARD_0_MCASP0_ACLKX_OUT,
	J7200_FREQ_VALUE_BOARD_0_MCASP1_ACLKR_OUT,
	J7200_FREQ_VALUE_BOARD_0_MCASP1_ACLKX_OUT,
	J7200_FREQ_VALUE_BOARD_0_MCASP2_ACLKR_OUT,
	J7200_FREQ_VALUE_BOARD_0_MCASP2_ACLKX_OUT,
	J7200_FREQ_VALUE_BOARD_0_MCU_CPTS0_RFT_CLK_OUT,
	J7200_FREQ_VALUE_BOARD_0_MCU_EXT_REFCLK0_OUT,
	J7200_FREQ_VALUE_BOARD_0_MCU_I2C0_SCL_OUT,
	J7200_FREQ_VALUE_BOARD_0_MCU_I2C1_SCL_OUT,
	J7200_FREQ_VALUE_BOARD_0_MCU_I3C0_SCL_OUT,
	J7200_FREQ_VALUE_BOARD_0_MCU_OSPI0_DQS_OUT,
	J7200_FREQ_VALUE_BOARD_0_MCU_RGMII1_RXC_OUT,
	J7200_FREQ_VALUE_BOARD_0_MCU_RMII1_REF_CLK_OUT,
	J7200_FREQ_VALUE_BOARD_0_RGMII1_RXC_OUT,
	J7200_FREQ_VALUE_BOARD_0_RGMII2_RXC_OUT,
	J7200_FREQ_VALUE_BOARD_0_RGMII3_RXC_OUT,
	J7200_FREQ_VALUE_BOARD_0_RGMII4_RXC_OUT,
	J7200_FREQ_VALUE_BOARD_0_RMII_REF_CLK_OUT,
	J7200_FREQ_VALUE_BOARD_0_TCK_OUT,
	J7200_FREQ_VALUE_BOARD_0_WKUP_I2C0_SCL_OUT,
	J7200_FREQ_VALUE_BOARD_0_WKUP_LF_CLKIN_OUT,
	J7200_FREQ_VALUE_CPSW_2GUSS_MCU_0_CPTS_GENF0,
	J7200_FREQ_VALUE_CPSW_2GUSS_MCU_0_MDIO_MDCLK_O,
	J7200_FREQ_VALUE_CPSW_2GUSS_MCU_0_RGMII1_TXC_O,
	J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_CPTS_GENF0,
	J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_MDIO_MDCLK_O,
	J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_PRE_RGMII1_TCLK,
	J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_PRE_RGMII2_TCLK,
	J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_PRE_RGMII3_TCLK,
	J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_PRE_RGMII4_TCLK,
	J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_SERDES1_TXCLK,
	J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_SERDES2_TXCLK,
	J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_SERDES3_TXCLK,
	J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_SERDES4_TXCLK,
	J7200_FREQ_VALUE_DEBUGSS_K3_WRAP_CV0_MAIN_0_CSTPIU_TRACECLK,
	J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_0_TIMER_PWM,
	J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_10_TIMER_PWM,
	J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_12_TIMER_PWM,
	J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_14_TIMER_PWM,
	J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_16_TIMER_PWM,
	J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_18_TIMER_PWM,
	J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_2_TIMER_PWM,
	J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_4_TIMER_PWM,
	J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_6_TIMER_PWM,
	J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_8_TIMER_PWM,
	J7200_FREQ_VALUE_DMTIMER_DMC1MS_MCU_0_TIMER_PWM,
	J7200_FREQ_VALUE_DMTIMER_DMC1MS_MCU_2_TIMER_PWM,
	J7200_FREQ_VALUE_DMTIMER_DMC1MS_MCU_4_TIMER_PWM,
	J7200_FREQ_VALUE_DMTIMER_DMC1MS_MCU_6_TIMER_PWM,
	J7200_FREQ_VALUE_DMTIMER_DMC1MS_MCU_8_TIMER_PWM,
	J7200_FREQ_VALUE_EMMCSD4SS_MAIN_0_EMMCSDSS_IO_CLK_O,
	J7200_FREQ_VALUE_FSS_MCU_0_HYPERBUS1P0_0_HPB_OUT_CLK_N,
	J7200_FREQ_VALUE_FSS_MCU_0_HYPERBUS1P0_0_HPB_OUT_CLK_P,
	J7200_FREQ_VALUE_FSS_MCU_0_OSPI_0_OSPI_OCLK_CLK,
	J7200_FREQ_VALUE_GPMC_MAIN_0_PO_GPMC_DEV_CLK,
	J7200_FREQ_VALUE_I3C_MAIN_0_I3C_SCL_DO,
	J7200_FREQ_VALUE_I3C_MCU_0_I3C_SCL_DO,
	J7200_FREQ_VALUE_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII1_TXC__A,
	J7200_FREQ_VALUE_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII2_TXC__A,
	J7200_FREQ_VALUE_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII3_TXC__A,
	J7200_FREQ_VALUE_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII4_TXC__A,
	J7200_FREQ_VALUE_MCASP_MAIN_0_MCASP_ACLKR_POUT,
	J7200_FREQ_VALUE_MCASP_MAIN_0_MCASP_ACLKX_POUT,
	J7200_FREQ_VALUE_MCASP_MAIN_0_MCASP_AHCLKR_POUT,
	J7200_FREQ_VALUE_MCASP_MAIN_0_MCASP_AHCLKX_POUT,
	J7200_FREQ_VALUE_MCASP_MAIN_1_MCASP_ACLKR_POUT,
	J7200_FREQ_VALUE_MCASP_MAIN_1_MCASP_ACLKX_POUT,
	J7200_FREQ_VALUE_MCASP_MAIN_1_MCASP_AHCLKR_POUT,
	J7200_FREQ_VALUE_MCASP_MAIN_1_MCASP_AHCLKX_POUT,
	J7200_FREQ_VALUE_MCASP_MAIN_2_MCASP_ACLKR_POUT,
	J7200_FREQ_VALUE_MCASP_MAIN_2_MCASP_ACLKX_POUT,
	J7200_FREQ_VALUE_MCASP_MAIN_2_MCASP_AHCLKR_POUT,
	J7200_FREQ_VALUE_MCASP_MAIN_2_MCASP_AHCLKX_POUT,
	J7200_FREQ_VALUE_MSHSI2C_WKUP_0_PORSCL,
	J7200_FREQ_VALUE_NAVSS256VCL_MAIN_0_CPTS0_GENF2,
	J7200_FREQ_VALUE_NAVSS256VCL_MAIN_0_CPTS0_GENF3,
	J7200_FREQ_VALUE_NAVSS256VCL_MAIN_0_CPTS0_GENF4,
	J7200_FREQ_VALUE_NAVSS256VCL_MAIN_0_CPTS_0_TS_GENF0,
	J7200_FREQ_VALUE_NAVSS256VCL_MAIN_0_CPTS_0_TS_GENF1,
	J7200_FREQ_VALUE_PCIE_G3X4_128_MAIN_1_PCIE_LANE0_TXCLK,
	J7200_FREQ_VALUE_PCIE_G3X4_128_MAIN_1_PCIE_LANE1_TXCLK,
	J7200_FREQ_VALUE_PCIE_G3X4_128_MAIN_1_PCIE_LANE2_TXCLK,
	J7200_FREQ_VALUE_PCIE_G3X4_128_MAIN_1_PCIE_LANE3_TXCLK,
	J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MAIN_0,
	J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MAIN_1,
	J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MAIN_12,
	J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MAIN_14,
	J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MAIN_2,
	J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MAIN_3,
	J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MAIN_4,
	J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MAIN_7,
	J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MAIN_8,
	J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MCU_0,
	J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MCU_1,
	J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MCU_2,
	J7200_FREQ_VALUE_SPI_MAIN_0_IO_CLKSPIO_CLK,
	J7200_FREQ_VALUE_SPI_MAIN_1_IO_CLKSPIO_CLK,
	J7200_FREQ_VALUE_SPI_MAIN_2_IO_CLKSPIO_CLK,
	J7200_FREQ_VALUE_SPI_MAIN_3_IO_CLKSPIO_CLK,
	J7200_FREQ_VALUE_SPI_MAIN_4_IO_CLKSPIO_CLK,
	J7200_FREQ_VALUE_SPI_MAIN_5_IO_CLKSPIO_CLK,
	J7200_FREQ_VALUE_SPI_MAIN_6_IO_CLKSPIO_CLK,
	J7200_FREQ_VALUE_SPI_MAIN_7_IO_CLKSPIO_CLK,
	J7200_FREQ_VALUE_SPI_MCU_0_IO_CLKSPIO_CLK,
	J7200_FREQ_VALUE_SPI_MCU_1_IO_CLKSPIO_CLK,
	J7200_FREQ_VALUE_SPI_MCU_2_IO_CLKSPIO_CLK,
	J7200_FREQ_VALUE_USB3P0SS_16FFC_MAIN_0_PIPE_TXCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN0_REFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN0_RXCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN0_RXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN0_TXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN0_TXMCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN1_REFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN1_RXCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN1_RXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN1_TXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN1_TXMCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN2_REFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN2_RXCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN2_RXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN2_TXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN2_TXMCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN3_REFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN3_RXCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN3_RXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN3_TXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN3_TXMCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN0_REFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN0_RXCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN0_RXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN0_TXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN0_TXMCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN1_REFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN1_RXCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN1_RXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN1_TXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN1_TXMCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN2_REFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN2_RXCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN2_RXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN2_TXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN2_TXMCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN3_REFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN3_RXCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN3_RXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN3_TXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN3_TXMCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN1_REFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN1_RXCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN1_RXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN1_TXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN1_TXMCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN3_REFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN3_RXCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN3_RXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN3_TXFCLK,
	J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN3_TXMCLK,
	J7200_FREQ_VALUE_COUNT,
};

enum {
	J7200_FREQ_RANGE_ANY,
	J7200_FREQ_RANGE_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
	J7200_FREQ_RANGE_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_32K_CLK,
	J7200_FREQ_RANGE_VCO_PLLFRACF_SSMOD_16FFT_MAIN_0,
	J7200_FREQ_RANGE_VCO_IN_PLLFRACF_SSMOD_16FFT_MAIN_0,
};

enum {
	PLL_ENTRY_MAIN_19_2MHZ_1000MHZ_F24BIT,
	PLL_ENTRY_MAIN_20MHZ_1000MHZ,
	PLL_ENTRY_MAIN_24MHZ_1000MHZ_F24BIT,
	PLL_ENTRY_MAIN_25MHZ_1000MHZ,
	PLL_ENTRY_MAIN_26MHZ_1000MHZ_F24BIT,
	PLL_ENTRY_MAIN_27MHZ_1000MHZ_F24BIT,
	PLL_ENTRY_PER0_19_2MHZ_960MHZ,
	PLL_ENTRY_PER0_20MHZ_960MHZ,
	PLL_ENTRY_PER0_24MHZ_960MHZ,
	PLL_ENTRY_PER0_25MHZ_960MHZ_F24BIT,
	PLL_ENTRY_PER0_26MHZ_960MHZ_F24BIT,
	PLL_ENTRY_PER0_27MHZ_960MHZ_F24BIT,
	PLL_ENTRY_PER1_19_2MHZ_900MHZ_F24BIT,
	PLL_ENTRY_PER1_20MHZ_900MHZ,
	PLL_ENTRY_PER1_24MHZ_900MHZ,
	PLL_ENTRY_PER1_25MHZ_900MHZ,
	PLL_ENTRY_PER1_26MHZ_900MHZ_F24BIT,
	PLL_ENTRY_PER1_27MHZ_900MHZ_F24BIT,
	PLL_ENTRY_CPSW_19_2MHZ_2000MHZ_F24BIT,
	PLL_ENTRY_CPSW_20MHZ_2000MHZ,
	PLL_ENTRY_CPSW_24MHZ_2000MHZ_F24BIT,
	PLL_ENTRY_CPSW_26MHZ_2000MHZ_F24BIT,
	PLL_ENTRY_CPSW_27MHZ_2000MHZ_F24BIT,
	PLL_ENTRY_AUDIO_19_2MHZ_2359_296MHZ_F24BIT,
	PLL_ENTRY_AUDIO_20MHZ_2359_296MHZ_F24BIT,
	PLL_ENTRY_AUDIO_24MHZ_2359_296MHZ_F24BIT,
	PLL_ENTRY_AUDIO_25MHZ_2359_296MHZ_F24BIT,
	PLL_ENTRY_AUDIO_26MHZ_2359_296MHZ_F24BIT,
	PLL_ENTRY_AUDIO_27MHZ_2359_296MHZ_F24BIT,
	PLL_ENTRY_ARM_25MHZ_2000MHZ,
	PLL_ENTRY_DDR_19_2MHZ_3200MHZ_F24BIT,
	PLL_ENTRY_DDR_20MHZ_3200MHZ,
	PLL_ENTRY_DDR_24MHZ_3200MHZ_F24BIT,
	PLL_ENTRY_DDR_25MHZ_3200MHZ,
	PLL_ENTRY_DDR_26MHZ_3200MHZ_F24BIT,
	PLL_ENTRY_DDR_27MHZ_3200MHZ_F24BIT,
	PLL_ENTRY_MCU_PER_19_2MHZ_2400MHZ,
	PLL_ENTRY_MCU_PER_20MHZ_2400MHZ,
	PLL_ENTRY_MCU_PER_24MHZ_2400MHZ,
	PLL_ENTRY_MCU_PER_25MHZ_2400MHZ,
	PLL_ENTRY_MCU_PER_26MHZ_2400MHZ_F24BIT,
	PLL_ENTRY_MCU_PER_27MHZ_2400MHZ_F24BIT,
};

enum {
	NO_DEFAULT_FREQ,
	FREQ_PLLFRACF_SSMOD_16FFT_MAIN_0_DEFAULT,
	FREQ_PLLFRACF_SSMOD_16FFT_MAIN_1_DEFAULT,
	FREQ_PLLFRACF_SSMOD_16FFT_MAIN_12_DEFAULT,
	FREQ_PLLFRACF_SSMOD_16FFT_MAIN_14_DEFAULT,
	FREQ_PLLFRACF_SSMOD_16FFT_MAIN_2_DEFAULT,
	FREQ_PLLFRACF_SSMOD_16FFT_MAIN_4_DEFAULT,
	FREQ_PLLFRACF_SSMOD_16FFT_MCU_1_DEFAULT,
};

u32 soc_clock_values[J7200_FREQ_VALUE_COUNT];

const struct clk_range soc_clock_ranges[] = {
	CLK_RANGE(J7200_FREQ_RANGE_ANY,						 0,	    ULONG_MAX),
	CLK_RANGE(J7200_FREQ_RANGE_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK, 12500000,  12500000),
	CLK_RANGE(J7200_FREQ_RANGE_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_32K_CLK,	 32000,	    32000),
	CLK_RANGE(J7200_FREQ_RANGE_VCO_IN_PLLFRACF_SSMOD_16FFT_MAIN_0,		 5000000,   1200000000),
	CLK_RANGE(J7200_FREQ_RANGE_VCO_PLLFRACF_SSMOD_16FFT_MAIN_0,		 800000000, 3200000000),
};

const struct clk_default soc_clock_freq_defaults[] = {
	CLK_DEFAULT(FREQ_PLLFRACF_SSMOD_16FFT_MAIN_0_DEFAULT,  1000000000UL, 1000000000UL, 1000000000UL),
	CLK_DEFAULT(FREQ_PLLFRACF_SSMOD_16FFT_MAIN_1_DEFAULT,  960000000UL,  960000000UL,  960000000UL),
	CLK_DEFAULT(FREQ_PLLFRACF_SSMOD_16FFT_MAIN_12_DEFAULT, 3200000000UL, 3200000000UL, 3200000000UL),
	CLK_DEFAULT(FREQ_PLLFRACF_SSMOD_16FFT_MAIN_14_DEFAULT, 2000000000UL, 2000000000UL, 2000000000UL),
	CLK_DEFAULT(FREQ_PLLFRACF_SSMOD_16FFT_MAIN_2_DEFAULT,  1800000000UL, 1800000000UL, 1800000001UL),
	CLK_DEFAULT(FREQ_PLLFRACF_SSMOD_16FFT_MAIN_4_DEFAULT,  2359296000UL, 2359296000UL, 2359296001UL),
	CLK_DEFAULT(FREQ_PLLFRACF_SSMOD_16FFT_MCU_1_DEFAULT,   2400000000UL, 2400000000UL, 2400000001UL),
};

const struct pll_table_entry soc_pll_table[] = {
	[PLL_ENTRY_MAIN_19_2MHZ_1000MHZ_F24BIT] =      {
		.freq_min_hz	= 1000000000UL,
		.freq_max_hz	= 1000000000UL,
		.plld		= 1U,
		.pllm		= 104U,
		.pllfm		= 2796203U,
		.clkod		= 2U,
	},
	[PLL_ENTRY_MAIN_20MHZ_1000MHZ] =	       {
		.freq_min_hz	= 1000000000UL,
		.freq_max_hz	= 1000000000UL,
		.plld		= 1U,
		.pllm		= 100U,
		.pllfm		= 0U,
		.clkod		= 2U,
	},
	[PLL_ENTRY_MAIN_24MHZ_1000MHZ_F24BIT] =	       {
		.freq_min_hz	= 1000000000UL,
		.freq_max_hz	= 1000000000UL,
		.plld		= 1U,
		.pllm		= 83U,
		.pllfm		= 5592406U,
		.clkod		= 2U,
	},
	[PLL_ENTRY_MAIN_25MHZ_1000MHZ] =	       {
		.freq_min_hz	= 1000000000UL,
		.freq_max_hz	= 1000000000UL,
		.plld		= 1U,
		.pllm		= 80U,
		.pllfm		= 0U,
		.clkod		= 2U,
	},
	[PLL_ENTRY_MAIN_26MHZ_1000MHZ_F24BIT] =	       {
		.freq_min_hz	= 1000000000UL,
		.freq_max_hz	= 1000000000UL,
		.plld		= 1U,
		.pllm		= 76U,
		.pllfm		= 15486661U,
		.clkod		= 2U,
	},
	[PLL_ENTRY_MAIN_27MHZ_1000MHZ_F24BIT] =	       {
		.freq_min_hz	= 1000000000UL,
		.freq_max_hz	= 1000000000UL,
		.plld		= 1U,
		.pllm		= 74U,
		.pllfm		= 1242757U,
		.clkod		= 2U,
	},
	[PLL_ENTRY_PER0_19_2MHZ_960MHZ] =	       {
		.freq_min_hz	= 960000000UL,
		.freq_max_hz	= 960000000UL,
		.plld		= 1U,
		.pllm		= 100U,
		.pllfm		= 0U,
		.clkod		= 2U,
	},
	[PLL_ENTRY_PER0_20MHZ_960MHZ] =		       {
		.freq_min_hz	= 960000000UL,
		.freq_max_hz	= 960000000UL,
		.plld		= 1U,
		.pllm		= 96U,
		.pllfm		= 0U,
		.clkod		= 2U,
	},
	[PLL_ENTRY_PER0_24MHZ_960MHZ] =		       {
		.freq_min_hz	= 960000000UL,
		.freq_max_hz	= 960000000UL,
		.plld		= 1U,
		.pllm		= 80U,
		.pllfm		= 0U,
		.clkod		= 2U,
	},
	[PLL_ENTRY_PER0_25MHZ_960MHZ_F24BIT] =	       {
		.freq_min_hz	= 960000000UL,
		.freq_max_hz	= 960000000UL,
		.plld		= 1U,
		.pllm		= 76U,
		.pllfm		= 13421773U,
		.clkod		= 2U,
	},
	[PLL_ENTRY_PER0_26MHZ_960MHZ_F24BIT] =	       {
		.freq_min_hz	= 960000000UL,
		.freq_max_hz	= 960000000UL,
		.plld		= 1U,
		.pllm		= 73U,
		.pllfm		= 14196106U,
		.clkod		= 2U,
	},
	[PLL_ENTRY_PER0_27MHZ_960MHZ_F24BIT] =	       {
		.freq_min_hz	= 960000000UL,
		.freq_max_hz	= 960000000UL,
		.plld		= 1U,
		.pllm		= 71U,
		.pllfm		= 1864136U,
		.clkod		= 2U,
	},
	[PLL_ENTRY_PER1_19_2MHZ_900MHZ_F24BIT] =       {
		.freq_min_hz	= 900000000UL,
		.freq_max_hz	= 900000000UL,
		.plld		= 1U,
		.pllm		= 93U,
		.pllfm		= 12582912U,
		.clkod		= 2U,
	},
	[PLL_ENTRY_PER1_20MHZ_900MHZ] =		       {
		.freq_min_hz	= 900000000UL,
		.freq_max_hz	= 900000000UL,
		.plld		= 1U,
		.pllm		= 90U,
		.pllfm		= 0U,
		.clkod		= 2U,
	},
	[PLL_ENTRY_PER1_24MHZ_900MHZ] =		       {
		.freq_min_hz	= 900000000UL,
		.freq_max_hz	= 900000000UL,
		.plld		= 1U,
		.pllm		= 75U,
		.pllfm		= 0U,
		.clkod		= 2U,
	},
	[PLL_ENTRY_PER1_25MHZ_900MHZ] =		       {
		.freq_min_hz	= 900000000UL,
		.freq_max_hz	= 900000000UL,
		.plld		= 1U,
		.pllm		= 72U,
		.pllfm		= 0U,
		.clkod		= 2U,
	},
	[PLL_ENTRY_PER1_26MHZ_900MHZ_F24BIT] =	       {
		.freq_min_hz	= 900000000UL,
		.freq_max_hz	= 900000001UL,
		.plld		= 1U,
		.pllm		= 69U,
		.pllfm		= 3871666U,
		.clkod		= 2U,
	},
	[PLL_ENTRY_PER1_27MHZ_900MHZ_F24BIT] =	       {
		.freq_min_hz	= 900000000UL,
		.freq_max_hz	= 900000000UL,
		.plld		= 1U,
		.pllm		= 66U,
		.pllfm		= 11184811U,
		.clkod		= 2U,
	},
	[PLL_ENTRY_CPSW_19_2MHZ_2000MHZ_F24BIT] =      {
		.freq_min_hz	= 2000000000UL,
		.freq_max_hz	= 2000000000UL,
		.plld		= 1U,
		.pllm		= 104U,
		.pllfm		= 2796203U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_CPSW_20MHZ_2000MHZ] =	       {
		.freq_min_hz	= 2000000000UL,
		.freq_max_hz	= 2000000000UL,
		.plld		= 1U,
		.pllm		= 100U,
		.pllfm		= 0U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_CPSW_24MHZ_2000MHZ_F24BIT] =	       {
		.freq_min_hz	= 2000000000UL,
		.freq_max_hz	= 2000000000UL,
		.plld		= 1U,
		.pllm		= 83U,
		.pllfm		= 5592406U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_CPSW_26MHZ_2000MHZ_F24BIT] =	       {
		.freq_min_hz	= 2000000000UL,
		.freq_max_hz	= 2000000000UL,
		.plld		= 1U,
		.pllm		= 76U,
		.pllfm		= 15486661U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_CPSW_27MHZ_2000MHZ_F24BIT] =	       {
		.freq_min_hz	= 2000000000UL,
		.freq_max_hz	= 2000000000UL,
		.plld		= 1U,
		.pllm		= 74U,
		.pllfm		= 1242757U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_AUDIO_19_2MHZ_2359_296MHZ_F24BIT] = {
		.freq_min_hz	= 2359296000UL,
		.freq_max_hz	= 2359296001UL,
		.plld		= 1U,
		.pllm		= 122U,
		.pllfm		= 14763951U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_AUDIO_20MHZ_2359_296MHZ_F24BIT] =   {
		.freq_min_hz	= 2359296000UL,
		.freq_max_hz	= 2359296000UL,
		.plld		= 1U,
		.pllm		= 117U,
		.pllfm		= 16186658U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_AUDIO_24MHZ_2359_296MHZ_F24BIT] =   {
		.freq_min_hz	= 2359296000UL,
		.freq_max_hz	= 2359296001UL,
		.plld		= 1U,
		.pllm		= 98U,
		.pllfm		= 5100275U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_AUDIO_25MHZ_2359_296MHZ_F24BIT] =   {
		.freq_min_hz	= 2359296000UL,
		.freq_max_hz	= 2359296000UL,
		.plld		= 1U,
		.pllm		= 94U,
		.pllfm		= 6238440U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_AUDIO_26MHZ_2359_296MHZ_F24BIT] =   {
		.freq_min_hz	= 2359296000UL,
		.freq_max_hz	= 2359296000UL,
		.plld		= 1U,
		.pllm		= 90U,
		.pllfm		= 12451276U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_AUDIO_27MHZ_2359_296MHZ_F24BIT] =   {
		.freq_min_hz	= 2359296000UL,
		.freq_max_hz	= 2359296001UL,
		.plld		= 1U,
		.pllm		= 87U,
		.pllfm		= 6397712U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_ARM_25MHZ_2000MHZ] =		       {
		.freq_min_hz	= 2000000000UL,
		.freq_max_hz	= 2000000000UL,
		.plld		= 1U,
		.pllm		= 80U,
		.pllfm		= 0U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_DDR_19_2MHZ_3200MHZ_F24BIT] =       {
		.freq_min_hz	= 3200000000UL,
		.freq_max_hz	= 3200000000UL,
		.plld		= 1U,
		.pllm		= 166U,
		.pllfm		= 11184811U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_DDR_20MHZ_3200MHZ] =		       {
		.freq_min_hz	= 3200000000UL,
		.freq_max_hz	= 3200000000UL,
		.plld		= 1U,
		.pllm		= 160U,
		.pllfm		= 0U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_DDR_24MHZ_3200MHZ_F24BIT] =	       {
		.freq_min_hz	= 3200000000UL,
		.freq_max_hz	= 3200000000UL,
		.plld		= 1U,
		.pllm		= 133U,
		.pllfm		= 5592406U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_DDR_25MHZ_3200MHZ] =		       {
		.freq_min_hz	= 3200000000UL,
		.freq_max_hz	= 3200000000UL,
		.plld		= 1U,
		.pllm		= 128U,
		.pllfm		= 0U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_DDR_26MHZ_3200MHZ_F24BIT] =	       {
		.freq_min_hz	= 3200000000UL,
		.freq_max_hz	= 3200000001UL,
		.plld		= 1U,
		.pllm		= 1230U,
		.pllfm		= 12905552U,
		.clkod		= 10U,
	},
	[PLL_ENTRY_DDR_27MHZ_3200MHZ_F24BIT] =	       {
		.freq_min_hz	= 3200000000UL,
		.freq_max_hz	= 3200000001UL,
		.plld		= 1U,
		.pllm		= 118U,
		.pllfm		= 8699298U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_MCU_PER_19_2MHZ_2400MHZ] =	       {
		.freq_min_hz	= 2400000000UL,
		.freq_max_hz	= 2400000000UL,
		.plld		= 1U,
		.pllm		= 125U,
		.pllfm		= 0U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_MCU_PER_20MHZ_2400MHZ] =	       {
		.freq_min_hz	= 2400000000UL,
		.freq_max_hz	= 2400000000UL,
		.plld		= 1U,
		.pllm		= 120U,
		.pllfm		= 0U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_MCU_PER_24MHZ_2400MHZ] =	       {
		.freq_min_hz	= 2400000000UL,
		.freq_max_hz	= 2400000000UL,
		.plld		= 1U,
		.pllm		= 100U,
		.pllfm		= 0U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_MCU_PER_25MHZ_2400MHZ] =	       {
		.freq_min_hz	= 2400000000UL,
		.freq_max_hz	= 2400000000UL,
		.plld		= 1U,
		.pllm		= 96U,
		.pllfm		= 0U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_MCU_PER_26MHZ_2400MHZ_F24BIT] =     {
		.freq_min_hz	= 2400000000UL,
		.freq_max_hz	= 2400000001UL,
		.plld		= 1U,
		.pllm		= 92U,
		.pllfm		= 5162221U,
		.clkod		= 1U,
	},
	[PLL_ENTRY_MCU_PER_27MHZ_2400MHZ_F24BIT] =     {
		.freq_min_hz	= 2400000000UL,
		.freq_max_hz	= 2400000000UL,
		.plld		= 1U,
		.pllm		= 88U,
		.pllfm		= 14913081U,
		.clkod		= 1U,
	},
};

static const u8 pllfracf_ssmod_16fft_main_0_entries[] = {
	PLL_ENTRY_MAIN_19_2MHZ_1000MHZ_F24BIT,
	PLL_ENTRY_MAIN_20MHZ_1000MHZ,
	PLL_ENTRY_MAIN_24MHZ_1000MHZ_F24BIT,
	PLL_ENTRY_MAIN_25MHZ_1000MHZ,
	PLL_ENTRY_MAIN_26MHZ_1000MHZ_F24BIT,
	PLL_ENTRY_MAIN_27MHZ_1000MHZ_F24BIT,
	PLL_TABLE_LAST,
};
static const u8 pllfracf_ssmod_16fft_main_1_entries[] = {
	PLL_ENTRY_PER0_19_2MHZ_960MHZ,
	PLL_ENTRY_PER0_20MHZ_960MHZ,
	PLL_ENTRY_PER0_24MHZ_960MHZ,
	PLL_ENTRY_PER0_25MHZ_960MHZ_F24BIT,
	PLL_ENTRY_PER0_26MHZ_960MHZ_F24BIT,
	PLL_ENTRY_PER0_27MHZ_960MHZ_F24BIT,
	PLL_TABLE_LAST,
};
static const u8 pllfracf_ssmod_16fft_main_12_entries[] = {
	PLL_ENTRY_DDR_19_2MHZ_3200MHZ_F24BIT,
	PLL_ENTRY_DDR_20MHZ_3200MHZ,
	PLL_ENTRY_DDR_24MHZ_3200MHZ_F24BIT,
	PLL_ENTRY_DDR_25MHZ_3200MHZ,
	PLL_ENTRY_DDR_26MHZ_3200MHZ_F24BIT,
	PLL_ENTRY_DDR_27MHZ_3200MHZ_F24BIT,
	PLL_TABLE_LAST,
};
static const u8 pllfracf_ssmod_16fft_main_14_entries[] = {
	PLL_ENTRY_CPSW_19_2MHZ_2000MHZ_F24BIT,
	PLL_ENTRY_CPSW_20MHZ_2000MHZ,
	PLL_ENTRY_CPSW_24MHZ_2000MHZ_F24BIT,
	PLL_ENTRY_ARM_25MHZ_2000MHZ,
	PLL_ENTRY_CPSW_26MHZ_2000MHZ_F24BIT,
	PLL_ENTRY_CPSW_27MHZ_2000MHZ_F24BIT,
	PLL_TABLE_LAST,
};
static const u8 pllfracf_ssmod_16fft_main_2_entries[] = {
	PLL_ENTRY_PER1_19_2MHZ_900MHZ_F24BIT,
	PLL_ENTRY_PER1_20MHZ_900MHZ,
	PLL_ENTRY_PER1_24MHZ_900MHZ,
	PLL_ENTRY_PER1_25MHZ_900MHZ,
	PLL_ENTRY_PER1_26MHZ_900MHZ_F24BIT,
	PLL_ENTRY_PER1_27MHZ_900MHZ_F24BIT,
	PLL_TABLE_LAST,
};
static const u8 pllfracf_ssmod_16fft_main_3_entries[] = {
	PLL_ENTRY_CPSW_19_2MHZ_2000MHZ_F24BIT,
	PLL_ENTRY_CPSW_20MHZ_2000MHZ,
	PLL_ENTRY_CPSW_24MHZ_2000MHZ_F24BIT,
	PLL_ENTRY_CPSW_20MHZ_2000MHZ,
	PLL_ENTRY_CPSW_26MHZ_2000MHZ_F24BIT,
	PLL_ENTRY_CPSW_27MHZ_2000MHZ_F24BIT,
	PLL_TABLE_LAST,
};
static const u8 pllfracf_ssmod_16fft_main_4_entries[] = {
	PLL_ENTRY_AUDIO_19_2MHZ_2359_296MHZ_F24BIT,
	PLL_ENTRY_AUDIO_20MHZ_2359_296MHZ_F24BIT,
	PLL_ENTRY_AUDIO_24MHZ_2359_296MHZ_F24BIT,
	PLL_ENTRY_AUDIO_25MHZ_2359_296MHZ_F24BIT,
	PLL_ENTRY_AUDIO_26MHZ_2359_296MHZ_F24BIT,
	PLL_ENTRY_AUDIO_27MHZ_2359_296MHZ_F24BIT,
	PLL_TABLE_LAST,
};
static const u8 pllfracf_ssmod_16fft_mcu_0_entries[] = {
	PLL_ENTRY_CPSW_19_2MHZ_2000MHZ_F24BIT,
	PLL_ENTRY_CPSW_20MHZ_2000MHZ,
	PLL_ENTRY_CPSW_20MHZ_2000MHZ,
	PLL_ENTRY_ARM_25MHZ_2000MHZ,
	PLL_ENTRY_CPSW_26MHZ_2000MHZ_F24BIT,
	PLL_ENTRY_CPSW_27MHZ_2000MHZ_F24BIT,
	PLL_TABLE_LAST,
};
static const u8 pllfracf_ssmod_16fft_mcu_1_entries[] = {
	PLL_ENTRY_MCU_PER_19_2MHZ_2400MHZ,
	PLL_ENTRY_MCU_PER_20MHZ_2400MHZ,
	PLL_ENTRY_MCU_PER_24MHZ_2400MHZ,
	PLL_ENTRY_MCU_PER_25MHZ_2400MHZ,
	PLL_ENTRY_MCU_PER_26MHZ_2400MHZ_F24BIT,
	PLL_ENTRY_MCU_PER_27MHZ_2400MHZ_F24BIT,
	PLL_TABLE_LAST,
};

static const struct clk_parent clk_ATL_PCLKMUX_parents[] = {
	{
		CLK_J7200_HSDIV2_16FFT_MAIN_4_HSDIVOUT1_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_2_HSDIVOUT2_CLK,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		CLK_J7200_POSTDIV2_16FFT_MAIN_0_HSDIVOUT7_CLK,
		1,
	},
	{
		CLK_J7200_BOARD_0_MCU_EXT_REFCLK0_OUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_EXT_REFCLK1_OUT,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		0,
	},
	{
		0,
		0,
	},
	{
		0,
		0,
	},
	{
		0,
		0,
	},
	{
		0,
		0,
	},
	{
		0,
		0,
	},
	{
		0,
		0,
	},
	{
		0,
		0,
	},
};
static const struct clk_data_mux_reg clk_data_ATL_PCLKMUX_out0 = {
	.data_mux		= {
		.parents	= clk_ATL_PCLKMUX_parents,
		.n		= ARRAY_SIZE(clk_ATL_PCLKMUX_parents),
	},
	.reg			= 0x00100000 + 33472,
	.bit			= 0,
};
static const struct clk_parent clk_AUDIO_REFCLKO_MUX_out0_parents[] = {
	{
		CLK_J7200_MCASP_MAIN_0_MCASP_AHCLKR_POUT,
		1,
	},
	{
		CLK_J7200_MCASP_MAIN_1_MCASP_AHCLKR_POUT,
		1,
	},
	{
		CLK_J7200_MCASP_MAIN_2_MCASP_AHCLKR_POUT,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		CLK_J7200_MCASP_MAIN_0_MCASP_AHCLKX_POUT,
		1,
	},
	{
		CLK_J7200_MCASP_MAIN_1_MCASP_AHCLKX_POUT,
		1,
	},
	{
		CLK_J7200_MCASP_MAIN_2_MCASP_AHCLKX_POUT,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT,
		1,
	},
	{
		CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_1,
		1,
	},
	{
		CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_2,
		1,
	},
	{
		CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_3,
		1,
	},
	{
		CLK_J7200_HSDIV2_16FFT_MAIN_4_HSDIVOUT2_CLK,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_AUDIO_REFCLKO_MUX_out0 = {
	.data_mux		= {
		.parents	= clk_AUDIO_REFCLKO_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_AUDIO_REFCLKO_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33504,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_AUDIO_REFCLKO_MUX_out1 = {
	.data_mux		= {
		.parents	= clk_AUDIO_REFCLKO_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_AUDIO_REFCLKO_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33508,
	.bit			= 0,
};
static const struct clk_parent clk_CLKOUT_MUX_parents[] = {
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT0_CLK,
		5,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT0_CLK,
		10,
	},
};
static const struct clk_data_mux_reg clk_data_CLKOUT_MUX_out0 = {
	.data_mux		= {
		.parents	= clk_CLKOUT_MUX_parents,
		.n		= ARRAY_SIZE(clk_CLKOUT_MUX_parents),
	},
	.reg			= 0x00100000 + 32784,
	.bit			= 0,
};
static const struct clk_parent clk_CPSW2G_CPTS_RCLK_MUX_parents[] = {
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT1_CLK,
		1,
	},
	{
		CLK_J7200_POSTDIV2_16FFT_MAIN_0_HSDIVOUT6_CLK,
		1,
	},
	{
		CLK_J7200_BOARD_0_MCU_CPTS0_RFT_CLK_OUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_CPTS0_RFT_CLK_OUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_MCU_EXT_REFCLK0_OUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_EXT_REFCLK1_OUT,
		1,
	},
	{
		CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN0_TXMCLK,
		1,
	},
	{
		CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN1_TXMCLK,
		1,
	},
	{
		CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN2_TXMCLK,
		1,
	},
	{
		CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN3_TXMCLK,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT1_CLK,
		1,
	},
	{
		CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		2,
	},
};
static const struct clk_data_mux_reg clk_data_CPSW2G_CPTS_RCLK_MUX_out0 = {
	.data_mux		= {
		.parents	= clk_CPSW2G_CPTS_RCLK_MUX_parents,
		.n		= ARRAY_SIZE(clk_CPSW2G_CPTS_RCLK_MUX_parents),
	},
	.reg			= 0x40F00000 + 32848,
	.bit			= 8,
};
static const struct clk_parent clk_CPSW5X_CPTS_RFT_MUX_parents[] = {
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT1_CLK,
		1,
	},
	{
		CLK_J7200_POSTDIV2_16FFT_MAIN_0_HSDIVOUT6_CLK,
		1,
	},
	{
		CLK_J7200_BOARD_0_MCU_CPTS0_RFT_CLK_OUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_CPTS0_RFT_CLK_OUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_MCU_EXT_REFCLK0_OUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_EXT_REFCLK1_OUT,
		1,
	},
	{
		CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN0_TXMCLK,
		1,
	},
	{
		CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN1_TXMCLK,
		1,
	},
	{
		CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN2_TXMCLK,
		1,
	},
	{
		CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN3_TXMCLK,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT1_CLK,
		1,
	},
	{
		CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_CPSW5X_CPTS_RFT_MUX_out0 = {
	.data_mux		= {
		.parents	= clk_CPSW5X_CPTS_RFT_MUX_parents,
		.n		= ARRAY_SIZE(clk_CPSW5X_CPTS_RFT_MUX_parents),
	},
	.reg			= 0x00100000 + 32912,
	.bit			= 0,
};
static const struct clk_parent clk_EMMCSD_REFCLK_SEL_out0_parents[] = {
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_0_HSDIVOUT2_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT2_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT2_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT2_CLK,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_EMMCSD_REFCLK_SEL_out0 = {
	.data_mux		= {
		.parents	= clk_EMMCSD_REFCLK_SEL_out0_parents,
		.n		= ARRAY_SIZE(clk_EMMCSD_REFCLK_SEL_out0_parents),
	},
	.reg			= 0x00100000 + 32944,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_EMMCSD_REFCLK_SEL_out1 = {
	.data_mux		= {
		.parents	= clk_EMMCSD_REFCLK_SEL_out0_parents,
		.n		= ARRAY_SIZE(clk_EMMCSD_REFCLK_SEL_out0_parents),
	},
	.reg			= 0x00100000 + 32948,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_GTC_CLK_MUX_out0 = {
	.data_mux		= {
		.parents	= clk_CPSW5X_CPTS_RFT_MUX_parents,
		.n		= ARRAY_SIZE(clk_CPSW5X_CPTS_RFT_MUX_parents),
	},
	.reg			= 0x00100000 + 32816,
	.bit			= 0,
};
static const struct clk_parent clk_MAIN_PLL4_XREF_SEL_parents[] = {
	{
		CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT4,
		1,
	},
	{
		CLK_J7200_BOARD_0_EXT_REFCLK1_OUT,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_MAIN_PLL4_XREF_SEL_out0 = {
	.data_mux		= {
		.parents	= clk_MAIN_PLL4_XREF_SEL_parents,
		.n		= ARRAY_SIZE(clk_MAIN_PLL4_XREF_SEL_parents),
	},
	.reg			= 0x43000000 + 32912,
	.bit			= 4,
};
static const struct clk_parent clk_MAIN_PLL_HFOSC_SEL_out0_parents[] = {
	{
		CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_HFOSC1_CLK_OUT,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_MAIN_PLL_HFOSC_SEL_out0 = {
	.data_mux		= {
		.parents	= clk_MAIN_PLL_HFOSC_SEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_PLL_HFOSC_SEL_out0_parents),
	},
	.reg			= 0x43000000 + 32896,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_PLL_HFOSC_SEL_out1 = {
	.data_mux		= {
		.parents	= clk_MAIN_PLL_HFOSC_SEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_PLL_HFOSC_SEL_out0_parents),
	},
	.reg			= 0x43000000 + 32900,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_PLL_HFOSC_SEL_out12 = {
	.data_mux		= {
		.parents	= clk_MAIN_PLL_HFOSC_SEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_PLL_HFOSC_SEL_out0_parents),
	},
	.reg			= 0x43000000 + 32944,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_PLL_HFOSC_SEL_out14 = {
	.data_mux		= {
		.parents	= clk_MAIN_PLL_HFOSC_SEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_PLL_HFOSC_SEL_out0_parents),
	},
	.reg			= 0x43000000 + 32952,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_PLL_HFOSC_SEL_out2 = {
	.data_mux		= {
		.parents	= clk_MAIN_PLL_HFOSC_SEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_PLL_HFOSC_SEL_out0_parents),
	},
	.reg			= 0x43000000 + 32904,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_PLL_HFOSC_SEL_out3 = {
	.data_mux		= {
		.parents	= clk_MAIN_PLL_HFOSC_SEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_PLL_HFOSC_SEL_out0_parents),
	},
	.reg			= 0x43000000 + 32908,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_PLL_HFOSC_SEL_out4 = {
	.data_mux		= {
		.parents	= clk_MAIN_PLL_HFOSC_SEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_PLL_HFOSC_SEL_out0_parents),
	},
	.reg			= 0x43000000 + 32912,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_PLL_HFOSC_SEL_out7 = {
	.data_mux		= {
		.parents	= clk_MAIN_PLL_HFOSC_SEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_PLL_HFOSC_SEL_out0_parents),
	},
	.reg			= 0x43000000 + 32924,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_PLL_HFOSC_SEL_out8 = {
	.data_mux		= {
		.parents	= clk_MAIN_PLL_HFOSC_SEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_PLL_HFOSC_SEL_out0_parents),
	},
	.reg			= 0x43000000 + 32928,
	.bit			= 0,
};
static const struct clk_parent clk_MAIN_TIMER_CLKSEL_out0_parents[] = {
	{
		CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_HFOSC1_CLK_OUT,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_0_HSDIVOUT1_CLK,
		1,
	},
	{
		CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT3_CLK,
		1,
	},
	{
		CLK_J7200_BOARD_0_MCU_EXT_REFCLK0_OUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_EXT_REFCLK1_OUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_WKUP_LF_CLKIN_OUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_CPTS0_RFT_CLK_OUT,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT3_CLK,
		1,
	},
	{
		CLK_J7200_POSTDIV2_16FFT_MAIN_2_HSDIVOUT6_CLK,
		1,
	},
	{
		0,
		1,
	},
	{
		CLK_J7200_NAVSS256VCL_MAIN_0_CPTS0_GENF2,
		1,
	},
	{
		CLK_J7200_NAVSS256VCL_MAIN_0_CPTS0_GENF3,
		1,
	},
	{
		CLK_J7200_CPSW_5XUSS_MAIN_0_CPTS_GENF0,
		1,
	},
	{
		CLK_J7200_NAVSS256VCL_MAIN_0_CPTS0_GENF4,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out0 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33024,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out1 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33028,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out10 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33064,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out11 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33068,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out12 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33072,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out13 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33076,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out14 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33080,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out15 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33084,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out16 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33088,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out17 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33092,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out18 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33096,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out19 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33100,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out2 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33032,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out3 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33036,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out4 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33040,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out5 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33044,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out6 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33048,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out7 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33052,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out8 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33056,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_TIMER_CLKSEL_out9 = {
	.data_mux		= {
		.parents	= clk_MAIN_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33060,
	.bit			= 0,
};
static const struct clk_parent clk_MAIN_WWDT_CLKSEL_out0_parents[] = {
	{
		CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_WKUP_LF_CLKIN_OUT,
		1,
	},
	{
		CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1,
	},
	{
		CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_32K_CLK,
		1,
	},
	{
		CLK_J7200_BOARD_0_HFOSC1_CLK_OUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_HFOSC1_CLK_OUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_HFOSC1_CLK_OUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_HFOSC1_CLK_OUT,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_MAIN_WWDT_CLKSEL_out0 = {
	.data_mux		= {
		.parents	= clk_MAIN_WWDT_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_WWDT_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33664,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_WWDT_CLKSEL_out1 = {
	.data_mux		= {
		.parents	= clk_MAIN_WWDT_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_WWDT_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33668,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_WWDT_CLKSEL_out6 = {
	.data_mux		= {
		.parents	= clk_MAIN_WWDT_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_WWDT_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33776,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MAIN_WWDT_CLKSEL_out7 = {
	.data_mux		= {
		.parents	= clk_MAIN_WWDT_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_WWDT_CLKSEL_out0_parents),
	},
	.reg			= 0x00100000 + 33780,
	.bit			= 0,
};
static const struct clk_parent clk_MCAN_CLK_MUX_out0_parents[] = {
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_0_HSDIVOUT4_CLK,
		1,
	},
	{
		CLK_J7200_BOARD_0_MCU_EXT_REFCLK0_OUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_HFOSC1_CLK_OUT,
		1,
	},
	{
		CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_MCAN_CLK_MUX_out0 = {
	.data_mux		= {
		.parents	= clk_MCAN_CLK_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_MCAN_CLK_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33920,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCAN_CLK_MUX_out1 = {
	.data_mux		= {
		.parents	= clk_MCAN_CLK_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_MCAN_CLK_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33924,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCAN_CLK_MUX_out10 = {
	.data_mux		= {
		.parents	= clk_MCAN_CLK_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_MCAN_CLK_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33960,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCAN_CLK_MUX_out11 = {
	.data_mux		= {
		.parents	= clk_MCAN_CLK_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_MCAN_CLK_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33964,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCAN_CLK_MUX_out12 = {
	.data_mux		= {
		.parents	= clk_MCAN_CLK_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_MCAN_CLK_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33968,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCAN_CLK_MUX_out13 = {
	.data_mux		= {
		.parents	= clk_MCAN_CLK_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_MCAN_CLK_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33972,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCAN_CLK_MUX_out14_0 = {
	.data_mux		= {
		.parents	= clk_MCAN_CLK_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_MCAN_CLK_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33976,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCAN_CLK_MUX_out15_0 = {
	.data_mux		= {
		.parents	= clk_MCAN_CLK_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_MCAN_CLK_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33980,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCAN_CLK_MUX_out16_0 = {
	.data_mux		= {
		.parents	= clk_MCAN_CLK_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_MCAN_CLK_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33984,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCAN_CLK_MUX_out17_0 = {
	.data_mux		= {
		.parents	= clk_MCAN_CLK_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_MCAN_CLK_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33988,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCAN_CLK_MUX_out2 = {
	.data_mux		= {
		.parents	= clk_MCAN_CLK_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_MCAN_CLK_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33928,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCAN_CLK_MUX_out3 = {
	.data_mux		= {
		.parents	= clk_MCAN_CLK_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_MCAN_CLK_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33932,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCAN_CLK_MUX_out4 = {
	.data_mux		= {
		.parents	= clk_MCAN_CLK_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_MCAN_CLK_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33936,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCAN_CLK_MUX_out5 = {
	.data_mux		= {
		.parents	= clk_MCAN_CLK_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_MCAN_CLK_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33940,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCAN_CLK_MUX_out6 = {
	.data_mux		= {
		.parents	= clk_MCAN_CLK_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_MCAN_CLK_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33944,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCAN_CLK_MUX_out7 = {
	.data_mux		= {
		.parents	= clk_MCAN_CLK_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_MCAN_CLK_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33948,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCAN_CLK_MUX_out8 = {
	.data_mux		= {
		.parents	= clk_MCAN_CLK_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_MCAN_CLK_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33952,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCAN_CLK_MUX_out9 = {
	.data_mux		= {
		.parents	= clk_MCAN_CLK_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_MCAN_CLK_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33956,
	.bit			= 0,
};
static const struct clk_parent clk_MCU_ADC_clk_sel_out0_parents[] = {
	{
		CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT1_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV1_16FFT_MCU_0_HSDIVOUT1_CLK,
		1,
	},
	{
		CLK_J7200_BOARD_0_MCU_EXT_REFCLK0_OUT,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_MCU_ADC_clk_sel_out0 = {
	.data_mux		= {
		.parents	= clk_MCU_ADC_clk_sel_out0_parents,
		.n		= ARRAY_SIZE(clk_MCU_ADC_clk_sel_out0_parents),
	},
	.reg			= 0x40F00000 + 32832,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCU_ADC_clk_sel_out1 = {
	.data_mux		= {
		.parents	= clk_MCU_ADC_clk_sel_out0_parents,
		.n		= ARRAY_SIZE(clk_MCU_ADC_clk_sel_out0_parents),
	},
	.reg			= 0x40F00000 + 32836,
	.bit			= 0,
};
static const struct clk_parent clk_MCU_CLKOUT_MUX_parents[] = {
	{
		CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT0_CLK,
		5,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT0_CLK,
		10,
	},
};
static const struct clk_data_mux_reg clk_data_MCU_CLKOUT_MUX_out0 = {
	.data_mux		= {
		.parents	= clk_MCU_CLKOUT_MUX_parents,
		.n		= ARRAY_SIZE(clk_MCU_CLKOUT_MUX_parents),
	},
	.reg			= 0x40F00000 + 32784,
	.bit			= 0,
};
static const struct clk_parent clk_MCU_R5_core0_clksel_parents[] = {
	{
		CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		1,
	},
	{
		CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		3,
	},
};
static const struct clk_data_mux_reg clk_data_MCU_R5_core0_clksel_out0 = {
	.data_mux		= {
		.parents	= clk_MCU_R5_core0_clksel_parents,
		.n		= ARRAY_SIZE(clk_MCU_R5_core0_clksel_parents),
	},
	.reg			= 0x40F00000 + 32896,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCU_R5_core1_clksel_out0 = {
	.data_mux		= {
		.parents	= clk_MCU_R5_core0_clksel_parents,
		.n		= ARRAY_SIZE(clk_MCU_R5_core0_clksel_parents),
	},
	.reg			= 0x40F00000 + 32896,
	.bit			= 0,
};
static const struct clk_parent clk_MCU_R5_phase0_clksel_parents[] = {
	{
		CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		3,
	},
	{
		0,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_MCU_R5_phase0_clksel_out0 = {
	.data_mux		= {
		.parents	= clk_MCU_R5_phase0_clksel_parents,
		.n		= ARRAY_SIZE(clk_MCU_R5_phase0_clksel_parents),
	},
	.reg			= 0x40F00000 + 32896,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCU_R5_phase1_clksel_out0 = {
	.data_mux		= {
		.parents	= clk_MCU_R5_phase0_clksel_parents,
		.n		= ARRAY_SIZE(clk_MCU_R5_phase0_clksel_parents),
	},
	.reg			= 0x40F00000 + 32896,
	.bit			= 0,
};
static const struct clk_parent clk_MCU_SPI1_CLK_MUX_parents[] = {
	{
		CLK_J7200_SPI_MAIN_3_IO_CLKSPIO_CLK,
		1,
	},
	{
		0,
		0,
	},
};
static const struct clk_data_mux_reg clk_data_MCU_SPI1_CLK_MUX_out0 = {
	.data_mux		= {
		.parents	= clk_MCU_SPI1_CLK_MUX_parents,
		.n		= ARRAY_SIZE(clk_MCU_SPI1_CLK_MUX_parents),
	},
	.reg			= 0x40F00000 + 16480,
	.bit			= 0,
};
static const struct clk_parent clk_MCU_TIMER1_CASCADE_parents[] = {
	{
		CLK_J7200_MCU_TIMER_CLKSEL_OUT1,
		1,
	},
	{
		CLK_J7200_DMTIMER_DMC1MS_MCU_0_TIMER_PWM,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_MCU_TIMER1_CASCADE_out0 = {
	.data_mux		= {
		.parents	= clk_MCU_TIMER1_CASCADE_parents,
		.n		= ARRAY_SIZE(clk_MCU_TIMER1_CASCADE_parents),
	},
	.reg			= 0x40F00000 + 16900,
	.bit			= 8,
};
static const struct clk_parent clk_MCU_TIMER3_CASCADE_parents[] = {
	{
		CLK_J7200_MCU_TIMER_CLKSEL_OUT3,
		1,
	},
	{
		CLK_J7200_DMTIMER_DMC1MS_MCU_2_TIMER_PWM,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_MCU_TIMER3_CASCADE_out0 = {
	.data_mux		= {
		.parents	= clk_MCU_TIMER3_CASCADE_parents,
		.n		= ARRAY_SIZE(clk_MCU_TIMER3_CASCADE_parents),
	},
	.reg			= 0x40F00000 + 16908,
	.bit			= 8,
};
static const struct clk_parent clk_MCU_TIMER5_CASCADE_parents[] = {
	{
		CLK_J7200_MCU_TIMER_CLKSEL_OUT5,
		1,
	},
	{
		CLK_J7200_DMTIMER_DMC1MS_MCU_4_TIMER_PWM,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_MCU_TIMER5_CASCADE_out0 = {
	.data_mux		= {
		.parents	= clk_MCU_TIMER5_CASCADE_parents,
		.n		= ARRAY_SIZE(clk_MCU_TIMER5_CASCADE_parents),
	},
	.reg			= 0x40F00000 + 16916,
	.bit			= 8,
};
static const struct clk_parent clk_MCU_TIMER7_CASCADE_parents[] = {
	{
		CLK_J7200_MCU_TIMER_CLKSEL_OUT7,
		1,
	},
	{
		CLK_J7200_DMTIMER_DMC1MS_MCU_6_TIMER_PWM,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_MCU_TIMER7_CASCADE_out0 = {
	.data_mux		= {
		.parents	= clk_MCU_TIMER7_CASCADE_parents,
		.n		= ARRAY_SIZE(clk_MCU_TIMER7_CASCADE_parents),
	},
	.reg			= 0x40F00000 + 16924,
	.bit			= 8,
};
static const struct clk_parent clk_MCU_TIMER9_CASCADE_parents[] = {
	{
		CLK_J7200_MCU_TIMER_CLKSEL_OUT9,
		1,
	},
	{
		CLK_J7200_DMTIMER_DMC1MS_MCU_8_TIMER_PWM,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_MCU_TIMER9_CASCADE_out0 = {
	.data_mux		= {
		.parents	= clk_MCU_TIMER9_CASCADE_parents,
		.n		= ARRAY_SIZE(clk_MCU_TIMER9_CASCADE_parents),
	},
	.reg			= 0x40F00000 + 16932,
	.bit			= 8,
};
static const struct clk_parent clk_MCU_TIMER_CLKSEL_out0_parents[] = {
	{
		CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1,
	},
	{
		CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		16,
	},
	{
		CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT2_CLK,
		1,
	},
	{
		CLK_J7200_BOARD_0_MCU_EXT_REFCLK0_OUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_WKUP_LF_CLKIN_OUT,
		1,
	},
	{
		CLK_J7200_CPSW_2GUSS_MCU_0_CPTS_GENF0,
		1,
	},
	{
		CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_32K_CLK,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_MCU_TIMER_CLKSEL_out0 = {
	.data_mux		= {
		.parents	= clk_MCU_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MCU_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x40F00000 + 33024,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCU_TIMER_CLKSEL_out1 = {
	.data_mux		= {
		.parents	= clk_MCU_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MCU_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x40F00000 + 33028,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCU_TIMER_CLKSEL_out2 = {
	.data_mux		= {
		.parents	= clk_MCU_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MCU_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x40F00000 + 33032,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCU_TIMER_CLKSEL_out3 = {
	.data_mux		= {
		.parents	= clk_MCU_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MCU_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x40F00000 + 33036,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCU_TIMER_CLKSEL_out4 = {
	.data_mux		= {
		.parents	= clk_MCU_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MCU_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x40F00000 + 33040,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCU_TIMER_CLKSEL_out5 = {
	.data_mux		= {
		.parents	= clk_MCU_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MCU_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x40F00000 + 33044,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCU_TIMER_CLKSEL_out6 = {
	.data_mux		= {
		.parents	= clk_MCU_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MCU_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x40F00000 + 33048,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCU_TIMER_CLKSEL_out7 = {
	.data_mux		= {
		.parents	= clk_MCU_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MCU_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x40F00000 + 33052,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCU_TIMER_CLKSEL_out8 = {
	.data_mux		= {
		.parents	= clk_MCU_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MCU_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x40F00000 + 33056,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_MCU_TIMER_CLKSEL_out9 = {
	.data_mux		= {
		.parents	= clk_MCU_TIMER_CLKSEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MCU_TIMER_CLKSEL_out0_parents),
	},
	.reg			= 0x40F00000 + 33060,
	.bit			= 0,
};
static const struct clk_parent clk_McASP_AHCLKR_MUX_out0_parents[] = {
	{
		CLK_J7200_BOARD_0_HFOSC1_CLK_OUT,
		1,
	},
	{
		CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_AUDIO_EXT_REFCLK0_OUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_AUDIO_EXT_REFCLK1_OUT,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT,
		1,
	},
	{
		CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_1,
		1,
	},
	{
		CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_2,
		1,
	},
	{
		CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_3,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_McASP_AHCLKR_MUX_out0 = {
	.data_mux		= {
		.parents	= clk_McASP_AHCLKR_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_McASP_AHCLKR_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33344,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_McASP_AHCLKR_MUX_out1 = {
	.data_mux		= {
		.parents	= clk_McASP_AHCLKR_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_McASP_AHCLKR_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33348,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_McASP_AHCLKR_MUX_out2 = {
	.data_mux		= {
		.parents	= clk_McASP_AHCLKR_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_McASP_AHCLKR_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33352,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_McASP_AHCLKX_MUX_out0 = {
	.data_mux		= {
		.parents	= clk_McASP_AHCLKR_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_McASP_AHCLKR_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33344,
	.bit			= 8,
};
static const struct clk_data_mux_reg clk_data_McASP_AHCLKX_MUX_out1 = {
	.data_mux		= {
		.parents	= clk_McASP_AHCLKR_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_McASP_AHCLKR_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33348,
	.bit			= 8,
};
static const struct clk_data_mux_reg clk_data_McASP_AHCLKX_MUX_out2 = {
	.data_mux		= {
		.parents	= clk_McASP_AHCLKR_MUX_out0_parents,
		.n		= ARRAY_SIZE(clk_McASP_AHCLKR_MUX_out0_parents),
	},
	.reg			= 0x00100000 + 33352,
	.bit			= 8,
};
static const struct clk_parent clk_McASP_AUXCLK_SEL_out0_parents[] = {
	{
		CLK_J7200_HSDIV2_16FFT_MAIN_4_HSDIVOUT0_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_2_HSDIVOUT2_CLK,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT,
		1,
	},
	{
		CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_1,
		1,
	},
	{
		CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_2,
		1,
	},
	{
		CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_3,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_McASP_AUXCLK_SEL_out0 = {
	.data_mux		= {
		.parents	= clk_McASP_AUXCLK_SEL_out0_parents,
		.n		= ARRAY_SIZE(clk_McASP_AUXCLK_SEL_out0_parents),
	},
	.reg			= 0x00100000 + 33280,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_McASP_AUXCLK_SEL_out1 = {
	.data_mux		= {
		.parents	= clk_McASP_AUXCLK_SEL_out0_parents,
		.n		= ARRAY_SIZE(clk_McASP_AUXCLK_SEL_out0_parents),
	},
	.reg			= 0x00100000 + 33284,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_McASP_AUXCLK_SEL_out2 = {
	.data_mux		= {
		.parents	= clk_McASP_AUXCLK_SEL_out0_parents,
		.n		= ARRAY_SIZE(clk_McASP_AUXCLK_SEL_out0_parents),
	},
	.reg			= 0x00100000 + 33288,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_NAVSS_CPTS_RCLK_MUX_out0 = {
	.data_mux		= {
		.parents	= clk_CPSW5X_CPTS_RFT_MUX_parents,
		.n		= ARRAY_SIZE(clk_CPSW5X_CPTS_RFT_MUX_parents),
	},
	.reg			= 0x00100000 + 32920,
	.bit			= 0,
};
static const struct clk_parent clk_OBSCLK0_MUX_parents[] = {
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_0_HSDIVOUT0_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_2_HSDIVOUT0_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT0_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV2_16FFT_MAIN_4_HSDIVOUT0_CLK,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		CLK_J7200_HSDIV0_16FFT_MAIN_12_HSDIVOUT0_CLK,
		1,
	},
	{
		CLK_J7200_OBSCLK1_MUX_OUT0,
		1,
	},
	{
		CLK_J7200_HSDIV1_16FFT_MAIN_14_HSDIVOUT0_CLK,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		0,
		1,
	},
	{
		CLK_J7200_NAVSS256VCL_MAIN_0_CPTS0_GENF3,
		1,
	},
	{
		CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1,
	},
	{
		CLK_J7200_BOARD_0_WKUP_LF_CLKIN_OUT,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_0_HSDIVOUT0_CLK,
		1,
	},
	{
		CLK_J7200_BOARD_0_HFOSC1_CLK_OUT,
		1,
	},
	{
		CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_OBSCLK0_MUX_out0 = {
	.data_mux		= {
		.parents	= clk_OBSCLK0_MUX_parents,
		.n		= ARRAY_SIZE(clk_OBSCLK0_MUX_parents),
	},
	.reg			= 0x00100000 + 32768,
	.bit			= 0,
};
static const struct clk_parent clk_OBSCLK1_MUX_parents[] = {
	{
		0,
		4,
	},
	{
		CLK_J7200_HSDIV0_16FFT_MAIN_8_HSDIVOUT0_CLK,
		8,
	},
	{
		0,
		4,
	},
	{
		0,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_OBSCLK1_MUX_out0 = {
	.data_mux		= {
		.parents	= clk_OBSCLK1_MUX_parents,
		.n		= ARRAY_SIZE(clk_OBSCLK1_MUX_parents),
	},
	.reg			= 0x00100000 + 32772,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_PCIE1_CPTS_RCLK_MUX_out0 = {
	.data_mux		= {
		.parents	= clk_CPSW5X_CPTS_RFT_MUX_parents,
		.n		= ARRAY_SIZE(clk_CPSW5X_CPTS_RFT_MUX_parents),
	},
	.reg			= 0x00100000 + 32900,
	.bit			= 0,
};
static const struct clk_parent clk_SERDES0_CORE_REFCLK_parents[] = {
	{
		CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_HFOSC1_CLK_OUT,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT4_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_2_HSDIVOUT4_CLK,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_SERDES0_CORE_REFCLK_out0 = {
	.data_mux		= {
		.parents	= clk_SERDES0_CORE_REFCLK_parents,
		.n		= ARRAY_SIZE(clk_SERDES0_CORE_REFCLK_parents),
	},
	.reg			= 0x00100000 + 33792,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_SPI3_CLK_MUX_out0 = {
	.data_mux		= {
		.parents	= clk_MCU_SPI1_CLK_MUX_parents,
		.n		= ARRAY_SIZE(clk_MCU_SPI1_CLK_MUX_parents),
	},
	.reg			= 0x40F00000 + 16480,
	.bit			= 0,
};
static const struct clk_parent clk_TIMER11_CASCADE_parents[] = {
	{
		CLK_J7200_MAIN_TIMER_CLKSEL_OUT11,
		1,
	},
	{
		CLK_J7200_DMTIMER_DMC1MS_MAIN_10_TIMER_PWM,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_TIMER11_CASCADE_out0 = {
	.data_mux		= {
		.parents	= clk_TIMER11_CASCADE_parents,
		.n		= ARRAY_SIZE(clk_TIMER11_CASCADE_parents),
	},
	.reg			= 0x00100000 + 16940,
	.bit			= 8,
};
static const struct clk_parent clk_TIMER13_CASCADE_parents[] = {
	{
		CLK_J7200_MAIN_TIMER_CLKSEL_OUT13,
		1,
	},
	{
		CLK_J7200_DMTIMER_DMC1MS_MAIN_12_TIMER_PWM,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_TIMER13_CASCADE_out0 = {
	.data_mux		= {
		.parents	= clk_TIMER13_CASCADE_parents,
		.n		= ARRAY_SIZE(clk_TIMER13_CASCADE_parents),
	},
	.reg			= 0x00100000 + 16948,
	.bit			= 8,
};
static const struct clk_parent clk_TIMER15_CASCADE_parents[] = {
	{
		CLK_J7200_MAIN_TIMER_CLKSEL_OUT15,
		1,
	},
	{
		CLK_J7200_DMTIMER_DMC1MS_MAIN_14_TIMER_PWM,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_TIMER15_CASCADE_out0 = {
	.data_mux		= {
		.parents	= clk_TIMER15_CASCADE_parents,
		.n		= ARRAY_SIZE(clk_TIMER15_CASCADE_parents),
	},
	.reg			= 0x00100000 + 16956,
	.bit			= 8,
};
static const struct clk_parent clk_TIMER17_CASCADE_parents[] = {
	{
		CLK_J7200_MAIN_TIMER_CLKSEL_OUT17,
		1,
	},
	{
		CLK_J7200_DMTIMER_DMC1MS_MAIN_16_TIMER_PWM,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_TIMER17_CASCADE_out0 = {
	.data_mux		= {
		.parents	= clk_TIMER17_CASCADE_parents,
		.n		= ARRAY_SIZE(clk_TIMER17_CASCADE_parents),
	},
	.reg			= 0x00100000 + 16964,
	.bit			= 8,
};
static const struct clk_parent clk_TIMER19_CASCADE_parents[] = {
	{
		CLK_J7200_MAIN_TIMER_CLKSEL_OUT19,
		1,
	},
	{
		CLK_J7200_DMTIMER_DMC1MS_MAIN_18_TIMER_PWM,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_TIMER19_CASCADE_out0 = {
	.data_mux		= {
		.parents	= clk_TIMER19_CASCADE_parents,
		.n		= ARRAY_SIZE(clk_TIMER19_CASCADE_parents),
	},
	.reg			= 0x00100000 + 16972,
	.bit			= 8,
};
static const struct clk_parent clk_TIMER1_CASCADE_parents[] = {
	{
		CLK_J7200_MAIN_TIMER_CLKSEL_OUT1,
		1,
	},
	{
		CLK_J7200_DMTIMER_DMC1MS_MAIN_0_TIMER_PWM,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_TIMER1_CASCADE_out0 = {
	.data_mux		= {
		.parents	= clk_TIMER1_CASCADE_parents,
		.n		= ARRAY_SIZE(clk_TIMER1_CASCADE_parents),
	},
	.reg			= 0x00100000 + 16900,
	.bit			= 8,
};
static const struct clk_parent clk_TIMER3_CASCADE_parents[] = {
	{
		CLK_J7200_MAIN_TIMER_CLKSEL_OUT3,
		1,
	},
	{
		CLK_J7200_DMTIMER_DMC1MS_MAIN_2_TIMER_PWM,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_TIMER3_CASCADE_out0 = {
	.data_mux		= {
		.parents	= clk_TIMER3_CASCADE_parents,
		.n		= ARRAY_SIZE(clk_TIMER3_CASCADE_parents),
	},
	.reg			= 0x00100000 + 16908,
	.bit			= 8,
};
static const struct clk_parent clk_TIMER5_CASCADE_parents[] = {
	{
		CLK_J7200_MAIN_TIMER_CLKSEL_OUT5,
		1,
	},
	{
		CLK_J7200_DMTIMER_DMC1MS_MAIN_4_TIMER_PWM,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_TIMER5_CASCADE_out0 = {
	.data_mux		= {
		.parents	= clk_TIMER5_CASCADE_parents,
		.n		= ARRAY_SIZE(clk_TIMER5_CASCADE_parents),
	},
	.reg			= 0x00100000 + 16916,
	.bit			= 8,
};
static const struct clk_parent clk_TIMER7_CASCADE_parents[] = {
	{
		CLK_J7200_MAIN_TIMER_CLKSEL_OUT7,
		1,
	},
	{
		CLK_J7200_DMTIMER_DMC1MS_MAIN_6_TIMER_PWM,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_TIMER7_CASCADE_out0 = {
	.data_mux		= {
		.parents	= clk_TIMER7_CASCADE_parents,
		.n		= ARRAY_SIZE(clk_TIMER7_CASCADE_parents),
	},
	.reg			= 0x00100000 + 16924,
	.bit			= 8,
};
static const struct clk_parent clk_TIMER9_CASCADE_parents[] = {
	{
		CLK_J7200_MAIN_TIMER_CLKSEL_OUT9,
		1,
	},
	{
		CLK_J7200_DMTIMER_DMC1MS_MAIN_8_TIMER_PWM,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_TIMER9_CASCADE_out0 = {
	.data_mux		= {
		.parents	= clk_TIMER9_CASCADE_parents,
		.n		= ARRAY_SIZE(clk_TIMER9_CASCADE_parents),
	},
	.reg			= 0x00100000 + 16932,
	.bit			= 8,
};
static const struct clk_data_div_reg clk_data_USART_Programmable_Clock_Divider_out0 = {
	.data_div	= {
		.n	= 4,
	},
	.reg		= 0x00100000 + 33216,
	.bit		= 0,
};
static const struct clk_data_div_reg clk_data_USART_Programmable_Clock_Divider_out1 = {
	.data_div	= {
		.n	= 4,
	},
	.reg		= 0x00100000 + 33220,
	.bit		= 0,
};
static const struct clk_data_div_reg clk_data_USART_Programmable_Clock_Divider_out2 = {
	.data_div	= {
		.n	= 4,
	},
	.reg		= 0x00100000 + 33224,
	.bit		= 0,
};
static const struct clk_data_div_reg clk_data_USART_Programmable_Clock_Divider_out3 = {
	.data_div	= {
		.n	= 4,
	},
	.reg		= 0x00100000 + 33228,
	.bit		= 0,
};
static const struct clk_data_div_reg clk_data_USART_Programmable_Clock_Divider_out4 = {
	.data_div	= {
		.n	= 4,
	},
	.reg		= 0x00100000 + 33232,
	.bit		= 0,
};
static const struct clk_data_div_reg clk_data_USART_Programmable_Clock_Divider_out5 = {
	.data_div	= {
		.n	= 4,
	},
	.reg		= 0x00100000 + 33236,
	.bit		= 0,
};
static const struct clk_data_div_reg clk_data_USART_Programmable_Clock_Divider_out6 = {
	.data_div	= {
		.n	= 4,
	},
	.reg		= 0x00100000 + 33240,
	.bit		= 0,
};
static const struct clk_data_div_reg clk_data_USART_Programmable_Clock_Divider_out7 = {
	.data_div	= {
		.n	= 4,
	},
	.reg		= 0x00100000 + 33244,
	.bit		= 0,
};
static const struct clk_data_div_reg clk_data_USART_Programmable_Clock_Divider_out8 = {
	.data_div	= {
		.n	= 4,
	},
	.reg		= 0x00100000 + 33248,
	.bit		= 0,
};
static const struct clk_data_div_reg clk_data_USART_Programmable_Clock_Divider_out9 = {
	.data_div	= {
		.n	= 4,
	},
	.reg		= 0x00100000 + 33252,
	.bit		= 0,
};
static const struct clk_data_mux_reg clk_data_USB0_REFCLK_SEL_out0 = {
	.data_mux		= {
		.parents	= clk_MAIN_PLL_HFOSC_SEL_out0_parents,
		.n		= ARRAY_SIZE(clk_MAIN_PLL_HFOSC_SEL_out0_parents),
	},
	.reg			= 0x00100000 + 32992,
	.bit			= 0,
};
static const struct clk_parent clk_USB0_SerDes_refclk_Mux_parents[] = {
	{
		CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN1_REFCLK,
		1,
	},
	{
		CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN3_REFCLK,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_USB0_SerDes_refclk_Mux_out0 = {
	.data_mux		= {
		.parents	= clk_USB0_SerDes_refclk_Mux_parents,
		.n		= ARRAY_SIZE(clk_USB0_SerDes_refclk_Mux_parents),
	},
	.reg			= 0x00100000 + 16384,
	.bit			= 27,
};
static const struct clk_parent clk_USB0_SerDes_rxclk_Mux_parents[] = {
	{
		CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN1_RXCLK,
		1,
	},
	{
		CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN3_RXCLK,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_USB0_SerDes_rxclk_Mux_out0 = {
	.data_mux		= {
		.parents	= clk_USB0_SerDes_rxclk_Mux_parents,
		.n		= ARRAY_SIZE(clk_USB0_SerDes_rxclk_Mux_parents),
	},
	.reg			= 0x00100000 + 16384,
	.bit			= 27,
};
static const struct clk_parent clk_USB0_SerDes_rxfclk_Mux_parents[] = {
	{
		CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN1_RXFCLK,
		1,
	},
	{
		CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN3_RXFCLK,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_USB0_SerDes_rxfclk_Mux_out0 = {
	.data_mux		= {
		.parents	= clk_USB0_SerDes_rxfclk_Mux_parents,
		.n		= ARRAY_SIZE(clk_USB0_SerDes_rxfclk_Mux_parents),
	},
	.reg			= 0x00100000 + 16384,
	.bit			= 27,
};
static const struct clk_parent clk_USB0_SerDes_txfclk_Mux_parents[] = {
	{
		CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN1_TXFCLK,
		1,
	},
	{
		CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN3_TXFCLK,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_USB0_SerDes_txfclk_Mux_out0 = {
	.data_mux		= {
		.parents	= clk_USB0_SerDes_txfclk_Mux_parents,
		.n		= ARRAY_SIZE(clk_USB0_SerDes_txfclk_Mux_parents),
	},
	.reg			= 0x00100000 + 16384,
	.bit			= 27,
};
static const struct clk_parent clk_USB0_SerDes_txmclk_Mux_parents[] = {
	{
		CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN1_TXMCLK,
		1,
	},
	{
		CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN3_TXMCLK,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_USB0_SerDes_txmclk_Mux_out0 = {
	.data_mux		= {
		.parents	= clk_USB0_SerDes_txmclk_Mux_parents,
		.n		= ARRAY_SIZE(clk_USB0_SerDes_txmclk_Mux_parents),
	},
	.reg			= 0x00100000 + 16384,
	.bit			= 27,
};
static const struct clk_data_from_dev clk_data_atl_main_0_atl_io_port_atclk_out = {
	.dev		= J7200_DEV_ATL0,
	.clk_idx	= J7200_DEV_ATL0_ATL_IO_PORT_ATCLK_OUT,
};
static const struct clk_data_from_dev clk_data_atl_main_0_atl_io_port_atclk_out_1 = {
	.dev		= J7200_DEV_ATL0,
	.clk_idx	= J7200_DEV_ATL0_ATL_IO_PORT_ATCLK_OUT_1,
};
static const struct clk_data_from_dev clk_data_atl_main_0_atl_io_port_atclk_out_2 = {
	.dev		= J7200_DEV_ATL0,
	.clk_idx	= J7200_DEV_ATL0_ATL_IO_PORT_ATCLK_OUT_2,
};
static const struct clk_data_from_dev clk_data_atl_main_0_atl_io_port_atclk_out_3 = {
	.dev		= J7200_DEV_ATL0,
	.clk_idx	= J7200_DEV_ATL0_ATL_IO_PORT_ATCLK_OUT_3,
};
static const struct clk_data_from_dev clk_data_board_0_hfosc1_clk_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_HFOSC1_CLK_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_AUDIO_EXT_REFCLK0_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_AUDIO_EXT_REFCLK0_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_AUDIO_EXT_REFCLK1_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_AUDIO_EXT_REFCLK1_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_CPTS0_RFT_CLK_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_CPTS0_RFT_CLK_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_EXT_REFCLK1_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_EXT_REFCLK1_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_GPMC0_CLK_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_GPMC0_CLK_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_I2C0_SCL_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_I2C0_SCL_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_I2C1_SCL_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_I2C1_SCL_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_I2C2_SCL_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_I2C2_SCL_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_I2C3_SCL_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_I2C3_SCL_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_I2C4_SCL_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_I2C4_SCL_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_I2C5_SCL_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_I2C5_SCL_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_I2C6_SCL_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_I2C6_SCL_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_I3C0_SCL_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_I3C0_SCL_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_LED_CLK_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_LED_CLK_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_MCASP0_ACLKR_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_MCASP0_ACLKR_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_MCASP0_ACLKX_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_MCASP0_ACLKX_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_MCASP1_ACLKR_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_MCASP1_ACLKR_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_MCASP1_ACLKX_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_MCASP1_ACLKX_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_MCASP2_ACLKR_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_MCASP2_ACLKR_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_MCASP2_ACLKX_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_MCASP2_ACLKX_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_MCU_CPTS0_RFT_CLK_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_MCU_CPTS0_RFT_CLK_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_MCU_EXT_REFCLK0_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_MCU_EXT_REFCLK0_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_MCU_I2C0_SCL_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_MCU_I2C0_SCL_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_MCU_I2C1_SCL_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_MCU_I2C1_SCL_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_MCU_I3C0_SCL_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_MCU_I3C0_SCL_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_MCU_OSPI0_DQS_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_MCU_OSPI0_DQS_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_MCU_RGMII1_RXC_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_MCU_RGMII1_RXC_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_MCU_RMII1_REF_CLK_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_MCU_RMII1_REF_CLK_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_RGMII1_RXC_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_RGMII1_RXC_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_RGMII2_RXC_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_RGMII2_RXC_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_RGMII3_RXC_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_RGMII3_RXC_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_RGMII4_RXC_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_RGMII4_RXC_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_RMII_REF_CLK_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_RMII_REF_CLK_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_TCK_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_TCK_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_WKUP_I2C0_SCL_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_WKUP_I2C0_SCL_OUT,
};
static const struct clk_data_from_dev clk_data_board_0_WKUP_LF_CLKIN_out = {
	.dev		= J7200_DEV_BOARD0,
	.clk_idx	= J7200_DEV_BOARD0_WKUP_LF_CLKIN_OUT,
};
static const struct clk_data_from_dev clk_data_cpsw_2guss_mcu_0_cpts_genf0 = {
	.dev		= J7200_DEV_MCU_CPSW0,
	.clk_idx	= J7200_DEV_MCU_CPSW0_CPTS_GENF0,
};
static const struct clk_data_from_dev clk_data_cpsw_2guss_mcu_0_mdio_mdclk_o = {
	.dev		= J7200_DEV_MCU_CPSW0,
	.clk_idx	= J7200_DEV_MCU_CPSW0_MDIO_MDCLK_O,
};
static const struct clk_data_from_dev clk_data_cpsw_2guss_mcu_0_rgmii1_txc_o = {
	.dev		= J7200_DEV_MCU_CPSW0,
	.clk_idx	= J7200_DEV_MCU_CPSW0_RGMII1_TXC_O,
};
static const struct clk_data_from_dev clk_data_cpsw_5xuss_main_0_cpts_genf0 = {
	.dev		= J7200_DEV_CPSW0,
	.clk_idx	= J7200_DEV_CPSW0_CPTS_GENF0,
};
static const struct clk_data_from_dev clk_data_cpsw_5xuss_main_0_mdio_mdclk_o = {
	.dev		= J7200_DEV_CPSW0,
	.clk_idx	= J7200_DEV_CPSW0_MDIO_MDCLK_O,
};
static const struct clk_data_from_dev clk_data_cpsw_5xuss_main_0_pre_rgmii1_tclk = {
	.dev		= J7200_DEV_CPSW0,
	.clk_idx	= J7200_DEV_CPSW0_PRE_RGMII1_TCLK,
};
static const struct clk_data_from_dev clk_data_cpsw_5xuss_main_0_pre_rgmii2_tclk = {
	.dev		= J7200_DEV_CPSW0,
	.clk_idx	= J7200_DEV_CPSW0_PRE_RGMII2_TCLK,
};
static const struct clk_data_from_dev clk_data_cpsw_5xuss_main_0_pre_rgmii3_tclk = {
	.dev		= J7200_DEV_CPSW0,
	.clk_idx	= J7200_DEV_CPSW0_PRE_RGMII3_TCLK,
};
static const struct clk_data_from_dev clk_data_cpsw_5xuss_main_0_pre_rgmii4_tclk = {
	.dev		= J7200_DEV_CPSW0,
	.clk_idx	= J7200_DEV_CPSW0_PRE_RGMII4_TCLK,
};
static const struct clk_data_from_dev clk_data_cpsw_5xuss_main_0_serdes1_txclk = {
	.dev		= J7200_DEV_CPSW0,
	.clk_idx	= J7200_DEV_CPSW0_SERDES1_TXCLK,
};
static const struct clk_data_from_dev clk_data_cpsw_5xuss_main_0_serdes2_txclk = {
	.dev		= J7200_DEV_CPSW0,
	.clk_idx	= J7200_DEV_CPSW0_SERDES2_TXCLK,
};
static const struct clk_data_from_dev clk_data_cpsw_5xuss_main_0_serdes3_txclk = {
	.dev		= J7200_DEV_CPSW0,
	.clk_idx	= J7200_DEV_CPSW0_SERDES3_TXCLK,
};
static const struct clk_data_from_dev clk_data_cpsw_5xuss_main_0_serdes4_txclk = {
	.dev		= J7200_DEV_CPSW0,
	.clk_idx	= J7200_DEV_CPSW0_SERDES4_TXCLK,
};
static const struct clk_data_from_dev clk_data_debugss_k3_wrap_cv0_main_0_cstpiu_traceclk = {
	.dev		= J7200_DEV_DEBUGSS_WRAP0,
	.clk_idx	= J7200_DEV_DEBUGSS_WRAP0_CSTPIU_TRACECLK,
};
static const struct clk_data_from_dev clk_data_dmtimer_dmc1ms_main_0_timer_pwm = {
	.dev		= J7200_DEV_TIMER0,
	.clk_idx	= J7200_DEV_TIMER0_TIMER_PWM,
};
static const struct clk_data_from_dev clk_data_dmtimer_dmc1ms_main_10_timer_pwm = {
	.dev		= J7200_DEV_TIMER10,
	.clk_idx	= J7200_DEV_TIMER10_TIMER_PWM,
};
static const struct clk_data_from_dev clk_data_dmtimer_dmc1ms_main_12_timer_pwm = {
	.dev		= J7200_DEV_TIMER12,
	.clk_idx	= J7200_DEV_TIMER12_TIMER_PWM,
};
static const struct clk_data_from_dev clk_data_dmtimer_dmc1ms_main_14_timer_pwm = {
	.dev		= J7200_DEV_TIMER14,
	.clk_idx	= J7200_DEV_TIMER14_TIMER_PWM,
};
static const struct clk_data_from_dev clk_data_dmtimer_dmc1ms_main_16_timer_pwm = {
	.dev		= J7200_DEV_TIMER16,
	.clk_idx	= J7200_DEV_TIMER16_TIMER_PWM,
};
static const struct clk_data_from_dev clk_data_dmtimer_dmc1ms_main_18_timer_pwm = {
	.dev		= J7200_DEV_TIMER18,
	.clk_idx	= J7200_DEV_TIMER18_TIMER_PWM,
};
static const struct clk_data_from_dev clk_data_dmtimer_dmc1ms_main_2_timer_pwm = {
	.dev		= J7200_DEV_TIMER2,
	.clk_idx	= J7200_DEV_TIMER2_TIMER_PWM,
};
static const struct clk_data_from_dev clk_data_dmtimer_dmc1ms_main_4_timer_pwm = {
	.dev		= J7200_DEV_TIMER4,
	.clk_idx	= J7200_DEV_TIMER4_TIMER_PWM,
};
static const struct clk_data_from_dev clk_data_dmtimer_dmc1ms_main_6_timer_pwm = {
	.dev		= J7200_DEV_TIMER6,
	.clk_idx	= J7200_DEV_TIMER6_TIMER_PWM,
};
static const struct clk_data_from_dev clk_data_dmtimer_dmc1ms_main_8_timer_pwm = {
	.dev		= J7200_DEV_TIMER8,
	.clk_idx	= J7200_DEV_TIMER8_TIMER_PWM,
};
static const struct clk_data_from_dev clk_data_dmtimer_dmc1ms_mcu_0_timer_pwm = {
	.dev		= J7200_DEV_MCU_TIMER0,
	.clk_idx	= J7200_DEV_MCU_TIMER0_TIMER_PWM,
};
static const struct clk_data_from_dev clk_data_dmtimer_dmc1ms_mcu_2_timer_pwm = {
	.dev		= J7200_DEV_MCU_TIMER2,
	.clk_idx	= J7200_DEV_MCU_TIMER2_TIMER_PWM,
};
static const struct clk_data_from_dev clk_data_dmtimer_dmc1ms_mcu_4_timer_pwm = {
	.dev		= J7200_DEV_MCU_TIMER4,
	.clk_idx	= J7200_DEV_MCU_TIMER4_TIMER_PWM,
};
static const struct clk_data_from_dev clk_data_dmtimer_dmc1ms_mcu_6_timer_pwm = {
	.dev		= J7200_DEV_MCU_TIMER6,
	.clk_idx	= J7200_DEV_MCU_TIMER6_TIMER_PWM,
};
static const struct clk_data_from_dev clk_data_dmtimer_dmc1ms_mcu_8_timer_pwm = {
	.dev		= J7200_DEV_MCU_TIMER8,
	.clk_idx	= J7200_DEV_MCU_TIMER8_TIMER_PWM,
};
static const struct clk_data_from_dev clk_data_emmcsd4ss_main_0_emmcsdss_io_clk_o = {
	.dev		= J7200_DEV_MMCSD1,
	.clk_idx	= J7200_DEV_MMCSD1_EMMCSDSS_IO_CLK_O,
};
static const struct clk_data_from_dev clk_data_fss_mcu_0_hyperbus1p0_0_hpb_out_clk_n = {
	.dev		= J7200_DEV_MCU_FSS0_HYPERBUS1P0_0,
	.clk_idx	= J7200_DEV_MCU_FSS0_HYPERBUS1P0_0_HPB_OUT_CLK_N,
};
static const struct clk_data_from_dev clk_data_fss_mcu_0_hyperbus1p0_0_hpb_out_clk_p = {
	.dev		= J7200_DEV_MCU_FSS0_HYPERBUS1P0_0,
	.clk_idx	= J7200_DEV_MCU_FSS0_HYPERBUS1P0_0_HPB_OUT_CLK_P,
};
static const struct clk_data_from_dev clk_data_fss_mcu_0_ospi_0_ospi_oclk_clk = {
	.dev		= J7200_DEV_MCU_FSS0_OSPI_0,
	.clk_idx	= J7200_DEV_MCU_FSS0_OSPI_0_OSPI_OCLK_CLK,
};
static const struct clk_parent clk_gpmc_fclk_sel_parents[] = {
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_0_HSDIVOUT3_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_2_HSDIVOUT1_CLK,
		6,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_2_HSDIVOUT1_CLK,
		4,
	},
	{
		CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK,
		4,
	},
};
static const struct clk_data_mux_reg clk_data_gpmc_fclk_sel_out0 = {
	.data_mux		= {
		.parents	= clk_gpmc_fclk_sel_parents,
		.n		= ARRAY_SIZE(clk_gpmc_fclk_sel_parents),
	},
	.reg			= 0x00100000 + 32976,
	.bit			= 0,
};
static const struct clk_data_from_dev clk_data_gpmc_main_0_po_gpmc_dev_clk = {
	.dev		= J7200_DEV_GPMC0,
	.clk_idx	= J7200_DEV_GPMC0_PO_GPMC_DEV_CLK,
};
static const struct clk_data_div_reg clk_data_hsdiv0_16fft_main_12_hsdiv0 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 4,
	},
	.reg			= 0x00680000UL + 0x1000UL * 12UL + 0x80UL + 0x4UL * 0UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv0_16fft_main_7_hsdiv0 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 2,
	},
	.reg			= 0x00680000UL + 0x1000UL * 7UL + 0x80UL + 0x4UL * 0UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv0_16fft_main_8_hsdiv0 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 1,
	},
	.reg			= 0x00680000UL + 0x1000UL * 8UL + 0x80UL + 0x4UL * 0UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv1_16fft_main_14_hsdiv0 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 2,
	},
	.reg			= 0x00680000UL + 0x1000UL * 14UL + 0x80UL + 0x4UL * 0UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv1_16fft_mcu_0_hsdiv0 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 2,
	},
	.reg			= 0x40D00000UL + 0x1000UL * 0UL + 0x80UL + 0x4UL * 0UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv1_16fft_mcu_0_hsdiv1 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 34,
	},
	.reg			= 0x40D00000UL + 0x1000UL * 0UL + 0x80UL + 0x4UL * 1UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv2_16fft_main_4_hsdiv0 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 12,
	},
	.reg			= 0x00680000UL + 0x1000UL * 4UL + 0x80UL + 0x4UL * 0UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv2_16fft_main_4_hsdiv1 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 8,
	},
	.reg			= 0x00680000UL + 0x1000UL * 4UL + 0x80UL + 0x4UL * 1UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv2_16fft_main_4_hsdiv2 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 12,
	},
	.reg			= 0x00680000UL + 0x1000UL * 4UL + 0x80UL + 0x4UL * 2UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_0_hsdiv0 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 4,
	},
	.reg			= 0x00680000UL + 0x1000UL * 0UL + 0x80UL + 0x4UL * 0UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_0_hsdiv1 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 10,
	},
	.reg			= 0x00680000UL + 0x1000UL * 0UL + 0x80UL + 0x4UL * 1UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_0_hsdiv2 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 10,
	},
	.reg			= 0x00680000UL + 0x1000UL * 0UL + 0x80UL + 0x4UL * 2UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_0_hsdiv3 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 15,
	},
	.reg			= 0x00680000UL + 0x1000UL * 0UL + 0x80UL + 0x4UL * 3UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_0_hsdiv4 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 25,
	},
	.reg			= 0x00680000UL + 0x1000UL * 0UL + 0x80UL + 0x4UL * 4UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_1_hsdiv0 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 10,
	},
	.reg			= 0x00680000UL + 0x1000UL * 1UL + 0x80UL + 0x4UL * 0UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_1_hsdiv1 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 6,
	},
	.reg			= 0x00680000UL + 0x1000UL * 1UL + 0x80UL + 0x4UL * 1UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_1_hsdiv2 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 10,
	},
	.reg			= 0x00680000UL + 0x1000UL * 1UL + 0x80UL + 0x4UL * 2UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_1_hsdiv3 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 10,
	},
	.reg			= 0x00680000UL + 0x1000UL * 1UL + 0x80UL + 0x4UL * 3UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_2_hsdiv0 = {
	.data_div	= {
		.n	= 128,
	},
	.reg		= 0x00680000UL + 0x1000UL * 2UL + 0x80UL + 0x4UL * 0UL,
	.bit		= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_2_hsdiv1 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 3,
	},
	.reg			= 0x00680000UL + 0x1000UL * 2UL + 0x80UL + 0x4UL * 1UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_2_hsdiv2 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 9,
	},
	.reg			= 0x00680000UL + 0x1000UL * 2UL + 0x80UL + 0x4UL * 2UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_2_hsdiv3 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 6,
	},
	.reg			= 0x00680000UL + 0x1000UL * 2UL + 0x80UL + 0x4UL * 3UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_2_hsdiv4 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 18,
	},
	.reg			= 0x00680000UL + 0x1000UL * 2UL + 0x80UL + 0x4UL * 4UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_3_hsdiv0 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 8,
	},
	.reg			= 0x00680000UL + 0x1000UL * 3UL + 0x80UL + 0x4UL * 0UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_3_hsdiv1 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 10,
	},
	.reg			= 0x00680000UL + 0x1000UL * 3UL + 0x80UL + 0x4UL * 1UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_3_hsdiv2 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 10,
	},
	.reg			= 0x00680000UL + 0x1000UL * 3UL + 0x80UL + 0x4UL * 2UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_3_hsdiv3 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 10,
	},
	.reg			= 0x00680000UL + 0x1000UL * 3UL + 0x80UL + 0x4UL * 3UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_main_3_hsdiv4 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 16,
	},
	.reg			= 0x00680000UL + 0x1000UL * 3UL + 0x80UL + 0x4UL * 4UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_mcu_1_hsdiv0 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 6,
	},
	.reg			= 0x40D00000UL + 0x1000UL * 1UL + 0x80UL + 0x4UL * 0UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_mcu_1_hsdiv1 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 40,
	},
	.reg			= 0x40D00000UL + 0x1000UL * 1UL + 0x80UL + 0x4UL * 1UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_mcu_1_hsdiv2 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 30,
	},
	.reg			= 0x40D00000UL + 0x1000UL * 1UL + 0x80UL + 0x4UL * 2UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_mcu_1_hsdiv3 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 25,
	},
	.reg			= 0x40D00000UL + 0x1000UL * 1UL + 0x80UL + 0x4UL * 3UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_mcu_1_hsdiv4 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 6,
	},
	.reg			= 0x40D00000UL + 0x1000UL * 1UL + 0x80UL + 0x4UL * 4UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_mcu_2_hsdiv0 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 8,
	},
	.reg			= 0x40D00000UL + 0x1000UL * 2UL + 0x80UL + 0x4UL * 0UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_mcu_2_hsdiv1 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 4,
	},
	.reg			= 0x40D00000UL + 0x1000UL * 2UL + 0x80UL + 0x4UL * 1UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_mcu_2_hsdiv2 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 10,
	},
	.reg			= 0x40D00000UL + 0x1000UL * 2UL + 0x80UL + 0x4UL * 2UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_mcu_2_hsdiv3 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 25,
	},
	.reg			= 0x40D00000UL + 0x1000UL * 2UL + 0x80UL + 0x4UL * 3UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_hsdiv4_16fft_mcu_2_hsdiv4 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 6,
	},
	.reg			= 0x40D00000UL + 0x1000UL * 2UL + 0x80UL + 0x4UL * 4UL,
	.bit			= 0,
};
static const struct clk_data_from_dev clk_data_i3c_main_0_i3c_scl_do = {
	.dev		= J7200_DEV_I3C0,
	.clk_idx	= J7200_DEV_I3C0_I3C_SCL_DO,
};
static const struct clk_data_from_dev clk_data_i3c_mcu_0_i3c_scl_do = {
	.dev		= J7200_DEV_MCU_I3C0,
	.clk_idx	= J7200_DEV_MCU_I3C0_I3C_SCL_DO,
};
static const struct clk_data_from_dev clk_data_j7vcl_cpsw_tx_rgmii_wrap_main_0_io__rgmii1_txc__a = {
	.dev		= J7200_DEV_CPSW_TX_RGMII0,
	.clk_idx	= J7200_DEV_CPSW_TX_RGMII0_IO__RGMII1_TXC__A,
};
static const struct clk_data_from_dev clk_data_j7vcl_cpsw_tx_rgmii_wrap_main_0_io__rgmii2_txc__a = {
	.dev		= J7200_DEV_CPSW_TX_RGMII0,
	.clk_idx	= J7200_DEV_CPSW_TX_RGMII0_IO__RGMII2_TXC__A,
};
static const struct clk_data_from_dev clk_data_j7vcl_cpsw_tx_rgmii_wrap_main_0_io__rgmii3_txc__a = {
	.dev		= J7200_DEV_CPSW_TX_RGMII0,
	.clk_idx	= J7200_DEV_CPSW_TX_RGMII0_IO__RGMII3_TXC__A,
};
static const struct clk_data_from_dev clk_data_j7vcl_cpsw_tx_rgmii_wrap_main_0_io__rgmii4_txc__a = {
	.dev		= J7200_DEV_CPSW_TX_RGMII0,
	.clk_idx	= J7200_DEV_CPSW_TX_RGMII0_IO__RGMII4_TXC__A,
};
static const struct clk_parent clk_k3_pll_ctrl_wrap_main_0_parents[] = {
	{
		CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT0,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_0_HSDIVOUT0_CLK,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_k3_pll_ctrl_wrap_main_0_sysclkout_clk = {
	.data_mux		= {
		.parents	= clk_k3_pll_ctrl_wrap_main_0_parents,
		.n		= ARRAY_SIZE(clk_k3_pll_ctrl_wrap_main_0_parents),
	},
	.reg			= 0x00410000,
};
static const struct clk_data_div_reg clk_data_k3_pll_ctrl_wrap_main_0_chip_div1_clk_clk = {
	.data_div	= {
		.n	= 32,
	},
	.reg		= 0x00410000 + 0x118,
	.bit		= 0,
};
static const struct clk_data_div_reg clk_data_k3_pll_ctrl_wrap_main_0_chip_div24_clk_clk = {
	.data_div	= {
		.n	= 32,
	},
	.reg		= 0x00410000 + 0x11c,
	.bit		= 0,
};
static const struct clk_parent clk_k3_pll_ctrl_wrap_wkup_0_parents[] = {
	{
		CLK_J7200_WKUP_FREF_CLKSEL_OUT0,
		1,
	},
	{
		CLK_J7200_HSDIV1_16FFT_MCU_0_HSDIVOUT0_CLK,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_k3_pll_ctrl_wrap_wkup_0_sysclkout_clk = {
	.data_mux		= {
		.parents	= clk_k3_pll_ctrl_wrap_wkup_0_parents,
		.n		= ARRAY_SIZE(clk_k3_pll_ctrl_wrap_wkup_0_parents),
	},
	.reg			= 0x42010000,
};
static const struct clk_data_div_reg clk_data_k3_pll_ctrl_wrap_wkup_0_chip_div1_clk_clk = {
	.data_div	= {
		.n	= 32,
	},
	.reg		= 0x42010000 + 0x118,
	.bit		= 0,
};
static const struct clk_data_div_reg clk_data_k3_pll_ctrl_wrap_wkup_0_chip_div24_clk_clk = {
	.data_div	= {
		.n	= 32,
	},
	.reg		= 0x42010000 + 0x11c,
	.bit		= 0,
};
static const struct clk_data_from_dev clk_data_mcasp_main_0_mcasp_aclkr_pout = {
	.dev		= J7200_DEV_MCASP0,
	.clk_idx	= J7200_DEV_MCASP0_MCASP_ACLKR_POUT,
};
static const struct clk_data_from_dev clk_data_mcasp_main_0_mcasp_aclkx_pout = {
	.dev		= J7200_DEV_MCASP0,
	.clk_idx	= J7200_DEV_MCASP0_MCASP_ACLKX_POUT,
};
static const struct clk_data_from_dev clk_data_mcasp_main_0_mcasp_ahclkr_pout = {
	.dev		= J7200_DEV_MCASP0,
	.clk_idx	= J7200_DEV_MCASP0_MCASP_AHCLKR_POUT,
};
static const struct clk_data_from_dev clk_data_mcasp_main_0_mcasp_ahclkx_pout = {
	.dev		= J7200_DEV_MCASP0,
	.clk_idx	= J7200_DEV_MCASP0_MCASP_AHCLKX_POUT,
};
static const struct clk_data_from_dev clk_data_mcasp_main_1_mcasp_aclkr_pout = {
	.dev		= J7200_DEV_MCASP1,
	.clk_idx	= J7200_DEV_MCASP1_MCASP_ACLKR_POUT,
};
static const struct clk_data_from_dev clk_data_mcasp_main_1_mcasp_aclkx_pout = {
	.dev		= J7200_DEV_MCASP1,
	.clk_idx	= J7200_DEV_MCASP1_MCASP_ACLKX_POUT,
};
static const struct clk_data_from_dev clk_data_mcasp_main_1_mcasp_ahclkr_pout = {
	.dev		= J7200_DEV_MCASP1,
	.clk_idx	= J7200_DEV_MCASP1_MCASP_AHCLKR_POUT,
};
static const struct clk_data_from_dev clk_data_mcasp_main_1_mcasp_ahclkx_pout = {
	.dev		= J7200_DEV_MCASP1,
	.clk_idx	= J7200_DEV_MCASP1_MCASP_AHCLKX_POUT,
};
static const struct clk_data_from_dev clk_data_mcasp_main_2_mcasp_aclkr_pout = {
	.dev		= J7200_DEV_MCASP2,
	.clk_idx	= J7200_DEV_MCASP2_MCASP_ACLKR_POUT,
};
static const struct clk_data_from_dev clk_data_mcasp_main_2_mcasp_aclkx_pout = {
	.dev		= J7200_DEV_MCASP2,
	.clk_idx	= J7200_DEV_MCASP2_MCASP_ACLKX_POUT,
};
static const struct clk_data_from_dev clk_data_mcasp_main_2_mcasp_ahclkr_pout = {
	.dev		= J7200_DEV_MCASP2,
	.clk_idx	= J7200_DEV_MCASP2_MCASP_AHCLKR_POUT,
};
static const struct clk_data_from_dev clk_data_mcasp_main_2_mcasp_ahclkx_pout = {
	.dev		= J7200_DEV_MCASP2,
	.clk_idx	= J7200_DEV_MCASP2_MCASP_AHCLKX_POUT,
};
static const struct clk_parent clk_mcu_OSPI0_iclk_sel_parents[] = {
	{
		CLK_J7200_BOARD_0_MCU_OSPI0_DQS_OUT,
		1,
	},
	{
		CLK_J7200_FSS_MCU_0_OSPI_0_OSPI_OCLK_CLK,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_mcu_OSPI0_iclk_sel_out0 = {
	.data_mux		= {
		.parents	= clk_mcu_OSPI0_iclk_sel_parents,
		.n		= ARRAY_SIZE(clk_mcu_OSPI0_iclk_sel_parents),
	},
	.reg			= 0x40F00000 + 32816,
	.bit			= 4,
};
static const struct clk_parent clk_mcu_OSPI_ref_clk_sel_out0_parents[] = {
	{
		CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT4_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT4_CLK,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_mcu_OSPI_ref_clk_sel_out0 = {
	.data_mux		= {
		.parents	= clk_mcu_OSPI_ref_clk_sel_out0_parents,
		.n		= ARRAY_SIZE(clk_mcu_OSPI_ref_clk_sel_out0_parents),
	},
	.reg			= 0x40F00000 + 32816,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_mcu_OSPI_ref_clk_sel_out1 = {
	.data_mux		= {
		.parents	= clk_mcu_OSPI_ref_clk_sel_out0_parents,
		.n		= ARRAY_SIZE(clk_mcu_OSPI_ref_clk_sel_out0_parents),
	},
	.reg			= 0x40F00000 + 32820,
	.bit			= 0,
};
static const struct clk_parent clk_mcu_WWD_clksel_out0_parents[] = {
	{
		CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_WKUP_LF_CLKIN_OUT,
		1,
	},
	{
		CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1,
	},
	{
		CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_32K_CLK,
		1,
	},
	{
		0,
		0,
	},
	{
		0,
		0,
	},
	{
		0,
		0,
	},
	{
		0,
		0,
	},
};
static const struct clk_data_mux_reg clk_data_mcu_WWD_clksel_out0 = {
	.data_mux		= {
		.parents	= clk_mcu_WWD_clksel_out0_parents,
		.n		= ARRAY_SIZE(clk_mcu_WWD_clksel_out0_parents),
	},
	.reg			= 0x40F00000 + 33152,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_mcu_WWD_clksel_out1 = {
	.data_mux		= {
		.parents	= clk_mcu_WWD_clksel_out0_parents,
		.n		= ARRAY_SIZE(clk_mcu_WWD_clksel_out0_parents),
	},
	.reg			= 0x40F00000 + 33156,
	.bit			= 0,
};
static const struct clk_parent clk_mcu_mcan_clk_sel_out0_parents[] = {
	{
		CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT3_CLK,
		1,
	},
	{
		CLK_J7200_BOARD_0_MCU_EXT_REFCLK0_OUT,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT2_CLK,
		1,
	},
	{
		CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_mcu_mcan_clk_sel_out0 = {
	.data_mux		= {
		.parents	= clk_mcu_mcan_clk_sel_out0_parents,
		.n		= ARRAY_SIZE(clk_mcu_mcan_clk_sel_out0_parents),
	},
	.reg			= 0x40F00000 + 32800,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_mcu_mcan_clk_sel_out1 = {
	.data_mux		= {
		.parents	= clk_mcu_mcan_clk_sel_out0_parents,
		.n		= ARRAY_SIZE(clk_mcu_mcan_clk_sel_out0_parents),
	},
	.reg			= 0x40F00000 + 32804,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_mcu_obsclk_div_out0 = {
	.data_div	= {
		.n	= 16,
	},
	.reg		= 0x43000000 + 32768,
	.bit		= 8,
};
static const struct clk_parent clk_mcu_obsclk_outmux_parents[] = {
	{
		CLK_J7200_MCU_OBSCLK_DIV_OUT0,
		1,
	},
	{
		CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_mcu_obsclk_outmux_out0 = {
	.data_mux		= {
		.parents	= clk_mcu_obsclk_outmux_parents,
		.n		= ARRAY_SIZE(clk_mcu_obsclk_outmux_parents),
	},
	.reg			= 0x43000000 + 32768,
	.bit			= 24,
};
static const struct clk_parent clk_mcuusart_clk_sel_parents[] = {
	{
		CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT3_CLK,
		1,
	},
	{
		CLK_J7200_POSTDIV2_16FFT_MAIN_1_HSDIVOUT5_CLK,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_mcuusart_clk_sel_out0 = {
	.data_mux		= {
		.parents	= clk_mcuusart_clk_sel_parents,
		.n		= ARRAY_SIZE(clk_mcuusart_clk_sel_parents),
	},
	.reg			= 0x40F00000 + 33216,
	.bit			= 0,
};
static const struct clk_data_from_dev clk_data_mshsi2c_wkup_0_porscl = {
	.dev		= J7200_DEV_WKUP_I2C0,
	.clk_idx	= J7200_DEV_WKUP_I2C0_PORSCL,
};
static const struct clk_data_from_dev clk_data_navss256vcl_main_0_cpts0_genf2 = {
	.dev		= J7200_DEV_NAVSS0,
	.clk_idx	= J7200_DEV_NAVSS0_CPTS0_GENF2,
};
static const struct clk_data_from_dev clk_data_navss256vcl_main_0_cpts0_genf3 = {
	.dev		= J7200_DEV_NAVSS0,
	.clk_idx	= J7200_DEV_NAVSS0_CPTS0_GENF3,
};
static const struct clk_data_from_dev clk_data_navss256vcl_main_0_cpts0_genf4 = {
	.dev		= J7200_DEV_NAVSS0,
	.clk_idx	= J7200_DEV_NAVSS0_CPTS0_GENF4,
};
static const struct clk_data_from_dev clk_data_navss256vcl_main_0_cpts_0_ts_genf0 = {
	.dev		= J7200_DEV_NAVSS0_CPTS_0,
	.clk_idx	= J7200_DEV_NAVSS0_CPTS_0_TS_GENF0,
};
static const struct clk_data_from_dev clk_data_navss256vcl_main_0_cpts_0_ts_genf1 = {
	.dev		= J7200_DEV_NAVSS0_CPTS_0,
	.clk_idx	= J7200_DEV_NAVSS0_CPTS_0_TS_GENF1,
};
static const struct clk_data_div_reg clk_data_osbclk0_div_out0 = {
	.data_div	= {
		.n	= 256,
	},
	.reg		= 0x00100000 + 32768,
	.bit		= 8,
};
static const struct clk_data_from_dev clk_data_pcie_g3x4_128_main_1_pcie_lane0_txclk = {
	.dev		= J7200_DEV_PCIE1,
	.clk_idx	= J7200_DEV_PCIE1_PCIE_LANE0_TXCLK,
};
static const struct clk_data_from_dev clk_data_pcie_g3x4_128_main_1_pcie_lane1_txclk = {
	.dev		= J7200_DEV_PCIE1,
	.clk_idx	= J7200_DEV_PCIE1_PCIE_LANE1_TXCLK,
};
static const struct clk_data_from_dev clk_data_pcie_g3x4_128_main_1_pcie_lane2_txclk = {
	.dev		= J7200_DEV_PCIE1,
	.clk_idx	= J7200_DEV_PCIE1_PCIE_LANE2_TXCLK,
};
static const struct clk_data_from_dev clk_data_pcie_g3x4_128_main_1_pcie_lane3_txclk = {
	.dev		= J7200_DEV_PCIE1,
	.clk_idx	= J7200_DEV_PCIE1_PCIE_LANE3_TXCLK,
};
static const struct clk_data_pll_16fft clk_data_pllfracf_ssmod_16fft_main_0 = {
	.data_pll			= {
		.vco_range_idx		= J7200_FREQ_RANGE_VCO_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.vco_in_range_idx	= J7200_FREQ_RANGE_VCO_IN_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.fractional_support	= STRUE,
		.devgrp			= DEVGRP_01,
		.pll_entries		= pllfracf_ssmod_16fft_main_0_entries,
		.default_freq_idx	= FREQ_PLLFRACF_SSMOD_16FFT_MAIN_0_DEFAULT,
	},
	.idx				= 0,
	.base				= 0x00680000,
};
static const struct clk_data_div clk_data_pllfracf_ssmod_16fft_main_0_postdiv = {
	.n	= 49,
};
static const struct clk_data_pll_16fft clk_data_pllfracf_ssmod_16fft_main_1 = {
	.data_pll			= {
		.vco_range_idx		= J7200_FREQ_RANGE_VCO_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.vco_in_range_idx	= J7200_FREQ_RANGE_VCO_IN_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.fractional_support	= STRUE,
		.devgrp			= DEVGRP_01,
		.pll_entries		= pllfracf_ssmod_16fft_main_1_entries,
		.default_freq_idx	= FREQ_PLLFRACF_SSMOD_16FFT_MAIN_1_DEFAULT,
	},
	.idx				= 1,
	.base				= 0x00680000,
};
static const struct clk_data_div clk_data_pllfracf_ssmod_16fft_main_1_postdiv = {
	.n	= 49,
};
static const struct clk_data_pll_16fft clk_data_pllfracf_ssmod_16fft_main_12 = {
	.data_pll			= {
		.vco_range_idx		= J7200_FREQ_RANGE_VCO_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.vco_in_range_idx	= J7200_FREQ_RANGE_VCO_IN_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.fractional_support	= STRUE,
		.devgrp			= DEVGRP_01,
		.pll_entries		= pllfracf_ssmod_16fft_main_12_entries,
		.default_freq_idx	= FREQ_PLLFRACF_SSMOD_16FFT_MAIN_12_DEFAULT,
	},
	.idx				= 12,
	.base				= 0x00680000,
};
static const struct clk_data_pll_16fft clk_data_pllfracf_ssmod_16fft_main_14 = {
	.data_pll			= {
		.vco_range_idx		= J7200_FREQ_RANGE_VCO_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.vco_in_range_idx	= J7200_FREQ_RANGE_VCO_IN_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.fractional_support	= STRUE,
		.devgrp			= DEVGRP_01,
		.pll_entries		= pllfracf_ssmod_16fft_main_14_entries,
		.default_freq_idx	= FREQ_PLLFRACF_SSMOD_16FFT_MAIN_14_DEFAULT,
	},
	.idx				= 14,
	.base				= 0x00680000,
};
static const struct clk_data_pll_16fft clk_data_pllfracf_ssmod_16fft_main_2 = {
	.data_pll			= {
		.vco_range_idx		= J7200_FREQ_RANGE_VCO_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.vco_in_range_idx	= J7200_FREQ_RANGE_VCO_IN_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.fractional_support	= STRUE,
		.devgrp			= DEVGRP_01,
		.pll_entries		= pllfracf_ssmod_16fft_main_2_entries,
		.default_freq_idx	= FREQ_PLLFRACF_SSMOD_16FFT_MAIN_2_DEFAULT,
	},
	.idx				= 2,
	.base				= 0x00680000,
};
static const struct clk_data_div clk_data_pllfracf_ssmod_16fft_main_2_postdiv = {
	.n	= 49,
};
static const struct clk_data_pll_16fft clk_data_pllfracf_ssmod_16fft_main_3 = {
	.data_pll			= {
		.vco_range_idx		= J7200_FREQ_RANGE_VCO_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.vco_in_range_idx	= J7200_FREQ_RANGE_VCO_IN_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.fractional_support	= STRUE,
		.devgrp			= DEVGRP_01,
		.pll_entries		= pllfracf_ssmod_16fft_main_3_entries,
		.default_freq_idx	= FREQ_PLLFRACF_SSMOD_16FFT_MAIN_14_DEFAULT,
	},
	.idx				= 3,
	.base				= 0x00680000,
};
static const struct clk_data_pll_16fft clk_data_pllfracf_ssmod_16fft_main_4 = {
	.data_pll			= {
		.vco_range_idx		= J7200_FREQ_RANGE_VCO_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.vco_in_range_idx	= J7200_FREQ_RANGE_VCO_IN_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.fractional_support	= STRUE,
		.devgrp			= DEVGRP_01,
		.pll_entries		= pllfracf_ssmod_16fft_main_4_entries,
		.default_freq_idx	= FREQ_PLLFRACF_SSMOD_16FFT_MAIN_4_DEFAULT,
	},
	.idx				= 4,
	.base				= 0x00680000,
};
static const struct clk_data_pll_16fft clk_data_pllfracf_ssmod_16fft_main_7 = {
	.data_pll			= {
		.vco_range_idx		= J7200_FREQ_RANGE_VCO_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.vco_in_range_idx	= J7200_FREQ_RANGE_VCO_IN_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.fractional_support	= STRUE,
		.devgrp			= DEVGRP_01,
		.pll_entries		= pllfracf_ssmod_16fft_main_0_entries,
		.default_freq_idx	= FREQ_PLLFRACF_SSMOD_16FFT_MAIN_14_DEFAULT,
	},
	.idx				= 7,
	.base				= 0x00680000,
};
static const struct clk_data_pll_16fft clk_data_pllfracf_ssmod_16fft_main_8 = {
	.data_pll			= {
		.vco_range_idx		= J7200_FREQ_RANGE_VCO_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.vco_in_range_idx	= J7200_FREQ_RANGE_VCO_IN_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.fractional_support	= STRUE,
		.devgrp			= DEVGRP_01,
		.pll_entries		= pllfracf_ssmod_16fft_main_14_entries,
		.default_freq_idx	= FREQ_PLLFRACF_SSMOD_16FFT_MAIN_14_DEFAULT,
	},
	.idx				= 8,
	.base				= 0x00680000,
};
static const struct clk_data_pll_16fft clk_data_pllfracf_ssmod_16fft_mcu_0 = {
	.data_pll			= {
		.vco_range_idx		= J7200_FREQ_RANGE_VCO_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.vco_in_range_idx	= J7200_FREQ_RANGE_VCO_IN_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.fractional_support	= STRUE,
		.devgrp			= DEVGRP_01,
		.pll_entries		= pllfracf_ssmod_16fft_mcu_0_entries,
		.default_freq_idx	= FREQ_PLLFRACF_SSMOD_16FFT_MAIN_14_DEFAULT,
	},
	.idx				= 0,
	.base				= 0x40D00000,
};
static const struct clk_data_pll_16fft clk_data_pllfracf_ssmod_16fft_mcu_1 = {
	.data_pll			= {
		.vco_range_idx		= J7200_FREQ_RANGE_VCO_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.vco_in_range_idx	= J7200_FREQ_RANGE_VCO_IN_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.fractional_support	= STRUE,
		.devgrp			= DEVGRP_01,
		.pll_entries		= pllfracf_ssmod_16fft_mcu_1_entries,
		.default_freq_idx	= FREQ_PLLFRACF_SSMOD_16FFT_MCU_1_DEFAULT,
	},
	.idx				= 1,
	.base				= 0x40D00000,
};
static const struct clk_data_pll_16fft clk_data_pllfracf_ssmod_16fft_mcu_2 = {
	.data_pll			= {
		.vco_range_idx		= J7200_FREQ_RANGE_VCO_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.vco_in_range_idx	= J7200_FREQ_RANGE_VCO_IN_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.fractional_support	= STRUE,
		.devgrp			= DEVGRP_01,
		.pll_entries		= pllfracf_ssmod_16fft_main_14_entries,
		.default_freq_idx	= FREQ_PLLFRACF_SSMOD_16FFT_MAIN_14_DEFAULT,
	},
	.idx				= 2,
	.base				= 0x40D00000,
};
static const struct clk_data_div_reg clk_data_postdiv2_16fft_main_0_hsdiv5 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 20,
	},
	.reg			= 0x00680000UL + 0x1000UL * 0UL + 0x80UL + 0x4UL * 5UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_postdiv2_16fft_main_0_hsdiv6 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 5,
	},
	.reg			= 0x00680000UL + 0x1000UL * 0UL + 0x80UL + 0x4UL * 6UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_postdiv2_16fft_main_0_hsdiv7 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 5,
	},
	.reg			= 0x00680000UL + 0x1000UL * 0UL + 0x80UL + 0x4UL * 7UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_postdiv2_16fft_main_1_hsdiv5 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 5,
	},
	.reg			= 0x00680000UL + 0x1000UL * 1UL + 0x80UL + 0x4UL * 5UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_postdiv2_16fft_main_1_hsdiv7 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 40,
	},
	.reg			= 0x00680000UL + 0x1000UL * 1UL + 0x80UL + 0x4UL * 7UL,
	.bit			= 0,
};
static const struct clk_data_div_reg clk_data_postdiv2_16fft_main_2_hsdiv6 = {
	.data_div		= {
		.n		= 128,
		.default_div	= 4,
	},
	.reg			= 0x00680000UL + 0x1000UL * 2UL + 0x80UL + 0x4UL * 6UL,
	.bit			= 0,
};
static const struct clk_data_from_dev clk_data_spi_main_0_io_clkspio_clk = {
	.dev		= J7200_DEV_MCSPI0,
	.clk_idx	= J7200_DEV_MCSPI0_IO_CLKSPIO_CLK,
};
static const struct clk_data_from_dev clk_data_spi_main_1_io_clkspio_clk = {
	.dev		= J7200_DEV_MCSPI1,
	.clk_idx	= J7200_DEV_MCSPI1_IO_CLKSPIO_CLK,
};
static const struct clk_data_from_dev clk_data_spi_main_2_io_clkspio_clk = {
	.dev		= J7200_DEV_MCSPI2,
	.clk_idx	= J7200_DEV_MCSPI2_IO_CLKSPIO_CLK,
};
static const struct clk_data_from_dev clk_data_spi_main_3_io_clkspio_clk = {
	.dev		= J7200_DEV_MCSPI3,
	.clk_idx	= J7200_DEV_MCSPI3_IO_CLKSPIO_CLK,
};
static const struct clk_data_from_dev clk_data_spi_main_4_io_clkspio_clk = {
	.dev		= J7200_DEV_MCSPI4,
	.clk_idx	= J7200_DEV_MCSPI4_IO_CLKSPIO_CLK,
};
static const struct clk_data_from_dev clk_data_spi_main_5_io_clkspio_clk = {
	.dev		= J7200_DEV_MCSPI5,
	.clk_idx	= J7200_DEV_MCSPI5_IO_CLKSPIO_CLK,
};
static const struct clk_data_from_dev clk_data_spi_main_6_io_clkspio_clk = {
	.dev		= J7200_DEV_MCSPI6,
	.clk_idx	= J7200_DEV_MCSPI6_IO_CLKSPIO_CLK,
};
static const struct clk_data_from_dev clk_data_spi_main_7_io_clkspio_clk = {
	.dev		= J7200_DEV_MCSPI7,
	.clk_idx	= J7200_DEV_MCSPI7_IO_CLKSPIO_CLK,
};
static const struct clk_data_from_dev clk_data_spi_mcu_0_io_clkspio_clk = {
	.dev		= J7200_DEV_MCU_MCSPI0,
	.clk_idx	= J7200_DEV_MCU_MCSPI0_IO_CLKSPIO_CLK,
};
static const struct clk_data_from_dev clk_data_spi_mcu_1_io_clkspio_clk = {
	.dev		= J7200_DEV_MCU_MCSPI1,
	.clk_idx	= J7200_DEV_MCU_MCSPI1_IO_CLKSPIO_CLK,
};
static const struct clk_data_from_dev clk_data_spi_mcu_2_io_clkspio_clk = {
	.dev		= J7200_DEV_MCU_MCSPI2,
	.clk_idx	= J7200_DEV_MCU_MCSPI2_IO_CLKSPIO_CLK,
};
static const struct clk_data_from_dev clk_data_usb3p0ss_16ffc_main_0_pipe_txclk = {
	.dev		= J7200_DEV_USB0,
	.clk_idx	= J7200_DEV_USB0_PIPE_TXCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln0_refclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN0_REFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln0_rxclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN0_RXCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln0_rxfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN0_RXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln0_txfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN0_TXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln0_txmclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN0_TXMCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln1_refclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN1_REFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln1_rxclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN1_RXCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln1_rxfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN1_RXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln1_txfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN1_TXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln1_txmclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN1_TXMCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln2_refclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN2_REFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln2_rxclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN2_RXCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln2_rxfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN2_RXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln2_txfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN2_TXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln2_txmclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN2_TXMCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln3_refclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN3_REFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln3_rxclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN3_RXCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln3_rxfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN3_RXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln3_txfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN3_TXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip1_ln3_txmclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP1_LN3_TXMCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln0_refclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN0_REFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln0_rxclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN0_RXCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln0_rxfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN0_RXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln0_txfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN0_TXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln0_txmclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN0_TXMCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln1_refclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN1_REFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln1_rxclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN1_RXCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln1_rxfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN1_RXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln1_txfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN1_TXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln1_txmclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN1_TXMCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln2_refclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN2_REFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln2_rxclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN2_RXCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln2_rxfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN2_RXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln2_txfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN2_TXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln2_txmclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN2_TXMCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln3_refclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN3_REFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln3_rxclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN3_RXCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln3_rxfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN3_RXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln3_txfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN3_TXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip2_ln3_txmclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP2_LN3_TXMCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip3_ln1_refclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP3_LN1_REFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip3_ln1_rxclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP3_LN1_RXCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip3_ln1_rxfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP3_LN1_RXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip3_ln1_txfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP3_LN1_TXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip3_ln1_txmclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP3_LN1_TXMCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip3_ln3_refclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP3_LN3_REFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip3_ln3_rxclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP3_LN3_RXCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip3_ln3_rxfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP3_LN3_RXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip3_ln3_txfclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP3_LN3_TXFCLK,
};
static const struct clk_data_from_dev clk_data_wiz16b8m4ct2_main_1_ip3_ln3_txmclk = {
	.dev		= J7200_DEV_SERDES_10G1,
	.clk_idx	= J7200_DEV_SERDES_10G1_IP3_LN3_TXMCLK,
};
static const struct clk_parent clk_wkup_FREF_clksel_parents[] = {
	{
		CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1,
	},
	{
		CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_wkup_FREF_clksel_out0 = {
	.data_mux		= {
		.parents	= clk_wkup_FREF_clksel_parents,
		.n		= ARRAY_SIZE(clk_wkup_FREF_clksel_parents),
	},
	.reg			= 0x43000000 + 32848,
	.bit			= 8,
};
static const struct clk_parent clk_wkup_gpio0_clksel_parents[] = {
	{
		CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6,
	},
	{
		CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK,
		6,
	},
	{
		CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_32K_CLK,
		1,
	},
	{
		CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_wkup_gpio0_clksel_out0 = {
	.data_mux		= {
		.parents	= clk_wkup_gpio0_clksel_parents,
		.n		= ARRAY_SIZE(clk_wkup_gpio0_clksel_parents),
	},
	.reg			= 0x43000000 + 32880,
	.bit			= 0,
};
static const struct clk_parent clk_wkup_i2c0_mcupll_bypass_clksel_parents[] = {
	{
		CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT3_CLK,
		1,
	},
	{
		CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_wkup_i2c0_mcupll_bypass_clksel_out0 = {
	.data_mux		= {
		.parents	= clk_wkup_i2c0_mcupll_bypass_clksel_parents,
		.n		= ARRAY_SIZE(clk_wkup_i2c0_mcupll_bypass_clksel_parents),
	},
	.reg			= 0x43000000 + 32864,
	.bit			= 0,
};
static const struct clk_parent clk_wkup_obsclk_mux_parents[] = {
	{
		CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
		1,
	},
	{
		0,
		1,
	},
	{
		CLK_J7200_HSDIV1_16FFT_MCU_0_HSDIVOUT0_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV1_16FFT_MCU_0_HSDIVOUT0_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT1_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT2_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT3_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT4_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT0_CLK,
		1,
	},
	{
		CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_32K_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT1_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT2_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT3_CLK,
		1,
	},
	{
		CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT4_CLK,
		1,
	},
	{
		CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1,
	},
	{
		CLK_J7200_BOARD_0_WKUP_LF_CLKIN_OUT,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_wkup_obsclk_mux_out0 = {
	.data_mux		= {
		.parents	= clk_wkup_obsclk_mux_parents,
		.n		= ARRAY_SIZE(clk_wkup_obsclk_mux_parents),
	},
	.reg			= 0x43000000 + 32768,
	.bit			= 0,
};
static const struct clk_parent clk_wkup_usart_mcupll_bypass_clksel_parents[] = {
	{
		CLK_J7200_WKUPUSART_CLK_SEL_OUT0,
		1,
	},
	{
		CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT,
		1,
	},
};
static const struct clk_data_mux_reg clk_data_wkup_usart_mcupll_bypass_clksel_out0 = {
	.data_mux		= {
		.parents	= clk_wkup_usart_mcupll_bypass_clksel_parents,
		.n		= ARRAY_SIZE(clk_wkup_usart_mcupll_bypass_clksel_parents),
	},
	.reg			= 0x43000000 + 32864,
	.bit			= 0,
};
static const struct clk_data_mux_reg clk_data_wkupusart_clk_sel_out0 = {
	.data_mux		= {
		.parents	= clk_mcuusart_clk_sel_parents,
		.n		= ARRAY_SIZE(clk_mcuusart_clk_sel_parents),
	},
	.reg			= 0x43000000 + 32868,
	.bit			= 0,
};

const struct clk_data soc_clock_data[] = {
	[CLK_J7200_GLUELOGIC_HFOSC0_CLKOUT] =				{
		.drv	= &clk_drv_soc_hfosc0,
		.flags	= 0,
	},
	[CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK] =	{
		.drv		= &clk_drv_fixed,
		.flags		= 0,
		.range_idx	= J7200_FREQ_RANGE_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_12P5M_CLK,
	},
	[CLK_J7200_WKUP_FREF_CLKSEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_wkup_FREF_clksel_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_PLLFRACF_SSMOD_16FFT_MCU_0_FOUTVCOP_CLK] =		{
		.parent		=					{
			CLK_J7200_WKUP_FREF_CLKSEL_OUT0,
			1,
		},
		.drv		= &clk_drv_pll_16fft,
		.freq_idx	= J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MCU_0,
		.data		= &clk_data_pllfracf_ssmod_16fft_mcu_0.data_pll.data,
	},
	[CLK_J7200_HSDIV1_16FFT_MCU_0_HSDIVOUT0_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MCU_0_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv1_16fft_mcu_0_hsdiv0.data_div.data,
	},
	[CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_SYSCLKOUT_CLK] =		{
		.drv	= &clk_drv_pllctrl_mux_reg_ro.drv,
		.flags	= 0,
		.data	= &clk_data_k3_pll_ctrl_wrap_wkup_0_sysclkout_clk.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV1_CLK_CLK] =		{
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.data	= &clk_data_k3_pll_ctrl_wrap_wkup_0_chip_div1_clk_clk.data_div.data,
		.parent =						{
			CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_SYSCLKOUT_CLK,
			1,
		},
	},
	[CLK_J7200_MCU_R5_CORE0_CLKSEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_R5_core0_clksel_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_R5_CORE1_CLKSEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_R5_core1_clksel_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_R5_PHASE0_CLKSEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_R5_phase0_clksel_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_R5_PHASE1_CLKSEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_R5_phase1_clksel_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_atl_main_0_atl_io_port_atclk_out.data,
		.freq_idx	= J7200_FREQ_VALUE_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT,
	},
	[CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_1] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_atl_main_0_atl_io_port_atclk_out_1.data,
		.freq_idx	= J7200_FREQ_VALUE_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_1,
	},
	[CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_2] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_atl_main_0_atl_io_port_atclk_out_2.data,
		.freq_idx	= J7200_FREQ_VALUE_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_2,
	},
	[CLK_J7200_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_3] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_atl_main_0_atl_io_port_atclk_out_3.data,
		.freq_idx	= J7200_FREQ_VALUE_ATL_MAIN_0_ATL_IO_PORT_ATCLK_OUT_3,
	},
	[CLK_J7200_BOARD_0_HFOSC1_CLK_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_hfosc1_clk_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_HFOSC1_CLK_OUT,
	},
	[CLK_J7200_BOARD_0_AUDIO_EXT_REFCLK0_OUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_AUDIO_EXT_REFCLK0_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_AUDIO_EXT_REFCLK0_OUT,
	},
	[CLK_J7200_BOARD_0_AUDIO_EXT_REFCLK1_OUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_AUDIO_EXT_REFCLK1_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_AUDIO_EXT_REFCLK1_OUT,
	},
	[CLK_J7200_BOARD_0_CPTS0_RFT_CLK_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_CPTS0_RFT_CLK_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_CPTS0_RFT_CLK_OUT,
	},
	[CLK_J7200_BOARD_0_EXT_REFCLK1_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_EXT_REFCLK1_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_EXT_REFCLK1_OUT,
	},
	[CLK_J7200_BOARD_0_GPMC0_CLK_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_GPMC0_CLK_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_GPMC0_CLK_OUT,
	},
	[CLK_J7200_BOARD_0_I2C0_SCL_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_I2C0_SCL_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_I2C0_SCL_OUT,
	},
	[CLK_J7200_BOARD_0_I2C1_SCL_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_I2C1_SCL_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_I2C1_SCL_OUT,
	},
	[CLK_J7200_BOARD_0_I2C2_SCL_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_I2C2_SCL_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_I2C2_SCL_OUT,
	},
	[CLK_J7200_BOARD_0_I2C3_SCL_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_I2C3_SCL_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_I2C3_SCL_OUT,
	},
	[CLK_J7200_BOARD_0_I2C4_SCL_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_I2C4_SCL_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_I2C4_SCL_OUT,
	},
	[CLK_J7200_BOARD_0_I2C5_SCL_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_I2C5_SCL_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_I2C5_SCL_OUT,
	},
	[CLK_J7200_BOARD_0_I2C6_SCL_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_I2C6_SCL_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_I2C6_SCL_OUT,
	},
	[CLK_J7200_BOARD_0_I3C0_SCL_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_I3C0_SCL_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_I3C0_SCL_OUT,
	},
	[CLK_J7200_BOARD_0_LED_CLK_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_LED_CLK_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_LED_CLK_OUT,
	},
	[CLK_J7200_BOARD_0_MCASP0_ACLKR_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_MCASP0_ACLKR_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_MCASP0_ACLKR_OUT,
	},
	[CLK_J7200_BOARD_0_MCASP0_ACLKX_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_MCASP0_ACLKX_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_MCASP0_ACLKX_OUT,
	},
	[CLK_J7200_BOARD_0_MCASP1_ACLKR_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_MCASP1_ACLKR_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_MCASP1_ACLKR_OUT,
	},
	[CLK_J7200_BOARD_0_MCASP1_ACLKX_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_MCASP1_ACLKX_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_MCASP1_ACLKX_OUT,
	},
	[CLK_J7200_BOARD_0_MCASP2_ACLKR_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_MCASP2_ACLKR_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_MCASP2_ACLKR_OUT,
	},
	[CLK_J7200_BOARD_0_MCASP2_ACLKX_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_MCASP2_ACLKX_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_MCASP2_ACLKX_OUT,
	},
	[CLK_J7200_BOARD_0_MCU_CPTS0_RFT_CLK_OUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_MCU_CPTS0_RFT_CLK_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_MCU_CPTS0_RFT_CLK_OUT,
	},
	[CLK_J7200_BOARD_0_MCU_EXT_REFCLK0_OUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_MCU_EXT_REFCLK0_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_MCU_EXT_REFCLK0_OUT,
	},
	[CLK_J7200_BOARD_0_MCU_I2C0_SCL_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_MCU_I2C0_SCL_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_MCU_I2C0_SCL_OUT,
	},
	[CLK_J7200_BOARD_0_MCU_I2C1_SCL_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_MCU_I2C1_SCL_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_MCU_I2C1_SCL_OUT,
	},
	[CLK_J7200_BOARD_0_MCU_I3C0_SCL_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_MCU_I3C0_SCL_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_MCU_I3C0_SCL_OUT,
	},
	[CLK_J7200_BOARD_0_MCU_OSPI0_DQS_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_MCU_OSPI0_DQS_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_MCU_OSPI0_DQS_OUT,
	},
	[CLK_J7200_BOARD_0_MCU_RGMII1_RXC_OUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_MCU_RGMII1_RXC_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_MCU_RGMII1_RXC_OUT,
	},
	[CLK_J7200_BOARD_0_MCU_RMII1_REF_CLK_OUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_MCU_RMII1_REF_CLK_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_MCU_RMII1_REF_CLK_OUT,
	},
	[CLK_J7200_BOARD_0_RGMII1_RXC_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_RGMII1_RXC_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_RGMII1_RXC_OUT,
	},
	[CLK_J7200_BOARD_0_RGMII2_RXC_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_RGMII2_RXC_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_RGMII2_RXC_OUT,
	},
	[CLK_J7200_BOARD_0_RGMII3_RXC_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_RGMII3_RXC_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_RGMII3_RXC_OUT,
	},
	[CLK_J7200_BOARD_0_RGMII4_RXC_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_RGMII4_RXC_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_RGMII4_RXC_OUT,
	},
	[CLK_J7200_BOARD_0_RMII_REF_CLK_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_RMII_REF_CLK_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_RMII_REF_CLK_OUT,
	},
	[CLK_J7200_BOARD_0_TCK_OUT] =					{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_TCK_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_TCK_OUT,
	},
	[CLK_J7200_BOARD_0_WKUP_I2C0_SCL_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_WKUP_I2C0_SCL_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_WKUP_I2C0_SCL_OUT,
	},
	[CLK_J7200_BOARD_0_WKUP_LF_CLKIN_OUT] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_board_0_WKUP_LF_CLKIN_out.data,
		.freq_idx	= J7200_FREQ_VALUE_BOARD_0_WKUP_LF_CLKIN_OUT,
	},
	[CLK_J7200_CPSW_2GUSS_MCU_0_CPTS_GENF0] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_cpsw_2guss_mcu_0_cpts_genf0.data,
		.freq_idx	= J7200_FREQ_VALUE_CPSW_2GUSS_MCU_0_CPTS_GENF0,
	},
	[CLK_J7200_CPSW_2GUSS_MCU_0_MDIO_MDCLK_O] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_cpsw_2guss_mcu_0_mdio_mdclk_o.data,
		.freq_idx	= J7200_FREQ_VALUE_CPSW_2GUSS_MCU_0_MDIO_MDCLK_O,
	},
	[CLK_J7200_CPSW_2GUSS_MCU_0_RGMII1_TXC_O] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_cpsw_2guss_mcu_0_rgmii1_txc_o.data,
		.freq_idx	= J7200_FREQ_VALUE_CPSW_2GUSS_MCU_0_RGMII1_TXC_O,
	},
	[CLK_J7200_CPSW_5XUSS_MAIN_0_MDIO_MDCLK_O] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_cpsw_5xuss_main_0_mdio_mdclk_o.data,
		.freq_idx	= J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_MDIO_MDCLK_O,
	},
	[CLK_J7200_DEBUGSS_K3_WRAP_CV0_MAIN_0_CSTPIU_TRACECLK] =	{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_debugss_k3_wrap_cv0_main_0_cstpiu_traceclk.data,
		.freq_idx	= J7200_FREQ_VALUE_DEBUGSS_K3_WRAP_CV0_MAIN_0_CSTPIU_TRACECLK,
	},
	[CLK_J7200_DMTIMER_DMC1MS_MCU_0_TIMER_PWM] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_dmtimer_dmc1ms_mcu_0_timer_pwm.data,
		.freq_idx	= J7200_FREQ_VALUE_DMTIMER_DMC1MS_MCU_0_TIMER_PWM,
	},
	[CLK_J7200_DMTIMER_DMC1MS_MCU_2_TIMER_PWM] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_dmtimer_dmc1ms_mcu_2_timer_pwm.data,
		.freq_idx	= J7200_FREQ_VALUE_DMTIMER_DMC1MS_MCU_2_TIMER_PWM,
	},
	[CLK_J7200_DMTIMER_DMC1MS_MCU_4_TIMER_PWM] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_dmtimer_dmc1ms_mcu_4_timer_pwm.data,
		.freq_idx	= J7200_FREQ_VALUE_DMTIMER_DMC1MS_MCU_4_TIMER_PWM,
	},
	[CLK_J7200_DMTIMER_DMC1MS_MCU_6_TIMER_PWM] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_dmtimer_dmc1ms_mcu_6_timer_pwm.data,
		.freq_idx	= J7200_FREQ_VALUE_DMTIMER_DMC1MS_MCU_6_TIMER_PWM,
	},
	[CLK_J7200_DMTIMER_DMC1MS_MCU_8_TIMER_PWM] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_dmtimer_dmc1ms_mcu_8_timer_pwm.data,
		.freq_idx	= J7200_FREQ_VALUE_DMTIMER_DMC1MS_MCU_8_TIMER_PWM,
	},
	[CLK_J7200_EMMCSD4SS_MAIN_0_EMMCSDSS_IO_CLK_O] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_emmcsd4ss_main_0_emmcsdss_io_clk_o.data,
		.freq_idx	= J7200_FREQ_VALUE_EMMCSD4SS_MAIN_0_EMMCSDSS_IO_CLK_O,
	},
	[CLK_J7200_FSS_MCU_0_HYPERBUS1P0_0_HPB_OUT_CLK_N] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_fss_mcu_0_hyperbus1p0_0_hpb_out_clk_n.data,
		.freq_idx	= J7200_FREQ_VALUE_FSS_MCU_0_HYPERBUS1P0_0_HPB_OUT_CLK_N,
	},
	[CLK_J7200_FSS_MCU_0_HYPERBUS1P0_0_HPB_OUT_CLK_P] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_fss_mcu_0_hyperbus1p0_0_hpb_out_clk_p.data,
		.freq_idx	= J7200_FREQ_VALUE_FSS_MCU_0_HYPERBUS1P0_0_HPB_OUT_CLK_P,
	},
	[CLK_J7200_FSS_MCU_0_OSPI_0_OSPI_OCLK_CLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_fss_mcu_0_ospi_0_ospi_oclk_clk.data,
		.freq_idx	= J7200_FREQ_VALUE_FSS_MCU_0_OSPI_0_OSPI_OCLK_CLK,
	},
	[CLK_J7200_GPMC_MAIN_0_PO_GPMC_DEV_CLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_gpmc_main_0_po_gpmc_dev_clk.data,
		.freq_idx	= J7200_FREQ_VALUE_GPMC_MAIN_0_PO_GPMC_DEV_CLK,
	},
	[CLK_J7200_HSDIV1_16FFT_MCU_0_HSDIVOUT1_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MCU_0_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv1_16fft_mcu_0_hsdiv1.data_div.data,
	},
	[CLK_J7200_I3C_MAIN_0_I3C_SCL_DO] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_i3c_main_0_i3c_scl_do.data,
		.freq_idx	= J7200_FREQ_VALUE_I3C_MAIN_0_I3C_SCL_DO,
	},
	[CLK_J7200_I3C_MCU_0_I3C_SCL_DO] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_i3c_mcu_0_i3c_scl_do.data,
		.freq_idx	= J7200_FREQ_VALUE_I3C_MCU_0_I3C_SCL_DO,
	},
	[CLK_J7200_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_32K_CLK] =	{
		.drv		= &clk_drv_fixed,
		.flags		= 0,
		.range_idx	= J7200_FREQ_RANGE_J7VC_WAKEUP_16FF_WKUP_0_WKUP_RCOSC_32K_CLK,
	},
	[CLK_J7200_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII1_TXC__A] = {
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_j7vcl_cpsw_tx_rgmii_wrap_main_0_io__rgmii1_txc__a.data,
		.freq_idx	= J7200_FREQ_VALUE_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII1_TXC__A,
	},
	[CLK_J7200_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII2_TXC__A] = {
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_j7vcl_cpsw_tx_rgmii_wrap_main_0_io__rgmii2_txc__a.data,
		.freq_idx	= J7200_FREQ_VALUE_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII2_TXC__A,
	},
	[CLK_J7200_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII3_TXC__A] = {
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_j7vcl_cpsw_tx_rgmii_wrap_main_0_io__rgmii3_txc__a.data,
		.freq_idx	= J7200_FREQ_VALUE_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII3_TXC__A,
	},
	[CLK_J7200_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII4_TXC__A] = {
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_j7vcl_cpsw_tx_rgmii_wrap_main_0_io__rgmii4_txc__a.data,
		.freq_idx	= J7200_FREQ_VALUE_J7VCL_CPSW_TX_RGMII_WRAP_MAIN_0_IO__RGMII4_TXC__A,
	},
	[CLK_J7200_MCASP_MAIN_0_MCASP_ACLKR_POUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_mcasp_main_0_mcasp_aclkr_pout.data,
		.freq_idx	= J7200_FREQ_VALUE_MCASP_MAIN_0_MCASP_ACLKR_POUT,
	},
	[CLK_J7200_MCASP_MAIN_0_MCASP_ACLKX_POUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_mcasp_main_0_mcasp_aclkx_pout.data,
		.freq_idx	= J7200_FREQ_VALUE_MCASP_MAIN_0_MCASP_ACLKX_POUT,
	},
	[CLK_J7200_MCASP_MAIN_0_MCASP_AHCLKR_POUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_mcasp_main_0_mcasp_ahclkr_pout.data,
		.freq_idx	= J7200_FREQ_VALUE_MCASP_MAIN_0_MCASP_AHCLKR_POUT,
	},
	[CLK_J7200_MCASP_MAIN_0_MCASP_AHCLKX_POUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_mcasp_main_0_mcasp_ahclkx_pout.data,
		.freq_idx	= J7200_FREQ_VALUE_MCASP_MAIN_0_MCASP_AHCLKX_POUT,
	},
	[CLK_J7200_MCASP_MAIN_1_MCASP_ACLKR_POUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_mcasp_main_1_mcasp_aclkr_pout.data,
		.freq_idx	= J7200_FREQ_VALUE_MCASP_MAIN_1_MCASP_ACLKR_POUT,
	},
	[CLK_J7200_MCASP_MAIN_1_MCASP_ACLKX_POUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_mcasp_main_1_mcasp_aclkx_pout.data,
		.freq_idx	= J7200_FREQ_VALUE_MCASP_MAIN_1_MCASP_ACLKX_POUT,
	},
	[CLK_J7200_MCASP_MAIN_1_MCASP_AHCLKR_POUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_mcasp_main_1_mcasp_ahclkr_pout.data,
		.freq_idx	= J7200_FREQ_VALUE_MCASP_MAIN_1_MCASP_AHCLKR_POUT,
	},
	[CLK_J7200_MCASP_MAIN_1_MCASP_AHCLKX_POUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_mcasp_main_1_mcasp_ahclkx_pout.data,
		.freq_idx	= J7200_FREQ_VALUE_MCASP_MAIN_1_MCASP_AHCLKX_POUT,
	},
	[CLK_J7200_MCASP_MAIN_2_MCASP_ACLKR_POUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_mcasp_main_2_mcasp_aclkr_pout.data,
		.freq_idx	= J7200_FREQ_VALUE_MCASP_MAIN_2_MCASP_ACLKR_POUT,
	},
	[CLK_J7200_MCASP_MAIN_2_MCASP_ACLKX_POUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_mcasp_main_2_mcasp_aclkx_pout.data,
		.freq_idx	= J7200_FREQ_VALUE_MCASP_MAIN_2_MCASP_ACLKX_POUT,
	},
	[CLK_J7200_MCASP_MAIN_2_MCASP_AHCLKR_POUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_mcasp_main_2_mcasp_ahclkr_pout.data,
		.freq_idx	= J7200_FREQ_VALUE_MCASP_MAIN_2_MCASP_AHCLKR_POUT,
	},
	[CLK_J7200_MCASP_MAIN_2_MCASP_AHCLKX_POUT] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_mcasp_main_2_mcasp_ahclkx_pout.data,
		.freq_idx	= J7200_FREQ_VALUE_MCASP_MAIN_2_MCASP_AHCLKX_POUT,
	},
	[CLK_J7200_MCU_OSPI0_ICLK_SEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_mcu_OSPI0_iclk_sel_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_WWD_CLKSEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_mcu_WWD_clksel_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_WWD_CLKSEL_OUT1] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_mcu_WWD_clksel_out1.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MSHSI2C_WKUP_0_PORSCL] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_mshsi2c_wkup_0_porscl.data,
		.freq_idx	= J7200_FREQ_VALUE_MSHSI2C_WKUP_0_PORSCL,
	},
	[CLK_J7200_NAVSS256VCL_MAIN_0_CPTS0_GENF3] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_navss256vcl_main_0_cpts0_genf3.data,
		.freq_idx	= J7200_FREQ_VALUE_NAVSS256VCL_MAIN_0_CPTS0_GENF3,
	},
	[CLK_J7200_PLLFRACF_SSMOD_16FFT_MCU_1_FOUTVCOP_CLK] =		{
		.parent		=					{
			CLK_J7200_WKUP_FREF_CLKSEL_OUT0,
			1,
		},
		.drv		= &clk_drv_pll_16fft,
		.freq_idx	= J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MCU_1,
		.data		= &clk_data_pllfracf_ssmod_16fft_mcu_1.data_pll.data,
	},
	[CLK_J7200_PLLFRACF_SSMOD_16FFT_MCU_2_FOUTVCOP_CLK] =		{
		.parent		=					{
			CLK_J7200_WKUP_FREF_CLKSEL_OUT0,
			1,
		},
		.drv		= &clk_drv_pll_16fft,
		.freq_idx	= J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MCU_2,
		.data		= &clk_data_pllfracf_ssmod_16fft_mcu_2.data_pll.data,
	},
	[CLK_J7200_SPI_MAIN_0_IO_CLKSPIO_CLK] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_spi_main_0_io_clkspio_clk.data,
		.freq_idx	= J7200_FREQ_VALUE_SPI_MAIN_0_IO_CLKSPIO_CLK,
	},
	[CLK_J7200_SPI_MAIN_1_IO_CLKSPIO_CLK] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_spi_main_1_io_clkspio_clk.data,
		.freq_idx	= J7200_FREQ_VALUE_SPI_MAIN_1_IO_CLKSPIO_CLK,
	},
	[CLK_J7200_SPI_MAIN_2_IO_CLKSPIO_CLK] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_spi_main_2_io_clkspio_clk.data,
		.freq_idx	= J7200_FREQ_VALUE_SPI_MAIN_2_IO_CLKSPIO_CLK,
	},
	[CLK_J7200_SPI_MAIN_3_IO_CLKSPIO_CLK] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_spi_main_3_io_clkspio_clk.data,
		.freq_idx	= J7200_FREQ_VALUE_SPI_MAIN_3_IO_CLKSPIO_CLK,
	},
	[CLK_J7200_SPI_MAIN_5_IO_CLKSPIO_CLK] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_spi_main_5_io_clkspio_clk.data,
		.freq_idx	= J7200_FREQ_VALUE_SPI_MAIN_5_IO_CLKSPIO_CLK,
	},
	[CLK_J7200_SPI_MAIN_6_IO_CLKSPIO_CLK] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_spi_main_6_io_clkspio_clk.data,
		.freq_idx	= J7200_FREQ_VALUE_SPI_MAIN_6_IO_CLKSPIO_CLK,
	},
	[CLK_J7200_SPI_MAIN_7_IO_CLKSPIO_CLK] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_spi_main_7_io_clkspio_clk.data,
		.freq_idx	= J7200_FREQ_VALUE_SPI_MAIN_7_IO_CLKSPIO_CLK,
	},
	[CLK_J7200_SPI_MCU_0_IO_CLKSPIO_CLK] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_spi_mcu_0_io_clkspio_clk.data,
		.freq_idx	= J7200_FREQ_VALUE_SPI_MCU_0_IO_CLKSPIO_CLK,
	},
	[CLK_J7200_SPI_MCU_1_IO_CLKSPIO_CLK] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_spi_mcu_1_io_clkspio_clk.data,
		.freq_idx	= J7200_FREQ_VALUE_SPI_MCU_1_IO_CLKSPIO_CLK,
	},
	[CLK_J7200_SPI_MCU_2_IO_CLKSPIO_CLK] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_spi_mcu_2_io_clkspio_clk.data,
		.freq_idx	= J7200_FREQ_VALUE_SPI_MCU_2_IO_CLKSPIO_CLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN0_TXMCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln0_txmclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN0_TXMCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN1_TXMCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln1_txmclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN1_TXMCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN2_TXMCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln2_txmclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN2_TXMCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN3_TXMCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln3_txmclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN3_TXMCLK,
	},
	[CLK_J7200_WKUP_GPIO0_CLKSEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_wkup_gpio0_clksel_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_PLL_HFOSC_SEL_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT1] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_PLL_HFOSC_SEL_out1.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT12] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_PLL_HFOSC_SEL_out12.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT14] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_PLL_HFOSC_SEL_out14.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT2] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_PLL_HFOSC_SEL_out2.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT3] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_PLL_HFOSC_SEL_out3.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT4] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_PLL_HFOSC_SEL_out4.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT8] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_PLL_HFOSC_SEL_out8.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_SPI1_CLK_MUX_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_SPI1_CLK_MUX_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT0_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MCU_1_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_mcu_1_hsdiv0.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT1_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MCU_1_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_mcu_1_hsdiv1.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT2_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MCU_1_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_mcu_1_hsdiv2.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT3_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MCU_1_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_mcu_1_hsdiv3.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MCU_1_HSDIVOUT4_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MCU_1_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_mcu_1_hsdiv4.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT0_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MCU_2_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_mcu_2_hsdiv0.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT1_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MCU_2_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_mcu_2_hsdiv1.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT2_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MCU_2_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_mcu_2_hsdiv2.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT3_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MCU_2_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_mcu_2_hsdiv3.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MCU_2_HSDIVOUT4_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MCU_2_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_mcu_2_hsdiv4.data_div.data,
	},
	[CLK_J7200_MCU_MCAN_CLK_SEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_mcu_mcan_clk_sel_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_MCAN_CLK_SEL_OUT1] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_mcu_mcan_clk_sel_out1.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_0_FOUTVCOP_CLK] =		{
		.parent		=					{
			CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT0,
			1,
		},
		.drv		= &clk_drv_pll_16fft,
		.freq_idx	= J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MAIN_0,
		.data		= &clk_data_pllfracf_ssmod_16fft_main_0.data_pll.data,
	},
	[CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_0_FOUTPOSTDIV_CLK] =	{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_0_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_postdiv.drv,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_pllfracf_ssmod_16fft_main_0_postdiv.data,
	},
	[CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_1_FOUTVCOP_CLK] =		{
		.parent		=					{
			CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT1,
			1,
		},
		.drv		= &clk_drv_pll_16fft,
		.freq_idx	= J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MAIN_1,
		.data		= &clk_data_pllfracf_ssmod_16fft_main_1.data_pll.data,
	},
	[CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_1_FOUTPOSTDIV_CLK] =	{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_1_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_postdiv.drv,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_pllfracf_ssmod_16fft_main_1_postdiv.data,
	},
	[CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_12_FOUTVCOP_CLK] =		{
		.parent		=					{
			CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT12,
			1,
		},
		.drv		= &clk_drv_pll_16fft,
		.freq_idx	= J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MAIN_12,
		.data		= &clk_data_pllfracf_ssmod_16fft_main_12.data_pll.data,
	},
	[CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_14_FOUTVCOP_CLK] =		{
		.parent		=					{
			CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT14,
			1,
		},
		.drv		= &clk_drv_pll_16fft,
		.freq_idx	= J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MAIN_14,
		.data		= &clk_data_pllfracf_ssmod_16fft_main_14.data_pll.data,
	},
	[CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_2_FOUTVCOP_CLK] =		{
		.parent		=					{
			CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT2,
			1,
		},
		.drv		= &clk_drv_pll_16fft,
		.freq_idx	= J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MAIN_2,
		.data		= &clk_data_pllfracf_ssmod_16fft_main_2.data_pll.data,
	},
	[CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_3_FOUTVCOP_CLK] =		{
		.parent		=					{
			CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT3,
			1,
		},
		.drv		= &clk_drv_pll_16fft,
		.freq_idx	= J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MAIN_3,
		.data		= &clk_data_pllfracf_ssmod_16fft_main_3.data_pll.data,
	},
	[CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_8_FOUTVCOP_CLK] =		{
		.parent		=					{
			CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT8,
			1,
		},
		.drv		= &clk_drv_pll_16fft,
		.freq_idx	= J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MAIN_8,
		.data		= &clk_data_pllfracf_ssmod_16fft_main_8.data_pll.data,
	},
	[CLK_J7200_POSTDIV2_16FFT_MAIN_0_HSDIVOUT6_CLK] =		{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_0_FOUTPOSTDIV_CLK,
			1,
		},
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_postdiv2_16fft_main_0_hsdiv6.data_div.data,
	},
	[CLK_J7200_POSTDIV2_16FFT_MAIN_1_HSDIVOUT5_CLK] =		{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_1_FOUTPOSTDIV_CLK,
			1,
		},
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_postdiv2_16fft_main_1_hsdiv5.data_div.data,
	},
	[CLK_J7200_WKUP_I2C0_MCUPLL_BYPASS_CLKSEL_OUT0] =		{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_wkup_i2c0_mcupll_bypass_clksel_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_WKUPUSART_CLK_SEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_wkupusart_clk_sel_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_PLL4_XREF_SEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_PLL4_XREF_SEL_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_ADC_CLK_SEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_ADC_clk_sel_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_ADC_CLK_SEL_OUT1] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_ADC_clk_sel_out1.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_CLKOUT_MUX_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_CLKOUT_MUX_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_TIMER_CLKSEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_TIMER_CLKSEL_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_TIMER_CLKSEL_OUT1] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_TIMER_CLKSEL_out1.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_TIMER_CLKSEL_OUT2] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_TIMER_CLKSEL_out2.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_TIMER_CLKSEL_OUT3] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_TIMER_CLKSEL_out3.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_TIMER_CLKSEL_OUT4] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_TIMER_CLKSEL_out4.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_TIMER_CLKSEL_OUT5] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_TIMER_CLKSEL_out5.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_TIMER_CLKSEL_OUT6] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_TIMER_CLKSEL_out6.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_TIMER_CLKSEL_OUT7] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_TIMER_CLKSEL_out7.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_TIMER_CLKSEL_OUT8] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_TIMER_CLKSEL_out8.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_TIMER_CLKSEL_OUT9] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_TIMER_CLKSEL_out9.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_HSDIV0_16FFT_MAIN_12_HSDIVOUT0_CLK] =		{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_12_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= CLK_DATA_FLAG_MODIFY_PARENT_FREQ,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv0_16fft_main_12_hsdiv0.data_div.data,
	},
	[CLK_J7200_HSDIV0_16FFT_MAIN_8_HSDIVOUT0_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_8_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= CLK_DATA_FLAG_MODIFY_PARENT_FREQ,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv0_16fft_main_8_hsdiv0.data_div.data,
	},
	[CLK_J7200_HSDIV1_16FFT_MAIN_14_HSDIVOUT0_CLK] =		{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_14_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= CLK_DATA_FLAG_MODIFY_PARENT_FREQ,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv1_16fft_main_14_hsdiv0.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_0_HSDIVOUT0_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_0_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_0_hsdiv0.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_0_HSDIVOUT3_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_0_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_0_hsdiv3.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_1_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_1_hsdiv0.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_2_HSDIVOUT0_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_2_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_2_hsdiv0.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_2_HSDIVOUT1_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_2_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_2_hsdiv1.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT0_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_3_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_3_hsdiv0.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT1_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_3_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_3_hsdiv1.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT4_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_3_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_3_hsdiv4.data_div.data,
	},
	[CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_SYSCLKOUT_CLK] =		{
		.drv	= &clk_drv_pllctrl_mux_reg_ro.drv,
		.flags	= 0,
		.data	= &clk_data_k3_pll_ctrl_wrap_main_0_sysclkout_clk.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK] =		{
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.data	= &clk_data_k3_pll_ctrl_wrap_main_0_chip_div1_clk_clk.data_div.data,
		.parent =						{
			CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_SYSCLKOUT_CLK,
			1,
		},
	},
	[CLK_J7200_MCU_OSPI_REF_CLK_SEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_mcu_OSPI_ref_clk_sel_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_OSPI_REF_CLK_SEL_OUT1] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_mcu_OSPI_ref_clk_sel_out1.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCUUSART_CLK_SEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_mcuusart_clk_sel_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_4_FOUTVCOP_CLK] =		{
		.parent		=					{
			CLK_J7200_MAIN_PLL4_XREF_SEL_OUT0,
			1,
		},
		.drv		= &clk_drv_pll_16fft,
		.freq_idx	= J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MAIN_4,
		.data		= &clk_data_pllfracf_ssmod_16fft_main_4.data_pll.data,
	},
	[CLK_J7200_WKUP_OBSCLK_MUX_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= CLK_DATA_FLAG_ALLOW_FREQ_CHANGE,
		.data	= &clk_data_wkup_obsclk_mux_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_WKUP_USART_MCUPLL_BYPASS_CLKSEL_OUT0] =		{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_wkup_usart_mcupll_bypass_clksel_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_CLKOUT_MUX_OUT0] =					{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_CLKOUT_MUX_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_CPSW2G_CPTS_RCLK_MUX_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_CPSW2G_CPTS_RCLK_MUX_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_TIMER1_CASCADE_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_TIMER1_CASCADE_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_TIMER3_CASCADE_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_TIMER3_CASCADE_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_TIMER5_CASCADE_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_TIMER5_CASCADE_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_TIMER7_CASCADE_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_TIMER7_CASCADE_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCU_TIMER9_CASCADE_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCU_TIMER9_CASCADE_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_OBSCLK1_MUX_OUT0] =					{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_OBSCLK1_MUX_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_GPMC_FCLK_SEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_gpmc_fclk_sel_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_HSDIV2_16FFT_MAIN_4_HSDIVOUT0_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_4_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv2_16fft_main_4_hsdiv0.data_div.data,
	},
	[CLK_J7200_HSDIV2_16FFT_MAIN_4_HSDIVOUT2_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_4_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv2_16fft_main_4_hsdiv2.data_div.data,
	},
	[CLK_J7200_MCU_OBSCLK_DIV_OUT0] =				{
		.parent =						{
			CLK_J7200_WKUP_OBSCLK_MUX_OUT0,
			1,
		},
		.drv	= &clk_drv_div_reg.drv,
		.flags	= CLK_DATA_FLAG_ALLOW_FREQ_CHANGE,
		.data	= &clk_data_mcu_obsclk_div_out0.data_div.data,
		.type	= CLK_TYPE_DIV,
	},
	[CLK_J7200_MCU_OBSCLK_OUTMUX_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= CLK_DATA_FLAG_ALLOW_FREQ_CHANGE,
		.data	= &clk_data_mcu_obsclk_outmux_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_AUDIO_REFCLKO_MUX_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_AUDIO_REFCLKO_MUX_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_AUDIO_REFCLKO_MUX_OUT1] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_AUDIO_REFCLKO_MUX_out1.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_OBSCLK0_MUX_OUT0] =					{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_OBSCLK0_MUX_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_OSBCLK0_DIV_OUT0] =					{
		.parent =						{
			CLK_J7200_OBSCLK0_MUX_OUT0,
			1,
		},
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.data	= &clk_data_osbclk0_div_out0.data_div.data,
		.type	= CLK_TYPE_DIV,
	},
	[CLK_J7200_CPSW5X_CPTS_RFT_MUX_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_CPSW5X_CPTS_RFT_MUX_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_GTC_CLK_MUX_OUT0] =					{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_GTC_CLK_MUX_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT7] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_PLL_HFOSC_SEL_out7.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_WWDT_CLKSEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_WWDT_CLKSEL_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_WWDT_CLKSEL_OUT1] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_WWDT_CLKSEL_out1.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_WWDT_CLKSEL_OUT6] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_WWDT_CLKSEL_out6.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_WWDT_CLKSEL_OUT7] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_WWDT_CLKSEL_out7.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCASP_AHCLKR_MUX_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_McASP_AHCLKR_MUX_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCASP_AHCLKR_MUX_OUT1] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_McASP_AHCLKR_MUX_out1.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCASP_AHCLKR_MUX_OUT2] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_McASP_AHCLKR_MUX_out2.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCASP_AHCLKX_MUX_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_McASP_AHCLKX_MUX_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCASP_AHCLKX_MUX_OUT1] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_McASP_AHCLKX_MUX_out1.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCASP_AHCLKX_MUX_OUT2] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_McASP_AHCLKX_MUX_out2.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_NAVSS_CPTS_RCLK_MUX_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_NAVSS_CPTS_RCLK_MUX_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_PCIE1_CPTS_RCLK_MUX_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_PCIE1_CPTS_RCLK_MUX_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_SPI3_CLK_MUX_OUT0] =					{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_SPI3_CLK_MUX_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT0] =		{
		.parent =						{
			CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
			1,
		},
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.data	= &clk_data_USART_Programmable_Clock_Divider_out0.data_div.data,
		.type	= CLK_TYPE_DIV,
	},
	[CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT1] =		{
		.parent =						{
			CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
			1,
		},
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.data	= &clk_data_USART_Programmable_Clock_Divider_out1.data_div.data,
		.type	= CLK_TYPE_DIV,
	},
	[CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT2] =		{
		.parent =						{
			CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
			1,
		},
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.data	= &clk_data_USART_Programmable_Clock_Divider_out2.data_div.data,
		.type	= CLK_TYPE_DIV,
	},
	[CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT3] =		{
		.parent =						{
			CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
			1,
		},
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.data	= &clk_data_USART_Programmable_Clock_Divider_out3.data_div.data,
		.type	= CLK_TYPE_DIV,
	},
	[CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT4] =		{
		.parent =						{
			CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
			1,
		},
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.data	= &clk_data_USART_Programmable_Clock_Divider_out4.data_div.data,
		.type	= CLK_TYPE_DIV,
	},
	[CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT5] =		{
		.parent =						{
			CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
			1,
		},
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.data	= &clk_data_USART_Programmable_Clock_Divider_out5.data_div.data,
		.type	= CLK_TYPE_DIV,
	},
	[CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT6] =		{
		.parent =						{
			CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
			1,
		},
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.data	= &clk_data_USART_Programmable_Clock_Divider_out6.data_div.data,
		.type	= CLK_TYPE_DIV,
	},
	[CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT7] =		{
		.parent =						{
			CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
			1,
		},
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.data	= &clk_data_USART_Programmable_Clock_Divider_out7.data_div.data,
		.type	= CLK_TYPE_DIV,
	},
	[CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT8] =		{
		.parent =						{
			CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
			1,
		},
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.data	= &clk_data_USART_Programmable_Clock_Divider_out8.data_div.data,
		.type	= CLK_TYPE_DIV,
	},
	[CLK_J7200_USART_PROGRAMMABLE_CLOCK_DIVIDER_OUT9] =		{
		.parent =						{
			CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT0_CLK,
			1,
		},
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.data	= &clk_data_USART_Programmable_Clock_Divider_out9.data_div.data,
		.type	= CLK_TYPE_DIV,
	},
	[CLK_J7200_USB0_REFCLK_SEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_USB0_REFCLK_SEL_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_CPSW_5XUSS_MAIN_0_CPTS_GENF0] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_cpsw_5xuss_main_0_cpts_genf0.data,
		.freq_idx	= J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_CPTS_GENF0,
	},
	[CLK_J7200_CPSW_5XUSS_MAIN_0_PRE_RGMII1_TCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_cpsw_5xuss_main_0_pre_rgmii1_tclk.data,
		.freq_idx	= J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_PRE_RGMII1_TCLK,
	},
	[CLK_J7200_CPSW_5XUSS_MAIN_0_PRE_RGMII2_TCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_cpsw_5xuss_main_0_pre_rgmii2_tclk.data,
		.freq_idx	= J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_PRE_RGMII2_TCLK,
	},
	[CLK_J7200_CPSW_5XUSS_MAIN_0_PRE_RGMII3_TCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_cpsw_5xuss_main_0_pre_rgmii3_tclk.data,
		.freq_idx	= J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_PRE_RGMII3_TCLK,
	},
	[CLK_J7200_CPSW_5XUSS_MAIN_0_PRE_RGMII4_TCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_cpsw_5xuss_main_0_pre_rgmii4_tclk.data,
		.freq_idx	= J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_PRE_RGMII4_TCLK,
	},
	[CLK_J7200_CPSW_5XUSS_MAIN_0_SERDES1_TXCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_cpsw_5xuss_main_0_serdes1_txclk.data,
		.freq_idx	= J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_SERDES1_TXCLK,
	},
	[CLK_J7200_CPSW_5XUSS_MAIN_0_SERDES2_TXCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_cpsw_5xuss_main_0_serdes2_txclk.data,
		.freq_idx	= J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_SERDES2_TXCLK,
	},
	[CLK_J7200_CPSW_5XUSS_MAIN_0_SERDES3_TXCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_cpsw_5xuss_main_0_serdes3_txclk.data,
		.freq_idx	= J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_SERDES3_TXCLK,
	},
	[CLK_J7200_CPSW_5XUSS_MAIN_0_SERDES4_TXCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_cpsw_5xuss_main_0_serdes4_txclk.data,
		.freq_idx	= J7200_FREQ_VALUE_CPSW_5XUSS_MAIN_0_SERDES4_TXCLK,
	},
	[CLK_J7200_DMTIMER_DMC1MS_MAIN_0_TIMER_PWM] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_dmtimer_dmc1ms_main_0_timer_pwm.data,
		.freq_idx	= J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_0_TIMER_PWM,
	},
	[CLK_J7200_DMTIMER_DMC1MS_MAIN_10_TIMER_PWM] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_dmtimer_dmc1ms_main_10_timer_pwm.data,
		.freq_idx	= J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_10_TIMER_PWM,
	},
	[CLK_J7200_DMTIMER_DMC1MS_MAIN_12_TIMER_PWM] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_dmtimer_dmc1ms_main_12_timer_pwm.data,
		.freq_idx	= J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_12_TIMER_PWM,
	},
	[CLK_J7200_DMTIMER_DMC1MS_MAIN_14_TIMER_PWM] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_dmtimer_dmc1ms_main_14_timer_pwm.data,
		.freq_idx	= J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_14_TIMER_PWM,
	},
	[CLK_J7200_DMTIMER_DMC1MS_MAIN_16_TIMER_PWM] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_dmtimer_dmc1ms_main_16_timer_pwm.data,
		.freq_idx	= J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_16_TIMER_PWM,
	},
	[CLK_J7200_DMTIMER_DMC1MS_MAIN_18_TIMER_PWM] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_dmtimer_dmc1ms_main_18_timer_pwm.data,
		.freq_idx	= J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_18_TIMER_PWM,
	},
	[CLK_J7200_DMTIMER_DMC1MS_MAIN_2_TIMER_PWM] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_dmtimer_dmc1ms_main_2_timer_pwm.data,
		.freq_idx	= J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_2_TIMER_PWM,
	},
	[CLK_J7200_DMTIMER_DMC1MS_MAIN_4_TIMER_PWM] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_dmtimer_dmc1ms_main_4_timer_pwm.data,
		.freq_idx	= J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_4_TIMER_PWM,
	},
	[CLK_J7200_DMTIMER_DMC1MS_MAIN_6_TIMER_PWM] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_dmtimer_dmc1ms_main_6_timer_pwm.data,
		.freq_idx	= J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_6_TIMER_PWM,
	},
	[CLK_J7200_DMTIMER_DMC1MS_MAIN_8_TIMER_PWM] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_dmtimer_dmc1ms_main_8_timer_pwm.data,
		.freq_idx	= J7200_FREQ_VALUE_DMTIMER_DMC1MS_MAIN_8_TIMER_PWM,
	},
	[CLK_J7200_HSDIV2_16FFT_MAIN_4_HSDIVOUT1_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_4_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv2_16fft_main_4_hsdiv1.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_0_HSDIVOUT1_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_0_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_0_hsdiv1.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_0_HSDIVOUT2_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_0_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_0_hsdiv2.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_0_HSDIVOUT4_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_0_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_0_hsdiv4.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT1_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_1_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_1_hsdiv1.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT2_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_1_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_1_hsdiv2.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_1_HSDIVOUT3_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_1_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_1_hsdiv3.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_2_HSDIVOUT2_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_2_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_2_hsdiv2.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_2_HSDIVOUT3_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_2_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_2_hsdiv3.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_2_HSDIVOUT4_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_2_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_2_hsdiv4.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT2_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_3_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_3_hsdiv2.data_div.data,
	},
	[CLK_J7200_HSDIV4_16FFT_MAIN_3_HSDIVOUT3_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_3_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv4_16fft_main_3_hsdiv3.data_div.data,
	},
	[CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_CHIP_DIV24_CLK_CLK] =	{
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.data	= &clk_data_k3_pll_ctrl_wrap_wkup_0_chip_div24_clk_clk.data_div.data,
		.parent =						{
			CLK_J7200_K3_PLL_CTRL_WRAP_WKUP_0_SYSCLKOUT_CLK,
			1,
		},
	},
	[CLK_J7200_NAVSS256VCL_MAIN_0_CPTS0_GENF2] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_navss256vcl_main_0_cpts0_genf2.data,
		.freq_idx	= J7200_FREQ_VALUE_NAVSS256VCL_MAIN_0_CPTS0_GENF2,
	},
	[CLK_J7200_NAVSS256VCL_MAIN_0_CPTS0_GENF4] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_navss256vcl_main_0_cpts0_genf4.data,
		.freq_idx	= J7200_FREQ_VALUE_NAVSS256VCL_MAIN_0_CPTS0_GENF4,
	},
	[CLK_J7200_NAVSS256VCL_MAIN_0_CPTS_0_TS_GENF0] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_navss256vcl_main_0_cpts_0_ts_genf0.data,
		.freq_idx	= J7200_FREQ_VALUE_NAVSS256VCL_MAIN_0_CPTS_0_TS_GENF0,
	},
	[CLK_J7200_NAVSS256VCL_MAIN_0_CPTS_0_TS_GENF1] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_navss256vcl_main_0_cpts_0_ts_genf1.data,
		.freq_idx	= J7200_FREQ_VALUE_NAVSS256VCL_MAIN_0_CPTS_0_TS_GENF1,
	},
	[CLK_J7200_PCIE_G3X4_128_MAIN_1_PCIE_LANE0_TXCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_pcie_g3x4_128_main_1_pcie_lane0_txclk.data,
		.freq_idx	= J7200_FREQ_VALUE_PCIE_G3X4_128_MAIN_1_PCIE_LANE0_TXCLK,
	},
	[CLK_J7200_PCIE_G3X4_128_MAIN_1_PCIE_LANE1_TXCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_pcie_g3x4_128_main_1_pcie_lane1_txclk.data,
		.freq_idx	= J7200_FREQ_VALUE_PCIE_G3X4_128_MAIN_1_PCIE_LANE1_TXCLK,
	},
	[CLK_J7200_PCIE_G3X4_128_MAIN_1_PCIE_LANE2_TXCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_pcie_g3x4_128_main_1_pcie_lane2_txclk.data,
		.freq_idx	= J7200_FREQ_VALUE_PCIE_G3X4_128_MAIN_1_PCIE_LANE2_TXCLK,
	},
	[CLK_J7200_PCIE_G3X4_128_MAIN_1_PCIE_LANE3_TXCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_pcie_g3x4_128_main_1_pcie_lane3_txclk.data,
		.freq_idx	= J7200_FREQ_VALUE_PCIE_G3X4_128_MAIN_1_PCIE_LANE3_TXCLK,
	},
	[CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_2_FOUTPOSTDIV_CLK] =	{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_2_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_postdiv.drv,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_pllfracf_ssmod_16fft_main_2_postdiv.data,
	},
	[CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_7_FOUTVCOP_CLK] =		{
		.parent		=					{
			CLK_J7200_MAIN_PLL_HFOSC_SEL_OUT7,
			1,
		},
		.drv		= &clk_drv_pll_16fft,
		.freq_idx	= J7200_FREQ_VALUE_PLLFRACF_SSMOD_16FFT_MAIN_7,
		.data		= &clk_data_pllfracf_ssmod_16fft_main_7.data_pll.data,
	},
	[CLK_J7200_POSTDIV2_16FFT_MAIN_0_HSDIVOUT5_CLK] =		{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_0_FOUTPOSTDIV_CLK,
			1,
		},
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_postdiv2_16fft_main_0_hsdiv5.data_div.data,
	},
	[CLK_J7200_POSTDIV2_16FFT_MAIN_0_HSDIVOUT7_CLK] =		{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_0_FOUTPOSTDIV_CLK,
			1,
		},
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_postdiv2_16fft_main_0_hsdiv7.data_div.data,
	},
	[CLK_J7200_POSTDIV2_16FFT_MAIN_1_HSDIVOUT7_CLK] =		{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_1_FOUTPOSTDIV_CLK,
			1,
		},
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_postdiv2_16fft_main_1_hsdiv7.data_div.data,
	},
	[CLK_J7200_POSTDIV2_16FFT_MAIN_2_HSDIVOUT6_CLK] =		{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_2_FOUTPOSTDIV_CLK,
			1,
		},
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_postdiv2_16fft_main_2_hsdiv6.data_div.data,
	},
	[CLK_J7200_SPI_MAIN_4_IO_CLKSPIO_CLK] =				{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_spi_main_4_io_clkspio_clk.data,
		.freq_idx	= J7200_FREQ_VALUE_SPI_MAIN_4_IO_CLKSPIO_CLK,
	},
	[CLK_J7200_USB3P0SS_16FFC_MAIN_0_PIPE_TXCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_usb3p0ss_16ffc_main_0_pipe_txclk.data,
		.freq_idx	= J7200_FREQ_VALUE_USB3P0SS_16FFC_MAIN_0_PIPE_TXCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN0_REFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln0_refclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN0_REFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN0_RXCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln0_rxclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN0_RXCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN0_RXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln0_rxfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN0_RXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN0_TXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln0_txfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN0_TXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN0_TXMCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln0_txmclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN0_TXMCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN1_REFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln1_refclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN1_REFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN1_RXCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln1_rxclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN1_RXCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN1_RXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln1_rxfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN1_RXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN1_TXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln1_txfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN1_TXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN1_TXMCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln1_txmclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN1_TXMCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN2_REFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln2_refclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN2_REFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN2_RXCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln2_rxclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN2_RXCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN2_RXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln2_rxfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN2_RXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN2_TXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln2_txfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN2_TXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN2_TXMCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln2_txmclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN2_TXMCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN3_REFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln3_refclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN3_REFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN3_RXCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln3_rxclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN3_RXCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN3_RXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln3_rxfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN3_RXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN3_TXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln3_txfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN3_TXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP1_LN3_TXMCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip1_ln3_txmclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP1_LN3_TXMCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN0_REFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln0_refclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN0_REFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN0_RXCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln0_rxclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN0_RXCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN0_RXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln0_rxfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN0_RXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN0_TXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln0_txfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN0_TXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN1_REFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln1_refclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN1_REFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN1_RXCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln1_rxclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN1_RXCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN1_RXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln1_rxfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN1_RXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN1_TXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln1_txfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN1_TXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN2_REFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln2_refclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN2_REFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN2_RXCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln2_rxclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN2_RXCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN2_RXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln2_rxfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN2_RXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN2_TXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln2_txfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN2_TXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN3_REFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln3_refclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN3_REFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN3_RXCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln3_rxclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN3_RXCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN3_RXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln3_rxfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN3_RXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP2_LN3_TXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip2_ln3_txfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP2_LN3_TXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN1_REFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip3_ln1_refclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN1_REFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN1_RXCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip3_ln1_rxclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN1_RXCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN1_RXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip3_ln1_rxfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN1_RXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN1_TXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip3_ln1_txfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN1_TXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN1_TXMCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip3_ln1_txmclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN1_TXMCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN3_REFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip3_ln3_refclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN3_REFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN3_RXCLK] =			{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip3_ln3_rxclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN3_RXCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN3_RXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip3_ln3_rxfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN3_RXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN3_TXFCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip3_ln3_txfclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN3_TXFCLK,
	},
	[CLK_J7200_WIZ16B8M4CT2_MAIN_1_IP3_LN3_TXMCLK] =		{
		.drv		= &clk_drv_from_device,
		.flags		= 0,
		.data		= &clk_data_wiz16b8m4ct2_main_1_ip3_ln3_txmclk.data,
		.freq_idx	= J7200_FREQ_VALUE_WIZ16B8M4CT2_MAIN_1_IP3_LN3_TXMCLK,
	},
	[CLK_J7200_ATL_PCLKMUX_OUT0] =					{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_ATL_PCLKMUX_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_EMMCSD_REFCLK_SEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_EMMCSD_REFCLK_SEL_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_EMMCSD_REFCLK_SEL_OUT1] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_EMMCSD_REFCLK_SEL_out1.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT1] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out1.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT10] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out10.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT11] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out11.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT12] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out12.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT13] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out13.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT14] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out14.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT15] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out15.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT16] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out16.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT17] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out17.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT18] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out18.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT19] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out19.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT2] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out2.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT3] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out3.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT4] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out4.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT5] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out5.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT6] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out6.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT7] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out7.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT8] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out8.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MAIN_TIMER_CLKSEL_OUT9] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MAIN_TIMER_CLKSEL_out9.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCAN_CLK_MUX_OUT0] =					{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCAN_CLK_MUX_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCAN_CLK_MUX_OUT1] =					{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCAN_CLK_MUX_out1.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCAN_CLK_MUX_OUT10] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCAN_CLK_MUX_out10.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCAN_CLK_MUX_OUT11] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCAN_CLK_MUX_out11.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCAN_CLK_MUX_OUT12] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCAN_CLK_MUX_out12.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCAN_CLK_MUX_OUT13] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCAN_CLK_MUX_out13.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCAN_CLK_MUX_OUT14_0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCAN_CLK_MUX_out14_0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCAN_CLK_MUX_OUT15_0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCAN_CLK_MUX_out15_0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCAN_CLK_MUX_OUT16_0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCAN_CLK_MUX_out16_0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCAN_CLK_MUX_OUT17_0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCAN_CLK_MUX_out17_0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCAN_CLK_MUX_OUT2] =					{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCAN_CLK_MUX_out2.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCAN_CLK_MUX_OUT3] =					{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCAN_CLK_MUX_out3.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCAN_CLK_MUX_OUT4] =					{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCAN_CLK_MUX_out4.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCAN_CLK_MUX_OUT5] =					{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCAN_CLK_MUX_out5.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCAN_CLK_MUX_OUT6] =					{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCAN_CLK_MUX_out6.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCAN_CLK_MUX_OUT7] =					{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCAN_CLK_MUX_out7.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCAN_CLK_MUX_OUT8] =					{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCAN_CLK_MUX_out8.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCAN_CLK_MUX_OUT9] =					{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_MCAN_CLK_MUX_out9.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCASP_AUXCLK_SEL_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_McASP_AUXCLK_SEL_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCASP_AUXCLK_SEL_OUT1] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_McASP_AUXCLK_SEL_out1.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_MCASP_AUXCLK_SEL_OUT2] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_McASP_AUXCLK_SEL_out2.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_SERDES0_CORE_REFCLK_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_SERDES0_CORE_REFCLK_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_TIMER11_CASCADE_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_TIMER11_CASCADE_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_TIMER13_CASCADE_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_TIMER13_CASCADE_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_TIMER15_CASCADE_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_TIMER15_CASCADE_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_TIMER17_CASCADE_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_TIMER17_CASCADE_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_TIMER19_CASCADE_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_TIMER19_CASCADE_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_TIMER1_CASCADE_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_TIMER1_CASCADE_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_TIMER3_CASCADE_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_TIMER3_CASCADE_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_TIMER5_CASCADE_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_TIMER5_CASCADE_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_TIMER7_CASCADE_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_TIMER7_CASCADE_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_TIMER9_CASCADE_OUT0] =				{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_TIMER9_CASCADE_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_USB0_SERDES_REFCLK_MUX_OUT0] =			{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_USB0_SerDes_refclk_Mux_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_USB0_SERDES_RXCLK_MUX_OUT0] =			{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_USB0_SerDes_rxclk_Mux_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_USB0_SERDES_RXFCLK_MUX_OUT0] =			{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_USB0_SerDes_rxfclk_Mux_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_USB0_SERDES_TXFCLK_MUX_OUT0] =			{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_USB0_SerDes_txfclk_Mux_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_USB0_SERDES_TXMCLK_MUX_OUT0] =			{
		.drv	= &clk_drv_mux_reg.drv,
		.flags	= 0,
		.data	= &clk_data_USB0_SerDes_txmclk_Mux_out0.data_mux.data,
		.type	= CLK_TYPE_MUX,
	},
	[CLK_J7200_HSDIV0_16FFT_MAIN_7_HSDIVOUT0_CLK] =			{
		.parent =						{
			CLK_J7200_PLLFRACF_SSMOD_16FFT_MAIN_7_FOUTVCOP_CLK,
			1,
		},
		.drv	= &clk_drv_div_pll_16fft_hsdiv.drv,
		.flags	= CLK_DATA_FLAG_MODIFY_PARENT_FREQ,
		.type	= CLK_TYPE_DIV,
		.data	= &clk_data_hsdiv0_16fft_main_7_hsdiv0.data_div.data,
	},
	[CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV24_CLK_CLK] =	{
		.drv	= &clk_drv_div_reg.drv,
		.flags	= 0,
		.data	= &clk_data_k3_pll_ctrl_wrap_main_0_chip_div24_clk_clk.data_div.data,
		.parent =						{
			CLK_J7200_K3_PLL_CTRL_WRAP_MAIN_0_SYSCLKOUT_CLK,
			1,
		},
	},
};

struct clk soc_clocks[ARRAY_SIZE(soc_clock_data)];
const size_t soc_clock_count = ARRAY_SIZE(soc_clock_data);
