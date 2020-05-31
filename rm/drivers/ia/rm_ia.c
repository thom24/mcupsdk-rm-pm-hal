/*
 * IRQ Interrupt Aggregator
 *
 * IRQ management interrupt aggregator infrastructure
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/sbool.h>
#include <types/short_types.h>
#include <types/errno.h>
#include <types/address_types.h>
#include <lib/io.h>
#include <lib/trace.h>

#include <rm_core.h>
#include <rm_ia.h>
#include <tisci/rm/tisci_rm_irq.h>
#include <security/rm_int_firewall.h>
#include <hosts.h>

#include <ia_inst.h>
#include <ia_init.h>
#include <ia_cfg.h>

#define IA_VINT_MAX_BITS             64u

#define IA_VINT_NULL                 0xFFFFu

/*
 * IA Register Macros
 */
#define IA_ENTRY_INTMAP_LO(e)        ((e) * 0x8u)
#define IA_ENTRY_INTMAP_HI(e)        (((e) * 0x8u) + 0x4u)

#define IA_RT_VINT_BASE(v)           (v * 0x00001000u)

#ifdef CONFIG_INTERRUPT_AGGREGATOR_UNMAPPED_EVENTS
#define IA_UENTRY_MAP_LO(e)          ((e) * 0x8U)
#endif

#define IA_RT_VINT_ENABLE_SET_LO     0x00000000u
#define IA_RT_VINT_ENABLE_SET_HI     0x00000004u
#define IA_RT_VINT_ENABLE_CLR_LO     0x00000008u
#define IA_RT_VINT_ENABLE_CLR_HI     0x0000000Cu
#define IA_RT_VINT_ENABLE_CLR_RESET  0x00000000u

/*
 * IA Register Fields
 */
#define IA_ENTRY_INTMAP_REGNUM_MASK  0x0001FF00u
#define IA_ENTRY_INTMAP_REGNUM_SHIFT 0x00000008u
#define IA_ENTRY_INTMAP_REGNUM_RESET 0x00000000u
#define IA_ENTRY_INTMAP_BITNUM_MASK  0x0000003Fu
#define IA_ENTRY_INTMAP_BITNUM_SHIFT 0x00000000u
#define IA_ENTRY_INTMAP_BITNUM_RESET 0x00000000u

#ifdef CONFIG_INTERRUPT_AGGREGATOR_UNMAPPED_EVENTS
#define IA_UENTRY_MAP_IRQMODE_MASK   0x80000000U
#define IA_UENTRY_MAP_IRQMODE_SHIFT  0x0000001FU
#define IA_UENTRY_MAP_UMAPIDX_MASK   0x0000FFFFU
#define IA_UENTRY_MAP_UMAPIDX_SHIFT  0x00000000U
#endif

#define IA_GENERIC_EVT_RESETVAL      0xFFFFU

/**
 * \brief Get IA instance mapped to provided device ID
 *
 * \param id IA device ID
 *
 * \return Pointer to IA instance, NULL if no instance mapped to ID
 */
static struct ia_instance *ia_get_inst(u16 id)
{
	struct ia_instance *inst = NULL;
	u16 i;

	for (i = 0u; i < IA_INST_COUNT; i++) {
		if (ia_inst[i].id == id) {
			inst = &ia_inst[i];

			if (rm_core_validate_devgrp(inst->id, inst->devgrp) !=
			    SUCCESS) {
				/*
				 * Return NULL instance if instance devgrp
				 * doesn't align with boardcfg devgrp
				 */
				inst = NULL;
			}
			break;
		}
	}

	return inst;
}

/**
 * \brief Validates the virtual interrupt status bit index
 *
 * Verifies the virtual interrupt status bit index does not exceed the max
 * number of status bits allowed for a virtual interrupt.
 *
 * \param vint_sb_index Virtual interrupt status bit index
 *
 * \return SUCCESS if resource assignment is valid else -EINVAL
 */
static s32 ia_validate_vint_sb_index(u8 vint_sb_index)
{
	s32 r = SUCCESS;

	if (vint_sb_index >= IA_VINT_MAX_BITS) {
		r = -EINVAL;
	}

	return r;
}

