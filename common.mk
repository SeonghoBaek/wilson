#####################################################
# Makefile for Nodebus
# Any qustion : sanghyeun.kim@lge.com
#####################################################
#====================================================
# Common Variable Definitions
#====================================================
SHELL = /bin/bash

ifeq ($(MAKECMDGOALS),)
	.DEFAULT_GOAL  := all
else

ifeq ($(MAKECMDGOALS),target)
include $(TOP_DIR)/target.inc	
endif

endif

ifeq ($(PLATFORM),PIONEER)
LIB_OUT := $(PWD)/lib/target
BIN_OUT := $(PWD)/bin/target
$(shell mkdir -p $(LIB_OUT))
$(shell mkdir -p $(BIN_OUT))
else
LIB_OUT := $(PWD)/lib
BIN_OUT := $(PWD)/bin
endif

#====================================================
# Common Build flags 
#====================================================
CXXCFLAGS :=
#CXXCFLAGS += -g -O2 -Wall -MMD
CXXCFLAGS += -g -O2 -MMD

CXXLFLAGS := 
CXXLFLAGS += -L$(LIB_OUT)

ifeq ($(PLATFORM),PIONEER)
CXXCFLAGS += $(MACH_OPT)
CXXLFLAGS += -L$(TOP_DIR)/lib/arm
endif
#CXXLFLAGS += -L$(TOP_DIR)/lib/x86
#endif

#====================================================
