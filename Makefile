#####################################################
# Makefile for Nodebus
# Any qustion : sanghyeun.kim@lge.com
#####################################################
#====================================================
# Sub modules 
#====================================================
#SUBDIRS = bus node external
SUBDIRS = bus node 
#====================================================
# Build Rules 
#====================================================
.PHONY : help all target $(SUBDIRS) clean

all : $(SUBDIRS) ;

$(SUBDIRS):
	$(MAKE) -C $@  

target:
	@for dir in $(SUBDIRS); do \
			$(MAKE) -C $$dir $@ ;\
	done

clean:
	@for dir in $(SUBDIRS); do \
			$(MAKE) -C $$dir $@ ;\
	done

help :
	@printf " \
	< Available Goals >\n \
	all		: default goal (ARCH : x86) \n \
	target	: build for target board (ARCH : arm) \n \
	help	: show this help messages \n \
	"
#====================================================
