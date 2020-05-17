/*
 * System Firmware Early PLL low level PLL init code
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef PLL_EARLY_H
#define PLL_EARLY_H
#include <types/address_types.h>
#include <types/short_types.h>
#include <types/devgrps.h>

#define INCLK_MAX 6

struct pll_early_data_entry {
	u16	pllm;
	u32	pllfm;
	u16	plld;
	u8	od;
	u8	post_div2;
};

struct pll_early_data {
	mapped_addr_t			base;
	struct pll_early_data_entry	pll_entries[INCLK_MAX];
	u16				hsdiv_defaults[10];
};

/**
 * \brief Devgrp description for early initialization logic
 * \param devgrp what devgrp this belongs to
 * \param early_pll_pllctrls NULL terminated list of PLL ctrl base
 * \param *early_plls_cfgs NULL terminated list of pll configs
 */
struct pll_early_devgrp_data {
	devgrp_t			devgrp;
	const u32			*early_pll_pllctrls;
	const struct pll_early_data	**early_plls_cfgs[];
};

/* NULL terminated list, should be of size at least 1 and at most MAX_NUM_DEVGRPS */
extern const struct pll_early_devgrp_data *const early_pll_devgrp[];

s32 pll_early_config(devgrp_t devgrp);

#endif /* PLL_EARLY_H */
