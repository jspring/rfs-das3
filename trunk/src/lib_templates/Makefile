
# Makefile - PATH GPS sample programs
#
# Copyright (c) 2012   Regents of the University of California
#

include $(CAPATH_MK_DEFS)

PATH_OBJS = $(OBJDIR)/dummy_tables.o

LIB = libveh_tables.so
LIB2 = libexpt_tables.so

PATH_LIBS += -ldl
PATH_CFLAGS += -pg
PATH_CFLAGS += -fPIC
PATH_CFLAGS += -I$(M56_DIR) -I$(VIDEO_DIR)/videorecorder

all: $(OBJDIR) $(PATH_OBJS) $(LIB).1.0  $(LIB2).1.0

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIB).1.0:
	gcc -shared -Wl,-soname,veh_tables.so.1 -o $(OBJDIR)/$(LIB).1.0 $(OBJDIR)/*.o
	ln -sf $(LIB).1.0 $(OBJDIR)/$(LIB)
	ln -sf $(LIB).1.0 $(OBJDIR)/$(LIB).1
$(LIB2).1.0:
	gcc -shared -Wl,-soname,expt_tables.so.1 -o $(OBJDIR)/$(LIB2).1.0 $(OBJDIR)/*.o
	ln -sf $(LIB2).1.0 $(OBJDIR)/$(LIB2)
	ln -sf $(LIB).1.0 $(OBJDIR)/$(LIB).1

clean:
	rm -f $(PATH_OBJS) $(TABLES) $(OBJDIR)/$(LIB)* $(OBJDIR)/$(LIB2)*
