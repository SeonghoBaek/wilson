#####################################################
# Makefile for Nodebus
# Any qustion : sanghyeun.kim@lge.com
#####################################################
TOP_DIR	:= $(shell pwd)/..
include $(TOP_DIR)/common.mk

src_dir := src
objs_dir := src/objs
lib_dir := $(LIB_OUT)
bin_dir := $(BIN_OUT)
include_dirs := include  /usr/include/libxml2

#====================================================
# Source file 
#====================================================
SRC = 
SRC += Log.cpp
SRC += Lock.cpp
SRC += Queue.cpp
SRC += XMLParser.cpp
SRC += Bridge.cpp
SRC += NodeNetwork.cpp
SRC += NodePort.cpp
SRC += NodeLooper.cpp
SRC += INodeBusService.cpp
SRC += DefaultService.cpp
SRC += DefaultGlobalService.cpp
SRC += Packet.cpp
SRC += BigNode.cpp
SRC += ClientNode.cpp
SRC += Normalizer.cpp


SRCS += $(addprefix $(src_dir)/,$(SRC)) 

LOCAL = LocalBusInit.cpp
LOCALS += $(addprefix $(src_dir)/,$(LOCAL))

GLOBAL = GlobalBusInit.cpp
GLOBALS += $(addprefix $(src_dir)/,$(GLOBAL))

#====================================================
# Object file 
#====================================================
$(shell mkdir -p $(objs_dir))
SRCO = $(addprefix $(objs_dir)/,$(SRC))
SHARED_OBJS = $(subst .cpp,.o,$(SRCO))

LOCALO = $(addprefix $(objs_dir)/,$(LOCAL))
LOCAL_OBJS = $(subst .cpp,.o,$(LOCALO))

GLOBALO = $(addprefix $(objs_dir)/,$(GLOBAL))
GLOBAL_OBJS = $(subst .cpp,.o,$(GLOBALO))

#====================================================
# Local Build Flags 
#====================================================
L_CFLAGS := $(addprefix -I,$(include_dirs))
L_LFLAGS := -lxml2 -lpthread -lnbus
#====================================================
# Build Rules 
#====================================================
.PHONY: target all clean
target : all  ;
all : $(SHARED_OBJS) $(LOCAL_OBJS) $(GLOBAL_OBJS) 
	@echo -e "\t@@@ Building libnbus.so... "
	$(CXX) -shared -o $(lib_dir)/libnbus.so $(SHARED_OBJS) $(CXXLFLAGS) -lxml2 
	@echo -e "\t@@@ Building lbus... "
	$(CXX) -o $(bin_dir)/lbus $(LOCAL_OBJS) $(CXXLFLAGS) $(L_LFLAGS) 
	@echo -e "\t@@@ Building gbus... "
	$(CXX) -o $(bin_dir)/gbus $(GLOBAL_OBJS) $(CXXLFLAGS) $(L_LFLAGS) 
	
#	rm -f $(GLOBAL_OBJS) $(LOCAL_OBJS) $(SHARED_OBJS)

$(objs_dir)/%.o : $(src_dir)/%.cpp
	$(CXX) -fpic -c $< $(CXXCFLAGS) $(L_CFLAGS) -o $(@) 

clean : 
	rm -rf $(objs_dir) $(lib_dir)/*
	
#====================================================
