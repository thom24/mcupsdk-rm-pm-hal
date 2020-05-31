/*
 * PSI-L
 *
 * PSI-L management infrastructure
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/sbool.h>
#include <types/short_types.h>
#include <types/address_types.h>
#include <types/errno.h>
#include <lib/io.h>
#include <lib/trace.h>
#include <devices_internal.h>

#include <osal/osal_core.h>
#include <tisci_provider/tisci.h>
#include <tisci/rm/tisci_rm_shared.h>
#include <tisci/rm/tisci_rm_psil.h>

#include <rm_core.h>
#include <rm_psil.h>
#include <rm_udmap.h>

#include <psil_inst.h>
#include <psil_cfg.h>

/*
 * PSI-L Configuration Proxy Register Macros
 */
#define PSIL_PROXY_TO                              (0x00000010u)
#define PSIL_PROXY_CMDA                            (0x00000100u)
#define PSIL_PROXY_CMDB                            (0x00000104u)
#define PSIL_PROXY_WDATA                           (0x00000108u)
#define PSIL_PROXY_RDATA                           (0x00000140u)

/*
 * PSI-L Configuration Proxy Register Fields
 */
#define PSIL_PROXY_TO_TOUT_MASK                    (0x80000000u)
#define PSIL_PROXY_TO_TOUT_SHIFT                   (0x0000001Fu)
#define PSIL_PROXY_TO_TOUT_FALSE                   (0x00000000u)
#define PSIL_PROXY_TO_TOUT_TRUE                    (0x00000001u)
#define PSIL_PROXY_TO_TOUT_CNT_MASK                (0x0000FFFFu)
#define PSIL_PROXY_TO_TOUT_CNT_SHIFT               (0x00000000u)

#define PSIL_PROXY_CMDA_PROXY_BUSY_MASK            (0x80000000u)
#define PSIL_PROXY_CMDA_PROXY_BUSY_SHIFT           (0x0000001Fu)
#define PSIL_PROXY_CMDA_PROXY_BUSY_FALSE           (0x00000000u)
#define PSIL_PROXY_CMDA_PROXY_BUSY_TRUE            (0x00000001u)
#define PSIL_PROXY_CMDA_PROXY_DIR_MASK             (0x40000000u)
#define PSIL_PROXY_CMDA_PROXY_DIR_SHIFT            (0x0000001Eu)
#define PSIL_PROXY_CMDA_PROXY_DIR_WRITE            (0x00000000u)
#define PSIL_PROXY_CMDA_PROXY_DIR_READ             (0x00000001u)
#define PSIL_PROXY_CMDA_PROXY_TOUT_MASK            (0x20000000u)
#define PSIL_PROXY_CMDA_PROXY_TOUT_SHIFT           (0x0000001Du)
#define PSIL_PROXY_CMDA_PROXY_TOUT_FALSE           (0x00000000u)
#define PSIL_PROXY_CMDA_PROXY_TOUT_TRUE            (0x00000001u)
#define PSIL_PROXY_CMDA_THREAD_ID_MASK             (0x0000FFFFu)
#define PSIL_PROXY_CMDA_THREAD_ID_SHIFT            (0x00000000u)

#define PSIL_PROXY_CMDB_BYTEN_MASK                 (0xF0000000u)
#define PSIL_PROXY_CMDB_BYTEN_SHIFT                (0x0000001Cu)
#define PSIL_PROXY_CMDB_BYTEN_ALL                  (0x0000000Fu)
#define PSIL_PROXY_CMDB_ADDRESS_MASK               (0x0000FFFFu)
#define PSIL_PROXY_CMDB_ADDRESS_SHIFT              (0x00000000u)
#define PSIL_PROXY_CMDB_ADDRESS_PEER_THREAD_ID     (0x00000000u)
#define PSIL_PROXY_CMDB_ADDRESS_PEER_CREDIT        (0x00000001u)
#define PSIL_PROXY_CMDB_ADDRESS_ENABLE             (0x00000002u)
#define PSIL_PROXY_CMDB_ADDRESS_CAPABILITIES       (0x00000040u)

/*
 * PSI-L Configuration Register Fields
 */
#define PSIL_CFG_PEER_THREAD_ID_PRIORITY_MASK      (0xE0000000u)
#define PSIL_CFG_PEER_THREAD_ID_PRIORITY_SHIFT     (0x0000001Du)
#define PSIL_CFG_PEER_THREAD_ID_WIDTH_MASK         (0x1F000000u)
#define PSIL_CFG_PEER_THREAD_ID_WIDTH_SHIFT        (0x00000018u)
#define PSIL_CFG_PEER_THREAD_ID_WIDTH_RESET        (0x00000000u)
#define PSIL_CFG_PEER_THREAD_ID_THREAD_ID_MASK     (0x0000FFFFu)
#define PSIL_CFG_PEER_THREAD_ID_THREAD_ID_SHIFT    (0x00000000u)
#define PSIL_CFG_PEER_THREAD_ID_THREAD_ID_RESET    (0x00000000u)

#define PSIL_CFG_PEER_CREDIT_CNT_MASK              (0x000000FFu)
#define PSIL_CFG_PEER_CREDIT_CNT_SHIFT             (0x00000000u)
#define PSIL_CFG_PEER_CREDIT_CNT_RESET             (0x00000000u)

