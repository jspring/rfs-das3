# Makefile
#
# Copyright (c) 2010   Regents of the University of California
#
include $(CAPATH_MK_DEFS)

DAS3_DIR = $(DISTRIB_DIR)/das3
VIDEO_DIR=$(DISTRIB_DIR)/capath/video/videorecorder

HDRS += wrfiles_nt.h alert.h vid_enet_srv.h

PATH_OBJS += $(OBJDIR)/altima_tables.o

PATH_CFLAGS += -I$(VIDEO_DIR)
PATH_CFLAGS += -I$(DAS3_DIR)/src
PATH_CFLAGS += -I$(DISTRIB_DIR)/path/sens/gyro/memsense/src
PATH_LDFLAGS += -L$(DAS3_DIR)/src

PATH_LIBS = -lwrfiles -levt300 -lpath_gps $(PATH_CORE_LIBS)

EXEC = $(OBJDIR)/nt_cr $(OBJDIR)/vid_enet_clt

all:    $(OBJDIR) $(PATH_OBJS)

$(OBJDIR):
	mkdir -p $(OBJDIR)
clean:
	\rm -f $(OBJDIR)/*.o *.*~ $(EXEC) *.err *.out *.log
