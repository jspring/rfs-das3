
#include $(CAPATH_MK_DEFS)
include capath_qnx.mk

all:
	make -C path 
	make -C steinhoff
	make -C accord
	make -C argonne_cacc
clean:
	make -C path clean
	make -C steinhoff clean
	make -C accord clean
	make -C argonne_cacc clean

install:
	if [ ! -d qnx7 ] ; then mkdir -p qnx7; fi
	cp -p ./path/db/qnx/db_slv $(QNX_TARGET)/x86_64/usr/bin
	cp -p ./accord/can/src/qnx/accord_can $(QNX_TARGET)/x86_64/usr/bin
	cp -p ./accord/can/src/qnx/clt_vars_accord $(QNX_TARGET)/x86_64/usr/bin
	cp -p ./argonne_cacc/qnx/argonne_cacc $(QNX_TARGET)/x86_64/usr/bin
	cp -p ./steinhoff/qnx/can_rx $(QNX_TARGET)/x86_64/usr/bin
	cp -p ./steinhoff/qnx/can_tx $(QNX_TARGET)/x86_64/usr/bin
	cp -p $(QNX_TARGET)/../../bsp/BSP*/images/x86_64-generic.build qnx7
	cp -p $(QNX_TARGET)/../../bsp/BSP*/images/x86_64-generic.bin qnx7