/**
 * \brief Get usage count for IA VINT status bits
 *
 * \param inst Pointer to IA instance
 *
 * \param vint IA VINT index
 *
 * \return Usage count for VINT
 */
static u8 ia_get_vint_usage_count(const struct ia_instance *inst, u16 vint)
{
	return inst->vint_usage_count[vint];
}

/**
 * \brief Configure IA VINT
 *
 * \param inst Pointer to IA instance
 *
 * \param evt IA event index
 *
 * \param vint IA VINT index
 *
 * \param vint_sb_index VINT status bit to map to event
 */
static s32 ia_configure_vint(struct ia_instance *inst, u16 evt, u16 vint,
			      u8 vint_sb_index)
{
	mapped_addr_t maddr;
	u32 entry_int_map_lo;
	u32 vint_enable_set;
	u32 vint_enable_set_addr;
	s32 r = SUCCESS;

	maddr = rm_core_map_region(inst->imap->base);
	entry_int_map_lo = rm_fmk(IA_ENTRY_INTMAP_REGNUM_SHIFT,
				  IA_ENTRY_INTMAP_REGNUM_MASK, vint);
	entry_int_map_lo |= rm_fmk(IA_ENTRY_INTMAP_BITNUM_SHIFT,
				   IA_ENTRY_INTMAP_BITNUM_MASK, vint_sb_index);
	if (writel_verified(entry_int_map_lo,
			    maddr + IA_ENTRY_INTMAP_LO(evt)) != SUCCESS) {
		/* Readback of write failed: halt */
		r = -EFAILVERIFY;
	}

	rm_core_unmap_region();
	if (r == SUCCESS)
	{
		/*
		 * Enable the status bit via the VINT's real-time VINT_ENABLE_SET
		 * register
		 */
		maddr = rm_core_map_region(inst->intr->base);
		if (vint_sb_index < 32U) {
			vint_enable_set_addr = IA_RT_VINT_BASE(vint) +
					       IA_RT_VINT_ENABLE_SET_LO;
			vint_enable_set = (0x1U << vint_sb_index);
		} else {
			vint_enable_set_addr = IA_RT_VINT_BASE(vint) +
					       IA_RT_VINT_ENABLE_SET_HI;
			vint_enable_set = (0x1U << (vint_sb_index - 32U));
		}

		/* Write then verify the bit status */
		writel(vint_enable_set, maddr + vint_enable_set_addr);
		if ((readl(maddr + vint_enable_set_addr) & vint_enable_set) !=
		    vint_enable_set) {
			/* The bit is not set after readback */
			r = -EFAILVERIFY;
		}
		rm_core_unmap_region();
		if (r == SUCCESS)
		{
			/* Increment vint usage count */
			inst->vint_usage_count[vint]++;

			if ((vint == 0u) && (vint_sb_index == 0u)) {
				/*
				 * Store event associated with VINT 0 bit 0
				 * since all INTMAP registers default to
				 * 0x0000
				 */
				inst->v0_b0_evt = evt;
			}
		}
	}
	return r;
}

/**
 * \brief Clear event to VINT status bit mapping
 *
 * Clears the specified event to VINT mapping.
 *
 * \param inst Pointer to IA instance
 *
 * \param evt IA event index
 *
 * \param vint IA VINT index
 *
 * \param vint_sb_index VINT status bit to unmap from global event
 */
