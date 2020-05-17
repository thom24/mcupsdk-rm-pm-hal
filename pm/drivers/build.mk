ifneq ($(CONFIG_PM),)

obj-$(CONFIG_CLOCK) += clock/
obj-y += device/

obj-$(CONFIG_PSC) += psc/
obj-y += misc/

endif
