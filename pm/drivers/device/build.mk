obj-y +=		device.o
obj-y +=		resource.o

obj-$(CONFIG_CLOCK) +=	device_clk.o
obj-$(CONFIG_PM) +=	device_pm.o

obj-$(CONFIG_PSC) +=	device_psc.o