static s32 ia_clear_vint(const struct ia_instance *inst, u16 evt, u16 vint,
			  u8 vint_sb_index)
{
	mapped_addr_t maddr;
	u32 entry_int_map_lo;
	u32 vint_enable_clr;
	u32 vint_enable_clr_addr;
	s32 r = SUCCESS;

	/*
	 * Disable the status bit via the VINT's real-time VINT_ENABLE_CLR
	 * register
	 */
	maddr = rm_core_map_region(inst->intr->base);
	if (vint_sb_index < 32u) {
		vint_enable_clr_addr = IA_RT_VINT_BASE(vint) +
				       IA_RT_VINT_ENABLE_CLR_LO;
		vint_enable_clr = 0x1u << vint_sb_index;
	} else {
		vint_enable_clr_addr = IA_RT_VINT_BASE(vint) +
				       IA_RT_VINT_ENABLE_CLR_HI;
		vint_enable_clr = 0x1u << (vint_sb_index - 32u);
	}
	writel(vint_enable_clr, maddr + vint_enable_clr_addr);
	/*
	 * Clearing the enable of the status bit will cause a readback to
	 * return the status of the internal enable register.  The cleared
	 * status bit must be zero.
	 */
	if ((readl(maddr + vint_enable_clr_addr) & vint_enable_clr) !=
	    0U) {
		/* Readback of cleared enable failed: halt */
		r = -EFAILVERIFY;
	}
	rm_core_unmap_region();
	if (r == SUCCESS)
	{
		maddr = rm_core_map_region(inst->imap->base);
		entry_int_map_lo = rm_fmk(IA_ENTRY_INTMAP_REGNUM_SHIFT,
					  IA_ENTRY_INTMAP_REGNUM_MASK, 0u);
		entry_int_map_lo |= rm_fmk(IA_ENTRY_INTMAP_BITNUM_SHIFT,
					   IA_ENTRY_INTMAP_BITNUM_MASK, 0u);

		if (writel_verified(entry_int_map_lo,
				    maddr + IA_ENTRY_INTMAP_LO(evt)) != SUCCESS) {
			/* Readback of write failed: halt */
			r = -EFAILVERIFY;
		}

		rm_core_unmap_region();
	}
	return r;
}

/**
 * \brief Clear an event's previously existing ROM mapping
 *
 * \param inst Pointer to IA instance
 *
 * \param evt IA event index
 *
 * \return SUCCESS if no clear performed or if clear succeeds, else -EFAIL
 */
static s32 ia_clear_rom_mapping(const struct ia_instance *inst, u16 evt)
{
	s32 r = SUCCESS;
	u8 i;
	struct ia_used_mapping *used_mapping;
	u16 fwl_ch;
	u8 hosts[FWL_MAX_PRIVID_SLOTS];
	mapped_addr_t maddr;
	u32 entry_int_map_lo;
	u16 reg_vint, reg_sb;

	for (i = 0U; i < inst->n_rom_usage; i++) {
		used_mapping = &inst->rom_usage[i];
		if ((used_mapping->cleared == SFALSE) &&
		    ((used_mapping->event - inst->sevt_offset) == evt)) {
			maddr = rm_core_map_region(inst->imap->base);
			entry_int_map_lo = readl(maddr + IA_ENTRY_INTMAP_LO(evt));
			rm_core_unmap_region();

			reg_vint = (u16) rm_fext(entry_int_map_lo,
						 IA_ENTRY_INTMAP_REGNUM_SHIFT,
						 IA_ENTRY_INTMAP_REGNUM_MASK);
			reg_sb = (u16) rm_fext(entry_int_map_lo,
					       IA_ENTRY_INTMAP_BITNUM_SHIFT,
					       IA_ENTRY_INTMAP_BITNUM_MASK);

			/*
			 * Configure channelized firewall for VINT
			 * used by ROM to be accessible to DMSC so
			 * it can be cleaned up
			 */
			fwl_ch = reg_vint + inst->intr->fwl_ch_start;
			hosts[0U] = HOST_ID_DMSC;
			if (sec_rm_fwl_set_perm(inst->intr->fwl_id,
						fwl_ch,
						hosts,
						1U) != EFTOK) {
				r = -EFAIL;
				break;
			}

			r = ia_clear_vint(inst, evt, reg_vint, reg_sb);
			if (r == SUCCESS) {
				used_mapping->cleared = STRUE;
			}
		}
	}

	return r;
}

