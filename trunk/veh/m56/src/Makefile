
# Makefile - PATH GPS sample programs
#
# Copyright (c) 2008   Regents of the University of California
#

include $(CAPATH_MK_DEFS)
KOMODO_DIR = /home/path/sens/can2usb/komodo/files/komodo-api-linux-i686-v1.00/c
M56_DIR = /home/das3/veh/m56/can/src
PATH_OBJS = $(KOMODO_DIR)/komodo.o $(OBJDIR)/cacc3_tables.o $(OBJDIR)/cacc3_b-table.o  $(OBJDIR)/cacc3_c-table.o $(OBJDIR)/cacc3_e-table.o $(OBJDIR)/cacc3_f-table.o $(OBJDIR)/cacc3_g-table.o
TABLES = cacc3_c-table.c cacc3_e-table.c cacc3_f-table.c cacc3_g-table.c

PATH_LIBS += -ldl
PATH_CFLAGS += -pg
PATH_CFLAGS += -I$(M56_DIR) -I$(VIDEO_DIR)/videorecorder

EXEC = $(OBJDIR)/wrfiles_cacc3 $(OBJDIR)/cacc3_create

#all: $(OBJDIR) $(PATH_OBJS) $(TABLES) $(EXEC)
all: $(OBJDIR) $(EXEC)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TABLES): cacc3_b-table.c
	./make_tables_from_template.sh

$(EXEC): $(PATH_OBJS) $(TABLES)

install:
	cp -p $(EXEC) ../../test
clean:
	rm -f $(PATH_OBJS) *.err $(EXEC) $(TABLES)