#define PSIL_CFG_ENABLE_ENABLE_MASK                (0x80000000u)
#define PSIL_CFG_ENABLE_ENABLE_SHIFT               (0x0000001Fu)
#define PSIL_CFG_ENABLE_ENABLE_DISABLED            (0x00000000u)
#define PSIL_CFG_ENABLE_ENABLE_ENABLED             (0x00000001u)

#define PSIL_CFG_CAPABILITIES_WIDTH_MASK           (0x1F000000u)
#define PSIL_CFG_CAPABILITIES_WIDTH_SHIFT          (0x00000018u)
#define PSIL_CFG_CAPABILITIES_CNT_MASK             (0x000000FFu)
#define PSIL_CFG_CAPABILITIES_CNT_SHIFT            (0x00000000u)

/**
 * \brief Get PSI-L instance mapped to provided device ID
 *
 * \param id PSI-L device ID
 *
 * \param trace_action RA action to trace
 *
 * \return Pointer to PSI-L instance, NULL if no instance mapped to ID
 */
static const struct psil_instance *psil_get_inst(u32 id, u8 trace_action)
{
	const struct psil_instance *inst = NULL;
	u32 i;

	for (i = 0u; i < psil_inst_count; i++) {
		if (psil_inst[i].id == id) {
			inst = &psil_inst[i];

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

	if (inst == NULL) {
		trace_action |= TRACE_RM_ACTION_FAIL;
	}

	rm_trace_sub(trace_action,
		     TRACE_RM_SUB_ACTION_DEVICE_ID,
		     id);

	return inst;
}

/**
 * \brief Check whether the PSI-L proxy is busy with a transaction
 *
 * \param inst PSI-L instance
 *
 * \return Returns STRUE if command proxy is busy, else SFALSE
 */
static sbool psil_cfg_is_cmd_busy(const struct psil_instance *inst)
{
	sbool busy = SFALSE;
	mapped_addr_t maddr;
	u32 cmda_reg;

	maddr = rm_core_map_region(inst->proxy->base);
	cmda_reg = readl(maddr + PSIL_PROXY_CMDA);
	rm_core_unmap_region();

	if (rm_fext(cmda_reg, PSIL_PROXY_CMDA_PROXY_BUSY_SHIFT,
		    PSIL_PROXY_CMDA_PROXY_BUSY_MASK) ==
	    PSIL_PROXY_CMDA_PROXY_BUSY_TRUE) {
		busy = STRUE;
	}

	return busy;
}

/**
 * \brief Check whether the PSI-L proxy has timed out on a transaction
 *
 * \param inst PSI-L instance
 *
 * \return Returns STRUE if command proxy timed out, else SFALSE
 */
static sbool psil_cfg_is_cmd_timed_out(const struct psil_instance *inst)
{
	sbool timeout = SFALSE;
	mapped_addr_t maddr;
	u32 cmda_reg;

	maddr = rm_core_map_region(inst->proxy->base);
	cmda_reg = readl(maddr + PSIL_PROXY_CMDA);
	rm_core_unmap_region();

	if (rm_fext(cmda_reg, PSIL_PROXY_CMDA_PROXY_TOUT_SHIFT,
		    PSIL_PROXY_CMDA_PROXY_TOUT_MASK) ==
	    PSIL_PROXY_CMDA_PROXY_TOUT_TRUE) {
		timeout = STRUE;
	}

	return timeout;
}

/**
 * \brief Clears the PSI-L proxy time out bit if a timeout is occurred
 *
 * \param inst PSI-L instance
 */
static s32 psil_cfg_clear_timeout(const struct psil_instance *inst)
{
	mapped_addr_t maddr;
	u32 to_reg;
	s32 r = SUCCESS;

	maddr = rm_core_map_region(inst->proxy->base);
	to_reg = readl(maddr + PSIL_PROXY_TO);

	if (rm_fext(to_reg, PSIL_PROXY_TO_TOUT_SHIFT,
		    PSIL_PROXY_TO_TOUT_MASK) ==
	    PSIL_PROXY_TO_TOUT_TRUE) {
		to_reg = rm_fmk(PSIL_PROXY_TO_TOUT_SHIFT,
				PSIL_PROXY_TO_TOUT_MASK,
				PSIL_PROXY_TO_TOUT_FALSE) |
			 (to_reg & ~PSIL_PROXY_TO_TOUT_MASK);
		if (writel_verified(to_reg, maddr + PSIL_PROXY_TO) !=
		    SUCCESS) {
			/* Readback of write failed: halt */
			r = -EFAILVERIFY;
		}
	}

	rm_core_unmap_region();
	return r;
}

/**
 * \brief Get read data out of the PSI-L command proxy
 *
 * \param inst PSI-L instance
 *
 * \return Returns the value in the command proxy's RDATA register
 */
static u32 psil_cfg_read_data(const struct psil_instance *inst)
{
	mapped_addr_t maddr;
	u32 rdata_reg;

	maddr = rm_core_map_region(inst->proxy->base);
	rdata_reg = readl(maddr + PSIL_PROXY_RDATA);
	rm_core_unmap_region();

	return rdata_reg;
}

/**
 * \brief Read from a PSI-L thread global config register through the PSI-L
 *        configuration proxy
 *
 * \param inst PSI-L instance
 *
 * \param thrd_id Thread ID
 *
 * \param thrd_reg Thread register within thread's global config space
 *
 * \param data Returns the data within the thread's global config register
 *
 * \return SUCCESS if read successful, else error.
 */
static s32 psil_cfg_read(const struct psil_instance *inst, u32 thrd_id,
			 u32 thrd_reg, u32 *data)
{
	s32 r = SUCCESS;
	mapped_addr_t maddr;
	u32 cmda_reg, cmdb_reg;

	/* Receiving a busy signal is a hard failure.  Assumption when
	 * executing the read is there are no in-flight transactions. */
	if (psil_cfg_is_cmd_busy(inst) != STRUE) {
		maddr = rm_core_map_region(inst->proxy->base);

		cmda_reg = rm_fmk(PSIL_PROXY_CMDA_PROXY_DIR_SHIFT,
				  PSIL_PROXY_CMDA_PROXY_DIR_MASK,
				  PSIL_PROXY_CMDA_PROXY_DIR_READ);
		cmda_reg |= rm_fmk(PSIL_PROXY_CMDA_THREAD_ID_SHIFT,
				   PSIL_PROXY_CMDA_THREAD_ID_MASK, thrd_id);
		writel(cmda_reg, maddr + PSIL_PROXY_CMDA);

		cmdb_reg = rm_fmk(PSIL_PROXY_CMDB_BYTEN_SHIFT,
				  PSIL_PROXY_CMDB_BYTEN_MASK,
				  PSIL_PROXY_CMDB_BYTEN_ALL);
		cmdb_reg |= rm_fmk(PSIL_PROXY_CMDB_ADDRESS_SHIFT,
				   PSIL_PROXY_CMDB_ADDRESS_MASK,
				   thrd_reg);
		writel(cmdb_reg, maddr + PSIL_PROXY_CMDB);

		rm_core_unmap_region();

		/* Driver maintains default timeout of 0x400 */
		while (psil_cfg_is_cmd_busy(inst) == STRUE) {
		}

		if (psil_cfg_is_cmd_timed_out(inst) == STRUE) {
			/* Clear timeout if last transaction timed out */
			r = psil_cfg_clear_timeout(inst);
			if (r == SUCCESS)
			{
				r = -ETIMEDOUT;
			}
		} else {
			*data = psil_cfg_read_data(inst);
		}
	} else {
		r = -EBUSY;
	}

	return r;
}

/**
 * \brief Write to a PSI-L thread global config register through the PSI-L
 *        configuration proxy
 *
 * \param inst PSI-L instance
 *
 * \param thrd_id Thread ID
 *
 * \param thrd_reg Thread register within thread's global config space
 *
 * \param data Data to write to thread's global config register
 *
 * \return SUCCESS if write successful, else error.
 */
static s32 psil_cfg_write(const struct psil_instance *inst, u32 thrd_id,
			  u32 thrd_reg, u32 data, sbool readback_verify)
{
	s32 r = SUCCESS;
	mapped_addr_t maddr;
	u32 cmda_reg, cmdb_reg;
	u32 readback;

	if (psil_cfg_is_cmd_busy(inst) != STRUE) {
		maddr = rm_core_map_region(inst->proxy->base);

		cmda_reg = rm_fmk(PSIL_PROXY_CMDA_PROXY_DIR_SHIFT,
				  PSIL_PROXY_CMDA_PROXY_DIR_MASK,
				  PSIL_PROXY_CMDA_PROXY_DIR_WRITE);
		cmda_reg |= rm_fmk(PSIL_PROXY_CMDA_THREAD_ID_SHIFT,
				   PSIL_PROXY_CMDA_THREAD_ID_MASK,
				   thrd_id);
		writel(cmda_reg, maddr + PSIL_PROXY_CMDA);

		cmdb_reg = rm_fmk(PSIL_PROXY_CMDB_BYTEN_SHIFT,
				  PSIL_PROXY_CMDB_BYTEN_MASK,
				  PSIL_PROXY_CMDB_BYTEN_ALL);
		cmdb_reg |= rm_fmk(PSIL_PROXY_CMDB_ADDRESS_SHIFT,
				   PSIL_PROXY_CMDB_ADDRESS_MASK,
				   thrd_reg);
		writel(cmdb_reg, maddr + PSIL_PROXY_CMDB);

		writel(data, maddr + PSIL_PROXY_WDATA);

		rm_core_unmap_region();

		/* Driver maintains default timeout of 0x400 */
		while (psil_cfg_is_cmd_busy(inst) == STRUE) {
		}

		if (psil_cfg_is_cmd_timed_out(inst) == STRUE) {
			/* Clear timeout if last transaction timed out */
			r = psil_cfg_clear_timeout(inst);
			if (r == SUCCESS)
			{
				r = -ETIMEDOUT;
			}
		} else {
			if (readback_verify == STRUE) {
				/* Readback value programmed through proxy. */
				r = psil_cfg_read(inst, thrd_id, thrd_reg,
						  &readback);
				if (r == SUCCESS) {
					if (data != readback) {
						/*
						 * Readback data
						 * mismatch: halt
						 */
						r = -EFAILVERIFY;
					}
				} else {
					/*
					 * Readback attempt failed despite
					 * previous proxy transaction
					 * completing: halt
					 */
					r = -ECONFUSED;
				}
			}
		}
	} else {
		r = -EBUSY;
	}

	return r;
}

/**
 * \brief Enables a thread via the thread's global configuration registers
 *
 * \param inst PSI-L instance
 *
 * \param thread Thread ID
 *
 * \return SUCCESS if thread enabled, else error
 */
static s32 psil_enable_thread(const struct psil_instance *inst, u32 thread)
{
	s32 r;
	u32 enable;

	enable = rm_fmk(PSIL_CFG_ENABLE_ENABLE_SHIFT,
			PSIL_CFG_ENABLE_ENABLE_MASK,
			PSIL_CFG_ENABLE_ENABLE_ENABLED);
	r = psil_cfg_write(inst, thread, PSIL_PROXY_CMDB_ADDRESS_ENABLE,
			   enable, STRUE);

	return r;
}


/**
 * \brief Disables a thread via the thread's global configuration registers
 *
 * \param inst PSI-L instance
 *
 * \param thread Thread ID
 *
 * \return SUCCESS if thread disabled, else error
 */
static s32 psil_disable_thread(const struct psil_instance *inst, u32 thread)
{
	s32 r;
	u32 disable;

	disable = rm_fmk(PSIL_CFG_ENABLE_ENABLE_SHIFT,
			 PSIL_CFG_ENABLE_ENABLE_MASK,
			 PSIL_CFG_ENABLE_ENABLE_DISABLED);
	r = psil_cfg_write(inst, thread, PSIL_PROXY_CMDB_ADDRESS_ENABLE,
			   disable, STRUE);

	return r;
}

/**
 * \brief Validate PSI-L thread
 *
 * \param inst PSI-L instance
 *
 * \param thread PSI-L thread
 *
 * \return SUCCESS if thread is valid, else -EINVAL
 */
static s32 psil_validate_thread(const struct psil_instance	*inst,
				u32				thread)
{
	s32 r = -EINVAL;
	u8 i;

	/* Is thread a valid source thread in PSI-L instance? */
	for (i = 0U; i < inst->n_src_thread_type; i++) {
		if ((thread >= inst->src_thread_types[i].start) &&
		    (thread <= inst->src_thread_types[i].end)) {
			r = SUCCESS;
			break;
		}
	}

	if (r != SUCCESS) {
		/* Is thread a valid destination thread in PSI-L instance? */
		for (i = 0U; i < inst->n_dst_thread_type; i++) {
			if ((thread >= inst->dst_thread_types[i].start) &&
			    (thread <= inst->dst_thread_types[i].end)) {
				r = SUCCESS;
				break;
			}
		}
	}

	return r;
}

/**
 * \brief Validate enable/disable status of PSI-L thread
 *
 * \param inst PSI-L instance
 *
 * \param thread Thread ID
 *
 * \param enable_val Value to check thread ENABLE register against.  Thread is
 *                   not valid if enable field of ENABLE register equals
 *                   enable_val
 *
 * \return SUCCESS if thread enable/disable status is valid, else -EINVAL
 */
static s32 psil_validate_thread_enable_status(
	const struct psil_instance	*inst,
	u32				thread,
	u32				enable_val)
{
	s32 r = SUCCESS;
	u32 enable;

	r = psil_cfg_read(inst, thread,
			  PSIL_PROXY_CMDB_ADDRESS_ENABLE, &enable);
	if (r == SUCCESS) {
		if (rm_fext(enable, PSIL_CFG_ENABLE_ENABLE_SHIFT,
			    PSIL_CFG_ENABLE_ENABLE_MASK) ==
		    enable_val) {
			r = -EINVAL;
		}
	}

	return r;
}

/**
 * \brief Gets the destination peer thread value within a source thread's
 *        PEER_THREAD_ID register
 *
 * \param inst PSI-L instance
 *
 * \param src_thrd Source thread
 *
 * \param dst_peer_thrd Returns the thread ID value within the source thread's
 *                      PeerThreadID field of the PEER_THREAD_ID register
 *
 * \return SUCCESS if peer thread ID retrieved successfully, else error
 */
static s32 psil_get_src_peer_thread(const struct psil_instance *inst,
				    u32 src_thrd, u32 *dst_peer_thrd)
{
	s32 r = SUCCESS;
	u32 peer_thrd_id_val;

	r = psil_cfg_read(inst, src_thrd,
			  PSIL_PROXY_CMDB_ADDRESS_PEER_THREAD_ID,
			  &peer_thrd_id_val);

	if (r == SUCCESS) {
		*dst_peer_thrd = rm_fext(
			peer_thrd_id_val,
			PSIL_CFG_PEER_THREAD_ID_THREAD_ID_SHIFT,
			PSIL_CFG_PEER_THREAD_ID_THREAD_ID_MASK);
	}

	return r;
}

/**
 * \brief Pairs the source thread with the destination thread
 *
 * If a thread maps to a UDMAP channel the UDMAP driver's channel thread ID
 * programming API is called to set the channel's peer thread ID.
 *
 * \param inst PSI-L instance
 *
 * \param src_thrd Source thread
 *
 * \param dst_thrd Destination thread
 *
 * \return SUCCESS if pairing is successful, else -EFAIL
 */
static s32 psil_pair(const struct psil_instance *inst, u32 src_thrd,
		     u32 dst_thrd)
{
	s32 r = SUCCESS;
	u32 capabilities_reg;
	u32 loc_thrd_width, loc_credit_cnt;
	u32 peer_thrd_id_reg, peer_credit_reg;

	/* Read destination thread capabilities */
	r = psil_cfg_read(inst, dst_thrd, PSIL_PROXY_CMDB_ADDRESS_CAPABILITIES,
			  &capabilities_reg);
	if (r == SUCCESS) {
		loc_thrd_width = rm_fext(capabilities_reg,
					 PSIL_CFG_CAPABILITIES_WIDTH_SHIFT,
					 PSIL_CFG_CAPABILITIES_WIDTH_MASK);
		loc_credit_cnt = rm_fext(capabilities_reg,
					 PSIL_CFG_CAPABILITIES_CNT_SHIFT,
					 PSIL_CFG_CAPABILITIES_CNT_MASK);

		peer_thrd_id_reg = rm_fmk(PSIL_CFG_PEER_THREAD_ID_WIDTH_SHIFT,
					  PSIL_CFG_PEER_THREAD_ID_WIDTH_MASK,
					  loc_thrd_width);
		peer_thrd_id_reg |= rm_fmk(
			PSIL_CFG_PEER_THREAD_ID_THREAD_ID_SHIFT,
			PSIL_CFG_PEER_THREAD_ID_THREAD_ID_MASK,
			dst_thrd);

		r = psil_cfg_write(inst, src_thrd,
				   PSIL_PROXY_CMDB_ADDRESS_PEER_THREAD_ID,
				   peer_thrd_id_reg, STRUE);
	}

	if (r == SUCCESS) {
		peer_credit_reg = rm_fmk(PSIL_CFG_PEER_CREDIT_CNT_SHIFT,
					 PSIL_CFG_PEER_CREDIT_CNT_MASK,
					 loc_credit_cnt);
		r = psil_cfg_write(inst, src_thrd,
				   PSIL_PROXY_CMDB_ADDRESS_PEER_CREDIT,
				   peer_credit_reg, STRUE);
		if (r != SUCCESS) {
			/* Set of peer credit register failed despite
			 * previous proxy transaction to set peer thread ID
			 * reg completing: halt */
			r = -ECONFUSED;
		}
	}

	if (r == SUCCESS) {
		r = psil_enable_thread(inst, dst_thrd);
		if (r == SUCCESS) {
			r = psil_enable_thread(inst, src_thrd);
			if (r != SUCCESS) {
				/* Enable of src thread failed despite previous
				 * proxy transaction to enable dst thread
				 * completing: halt */
				r = -ECONFUSED;
			}
		}
	}

	return r;
}

/**
 * \brief Unpairs the source thread from the destination thread
 *
 * If a thread maps to a UDMAP channel the UDMAP driver's channel thread ID
 * programming API is called to clear the channel's peer thread ID.
 *
 * \param inst PSI-L instance
 *
 * \param src_thrd Source thread
 *
 * \param dst_thrd Destination thread
 *
 * \return SUCCESS if unpairing is successful, else -EFAIL
 */
static s32 psil_unpair(const struct psil_instance *inst, u32 src_thrd,
		       u32 dst_thrd)
{
	s32 r = SUCCESS;
	u32 peer_thrd_id_reg, peer_credit_reg;

	r = psil_disable_thread(inst, src_thrd);
	if (r == SUCCESS) {
		r = psil_disable_thread(inst, dst_thrd);
		if (r != SUCCESS) {
			/* Disable of dst thread failed despite previous
			 * proxy transaction to disable src thread
			 * completing: halt */
			r = -ECONFUSED;
		}
	}

	if (r == SUCCESS) {
		/* Clear the peer thread ID register */
		peer_thrd_id_reg = rm_fmk(PSIL_CFG_PEER_THREAD_ID_WIDTH_SHIFT,
					  PSIL_CFG_PEER_THREAD_ID_WIDTH_MASK,
					  PSIL_CFG_PEER_THREAD_ID_WIDTH_RESET);
		peer_thrd_id_reg |= rm_fmk(
			PSIL_CFG_PEER_THREAD_ID_THREAD_ID_SHIFT,
			PSIL_CFG_PEER_THREAD_ID_THREAD_ID_MASK,
			PSIL_CFG_PEER_THREAD_ID_THREAD_ID_RESET);

		r = psil_cfg_write(inst, src_thrd,
				   PSIL_PROXY_CMDB_ADDRESS_PEER_THREAD_ID,
				   peer_thrd_id_reg, STRUE);
		if (r != SUCCESS) {
			/* Clear of peer thread ID register failed despite
			 * previous proxy transactions to disable threads
			 * completing: halt */
			r = -ECONFUSED;
		}
	}

	if (r == SUCCESS) {
		/* Clear the peer credit register */
		peer_credit_reg = rm_fmk(PSIL_CFG_PEER_CREDIT_CNT_SHIFT,
					 PSIL_CFG_PEER_CREDIT_CNT_MASK,
					 PSIL_CFG_PEER_CREDIT_CNT_RESET);
		r = psil_cfg_write(inst, src_thrd,
				   PSIL_PROXY_CMDB_ADDRESS_PEER_CREDIT,
				   peer_credit_reg, STRUE);
		if (r != SUCCESS) {
			/* Clear of peer credit register failed despite
			 * previous proxy transactions to disable threads
			 * and clear peer thread ID reg completing: halt */
			r = -ECONFUSED;
		}
	}

	return r;
}

/**
 * \brief Calls remote SoC subsystem drivers to configure additional
 *        thread-based registers
 *
 * Some SoC subsystems (currently only UDMAP) require additional configure when
 * two threads are paired.  Typically, a thread maps to an element within the
 * remote subsystem.  The remote element contains a register that must be set
 * to the thread ID to which it's mapped thread is paired.
 *
 * \param inst PSI-L instance
 *
 * \param src_thrd Source thread
 *
 * \param dst_thrd Destination thread
 *
 * \param clear Clears the remote subsystem registers if STRUE, sets them to
 *              thread value if SFALSE
 *
 * \return SUCCESS if remote driver programming is successful, else error
 */
static s32 psil_set_dev_thrd_id(const struct psil_instance *inst, u32 src_thrd,
				u32 dst_thrd, sbool clear)
{
	s32 r = SUCCESS;
	u8 i;
	const struct psil_thread_type *thread_type;
	sbool program_src = SFALSE;
	sbool program_dst = SFALSE;
	u32 index;

	/* UDMAP channel THRD_ID registers must be set to the thread ID to
	 * which the channel has been paired.  Call UDMAP to perform the
	 * programming */

	for (i = 0; i < inst->n_src_thread_type; i++) {
		thread_type = &inst->src_thread_types[i];
		if ((src_thrd >= thread_type->start) &&
		    (src_thrd <= thread_type->end)) {
			if (thread_type->dev_id != SOC_DEV_NONE) {
				program_src = STRUE;
			}
			break;
		}
	}

	if (program_src == STRUE) {
		index = src_thrd - thread_type->start;
		if (clear == SFALSE) {
			/* Program UDMAP tx ch THRD_ID register with
			 * destination thread ID */
			r = rm_udmap_set_thrd_id(thread_type->dev_id, index,
						 STRUE, dst_thrd);
		} else {
			/* Clear the UDMAP tx ch THRD_ID register */
			r = rm_udmap_set_thrd_id(thread_type->dev_id, index,
						 STRUE,
						 RM_UDMAP_THRD_ID_RESETVAL);
		}
	}

	for (i = 0; i < inst->n_dst_thread_type; i++) {
		thread_type = &inst->dst_thread_types[i];
		if ((dst_thrd >= thread_type->start) &&
		    (dst_thrd <= thread_type->end)) {
			if (thread_type->dev_id != SOC_DEV_NONE) {
				program_dst = STRUE;
			}
			break;
		}
	}

	if ((r == SUCCESS) && (program_dst == STRUE)) {
		index = dst_thrd - thread_type->start;
		if (clear == SFALSE) {
			/* Program UDMAP rx ch THRD_ID register with
			 * source thread ID */
			r = rm_udmap_set_thrd_id(thread_type->dev_id, index,
						 SFALSE, src_thrd);
		} else {
			/* Clear the UDMAP rx ch THRD_ID register */
			r = rm_udmap_set_thrd_id(thread_type->dev_id, index,
						 SFALSE,
						 RM_UDMAP_THRD_ID_RESETVAL);
		}
	}

	return r;
}

/**
 * \brief Disable a thread previously used by ROM
 *
 * \param inst Pointer to PSI-L instance
 *
 * \param thread PSI-L thread
 *
 * \return SUCCESS if no disable needed or if disable succeeds, else -EFAIL
 */
static s32 psil_disable_rom_thread(const struct psil_instance *inst, u16 thread)
{
	s32 r = SUCCESS;
	u8 i;
	struct psil_used_thread *used_thread;

	for (i = 0U; i < PSIL_ROM_USAGE_CNT; i++) {
		used_thread = &psil_rom_usage[i];

		if ((used_thread->disabled == SFALSE) &&
		    (used_thread->thread == thread)) {
			/*
			 * Disable PSI-L thread used by ROM prior to SYSFW boot.
			 * Doesn't matter which psil instance is used.
			 */
			r = psil_disable_thread(inst, thread);
			used_thread->disabled = STRUE;
			break;
		}
	}

	return r;
}

/**
 * \brief PSI-L thread pairing message handler
 *
 * \param msg_recv TISCI message
 *
 * \return SUCCESS if message processed successfully, else error
 */
static s32 psil_pair_msg_handler(u32 *msg_recv)
{
	s32 r = SUCCESS;
	struct tisci_msg_rm_psil_pair_req *msg =
		(struct tisci_msg_rm_psil_pair_req *) msg_recv;
	struct tisci_msg_rm_psil_pair_resp *resp =
		(struct tisci_msg_rm_psil_pair_resp *) msg_recv;
	const struct psil_instance *inst = NULL;
	u8 trace_action = TRACE_RM_ACTION_PSIL_PAIR;

	inst = psil_get_inst(msg->nav_id, trace_action);
	if (inst == NULL) {
		r = -EINVAL;
	}

	if (r == SUCCESS) {
		r = psil_validate_thread(inst, msg->src_thread);
		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
		}

		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_PSIL_SRC_THREAD,
			     msg->src_thread);
	}
	if (r == SUCCESS) {
		r = psil_validate_thread(inst, msg->dst_thread);
		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
		}

		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_PSIL_DST_THREAD,
			     msg->dst_thread);
	}

	/*
	 * Now that basic validation has been performed check for ROM usage
	 * and disable any ROM used threads prior to the thread enable
	 * validation
	 */
	if (r == SUCCESS) {
		r = psil_disable_rom_thread(inst, msg->src_thread);
	}
	if (r == SUCCESS) {
		r = psil_disable_rom_thread(inst, msg->dst_thread);
	}

	if (r == SUCCESS) {
		r = psil_validate_thread_enable_status(inst,
						       msg->src_thread,
						       PSIL_CFG_ENABLE_ENABLE_ENABLED);
		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
			rm_trace_sub(trace_action,
				     TRACE_RM_SUB_ACTION_PSIL_THREAD_ENABLED,
				     msg->src_thread);
		}
	}
	if (r == SUCCESS) {
		r = psil_validate_thread_enable_status(inst,
						       msg->dst_thread,
						       PSIL_CFG_ENABLE_ENABLE_ENABLED);
		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
			rm_trace_sub(trace_action,
				     TRACE_RM_SUB_ACTION_PSIL_THREAD_ENABLED,
				     msg->dst_thread);
		}
	}

	if (r == SUCCESS) {
		r = psil_pair(inst, msg->src_thread, msg->dst_thread);
	}

	if (r == SUCCESS) {
		/* Some SoC devices require additional programming of thread
		 * registers.  Do that now that pairing has been setup */
		r = psil_set_dev_thrd_id(inst, msg->src_thread,
					 msg->dst_thread, SFALSE);
		if (r != SUCCESS) {
			/* Setting of device thread ID register failed despite
			 * threads being valid and pairing succeeding: halt */
			r = -ECONFUSED;
		}
	}

	r = rm_core_send_response((struct tisci_header *) resp,
				  sizeof(*resp),
				  r);

	return r;
}

