#
# Top level Makefile
#
# Top level Makefile for RM/PM HAL
#
# Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
# ALL RIGHTS RESERVED
#

# No make, you have no idea what you are doing
.SUFFIXES:

# Please don't remove intermediate files
.SECONDARY:

Makefile: ;

BUILD_SRC ?= .
srctree = $(BUILD_SRC)
srcroot = $(srctree)

include $(srcroot)/build/build.githooks

FORCE:
PHONY += FORCE
.PHONY: $(PHONY)
