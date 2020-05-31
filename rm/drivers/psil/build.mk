# Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
# ALL RIGHTS RESERVED

cppflags-y += -I$(srctree)/rm_pm_hal/rm/drivers/psil/include
cppflags-y += -I$(srctree)/rm_pm_hal/rm/drivers/psil/soc/$(TARGET_SOC)

obj-$(CONFIG_RM_PSIL) += rm_psil.o

obj-$(CONFIG_RM_PSIL) += soc/
