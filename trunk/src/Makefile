include $(CAPATH_MK_DEFS)

M56_DIR = /home/das3/veh/m56/can/src
VIDEORECORDER_DIR = $(VIDEO_DIR)/videorecorder

PATH_CFLAGS += -I$(M56_DIR) -I$(VIDEORECORDER_DIR)

EXEC = $(OBJDIR)/wrfiles_das3

all: $(EXEC)

$(EXEC):
	gcc -Wall -fPIC -c *.c -I. -I/home/path/local -I/home/path/db -I/home/path/sens/include -I/home/das3/veh/m56/can/src -I/home/video/videorecorder -o $(OBJDIR)/wrfiles_das3.o
	gcc -Wall -L/home/das3/veh/m56/src -L/home/path/local/lnx -L/home/path/db/lnx -L/home/path/sens/lib -L. $(OBJDIR)/wrfiles_das3.o -lveh_tables -lexpt_tables -ldb_clts -llocals -lrt -lm -o $(OBJDIR)/wrfiles_das3

clean:
	rm -f $(OBJDIR)/wrfiles_das3*
