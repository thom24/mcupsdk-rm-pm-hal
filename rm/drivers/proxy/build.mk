# Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
# ALL RIGHTS RESERVED

cppflags-y += -I$(srctree)/rm_pm_hal/rm/drivers/proxy/include
cppflags-y += -I$(srctree)/rm_pm_hal/rm/drivers/proxy/soc/$(TARGET_SOC)

obj-$(CONFIG_RM_PROXY) += rm_proxy.o

obj-$(CONFIG_RM_PROXY) += soc/
