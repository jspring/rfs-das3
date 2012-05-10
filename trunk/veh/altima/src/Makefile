# Makefile
#
# Copyright (c) 2010   Regents of the University of California
#
include $(CAPATH_MK_DEFS)

DAS3_DIR = $(DISTRIB_DIR)/das3
DAS3_INCLUDE_DIR = $(DAS3_DIR)/include
DAS3_LIB_DIR = $(DAS3_DIR)/lib
VIDEO_DIR=$(DISTRIB_DIR)/capath/video/videorecorder

HDRS += vid_enet_srv.h

PATH_OBJS += $(OBJDIR)/altima_tables.o

PATH_CFLAGS += -I$(VIDEO_DIR)
PATH_CFLAGS += -I$(DISTRIB_DIR)/path/sens/gyro/memsense/src
PATH_CFLAGS += -I$(DAS3_INCLUDE_DIR)
PATH_CFLAGS += -fPIC
PATH_LDFLAGS += -L$(SENS_LIB_DIR)/$(OBJDIR)

PATH_LIBS = -levt300 -lpath_gps $(PATH_CORE_LIBS)

LIB = libaltima_tables.so
EXEC = $(OBJDIR)/wrfiles $(OBJDIR)/altima_cr

all:    $(OBJDIR) $(PATH_OBJS) $(EXEC) $(LIB).1.0

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIB).1.0:
	gcc -shared -Wl,-soname,libaltima_tables.so.1 -o $(OBJDIR)/$(LIB).1.0 $(OBJDIR)/altima_tables.o
	ln -sf $(LIB).1.0 $(OBJDIR)/$(LIB)
	ln -sf $(LIB).1.0 $(OBJDIR)/$(LIB).1

install:
	cp -p $(EXEC) ../test

clean:
	\rm -f $(OBJDIR)/*.o *.*~ $(EXEC) *.err *.out *.log
