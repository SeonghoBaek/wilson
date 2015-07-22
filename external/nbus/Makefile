include_dirs := .
src_dir := .

SRC = 
SRC += bridge.c nbus.c

SRCS += $(addprefix $(src_dir)/,$(SRC)) 

OBJS = $(subst .c,.o,$(SRCS))


CPPFLAGS += $(addprefix -I,$(include_dirs))

.PHONY: all

all : $(OBJS)
	gcc  -shared -o ../../lib/libcnbus.so $(OBJS) -lpthread
	rm -f $(OBJS)

%.o : %.c 
	gcc -fpic -c $< $(CPPFLAGS) -o $(@)
	
clean : 
	rm -f $(OBJS)