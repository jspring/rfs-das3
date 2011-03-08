
# Makefile - PATH GPS sample programs
#
# Copyright (c) 2008   Regents of the University of California
#

HDRS=nt_peak_can.h altima.h 

include $(CAPATH_MK_DEFS)

PATH_OBJS = $(OBJDIR)/nt_peak_can.o

EXEC = $(OBJDIR)/nt_peak_can_test \
	$(OBJDIR)/altima_db_read \
	$(OBJDIR)/send_ignition_off\
	$(OBJDIR)/altima_db_write

all: $(OBJDIR) $(PATH_OBJS) $(EXEC)

$(OBJDIR):
	mkdir -p $(OBJDIR)

install:
	cp -p $(EXEC) ../../test
clean:
	rm -f $(OBJDIR)/*.o *.err $(EXEC)
