# Comment/uncomment the following line to disable/enable debugging
#DEBUG = y
CFLAGS_hijj.ko := -DDEBUG

# Add your debugging flag (or not) to CFLAGS
ifeq ($(DEBUG),y)
	DEBFLAGS = -O -g -DSHORT_DEBUG # "-O" is needed to expand inlines
else
	DEBFLAGS = -O2
endif

CFLAGS += $(DEBFLAGS)
CFLAGS += -I..

ifneq ($(KERNELRELEASE),)
# call from kernel build system

obj-m	+= h.o
h-y :=mem3.o 

	

else

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

endif



depend .depend dep:
	$(CC) $(CFLAGS) -M *.c > .depend


ifeq (.depend,$(wildcard .depend))
include .depend
endif
clean	:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions	
	

