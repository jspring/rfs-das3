include $(CAPATH_MK_DEFS)

M56_DIR = /home/das3/veh/m56/can/src
VIDEORECORDER_DIR = $(VIDEO_DIR)/videorecorder

PATH_CFLAGS += -I$(M56_DIR) -I$(VIDEORECORDER_DIR)
PATH_LIBS += -levt300

EXEC = $(OBJDIR)/wrfiles_das3

all: $(OBJDIR) $(EXEC)

$(EXEC):
	make -C lib_templates
	if [ ! -h libveh_tables.so ] ; then  echo "Making veh_tables library link to dummy table"; ln -sf lib_templates/lnx/libveh_tables.so.1.0 libveh_tables.so; ln -sf lib_templates/lnx/libveh_tables.so.1.0 libveh_tables.so.1; fi
	if [ ! -h libexpt_tables.so ] ; then echo "Making expt_tables library link to dummy table"; ln -s lib_templates/lnx/libexpt_tables.so.1.0 libexpt_tables.so ; ln -s lib_templates/lnx/libexpt_tables.so.1.0 libexpt_tables.so.1 ; fi 
	gcc -Wall -fPIC -c *.c -I. -I/home/path/local -I/home/path/db -I/home/path/sens/include -I/home/das3/veh/m56/can/src -I/home/video/videorecorder -o $(OBJDIR)/wrfiles_das3.o
	gcc -Wall -L/home/das3/veh/m56/src/lnx -L/home/cacc3/veh/lnx -L/home/path/local/lnx -L/home/path/db/lnx -L/home/path/sens/lib/lnx -L. $(OBJDIR)/wrfiles_das3.o -levt300 -lveh_tables -lexpt_tables -ldb_clts -llocals -lrt -lm -o $(OBJDIR)/wrfiles_das3

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(OBJDIR)/wrfiles_das3* lib*so*
	make -C lib_templates clean
