/*
 * Proxy
 *
 * proxy driver instance definition
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef PROXY_INST_H
#define PROXY_INST_H

#include <types/short_types.h>
#include <types/devgrps.h>
#include <soc/rm_mmr.h>
#include <rm_irq.h>

/**
 * \brief
 * proxy instance containing all data required to manage a
 * Navigator Subsystem proxy
 *
 * \param id
 * Device ID of NavSS proxy
 *
 * \param initialized
 * Instance initialization flag
 *
 * \param devgrp
 * Device group to which instance belongs
 *
 * \param cfg
 * Proxy subsystem's OES MMR region
 *
 * \param target0_data
 * Proxy subsystem's target data control MMR region
 *
 * \param n_proxies
 * Total number of proxies in the subsystem
 *
 * \param proxy_utype
 * Resource assignment type mapped to proxies
 *
 * \param oes_handler
 * IRQ event source handler
 */
struct proxy_instance {
	const u16			id;
	sbool				initialized;
	const devgrp_t			devgrp;
	const struct rm_mmr *const	cfg;
	const struct rm_mmr *const	target0_data;
	const u16			n_proxies;
	const u16			proxy_utype;
	struct rm_irq_oes_src		oes_handler;
};

#endif /* PROXY_INST_H */
