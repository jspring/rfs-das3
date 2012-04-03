# Typical Makefile for ui/src Directory
#
# Do the build in the "path" directory for those libraries first.
# Do the build in the "das3" directory for those libraries second.
#
# Copyright (c) 2012   Regents of the University of California
#

include $(CAPATH_MK_DEFS)

CANDIR=$(DISTRIB_DIR)/das3/veh
VS_OBJ_DIR=$(DISTRIB_DIR)/das3/ui/src/$(OBJDIR)

PATH_CFLAGS += $(TILCON_CFLAGS)
PATH_CFLAGS += -I$(CANDIR)/altima/can
PATH_CFLAGS += -I$(CANDIR)/audi/can/src
PATH_CFLAGS += -I$(CANDIR)/m56/can/src
PATH_CFLAGS += -g
PATH_LDFLAGS += $(TILCON_LDFLAGS)
PATH_LIBS = $(TILCON_LIBS) -lpath_gps $(PATH_CORE_LIBS)

PATH_OBJS += $(VS_OBJ_DIR)/vs_altima_db_read.o $(VS_OBJ_DIR)/vs_audi_db_read.o

EXEC =	$(OBJDIR)/vehicle_status

.o:
	$(PATH_LINKPP) $(LDFLAGS) $(PATH_LDFLAGS) -o $@ $@.o $(PATH_OBJS) $(PATH_LIBS)

all: $(OBJDIR) $(PATH_OBJS) $(EXEC)

$(OBJDIR):
	mkdir -p $(OBJDIR)
clean:
	rm -f $(OBJDIR)/*.o *.err *.a $(EXEC)

install:
#	cp $(EXEC) ../../test