/**
 * \brief Validate IA event for in use or free cases
 *
 * \param inst Pointer to IA instance
 *
 * \param evt IA input event
 *
 * \param vint Virtual interrupt.  Only applicable for "in_use" check
 *
 * \param vint_sb_index VINT status bit.  Only applicable for "in_use" check
 *
 * \param in_use Validate for in use case if STRUE, else validate for free case
 *
 * \return SUCCESS if validation succeeds, else -EINVAL
 */
static s32 ia_validate_evt(const struct ia_instance *inst, u16 evt, u16 vint,
			   u8 vint_sb_index, sbool in_use)
{
	s32 r = SUCCESS;
	mapped_addr_t maddr;
	u32 entry_int_map_lo;
	u16 reg_vint, reg_sb;

	if (evt >= inst->n_sevt) {
		r = -EINVAL;
	}

	if ((r == SUCCESS) &&
	    (in_use == SFALSE) &&
	    (inst->rom_usage != NULL)) {
		/*
		 * Did ROM use the event to VINT mapping during boot?
		 * The mapping is cleared if it was used by ROM.  The clear
		 * only occurs once for each mapping.
		 */
		r = ia_clear_rom_mapping(inst, evt);
	}

	if (r == SUCCESS) {
		maddr = rm_core_map_region(inst->imap->base);

		entry_int_map_lo = readl(maddr + IA_ENTRY_INTMAP_LO(evt));

		if (in_use == STRUE) {
			/* Check if event is in use */
			reg_vint = (u16) rm_fext(entry_int_map_lo,
						 IA_ENTRY_INTMAP_REGNUM_SHIFT,
						 IA_ENTRY_INTMAP_REGNUM_MASK);
			reg_sb = (u16) rm_fext(entry_int_map_lo,
					       IA_ENTRY_INTMAP_BITNUM_SHIFT,
					       IA_ENTRY_INTMAP_BITNUM_MASK);
			if ((reg_vint == 0u) && (reg_sb == 0u)) {
				/*
				 * INTMAP register's default value is zero
				 * which signifies VINT 0 bit 0.  Validate
				 * against the instance's saved view of
				 * VINT 0 bit 0.
				 */
				if ((vint != reg_vint) &&
				    (vint_sb_index != reg_sb) &&
				    (evt != inst->v0_b0_evt)) {
					r = -EINVAL;
				}
			} else {
				if ((vint != reg_vint) &&
				    (vint_sb_index != reg_sb)) {
					r = -EINVAL;
				}
			}
		} else {
			/* Check if event is free */
			if ((entry_int_map_lo != 0u) ||
			    (evt == inst->v0_b0_evt)) {
				r = -EINVAL;
			}
		}

		rm_core_unmap_region();
	}

	return r;
}

#ifdef CONFIG_INTERRUPT_AGGREGATOR_UNMAPPED_EVENTS
/**
 * \brief Gets the global event in an unmapped event UENTRY_MAP register
 *
 * \param host Host ID of processing entity attempting to get the event.
 *
 * \param id SoC device ID in which the OES index resides
 *
 * \param oes_index Flattened OES register index.  Needs to be decoded based on
 *                  IA instance unmapped event offsets.
 *
 * \param evt Returns the global event value within the OES index's UENTRY_MAP
 *            register
 *
 * \return SUCCESS if global event retrieved successfully, else error
 */
static s32 ia_get_oes_evt(u8 host, u16 id, u16 oes_index, u16 *evt)
{
	s32 r = SUCCESS;
	const struct ia_instance *inst = NULL;
	u8 trace_action = TRACE_RM_ACTION_IRQ_IA_OES_GET;
	u8 i;
	mapped_addr_t maddr;
	u32 evt_addr;
	u32 evt_reg;

	if (evt == NULL) {
		r = -EINVAL;
	} else {
		inst = ia_get_inst(id);
		if (inst == NULL) {
			trace_action |= TRACE_RM_ACTION_FAIL;
			r = -EINVAL;
		}

		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_DEVICE_ID,
			     id);
	}

	if (r == SUCCESS) {
		for (i = 0U; i < inst->n_unmapped_events; i++) {
			if ((oes_index >= inst->unmapped_events[i].start) &&
			    (oes_index < inst->unmapped_events[i].end)) {
				r = rm_core_resasg_validate_resource(
					host,
					inst->unmapped_events[i].utype,
					oes_index);
				break;
			}
		}

		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
		}

		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_OES_REG_INDEX,
			     oes_index);
	}

	if (r == SUCCESS) {
		maddr = rm_core_map_region(inst->unmap->base);
		evt_addr = maddr + IA_UENTRY_MAP_LO(oes_index);

		evt_reg = readl(evt_addr);
		rm_core_unmap_region();

		*evt = rm_fext(evt_reg, IA_UENTRY_MAP_UMAPIDX_SHIFT,
			       IA_UENTRY_MAP_UMAPIDX_MASK);
		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_EVENT,
			     *evt);
	}

	return r;
}

