# Makefile for Audi cSlap stuff
#cc exampleclient.c -o exampleclient  -I../../../include -L../../../lib -lcslap

include $(CAPATH_MK_DEFS)

PATH_CFLAGS+=  -I../include
PATH_LDFLAGS += -L../lib
PATH_LIBS += -lcslap

EXEC = $(OBJDIR)/exampleclient $(OBJDIR)/audi_can

all:    $(OBJDIR) $(EXEC)

$(OBJDIR):
	mkdir -p $(OBJDIR)
install:
	cp -p $(EXEC) ../../test
clean:
	rm -f $(OBJDIR)/* *.err *.o
