/*
 * IRQ Interrupt Aggregator
 *
 * IRQ Interrupt Aggregator initialization data structure
 *
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef IA_INIT_H
#define IA_INIT_H

#include <ia_pe_conf.h>

#include <types/short_types.h>

/**
 * \brief Initialization of Interrupt aggregator
 *
 * \param id
 * Device ID for Interrupt agregator
 *
 * \param event_id
 * Event ID (global)
 *
 * \param vint
 * Virq to map to
 */
struct ia_init {
	const u16	id;
	const u16	event_id;
	const u16	vint;
};

extern const struct ia_init ia_soc_pe_init_list[IA_SOC_PE_INIT_NUM];

#endif /* IA_INIT_H */
