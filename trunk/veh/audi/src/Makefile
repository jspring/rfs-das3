# Makefile
#
# Copyright (c) 2010   Regents of the University of California
#
include $(CAPATH_MK_DEFS)

DAS3_DIR=$(DISTRIB_DIR)/das3
AUDI_DIR=$(DAS3_DIR)/veh
VIDEO_DIR=$(DISTRIB_DIR)/capath/video/videorecorder
AUDI_CAN_DIR=$(NT_ONBOARD_DIR)/can

HDRS += wrfiles_nt.h alert.h vid_enet_srv.h

PATH_OBJS += $(OBJDIR)/audi_tables.o

PATH_CFLAGS += -I$(VIDEO_DIR) -I$(NT_CAN_DIR)/altima
PATH_CFLAGS += -I$(NT_CAN_DIR)/audi/cSlap-1.0.5-i386-Release/src
PATH_CFLAGS += -I$(DISTRIB_DIR)/path/sens/gyro/memsense/src

PATH_LIBS = -levt300 -lpath_gps $(PATH_CORE_LIBS)

EXEC = $(OBJDIR)/nt_cr $(OBJDIR)/vid_enet_clt

all:    $(OBJDIR) $(PATH_OBJS)

$(OBJDIR):
	mkdir -p $(OBJDIR)
clean:
	\rm -f $(OBJDIR)/*.o *.*~ $(EXEC) *.err *.out *.log

install:
	mkdir -p $(NT_ONBOARD_DIR)/test/data
	cp $(EXEC) $(NT_ONBOARD_DIR)/test

