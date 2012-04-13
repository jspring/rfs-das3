# Makefile for Data Acquisition System v3 
#
# Do the build in the "path" directory for those libraries first.
#
# Copyright (c) 2012   Regents of the University of California
#

include $(CAPATH_MK_DEFS)

all:
	./make_includes.sh
	make -C veh
	make -C ui/src

ui/src: 
	make -C ui/src
	make -C ui/src install

install:
	make -C veh install
	make -C ui/src install
clean:
	rm -rf include
	make -C veh clean
	make -C ui/src clean
