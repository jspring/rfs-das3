
# Makefile - PATH GPS sample programs
#
# Copyright (c) 2008   Regents of the University of California
#

include $(CAPATH_MK_DEFS)
KOMODO_DIR = /home/path/sens/can2usb/komodo/files/komodo-api-linux-i686-v1.00/c
PATH_OBJS = $(KOMODO_DIR)/komodo.o $(OBJDIR)/m56_lib.o
PATH_INCLUDES = m56_can.h
PATH_LIBS += -ldl
PATH_CFLAGS += -pg

EXEC = $(OBJDIR)/m56_can


all: $(OBJDIR) $(PATH_INCLUDES) $(PATH_OBJS) $(EXEC)

$(OBJDIR):
	mkdir -p $(OBJDIR)

install:
	cp -p $(EXEC) ../../test
clean:
	rm -f $(OBJDIR)/*.o *.err $(EXEC)
