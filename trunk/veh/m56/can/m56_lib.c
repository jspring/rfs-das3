/*
** m56_lib.c - contains function definitions for m56_can.c
*/

#include <db_include.h>
#include <komodo.h>

int printmsg(db_komodo_t *db_kom);
int printcan(db_komodo_t *db_kom){
	int i;

	printf("CAN ID: %#03x msg: ", db_kom->id);
	for(i=0 ; i<8; i++)
		printf("%#02x ", db_kom->msg[i]);
	printf("\n");
	return 0;
}