/**
 * \brief Sets the global event in an unmapped event UENTRY_MAP register
 *
 * \param host Host ID of processing entity attempting to set the event.
 *
 * \param id SoC device ID in which the OES index resides
 *
 * \param oes_index Flattened OES register index.  Needs to be decoded based on
 *                  IA instance unmapped event offsets.
 *
 * \param evt Global event value to program into the OES index's UENTRY_MAP
 *            register
 *
 * \return SUCCESS if global event programmed successfully, else error
 */
static s32 ia_set_oes_evt(u8 host, u16 id, u16 oes_index, u16 evt)
{
	s32 r = SUCCESS;
	const struct ia_instance *inst = NULL;
	u8 i;
	mapped_addr_t maddr;
	u32 evt_reg;
	u32 evt_addr;
	u8 trace_action = TRACE_RM_ACTION_IRQ_IA_OES_SET;

	rm_trace_sub(trace_action,
		     TRACE_RM_SUB_ACTION_EVENT,
		     evt);

	inst = ia_get_inst(id);
	if (inst == NULL) {
		trace_action |= TRACE_RM_ACTION_FAIL;
		r = -EINVAL;
	}
	rm_trace_sub(trace_action,
		     TRACE_RM_SUB_ACTION_DEVICE_ID,
		     id);

	if (r == SUCCESS) {
		r = -EINVAL;

		for (i = 0U; i < inst->n_unmapped_events; i++) {
			if ((oes_index >= inst->unmapped_events[i].start) &&
			    (oes_index < inst->unmapped_events[i].end)) {
				r = rm_core_resasg_validate_resource(
					host,
					inst->unmapped_events[i].utype,
					oes_index);
				break;
			}
		}

		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
		}

		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_OES_REG_INDEX,
			     oes_index);
	}

	if (r == SUCCESS) {
		/* oes_index verified already at this point */
		maddr = rm_core_map_region(inst->unmap->base);
		evt_reg = rm_fmk(IA_UENTRY_MAP_IRQMODE_SHIFT,
				 IA_UENTRY_MAP_IRQMODE_MASK, 0U);
		evt_reg |= rm_fmk(IA_UENTRY_MAP_UMAPIDX_SHIFT,
				  IA_UENTRY_MAP_UMAPIDX_MASK, evt);
		evt_addr = maddr + IA_UENTRY_MAP_LO(oes_index);

		if (writel_verified(evt_reg, evt_addr) != SUCCESS) {
			/* Readback of write failed: halt */
			r = -EFAILVERIFY;
		}
		rm_core_unmap_region();
	}

	return r;
}
#endif /* CONFIG_INTERRUPT_AGGREGATOR_UNMAPPED_EVENTS */

sbool rm_ia_is_managed_resasg_utype(u16 utype)
{
	sbool r = SFALSE;
	u16 i;

#ifdef CONFIG_INTERRUPT_AGGREGATOR_UNMAPPED_EVENTS
	u8 j;
#endif

	for (i = 0U; i < IA_INST_COUNT; i++) {
		if (utype == ia_inst[i].vint_utype) {
			r = STRUE;
		}

#ifdef CONFIG_INTERRUPT_AGGREGATOR_UNMAPPED_EVENTS
		if (r == SFALSE) {
			for (j = 0U; j < ia_inst[i].n_unmapped_events; j++) {
				if (utype == ia_inst[i].unmapped_events[j].utype) {
					r = STRUE;
					break;
				}
			}
		}
#endif

		if (r == STRUE) {
			break;
		}
	}

	return r;
}