/**
 * \brief PSI-L thread unpairing message handler
 *
 * \param msg_recv TISCI message
 *
 * \return SUCCESS if message processed successfully, else error
 */
static s32 psil_unpair_msg_handler(u32 *msg_recv)
{
	s32 r = SUCCESS;
	struct tisci_msg_rm_psil_unpair_req *msg =
		(struct tisci_msg_rm_psil_unpair_req *) msg_recv;
	struct tisci_msg_rm_psil_unpair_resp *resp =
		(struct tisci_msg_rm_psil_unpair_resp *) msg_recv;
	const struct psil_instance *inst = NULL;
	u32 peer_thrd_dst;
	u8 trace_action = TRACE_RM_ACTION_PSIL_UNPAIR;

	inst = psil_get_inst(msg->nav_id, trace_action);
	if (inst == NULL) {
		r = -EINVAL;
	}

	if (r == SUCCESS) {
		r = psil_validate_thread(inst, msg->src_thread);
		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
		}

		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_PSIL_SRC_THREAD,
			     msg->src_thread);
		if (r == SUCCESS) {
			r = psil_validate_thread_enable_status(inst,
							       msg->src_thread,
							       PSIL_CFG_ENABLE_ENABLE_DISABLED);
			if (r != SUCCESS) {
				trace_action |= TRACE_RM_ACTION_FAIL;
				rm_trace_sub(trace_action,
					     TRACE_RM_SUB_ACTION_PSIL_THREAD_DISABLED,
					     msg->src_thread);
			}
		}
	}

	if (r == SUCCESS) {
		r = psil_validate_thread(inst, msg->dst_thread);
		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
		}

		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_PSIL_DST_THREAD,
			     msg->dst_thread);
		if (r == SUCCESS) {
			r = psil_validate_thread_enable_status(inst,
							       msg->dst_thread,
							       PSIL_CFG_ENABLE_ENABLE_DISABLED);
			if (r != SUCCESS) {
				trace_action |= TRACE_RM_ACTION_FAIL;
				rm_trace_sub(trace_action,
					     TRACE_RM_SUB_ACTION_PSIL_THREAD_DISABLED,
					     msg->dst_thread);
			}
		}
	}

	if (r == SUCCESS) {
		/* Source thread must have destination thread as its peer
		 * destination thread */
		r = psil_get_src_peer_thread(inst, msg->src_thread,
					     &peer_thrd_dst);
		if ((r == SUCCESS) && (peer_thrd_dst != msg->dst_thread)) {
			trace_action |= TRACE_RM_ACTION_FAIL;
			r = -EINVAL;
		}

		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_PSIL_SRC_THREAD_PEER,
			     peer_thrd_dst);
	}

	if (r == SUCCESS) {
		r = psil_unpair(inst, msg->src_thread, msg->dst_thread);
	}

	if (r == SUCCESS) {
		/* Some SoC devices require additional programming of thread
		 * registers.  Clear the them now that unpair is complete */
		r = psil_set_dev_thrd_id(inst, msg->src_thread,
					 msg->dst_thread, STRUE);
		if (r != SUCCESS) {
			/* Clearing of device thread ID register failed despite
			 * threads being valid and unpairing succeeding: halt */
			r = -ECONFUSED;
		}
	}

	r = rm_core_send_response((struct tisci_header *) resp,
				  sizeof(*resp),
				  r);

	return r;
}

