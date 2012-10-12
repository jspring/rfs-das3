# Makefile
#
# Copyright (c) 2006   Regents of the University of California
#

include $(CAPATH_MK_DEFS)

#DSCUD_DIR = /usr/local/dscud5

#PATH_CFLAGS += -I$(DSCUD_DIR) 
PATH_CFLAGS += -I../src 
PATH_CFLAGS += -I$(ATSC_INC_DIR) 
PATH_CFLAGS += -I$(CICAS_EXP_DIR) -I$(CICAS_FUSION_DIR) 
PATH_CFLAGS += -I$(CICAS_VEH_DIR)
PATH_LDFLAGS += -L../src -L$(DSCUD_DIR) -L$(SENS_DIR)/gpio/lnx
PATH_OBJS += $(OBJDIR)/cab_tables.o

PATH_LIBS += -levt300 -lpath_gps -lsms $(PATH_CORE_LIBS)
#PATH_LIBS += -ldscud5 -levt300 -lpath_gps -lsms -lgpio $(PATH_CORE_LIBS)

EXEC =  $(OBJDIR)/wrfiles_cab
#EXEC =  $(OBJDIR)/chgdii\
#	$(OBJDIR)/cicas_create\
#	$(OBJDIR)/delay\
#	$(OBJDIR)/readsr\
#	$(OBJDIR)/read_evtlog\
#	$(OBJDIR)/read_xe\
#	$(OBJDIR)/read_xs\
#	$(OBJDIR)/wrfiles_cab
##	$(OBJDIR)/gpio\

all: 	$(OBJDIR) $(PATH_OBJS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(EXEC): ../src/wrfiles_cab.c $(PATH_OBJS)
	$(PATH_LINK) $(PATH_LDFLAGS) -o $@ $^  $(PATH_LIBS)


#$(OBJDIR)/check_size: $(OBJDIR)/check_size.o 
#$(OBJDIR)/chgdii: $(OBJDIR)/chgdii.o
#$(OBJDIR)/cicas_create: $(OBJDIR)/cicas_create.o
#$(OBJDIR)/delay:  $(OBJDIR)/delay.o
#$(OBJDIR)/gpio: $(OBJDIR)/gpio.o
#$(OBJDIR)/readsr: $(OBJDIR)/readsr.o
#$(OBJDIR)/read_xs: $(OBJDIR)/read_xs.o
#$(OBJDIR)/read_evtlog: $(OBJDIR)/read_evtlog.o
#$(OBJDIR)/read_xe: $(OBJDIR)/read_xe.o $(PATH_OBJS)
#$(OBJDIR)/wrfiles_cab: $(OBJDIR)/wrfiles_cab.o $(PATH_OBJS)

clean: 
	\rm -f $(OBJDIR)/*.o $(OBJDIR)/*.err *.*~ $(EXEC)

install:
	\cp $(EXEC) ../test

# DO NOT DELETE
