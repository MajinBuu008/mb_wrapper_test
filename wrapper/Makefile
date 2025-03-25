
obj-m += mb_wrapper.o
mb_wrapper-objs := wrapper_main.o wrapper_misc.o

PWD := $(shell pwd)

ccflags-y += $(MB_CFLAGS)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean