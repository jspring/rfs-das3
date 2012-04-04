# Typical Makefile for ui/src Directory
#
# Do the build in the "path" directory for those libraries first.
# Do the build in the "das3" directory for those libraries second.
#
# Copyright (c) 2012   Regents of the University of California
#

include $(CAPATH_MK_DEFS)

CANDIR=$(DISTRIB_DIR)/das3/veh

PATH_CFLAGS += $(TILCON_CFLAGS)
PATH_CFLAGS += -I$(CANDIR)/altima/can
PATH_CFLAGS += -I$(CANDIR)/audi/can/src
PATH_CFLAGS += -I$(CANDIR)/m56/can/src
PATH_CFLAGS += -g
PATH_LDFLAGS += $(TILCON_LDFLAGS)
PATH_LIBS = $(TILCON_LIBS) -lpath_gps $(PATH_CORE_LIBS)

PATH_OBJS += $(OBJDIR)/vs_altima_db_read.o $(OBJDIR)/vs_audi_db_read.o

EXEC =	$(OBJDIR)/vehicle_status

#all: $(OBJDIR) $(PATH_OBJS) $(EXEC)
all: $(OBJDIR) $(PATH_OBJS)

$(OBJDIR):
	mkdir -p $(OBJDIR)
clean:
	rm -f $(OBJDIR)/*.o *.err *.a $(EXEC)

install:
#	cp $(EXEC) ../../test
