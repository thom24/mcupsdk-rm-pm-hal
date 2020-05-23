# Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
# ALL RIGHTS RESERVED

cppflags-y += -I$(srctree)/rm_pm_hal/rm/drivers/ir/include
cppflags-y += -I$(srctree)/rm_pm_hal/rm/drivers/ir/soc/$(TARGET_SOC)/

obj-$(CONFIG_RM_IRQ) += rm_ir.o

obj-$(CONFIG_RM_IRQ) += soc/
