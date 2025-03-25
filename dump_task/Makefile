
obj-m += mb_dump_task.o
mb_dump_task-objs := dump_task_main.o

PWD := $(shell pwd)

ccflags-y += $(MB_CFLAGS)
KBUILD_EXTRA_SYMBOLS += $(MB_WRAPPER_MOD_PATH)/Module.symvers

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean