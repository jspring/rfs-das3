/**\file
 * 	Read function for Peak CAN-to-USB converter.
 * 	See header hn_peak_can.h file for description.
 */
#include <sys_os.h>
#include "nt_peak_can.h"

int peak_can_verbose;	/// defined in net_peak_can.c

/** 	peak_can_read_line  parses out lines of type 'm' and
 * 	returns a 32-bit 'id', boolean 'extended' and fills in an 8-byte
 * 	'data' array, similar to the interface in the other PATH CAN drivers.
 * 	The interface function calls fgets to get one line of data from
 * 	an already opened file 'fp'. 
 *
 * 	RETURNS: number of bytes placed in 'data' array, -1 on end of file,
 * 	or a negative error code if the line did not have a correct 'm' 
 * 	message string.
 */
int peak_can_read_line(FILE *fp, unsigned long *id, 
	unsigned char *extended, unsigned char *data,
	int *ts_msec, int *ts_usec)
{
	char buf[PEAK_MAXLINE];	/// holds input line
	int stop, start;	/// indices for beginning and end of a field
	int num_bytes;		/// number of data bytes in CAN message
	int i;
	
	/// read line from file
	if (!fgets(buf, PEAK_MAXLINE, fp)) return PEAK_CAN_EOF; 

	/// check if first field is 'm' (CAN message string)
	stop = -1;	/// begin at start of array
	if (!get_field_index(buf, &start, &stop)) return PEAK_CAN_BAD_CODE;
	if (buf[start] != 'm') return PEAK_CAN_BAD_CODE;
	
	/// read frame type field and set 'extended' for return
	if (!get_field_index(buf, &start, &stop)) return PEAK_CAN_BAD_FRAME_T;
	if (buf[start] == 's') 
		*extended = 0;
	else if (buf[start] == 'e')
		*extended = 1;
	else
		return PEAK_CAN_BAD_FRAME_T;
	
	/// read CAN ID, extended or standard, it will be returned as int
	if (!get_field_index(buf, &start, &stop)) return PEAK_CAN_BAD_ID;
	sscanf(&buf[start], "%li", id);	

	/// read number of bytes, and check that it is correct for CAN
	if (!get_field_index(buf, &start, &stop)) return PEAK_CAN_BAD_COUNT;
	sscanf(&buf[start], "%i", &num_bytes);	
	if ((num_bytes < 0) || (num_bytes > 8)) return PEAK_CAN_BAD_COUNT;
	
	/// fill data array with values from message
	memset(data, 0, 8);
	for (i = 0; i < num_bytes; i++) {	
		if (!get_field_index(buf, &start, &stop)) 
			return PEAK_CAN_BAD_DATA;
		sscanf(&buf[start], "%hhi", &data[i]);	
	}
	// read timestamps but do not return error code if there is
	// an error while getting these fields from the array
	*ts_msec = 0;
	*ts_usec = 0;
	if (!get_field_index(buf, &start, &stop)) return num_bytes;
	sscanf(&buf[start], "%i", ts_msec);	
	if (!get_field_index(buf, &start, &stop)) return num_bytes;
	sscanf(&buf[start], "%i", ts_usec);	

	/// Return the number of bytes filled in for the CAN data
	return (num_bytes);	
}

/** Print the data returned by peak_can_read_line
 */
void peak_can_print_line(FILE *fp, unsigned long id, 
	unsigned char extended, unsigned char *data,
	int ts_msec, int ts_usec, int num_bytes, int do_hex)
{
	int i;
	fprintf(fp, "0x%lx %s ", id, extended?"Ext":"Std"); 
	for (i = 0; i < num_bytes; i++) { 
		if (do_hex)
			fprintf(fp, "0x%02hhx ", data[i]);
		else
			fprintf(fp, "%3hhu  ", data[i]);
	}
	/// fill to line up timestamps
	for (i = num_bytes; i < 8; i++)
		fprintf(fp, "     ");
	fprintf(fp, "%d %d ", ts_msec, ts_usec);
	fprintf(fp, "\n");
}

	
/** Interpret and print the error codes returned by peak_can_read_line
 */
void peak_can_print_error (int val)
{
	switch (val) {
	case PEAK_CAN_EOF:
		printf("EOF or fgets error while reading PEAK CAN stream\n");
		break;
	case PEAK_CAN_BAD_CODE:
		printf("Bad PEAK CAN code field\n");
		break;
	case PEAK_CAN_BAD_FRAME_T:
		printf("Bad PEAK CAN frame type field\n");
		break;
	case PEAK_CAN_BAD_ID:
		printf("Bad PEAK CAN ID field\n");
		break;
	case PEAK_CAN_BAD_COUNT:
		printf("Bad PEAK CAN byte count field\n");
		break;
	case PEAK_CAN_BAD_DATA:
		printf("Bad PEAK CAN data field\n");
		break;
	default:
		printf("Unknown PEAK CAN error\n");
		break;
	}
}

