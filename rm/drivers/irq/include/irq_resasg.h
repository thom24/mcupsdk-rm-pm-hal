/*
 * Interrupt Management
 *
 * Interrupt management resource assignment definition
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef IRQ_RESASG_H
#define IRQ_RESASG_H

#include <types/short_types.h>
#include <soc/rm_mmr.h>
#include <rm_irq.h>


/**
 * \brief
 * Global event type information
 *
 * \param start
 * Global event type start index
 *
 * \param num
 * Number of Global events for the type
 *
 * \param utype
 * Global event type resource assignment type
 */
struct irq_global_event_type {
	const u16	start;
	const u16	num;
	const u16	utype;
};

/**
 * Extern for IRQ subsystem global event types array
 */
extern const struct irq_global_event_type irq_global_event_types[];

/**
 * Extern for number of IRQ subsystem global event types
 */
extern const u16 irq_global_event_types_count;

#endif /* IRQ_RESASG_H */
