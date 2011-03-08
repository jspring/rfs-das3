# Makefile
#
# Copyright (c) 2006   Regents of the University of California
#

include $(CAPATH_MK_DEFS)

DAS3DIR = /home/capath/das3
ALTIMA_DIR = $(DAS3DIR)/veh/altima/src
PATH_CFLAGS += -I$(ATSC_INC_DIR) 
PATH_CFLAGS += -I$(CICAS_EXP_DIR) -I$(CICAS_FUSION_DIR) 
PATH_CFLAGS += -I$(CICAS_VEH_DIR)
PATH_CFLAGS += -I$(ALTIMA_DIR)
PATH_CFLAGS += -I$(VIDEO_DIR)
PATH_LDFLAGS += -L$(DSCUD_DIR) -L$(SENS_DIR)/gpio/lnx
PATH_OBJS += $(OBJDIR)/wrfiles_lib.o

PATH_LIBS += -levt300 -lpath_gps -lsms $(PATH_CORE_LIBS)

EXEC = $(OBJDIR)/libwrfiles.a

all: 	$(OBJDIR) $(PATH_OBJS) $(EXEC)

$(OBJDIR)/libwrfiles.a:	$(PATH_OBJS) 
	$(PATH_AR) $(PATH_AR_FLAGS)  $@ $(PATH_OBJS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean: 
	\rm -f $(OBJDIR)/*.o $(OBJDIR)/*.a $(OBJDIR)/*.err *.*~ $(EXEC)

# DO NOT DELETE
