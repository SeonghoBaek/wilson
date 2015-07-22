#####################################################
# Makefile for Nodebus
# Any qustion : sanghyeun.kim@lge.com
#####################################################
#====================================================
# Sub modules 
#====================================================
SUBDIRS = atm plogman pionode
#====================================================
# Build Rules 
#====================================================
.PHONY : all target $(SUBDIRS) clean

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

#====================================================

