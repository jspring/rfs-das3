
# Makefile - PATH GPS sample programs
#
# Copyright (c) 2012   Regents of the University of California
#

include $(CAPATH_MK_DEFS)

KOMODO_DIR = /home/path/sens/can2usb/komodo/files/komodo-api-linux-i686-v1.00/c
M56_DIR = /home/das3/veh/m56/can/src

PATH_OBJS = $(KOMODO_DIR)/komodo.o \
	$(OBJDIR)/m56_tables.o \
	$(OBJDIR)/cacc3_b-table.o  \
	$(OBJDIR)/cacc3_c-table.o \
	$(OBJDIR)/cacc3_e-table.o \
	$(OBJDIR)/cacc3_f-table.o \
	$(OBJDIR)/cacc3_g-table.o

TABLES = cacc3_c-table.c cacc3_e-table.c cacc3_f-table.c cacc3_g-table.c
LIB = libm56_tables.so

PATH_LIBS += -ldl
PATH_CFLAGS += -pg
PATH_CFLAGS += -fPIC
PATH_CFLAGS += -I$(M56_DIR) -I$(VIDEO_DIR)/videorecorder

EXEC = $(OBJDIR)/m56_create

all: $(OBJDIR) $(TABLES) $(PATH_OBJS) $(EXEC) $(LIB).1.0 

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TABLES): cacc3_b-table.c
	./make_tables_from_template.sh

$(LIB).1.0:
	gcc -shared -Wl,-soname,libm56_tables.so.1 -o $(OBJDIR)/$(LIB).1.0 $(OBJDIR)/*.o
	ln -sf $(LIB).1.0 $(OBJDIR)/$(LIB)
	ln -sf $(LIB).1.0 $(OBJDIR)/$(LIB).1

install:
	cp -p $(EXEC) ../../test
clean:
	rm -f $(PATH_OBJS) $(EXEC) $(TABLES) $(OBJDIR)/$(LIB)*
