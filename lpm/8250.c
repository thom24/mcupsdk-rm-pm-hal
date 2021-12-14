/*
 * System Firmware
 *
 * Minimal driver for UART access
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

#include <config.h>

#include "lpm_io.h"
#include "serial_8250.h"

static u32 uart_base_addr;

static void serial_8250_writel(u32 v, u32 reg)
{
	writel(v, reg + uart_base_addr);
}

static u32 serial_8250_readl(u32 reg)
{
	return readl(reg + uart_base_addr);
}

void serial_8250_init(const struct uart_16550_config *cfg)
{
	u32 val, clkdiv;

	uart_base_addr = cfg->base_addr;

	clkdiv = cfg->uart_clk / (16 * cfg->baud_rate);

	/* This read operation also acts as a fence */
	val = serial_8250_readl(UART_16550_LCR);
	val |= UART_16550_LCR_DLAB;
	serial_8250_writel(val, UART_16550_LCR);

	val = clkdiv & 0xFF;
	serial_8250_writel(val, UART_16550_DLL);
	val = (clkdiv >> 8) & 0xFF;
	serial_8250_writel(val, UART_16550_DLH);

	/*
	 * This read operation also acts as a fence to make sure that
	 * DLL DLH values have actually been "stuck"
	 */
	val = serial_8250_readl(UART_16550_LCR);
	val &= (~UART_16550_LCR_DLAB);
	serial_8250_writel(val, UART_16550_LCR);
	serial_8250_writel(UART_16550_LCR_WORDSZ_8, UART_16550_LCR);
	serial_8250_writel(0, UART_16550_IER);
	/*
	 * Force a posted read to make sure things are in-order before we
	 * enable UART via MDR1 - we ignore result
	 */
	serial_8250_readl(UART_16550_IER);

	serial_8250_writel(0x0, UART_16550_MDR1);
	/*
	 * Force a posted read to make sure things are in-order before we
	 * enable FIFO - we ignore result
	 */
	serial_8250_readl(UART_16550_MDR1);

	serial_8250_writel(UART_16550_FCR_FIFOEN, UART_16550_FCR);
	serial_8250_writel((UART_16550_MCR_RTS | UART_16550_MCR_DTR), UART_16550_MCR);
	/*
	 * Force a posted read to make sure FIFO is enabled before we send
	 * data - we ignore result
	 */
	serial_8250_readl(UART_16550_MCR);
}

int lpm_console_tx(int data)
{
	u32 val;
	int i = 0;

	/*
	 * Add a carriage return before newline to support
	 * unflexible terminals.
	 */
	if (data == '\n') {
		lpm_console_tx('\r');
	}

	/*
	* Poll the Line Status Register to ensure FIFO space is
	* available before writing to avoid dropping chars.
	*/
	do {
		val = serial_8250_readl(UART_16550_LSR);
	} while ((i++ < 10000) && ((val & UART_16550_LSR_TX_FIFO_E) == 0));

	serial_8250_writel(data, UART_16550_THR);

	return 0;
}

int lpm_puts(const char *str)
{
	const char *start = str;

	while (*str) {
		lpm_console_tx(*str++);
	}
	return str - start;
}
