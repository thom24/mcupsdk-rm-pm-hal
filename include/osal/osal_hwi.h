/*
 * System Firmware OSAL HWI layer
 *
 * OSAL HWI layer for generic peripheral interrupts
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef OSAL_OSAL_HWI_H
#define OSAL_OSAL_HWI_H

#include <arch/interrupt.h>
#include <types/short_types.h>

#include <osal_hwi_ids.h>

typedef void (*hwip_fxn)(u32 arg0);

/**
 * \struct osal_hwi_data
 * \brief Contains data needed for HWI operation.
 *
 * \param irq_num The irq number for this HWI.
 * \param hwi_id The HWI_IDS enum value to identify this HWI.
 * \param priority Priority level passed to the OSAL of this interrupt. This
 *		   is the priority level within the hardware and should match all
 *		   other HWIs defined at the same logical queue priority and
 *		   execution level.
 * \param handler IRQ function that will be run when this interrupt is triggered.
 * \param arg Pointer to data that will be passed as an argument to #handler.
 */
struct osal_hwi_data {
	u32		irq_num;
	s32		hwi_id;
	s32		priority;
	hwip_fxn	handler;
	void		*arg;
};

/**
 * \brief Initialize all registered periperhal interrupts.
 *
 * \return Error code on failure, SUCCESS otherwise.
 */
s32 osal_peripheral_interrupt_init(void);

extern const struct osal_hwi_data *osal_peripheral_interrupt_list[];
extern const u8 osal_peripheral_interrupt_list_count;

#endif /* OSAL_OSAL_HWI_H */
