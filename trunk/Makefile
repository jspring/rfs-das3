# Makefile for Data Acquistion System v3 
#
# Do the build in the "path" directory for those libraries first.
#
# Copyright (c) 2012   Regents of the University of California
#

include $(CAPATH_MK_DEFS)

all:
	./make_includes
	make -C veh
	make -C src
	make -C ui/src

ui/src: 
	make -C ui/src
	make -C ui/src install

install:
	make -C veh install
	make -C src install
	make -C ui/src install
clean:
	make -C veh clean
	make -C src clean
	make -C ui/src clean