s32 rm_ia_validate_vint(u8 host, u16 id, u16 vint)
{
	s32 r = SUCCESS;
	const struct ia_instance *inst = NULL;

	inst = ia_get_inst(id);
	if (inst == NULL) {
		r = -EINVAL;
	} else {
		if (vint >= inst->n_vint) {
			r = -EINVAL;
		}
	}

	if (r == SUCCESS) {
		r = rm_core_resasg_validate_resource(host, inst->vint_utype,
						     vint);
	}

	return r;
}

s32 rm_ia_vint_map(u16 id, u16 vint, u16 global_evt, u8 vint_sb_index)
{
	s32 r = SUCCESS;
	struct ia_instance *inst;
	u16 evt;
	u8 trace_action = TRACE_RM_ACTION_IRQ_IA_MAP_VINT;

	inst = ia_get_inst(id);
	if (inst == NULL) {
		trace_action |= TRACE_RM_ACTION_FAIL;
		r = -EINVAL;
	}
	rm_trace_sub(trace_action,
		     TRACE_RM_SUB_ACTION_DEVICE_ID,
		     id);

	if (r == SUCCESS) {
		r = ia_validate_vint_sb_index(vint_sb_index);
		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
		}
		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_IA_VINT_STATUS_BIT,
			     vint_sb_index);
	}

	if (r == SUCCESS) {
		evt = global_evt - inst->sevt_offset;
		/* Check if event is free */
		r = ia_validate_evt(inst, evt, 0U, 0U, SFALSE);
		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
		}
		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_IA_GLOBAL_EVENT,
			     global_evt);
	}

	if (r == SUCCESS) {
		if (vint >= inst->n_vint) {
			r = -EINVAL;
		} else {
			/* Check if VINT mapping is full */
			if (ia_get_vint_usage_count(inst, vint) >=
			    IA_VINT_MAX_BITS) {
				r = -EINVAL;
			}
		}

		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
		}
		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_IA_VINT,
			     vint);
	}

	if (r == SUCCESS) {
		/* Configure the VINT INTR channelized firewall */
		r = rm_core_resasg_cfg_firewall(inst->id,
						inst->vint_utype,
						inst->intr->fwl_id,
						inst->intr->fwl_ch_start,
						vint,
						STRUE,
						SFALSE,
						SFALSE);
	}

	if (r == SUCCESS) {
		r = ia_configure_vint(inst, evt, vint, vint_sb_index);
	}

	return r;
}

s32 rm_ia_vint_unmap(u16 id, u16 vint, u16 global_evt, u8 vint_sb_index)
{
	s32 r = SUCCESS;
	struct ia_instance *inst;
	u16 evt;
	u8 trace_action = TRACE_RM_ACTION_IRQ_IA_UNMAP_VINT;

	inst = ia_get_inst(id);
	if (inst == NULL) {
		trace_action |= TRACE_RM_ACTION_FAIL;
		r = -EINVAL;
	}
	rm_trace_sub(trace_action,
		     TRACE_RM_SUB_ACTION_DEVICE_ID,
		     id);

	if (r == SUCCESS) {
		if (vint >= inst->n_vint) {
			r = -EINVAL;
		} else {
			/* Check if VINT mapping is full */
			if (ia_get_vint_usage_count(inst, vint) == 0u) {
				r = -EINVAL;
			}
		}
		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
		}
		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_IA_VINT,
			     vint);
	}

	if (r == SUCCESS) {
		r = ia_validate_vint_sb_index(vint_sb_index);
		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
		}
		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_IA_VINT_STATUS_BIT,
			     vint_sb_index);
	}

	if (r == SUCCESS) {
		evt = global_evt - inst->sevt_offset;
		/* Check if event is mapped to vint status bit */
		r = ia_validate_evt(inst, evt, vint, vint_sb_index, STRUE);
		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
		}
		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_IA_GLOBAL_EVENT,
			     global_evt);
	}

	if (r == SUCCESS) {
		r = ia_clear_vint(inst, evt, vint, vint_sb_index);
	}
	if (r == SUCCESS) {
		inst->vint_usage_count[vint]--;

		if (inst->v0_b0_evt == evt) {
			/* Cleared event was mapped to VINT 0 bit 0 */
			inst->v0_b0_evt = IA_GENERIC_EVT_RESETVAL;
		}
	}

	return r;
}

