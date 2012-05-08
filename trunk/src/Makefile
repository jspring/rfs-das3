include $(CAPATH_MK_DEFS)

M56_DIR = /home/das3/veh/m56/can/src
VIDEORECORDER_DIR = $(VIDEO_DIR)/videorecorder

PATH_CFLAGS += -I$(M56_DIR) -I$(VIDEORECORDER_DIR)

EXEC = $(OBJDIR)/wrfiles_das3

all: $(OBJDIR) $(EXEC)

$(EXEC):
	if [[ ! -h libveh_tables.so ]] ; then  ln -s lib_templates/lnx/libdummy_tables.so.1 libveh_tables.so; fi
	if [[ ! -h libexpt_tables.so ]] ; then ln -s lib_templates/lnx/libdummy_tables.so.1 libexpt_tables.so ; fi 
	gcc -Wall -fPIC -c *.c -I. -I/home/path/local -I/home/path/db -I/home/path/sens/include -I/home/das3/veh/m56/can/src -I/home/video/videorecorder -o $(OBJDIR)/wrfiles_das3.o
	gcc -Wall -L/home/das3/veh/m56/src/lnx -L/home/cacc3/veh/lnx -L/home/path/local/lnx -L/home/path/db/lnx -L/home/path/sens/lib -L. $(OBJDIR)/wrfiles_das3.o -lveh_tables -lexpt_tables -ldb_clts -llocals -lrt -lm -o $(OBJDIR)/wrfiles_das3

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(OBJDIR)/wrfiles_das3*
