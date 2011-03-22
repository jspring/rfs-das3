# Makefile for CICAS code at RFS interseciton and on vehicles 
#
# Do the build in the "path" directory for those libraries first.
# Code also depends on header files in the "atsc" directory tree
#
# Copyright (c) 2008   Regents of the University of California
#

include $(CAPATH_MK_DEFS)

all:
	./make_includes
	make -C src
	make -C veh
	make -C ui/src

#$(EXP_LIBRARY): $(wildcard exp/*.[ch])
#	make -C exp
#	make -C exp install

# separate from all because cannot be done in many environments
ui/src: 
	make -C ui/src
	make -C ui/src install

install:
	make -C src install
	make -C veh install
	make -C ui/src install
clean:
	make -C src clean
	make -C veh clean
	make -C ui/src clean
