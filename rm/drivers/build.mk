# Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
# ALL RIGHTS RESERVED

obj-$(CONFIG_RM_IRQ) += irq/
obj-y += ir/
obj-y += ia/
obj-$(CONFIG_RM_RA) += ra/
obj-$(CONFIG_RM_UDMAP) += udmap/
obj-$(CONFIG_RM_PSIL) += psil/
obj-$(CONFIG_RM_PROXY) += proxy/
