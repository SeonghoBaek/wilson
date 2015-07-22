SUBDIRS = nbus

.PHONY: all subdirs $(SUBDIRS) 

subdirs: $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	for dir in $(SUBDIRS); do \
			$(MAKE) -C $$dir $@;\
	done

