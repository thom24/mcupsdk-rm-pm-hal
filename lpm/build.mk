cppflags-$(CONFIG_LPM_DM_STUB) += -I$(srctree)/lpm/include
cppflags-$(CONFIG_LPM_DM_STUB) += -I$(srctree)/pm/include
cppflags-$(CONFIG_LPM_DM_STUB) += -I$(srctree)/lpm/include/soc/$(TARGET_SOC)

obj-y += soc/

obj-y += main.o
obj-y += psc_raw.o
obj-y += pll_16fft_raw.o