/**
 * \brief PSI-L thread read message handler
 *
 * \param msg_recv TISCI message
 *
 * \return SUCCESS if message processed successfully, else error
 */
static s32 psil_read_msg_handler(u32 *msg_recv)
{
	s32 r = SUCCESS;
	struct tisci_msg_rm_psil_read_req *msg =
		(struct tisci_msg_rm_psil_read_req *) msg_recv;
	struct tisci_msg_rm_psil_read_resp *resp =
		(struct tisci_msg_rm_psil_read_resp *) msg_recv;
	const struct psil_instance *inst = NULL;
	u32 value = 0U;
	u8 trace_action = TRACE_RM_ACTION_PSIL_READ;

	inst = psil_get_inst(msg->nav_id, trace_action);
	if (inst == NULL) {
		r = -EINVAL;
	}

	if (r == SUCCESS) {
		r = psil_validate_thread(inst, msg->thread);
		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
		}

		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_PSIL_THREAD,
			     msg->thread);
	}

	if (r == SUCCESS) {
		r = psil_cfg_read(inst, msg->thread, msg->taddr, &value);
		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
		}

		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_PSIL_THREAD_CFG_REG_ADDR,
			     msg->taddr);
		if (r == SUCCESS) {
			rm_trace_sub(trace_action,
				     TRACE_RM_SUB_ACTION_PSIL_THREAD_CFG_REG_VAL_HI,
				     ((value >> 16U) & TRACE_DEBUG_SUB_ACTION_VAL_MASK));
			rm_trace_sub(trace_action,
				     TRACE_RM_SUB_ACTION_PSIL_THREAD_CFG_REG_VAL_LO,
				     (value & TRACE_DEBUG_SUB_ACTION_VAL_MASK));
		}
	}

	if (r == SUCCESS) {
		resp->data = value;
	}

	r = rm_core_send_response((struct tisci_header *) resp,
				  sizeof(*resp),
				  r);

	return r;
}

/**
 * \brief PSI-L thread write message handler
 *
 * \param msg_recv TISCI message
 *
 * \return SUCCESS if message processed successfully, else error
 */
static s32 psil_write_msg_handler(u32 *msg_recv)
{
	s32 r = SUCCESS;
	struct tisci_msg_rm_psil_write_req *msg =
		(struct tisci_msg_rm_psil_write_req *) msg_recv;
	struct tisci_msg_rm_psil_write_resp *resp =
		(struct tisci_msg_rm_psil_write_resp *) msg_recv;
	const struct psil_instance *inst = NULL;
	u8 trace_action = TRACE_RM_ACTION_PSIL_WRITE;

	inst = psil_get_inst(msg->nav_id, trace_action);
	if (inst == NULL) {
		r = -EINVAL;
	}

	if (r == SUCCESS) {
		r = psil_validate_thread(inst, msg->thread);
		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
		}

		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_PSIL_THREAD,
			     msg->thread);
	}

	if (r == SUCCESS) {
		/*
		 * Do not read back and verify because format of RT registers
		 * is not known.  It's up to the application to use the
		 * psil_pair message to perform its own read back verify
		 */
		r = psil_cfg_write(inst, msg->thread, msg->taddr, msg->data,
				   SFALSE);
		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
		}

		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_PSIL_THREAD_CFG_REG_ADDR,
			     msg->taddr);
		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_PSIL_THREAD_CFG_REG_VAL_HI,
			     ((msg->data >> 16U) & TRACE_DEBUG_SUB_ACTION_VAL_MASK));
		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_PSIL_THREAD_CFG_REG_VAL_LO,
			     (msg->data & TRACE_DEBUG_SUB_ACTION_VAL_MASK));
	}

	r = rm_core_send_response((struct tisci_header *) resp,
				  sizeof(*resp),
				  r);

	return r;
}

