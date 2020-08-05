# Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
# ALL RIGHTS RESERVED

ifneq ($(CONFIG_PM),)

obj-$(CONFIG_CLOCK) +=		clocks.o
obj-$(CONFIG_CLOCK) +=		clk_mux_j7_dpi.o
obj-$(CONFIG_CLOCK) +=		clk_soc_hfosc0.o
obj-$(CONFIG_CLOCK) +=		clk_mux_j7_ahclko.o
obj-y +=			devices.o
obj-y +=			dmsc.o
obj-y +=			host_idx_mapping.o

endif
_src := $(src)
cppflags-y += -I$(_src)/include
