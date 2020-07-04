# Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
# ALL RIGHTS RESERVED

INCLUDE_THIS_FILE=n
ifeq ($(CONFIG_PM),y)
INCLUDE_THIS_FILE=y
endif
ifeq ($(CONFIG_RM),y)
INCLUDE_THIS_FILE=y
endif

obj-$(INCLUDE_THIS_FILE) += boardcfg-user.o
obj-$(INCLUDE_THIS_FILE) += $(TARGET_SOC)/
