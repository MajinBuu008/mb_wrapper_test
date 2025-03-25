
PWD := $(shell pwd)

MB_CFLAGS += -I$(PWD)/include
MB_WRAPPER_MOD_PATH = $(PWD)/wrapper/

export MB_CFLAGS
export MB_WRAPPER_MOD_PATH

all:
	$(MAKE) -C wrapper
	$(MAKE) -C dump_task

clean:
	$(MAKE) -C wrapper clean
	$(MAKE) -C dump_task clean