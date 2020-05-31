/*
 * System Firmware Source File
 *
 * Board Configuration Data Structures
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef BOARD_CFG_RM_H
#define BOARD_CFG_RM_H

#include <lib/bitops.h>
#include <types/ftbool.h>
#include <types/devgrps.h>
#include <types/short_types.h>
#include <hosts.h>

/**
 * \brief Contains a unique magic number for each substructure and the size
 *	  of the associated superstructure for data validation/API
 *	  compatibility checks.
 *
 * \param magic Unique magic number for data integrity check.
 * \param size `sizeof(superstructure containing this header)` for data
 *	       integrity check.
 */
struct boardcfg_substructure_rm_header {
	u16	magic;
	u16	size;
} __attribute__((__packed__));

/**
 * \brief Board Config data ABI version.
 *
 * \param boardcfg_abi_maj Major Board Config data ABI version.
 * \param boardcfg_abi_min Minor Board Config data ABI version.
 */
struct boardcfg_abi_rm_rev {
	u8	boardcfg_abi_maj;
	u8	boardcfg_abi_min;
} __attribute__((__packed__));

/**
 * \brief Resource Management host ID configuration entry describing a
 *        host's allowed system priorities as well as a host's supervisor
 *
 * \param host_id Processing entity host ID
 *
 * \param allowed_qos Allowed QoS level configuration for host ID:
 *
 *                    The host ID gets assigned a list of QoS levels which
 *                    are allowed. As QoS level is a 3-bit field, there are
 *                    8 possible order-IDs. Thus in one 16-bit word, flags
 *                    are set specifying whether or not the QoS level is
 *                    allowed for the host ID. For each QoS level, the value
 *                    of 01b means not allowed, 10b means allowed, and 11b
 *                    and 00b are invalid/errors. These are encoded in a
 *                    bitfield because there is one set of allowed QoS levels
 *                    for every host ID.
 *
 * \param allowed_orderid Allowed order-ID configuration for the host ID:
 *
 *                        The host ID gets assigned a list of order-IDs which
 *                        are allowed. As order-ID is a 4-bit field, there are
 *                        16 possible order-IDs. Thus in one 32-bit word, flags
 *                        are set specifying whether or not the order-ID is
 *                        allowed for the host ID. For each order-ID, the value
 *                        of 01b means not allowed, 10b means allowed, and 11b
 *                        and 00b are invalid/errors. These are encoded in a
 *                        bitfield because there is one set of allowed
 *                        order-IDs for every host ID.
 *
 * \param allowed_atype Allowed atype configuration for the host ID:
 *
 *                      The host ID gets assigned a list of atypes which
 *                      are allowed. atype is a 2-bit field with 3 possible
 *                      values. Thus in one 8-bit word, flags are set
 *                      specifying whether or not an atype value is
 *                      allowed for the host ID. For each atype, the value
 *                      of 01b means not allowed, 10b means allowed, and 11b
 *                      and 00b are invalid/errors. These are encoded in a
 *                      bitfield because there is one set of allowed atypes
 *                      for every host ID.
 *
 * \param allowed_priority Allowed bus priority configuration for host ID:
 *
 *                         The host ID gets assigned a list of bus priorities
 *                         which are allowed. As bus priority is a 3-bit field,
 *                         there are 8 possible bus priorities. Thus in one
 *                         16-bit word, flags are set specifying whether or not
 *                         the bus priority is allowed for the host ID. For each
 *                         bus priority, the value of 01b means not allowed,
 *                         10b means allowed, and 11b and 00b are
 *                         invalid/errors. These are encoded in a bitfield
 *                         because there is one set of allowed bus priorities
 *                         for every host ID.
 *
 * \param allowed sched_priority Allowed UDMAP channel scheduling priority
 *                               configuration for host ID:
 *
 *                               The host ID gets assigned a list of UDMAP
 *                               channel scheduling priorities which are
 *                               allowed. As UDMAP channel scheduling priority
 *                               is a 2-bit field, there are 4 possible UDMAP
 *                               channel scheduling priorities. Thus in one
 *                               8-bit word, flags are set specifying whether or
 *                               not UDMAP channel scheduling priority is
 *                               allowed for the host ID. For each priority, the
 *                               value of 01b means not allowed, 10b means
 *                               allowed, and 11b and 00b are invalid/errors.
 *                               These are encoded in a bitfield because there
 *                               is one set of allowed UDMAP channel scheduling
 *                               priorities for every host ID.
 */
