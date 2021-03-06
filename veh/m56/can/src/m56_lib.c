/*
** m56_lib.c - contains function definitions for m56_can.c
*/

#include <db_include.h>
#include <komodo.h>
#include <m56_can.h>

m56_ignition_status_t m56_ignition_status;

int printmsg(db_komodo_t *db_kom) {
	int i;
}

int printcan(db_komodo_t *db_kom){
	int i;

	printf("CAN ID: %#03x msg: ", db_kom->id);
	for(i=0 ; i<8; i++)
		printf("%#02x ", db_kom->msg[i]);
	printf("\n");
	return 0;
}
