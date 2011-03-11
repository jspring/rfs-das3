# Makefile
#
# Copyright (c) 2008   Regents of the University of California
#
include $(CAPATH_MK_DEFS)
NT_CANDIR=/home/nt-onboard/can
NT_SRCDIR=/home/nt-onboard/src

PATH_CFLAGS += $(TILCON_CFLAGS) -I$(NT_CANDIR)/altima 
PATH_CFLAGS += -I$(NT_CANDIR)/audi/cSlap-1.0.5-i386-Release/src
PATH_CFLAGS +=  -I$(NT_SRCDIR)
PATH_CFLAGS += -g
PATH_LDFLAGS += $(TILCON_LDFLAGS)
PATH_LIBS = $(TILCON_LIBS) -lpath_gps $(PATH_CORE_LIBS)

PATH_OBJS += $(OBJDIR)/vs_altima_db_read.o $(OBJDIR)/vs_audi_db_read.o

EXEC =	$(OBJDIR)/vehicle_status

.o:
	$(PATH_LINKPP) $(LDFLAGS) $(PATH_LDFLAGS) -o $@ $@.o $(PATH_OBJS) $(PATH_LIBS)

all: $(OBJDIR) $(PATH_OBJS) $(EXEC)

$(OBJDIR):
	mkdir -p $(OBJDIR)
clean:
	rm -f $(OBJDIR)/*.o *.err *.a $(EXEC)

install:
	cp $(EXEC) ../../test