struct boardcfg_rm_host_cfg_entry {
	u8	host_id;
	u8	allowed_atype;
	u16	allowed_qos;
	u32	allowed_orderid;
	u16	allowed_priority;
	u8	allowed_sched_priority;
} __attribute__((__packed__));

/* \brief How many host configuration list entries */
#define BOARDCFG_RM_HOST_CFG_ENTRIES (32U)

/**
 * \brief Resource Management host ID configuration describing a host's allowed
 *        system priorities
 *
 * \param subhdr Magic and size for integrity check.
 * \param host_cfg_entries @ref boardcfg_rm_host_cfg_entry entries up to
 *                         @ref BOARDCFG_RM_HOST_CFG_ENTRIES
 */
struct boardcfg_rm_host_cfg {
	struct boardcfg_substructure_rm_header	subhdr;
	struct boardcfg_rm_host_cfg_entry	host_cfg_entries[
		BOARDCFG_RM_HOST_CFG_ENTRIES];
};

/**
 * \brief One contiguous block of any resource to be assigned to one
 *	  processing entity.
 *
 * \param start_resource First resource number (inclusive) for a host_id
 *			 and resource.
 * \param num_resource Number of continuous resources allocated to a
 *		       host_id and resource. 0 means unused.
 * \param type Unique type value identifying the specific resource to which the
 *             range assignment applies
 * \param host_id Processing entity host ID to which the resource range is
 *                assigned
 */
struct boardcfg_rm_resasg_entry {
	u16	start_resource;
	u16	num_resource;
	u16	type;
	u8	host_id;
	u8	reserved;
};

/**
 * \brief RM boardcfg resource assignment configuration.
 *
 * \param subhdr Magic and size for integrity check.
 * \param resasg_entries_size Size of resasg_entries array in bytes
 * \param resasg_entries Array of @ref boardcfg_rm_resasg_entry containing
 *                       resource range assignments to hosts.
 */
struct boardcfg_rm_resasg {
	struct boardcfg_substructure_rm_header	subhdr;
	u16					resasg_entries_size;
	u16					reserved;
	struct boardcfg_rm_resasg_entry		resasg_entries[];
} __attribute__((__packed__));

/**
 * \brief Resource Management configuration.
 *
 * \param rev Resource Management board config ABI version (separate from Board
 *            Config ABI version)
 * \param host_cfg Array of host configuration structures.
 * \param resasg Resource assignment configuration structure.
 */
struct boardcfg_rm {
	struct boardcfg_abi_rm_rev		rev;
	struct boardcfg_rm_host_cfg	host_cfg;
	struct boardcfg_rm_resasg	resasg;
} __attribute__((__packed__));

/**
 * \brief Get a pointer to the local copy of the boardcfg_rm_host_cfg data.
 *
 * \return NULL if the local RM board data has not yet been received or is
 *         invalid, pointer otherwise.
 */
const struct boardcfg_rm_host_cfg *boardcfg_get_rm_host_cfg(void);

/**
 * \brief Get a the size of the local copy of the boardcfg_rm_resasg_entry data.
 *
 * \return Zero if the local RM board data has not yet been received or is
 *         invalid, greater than zero otherwise.
 */
u16 boardcfg_get_rm_resasg_size(void);

/**
 * \brief Get a pointer to the local copy of the boardcfg_rm_resasg data.
 *
 * \return NULL if the local RM board data has not yet been received or is
 *         invalid, pointer otherwise.
 */
const struct boardcfg_rm_resasg_entry *boardcfg_get_rm_resasg(void);

/**
 * \brief Get the RM device group from the local boardcfg_rm data.
 *
 * \param devgrp Pointer to a device group variable in which the device group
 *        is returned on SUCCESS
 *
 * \return EINIT if the local RM board data has not yet been received or is
 *         invalid, SUCCESS if in the board data has been received and is valid.
 */
s32 boardcfg_get_rm_devgrp(devgrp_t *devgrp);

#endif          /* BOARD_CFG_RM_H */
