# Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
# ALL RIGHTS RESERVED

cppflags-y += -I$(srctree)/rm_pm_hal/rm/core/soc/$(TARGET_SOC)

obj-$(CONFIG_RM) += rm.o
obj-$(CONFIG_RM) += rm_core.o
