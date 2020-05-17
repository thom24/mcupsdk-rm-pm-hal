ifneq ($(CONFIG_PM),)

obj-y +=			dmsc.o
obj-$(CONFIG_CLOCK) +=		clocks.o
obj-$(CONFIG_CLOCK) +=		clk_soc_hfosc0.o
obj-y +=			devices.o
obj-y +=			host_idx_mapping.o

endif

_src := $(src)
cppflags-y += -I$(_src)/include
