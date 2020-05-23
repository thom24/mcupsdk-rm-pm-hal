/*
 * IRQ Interrupt Router
 *
 * IRQ Interrupt Router initialization data structure
 *
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef IR_INIT_H
#define IR_INIT_H

#include <ir_pe_conf.h>

#include <types/short_types.h>

/**
 * \brief Initialization of Interrupt aggregator
 *
 * \param id
 * Device ID for Interrupt agregator
 *
 * \param inp
 * Input virtual IRQ
 *
 * \param outp
 * Output IRQ to map to
 */
struct ir_init {
	const u16	id;
	const u16	inp;
	const u16	outp;
};

extern const struct ir_init ir_soc_pe_init_list[IR_SOC_PE_INIT_NUM];

#endif /* IR_INIT_H */
