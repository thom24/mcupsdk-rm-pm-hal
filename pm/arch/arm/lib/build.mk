ifneq ($(CONFIG_PM),)

obj-y += ll_lsr16.o
obj-y += ll_lsl16.o
obj-y += ll_mul16.o
obj-y += umull16.o


endif
