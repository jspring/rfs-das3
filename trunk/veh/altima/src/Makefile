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
PATH_LDFLAGS += -L$(SENS_LIB_DIR)/$(OBJDIR)

PATH_LIBS = -levt300 -lpath_gps $(PATH_CORE_LIBS)

EXEC = $(OBJDIR)/wrfiles $(OBJDIR)/altima_cr

all:    $(OBJDIR) $(PATH_OBJS) $(EXEC)

$(OBJDIR):
	mkdir -p $(OBJDIR)

install:
	cp -p $(EXEC) ../test

clean:
	\rm -f $(OBJDIR)/*.o *.*~ $(EXEC) *.err *.out *.log
