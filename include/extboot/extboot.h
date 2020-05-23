/*
 * System Firmware Source File
 *
 * Extended Boot Data Structures for supporting combined image format
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef EXT_BOOT_H
#define EXT_BOOT_H

#include <lib/bitops.h>
#include <types/ftbool.h>
#include <types/short_types.h>

/**
 * \brief Describes the board config data
 *
 * \param type Type of board config data. This should map to corresponding TISCI
 *		message type. For example, a PM boardcfg should have a descriptor
 *		type TISCI_MSG_BOARD_CONFIG_PM.
 * \param offset Offset for board config data from beginning of SYSFW data binary blob
 * \param size Size of board config data
 * \param devgrp Device group to be used by SYSFW for automatic board config processing
 * \param reserved Reserved field. Not to be used.
 */
struct extboot_boardcfg_desc {
	u16	type;
	u16	offset;
	u16	size;
	u8	devgrp;
	u8	reserved;
} __attribute__((__packed__));

#ifdef CONFIG_COMBINED_IMAGE
/**
 * \brief Check and validate extended boot structure placed by ROM
 *
 * \return SUCCESS if successful, error code otherwise
 *
 */
s32 extboot_init_and_validate(void);

/**
 * \brief Check if extended boot info is populated by ROM. If this boot info
 *		is not present, SYSFW will default to legacy boot flow.
 *
 * \return FT_TRUE if present, FT_FALSE if invalid
 *
 */
ftbool extboot_is_present(void);

/**
 * \brief Check if the board config data populated by ROM is valid.
 *
 * \return FT_TRUE if valid, FT_FALSE if invalid
 *
 */
ftbool extboot_is_valid(void);

/**
 * \brief get the status of extended boot
 *
 * \return status of extended boot
 *
 */
u32 extboot_get_status(void);

/**
 * \brief get the base address for boardcfg data blob.
 *
 * \return Base address of boardcfg data blob, 0 if invalid
 *
 */
u32 extboot_get_base(void);

/**
 * \brief get the size of boardcfg data blob.
 *
 * \return Size of boardcfg binary blob, 0 if invalid.
 *
 */
u32 extboot_get_size(void);

/**
 * \brief get the SW revision of boardcfg data blob.
 *
 * \return SW revision of boardcfg data blob
 *
 */
u8 extboot_get_swrev(void);

/**
 * \brief get the boardcfg data for a given boardcfg type. This function should be called
 *			only if extboot_boardcfg_is_valid() is FT_TRUE.
 *
 * \param type Type of boardcfg data. This should map to one of the TISCI message types
 *
 * \return Pointer to boardcfg data, NULL if invalid
 *
 */
const struct extboot_boardcfg_desc *extboot_boardcfg_get_desc(u16 type);


/**
 * \brief set the parse status after validating boardcfg data
 *
 * \param type Type of boardcfg data. This should map to one of the TISCI message types
 *
 * \return None
 *
 */
void extboot_boardcfg_set_valid(u16 type);

/**
 * \brief check if the specified boardcfg data is present
 *
 * \param type Type of boardcfg data. This should map to one of the TISCI message types
 *
 * \return FT_TRUE if present, FT_FALSE otherwise
 *
 */
ftbool extboot_boardcfg_is_present(u16 type);

/**
 * \brief check if the specified boardcfg data is valid
 *
 * \param type Type of boardcfg data. This should map to one of the TISCI message types
 *
 * \return FT_TRUE if valid, FT_FALSE otherwise
 *
 */
ftbool extboot_boardcfg_is_valid(u16 type);

#else

static inline s32 extboot_init_and_validate(void)
{
	return 0;
}

static inline ftbool extboot_is_present(void)
{
	return FT_FALSE;
}

static inline ftbool extboot_is_valid(void)
{
	return FT_FALSE;
}

static inline u32 extboot_get_status(void)
{
	return 0;
}

static inline u32 extboot_get_base(void)
{
	return 0;
}

static inline u32 extboot_get_size(void)
{
	return 0;
}

static inline u8 extboot_get_swrev(void)
{
	return 0;
}

static inline const struct extboot_boardcfg_desc *extboot_boardcfg_get_desc(u16 type __attribute__((unused)))
{
	return NULL;
}

static inline void extboot_boardcfg_set_valid(u16 type __attribute__((unused)))
{
}

static inline ftbool extboot_boardcfg_is_present(u16 type __attribute__((unused)))
{
	return FT_FALSE;
}

static inline ftbool extboot_boardcfg_is_valid(u16 type __attribute__((unused)))
{
	return FT_FALSE;
}

#endif

#endif