static struct tisci_client tisci_msg_rm_psil_pair = {
	.handler	= psil_pair_msg_handler,
	.subsystem	= SUBSYSTEM_RM,
};

static struct tisci_client tisci_msg_rm_psil_unpair = {
	.handler	= psil_unpair_msg_handler,
	.subsystem	= SUBSYSTEM_RM,
};

static struct tisci_client tisci_msg_rm_psil_read = {
	.handler	= psil_read_msg_handler,
	.subsystem	= SUBSYSTEM_RM,
};

static struct tisci_client tisci_msg_rm_psil_write = {
	.handler	= psil_write_msg_handler,
	.subsystem	= SUBSYSTEM_RM,
};

s32 rm_psil_get_dru_dst_offset(u16 nav_id, u16 *dru_dst_offset)
{
	s32 r = SUCCESS;
	const struct psil_instance *inst = NULL;
	u8 trace_action = TRACE_RM_ACTION_PSIL_DRU_DST_OFFSET;

	inst = psil_get_inst(nav_id, trace_action);
	if (inst == NULL) {
		r = -EINVAL;
	} else {
		*dru_dst_offset = inst->dru_ch0_dst_thread_offset;
		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_PSIL_THREAD,
			     *dru_dst_offset);
	}

	return r;
}

s32 rm_psil_init(void)
{
	s32 r = SUCCESS;

	if (r == SUCCESS) {
		r = tisci_user_client_register(TISCI_MSG_RM_PSIL_PAIR,
					       &tisci_msg_rm_psil_pair);
	}

	if (r == SUCCESS) {
		r = tisci_user_client_register(TISCI_MSG_RM_PSIL_UNPAIR,
					       &tisci_msg_rm_psil_unpair);
	}

	if (r == SUCCESS) {
		r = tisci_user_client_register(TISCI_MSG_RM_PSIL_READ,
					       &tisci_msg_rm_psil_read);
	}

	if (r == SUCCESS) {
		r = tisci_user_client_register(TISCI_MSG_RM_PSIL_WRITE,
					       &tisci_msg_rm_psil_write);
	}

	if (r != SUCCESS) {
		rm_trace_sub(TRACE_RM_ACTION_PSIL_INIT |
			     TRACE_RM_ACTION_FAIL, 0U, 0U);
	}

	return r;
}
