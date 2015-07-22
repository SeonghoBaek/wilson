#############################################################################
# Makefile for ARM target board 
#############################################################################

#-----------------------------------------------------------------------------
#		Toolchain Definition
#-----------------------------------------------------------------------------
CROSS_TOOL              :=   arm-lg115x-linux-gnueabi-
CC						:=   $(CROSS_TOOL)gcc
CXX						:=   $(CROSS_TOOL)g++
AS						:=   $(CROSS_TOOL)as
AR						:=   $(CROSS_TOOL)ar
LD						:=   $(CROSS_TOOL)ld
STRIP                   :=   $(CROSS_TOOL)strip
OBJCOPY                 :=   $(CROSS_TOOL)objcopy
NM                      :=   $(CROSS_TOOL)nm -na
#-----------------------------------------------------------------------------
#		Arch. Specifi Build Options 
#-----------------------------------------------------------------------------
MACH_OPT	:= 
MACH_OPT	+= -D__ARM__
MACH_OPT	+= -D__LINUX_ARM_ARCH__=7
MACH_OPT	+= -march=armv7-a
MACH_OPT	+= -msoft-float -mfloat-abi=softfp
#-----------------------------------------------------------------------------
# Variables Definition 	
#-----------------------------------------------------------------------------

PLATFORM	:= PIONEER
ARCH	:= arm
TOOLCHAIN_PATH := $(PATH):/home/utils/toolchain/arm-lg115x-linux-gnueabi-2012.09_nc4/bin

export PLATFORM ARCH  
export PATH	:= $(TOOLCHAIN_PATH)

#############################k################################################
