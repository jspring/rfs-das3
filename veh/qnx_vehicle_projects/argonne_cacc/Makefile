
# Makefile - PATH GPS sample programs
#
# Copyright (c) 2008   Regents of the University of California
#

include capath_qnx.mk

PATH_OBJS += $(OBJDIR)/long_control.o
PATH_CFLAGS += -I/home/das3/src -I../../common -I../include -fPIC
PATH_LDFLAGS += -fPIC -L../lib

EXEC = $(OBJDIR)/argonne_cacc

all: $(OBJDIR) $(PATH_INCLUDES) $(PATH_OBJS) $(EXEC)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(OBJDIR)/*.o *.err $(EXEC)
