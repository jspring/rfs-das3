# Makefile for main longitudinal control directory, authored by Xiao-yun Lu
include $(CAPATH_MK_DEFS)

TRUCKDIR = $(DISTRIB_DIR)/truckcontrol
COMMON_DIR = ../common
PRIUS_DIR = ../can/src
#VEHCOMM_DIR = $(TRUCKDIR)/long_ctl/src/vehcomm
AVCS_DIR = $(TRUCKDIR)/long_ctl/src/avcs

CFLAGS = $(PATH_CFLAGS) -I$(COMMON_DIR) -I$(PRIUS_DIR) -DPROTOTYPE
#CFLAGS = $(PATH_CFLAGS) -I$(COMMON_DIR) -I$(JBUS_DIR)/include -DPROTOTYPE
#CFLAGS += -I$(VEHCOMM_DIR) -I$(AVCS_DIR)

LINK = $(PATH_LINK)
#LINKFLAGS = $(PATH_LDFLAGS) -L$(COMMON_DIR) -L. -L$(JBUS_DIR)/lib
LINKFLAGS = $(PATH_LDFLAGS) -L$(COMMON_DIR) -L.
#LIBS = -llong_utils -ljbus -ltrack $(PATH_LIBS) 
LIBS = -llong_utils $(PATH_LIBS) 

#TRACKLIB = libtrack.a

#
# User Defined macros for files, directories, etc.
#

# Location/name of executable
TARGET = $(OBJDIR)/long_prs

# Files from this directory to include in executable
#LONG_CTL_SRCS = long_trk.c long_trk_func.c
#LONG_CTL_OBJS = $(LONG_CTL_SRCS:c=o)

#
# Default rules
#

#all:   $(TRACKLIB) $(TARGET) 
all:   $(TARGET) 

.c.o:
	$(CC) $(CFLAGS) -o $@ $<

#
# Object file dependencies
#

long_ctl_prius.o:	$(COMMON_DIR)/long_ctl_prius.c $(COMMON_DIR)/long_ctl_prius.h
	$(CC) $(CFLAGS) -o $@ $<

#$(TARGET): $(LONG_CTL_OBJS) 
$(TARGET): long_ctl_prius.o $(LONG_CTL_OBJS) 
	$(LINK) $(LINKFLAGS) -o $@ $^ $(LIBS)
	if [ ! -d $(OBJDIR) ] ; then mkdir -p $(OBJDIR) ; fi

$(LONG_CTL_OBJS): $(COMMON_DIR)/long_ctl_prius.h track.h long_trk.h

#
# Distribution control rules
#

#install:  all
#	cp -f $(TARGET) $(TRUCKDIR)/test

clean:
	/bin/rm -f *.o \
	*.err \
	$(TARGET)

distclean: clean
	cd $(DISTRIB_DIR)/long_ctl/test; /bin/rm -f cmdtest

