
# Makefile - PATH GPS sample programs
#
# Copyright (c) 2008   Regents of the University of California
#

#include $(CAPATH_MK_DEFS)
include /home/path/build/capath_qnx.mk

PATH_OBJS = $(OBJDIR)/prius_lib.o
PATH_INCLUDES = prius_can.h
PATH_CFLAGS += -I/home/das3/src -I../../common -fPIC
PATH_LDFLAGS += -fPIC

EXEC = $(OBJDIR)/prius_can $(OBJDIR)/clt_vars

all: $(OBJDIR) $(PATH_INCLUDES) $(PATH_OBJS) $(EXEC)

$(OBJDIR):
	mkdir -p $(OBJDIR)

install:
	cp -p $(EXEC) ../../test
clean:
	rm -f $(OBJDIR)/*.o *.err $(EXEC)
