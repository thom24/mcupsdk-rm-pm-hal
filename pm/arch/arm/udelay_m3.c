/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <delay.h>
#include <clk.h>
#include <lib/ioremap.h>
#include <lib/io.h>
#include <div64.h>
#include <device.h>
#include <resource.h>
#include <device_clk.h>
#include <arch/regs_cm3.h>

#define SYS_STCSR_COUNTFLAG     BIT(16)
#define SYS_STCSR_CLKSOURCE     BIT(2)
#define SYS_STCSR_TICKINT       BIT(1)
#define SYS_STCSR_ENABLE        BIT(0)

void udelay(u32 us)
{
	static unsigned long pmmc_ref_freq_hz;
	unsigned long long cycles;
	unsigned long v;
	unsigned long long freq;

	if (!us) {
		return;
	}

	if (!pmmc_ref_freq_hz) {
		const struct resource_clk *clk;

		clk = device_resource_clk(this_dev, 0);
		if (clk) {
			pmmc_ref_freq_hz = device_clk_get_freq(this_dev,
							       clk->clk_id);
		}
	}

	freq = pmmc_ref_freq_hz ? : 0;
	if (!freq) {
		/* Max possible is 50MHz */
		freq = FREQ_MHZ(50.0);
	}

	/* Calculate number of cycles required, rounding up */
	cycles = div64(freq * us + 999999ULL, 1000000);

	/* Use external clock source */
	v = readl(SYS_STCSR);
	v &= ~SYS_STCSR_CLKSOURCE;

	/* Don't generate an interrupt */
	v &= ~SYS_STCSR_TICKINT;

	/* Make sure counter is disabled */
	v &= ~SYS_STCSR_ENABLE;
	writel(v, SYS_STCSR);

	while (cycles) {
		/* Write number of clock cycles to count */
		if (cycles > 0x00ffffff) {
			v = 0x00ffffff;
		} else {
			v = cycles;
		}
		cycles -= v;
		writel(v, SYS_STRVR);

		/* Extra read to ensure COUNTFLAG clears */
		v = readl(SYS_STCSR);

		/* Start counting */
		v |= SYS_STCSR_ENABLE;
		writel(v, SYS_STCSR);

		/* Wait for timer to finish counting down */
		while (!(readl(SYS_STCSR) & SYS_STCSR_COUNTFLAG)) {
		}

		/* Disable counter */
		v &= ~SYS_STCSR_ENABLE;
		writel(v, SYS_STCSR);
	}
}