s32 rm_ia_vint_get_info(u16 id, u16 vint, u8 *n_evts)
{
	s32 r = SUCCESS;
	const struct ia_instance *inst;

	if (n_evts == NULL) {
		r = -EINVAL;
	} else {
		inst = ia_get_inst(id);
		if (inst == NULL) {
			r = -EINVAL;
		} else {
			if (vint >= inst->n_vint) {
				r = -EINVAL;
			}
		}
	}

	if (r == SUCCESS) {
		*n_evts = inst->vint_usage_count[vint];
	}

	return r;
}

s32 rm_ia_init(void)
{
	s32 r = SUCCESS;
	u32 i, j;
	u16 fwl_ch;
	u8 hosts[FWL_MAX_PRIVID_SLOTS];

	for (i = 0U; i < IA_INST_COUNT; i++) {
		if ((rm_core_validate_devgrp(ia_inst[i].id, ia_inst[i].devgrp) ==
		     SUCCESS) &&
		    (ia_inst[i].initialized == SFALSE)) {
#if defined(CONFIG_RM_IRQ) && defined(CONFIG_INTERRUPT_AGGREGATOR_UNMAPPED_EVENTS)
			ia_inst[i].oes_handler.oes_get = ia_get_oes_evt;
			ia_inst[i].oes_handler.oes_set = ia_set_oes_evt;

			r = rm_irq_oes_src_register(ia_inst[i].id,
						    &ia_inst[i].oes_handler);
#endif

			for (j = 0U; j < ia_inst[i].n_vint; j++) {
				ia_inst[i].vint_usage_count[j] = 0U;
			}

			ia_inst[i].v0_b0_evt = IA_GENERIC_EVT_RESETVAL;

			for (j = 0U;
			     (j < IA_SOC_PE_INIT_NUM) && (r == SUCCESS);
			     j++) {
				if (ia_soc_pe_init_list[j].id == ia_inst[i].id) {
					/*
					 * Configure channelized firewalls for VINTs
					 * used by DMSC
					 */
					fwl_ch = ia_soc_pe_init_list[j].vint +
						 ia_inst[i].intr->fwl_ch_start;
					hosts[0U] = HOST_ID_DMSC;
					if (sec_rm_fwl_set_perm(ia_inst[i].intr->fwl_id,
								fwl_ch,
								hosts,
								1U) != EFTOK) {
						r = -EFAIL;
					}

					if (r == SUCCESS) {
						r = rm_ia_vint_map(
							ia_soc_pe_init_list[j].id,
							ia_soc_pe_init_list[j].vint,
							ia_soc_pe_init_list[j].event_id,
							0U);
					}
				}
			}

			if (r != SUCCESS) {
				break;
			} else {
				ia_inst[i].initialized = STRUE;
			}
		}
	}


	if (r != SUCCESS) {
		rm_trace_sub(TRACE_RM_ACTION_IRQ_IA_INIT |
			     TRACE_RM_ACTION_FAIL, 0U, 0U);
	}

	return r;
}

s32 rm_ia_deinit(devgrp_t devgrp)
{
	s32 r = -EFAIL;
	u8 i;

	for (i = 0U; i < IA_INST_COUNT; i++) {
		if ((rm_core_validate_devgrp(ia_inst[i].id, ia_inst[i].devgrp) ==
		     SUCCESS) &&
			(ia_inst[i].initialized == STRUE) &&
		    (ia_inst[i].devgrp == devgrp)) {
			ia_inst[i].initialized = SFALSE;
			r = SUCCESS;
		}
	}

	return r;
}
