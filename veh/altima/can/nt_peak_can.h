/**\file
 * 	Definitions and prototypes for California PATH code
 * 	using the Peak CAN-to-USB converter with Linux driver
 * 	(peak-linux-driver.6.19.tar.gz, www.peak-system.com).
 *
 * 	Driver is used in mode where installation of the driver
 * 	makes a text stream available on a USB port, with the following
 * 	format.
 *
 * 	Column 1: 
 * 		m	Message string follows
 * 		r	RTR-message string follows
 * 		i	Initialisation string follows (write only)
 * 		#	Comment follows (write only)
 * 	Column 2:
 * 		s	Standard frame
 * 		e	Extended frame
 * 	Column 3:	Identifier (hex)
 * 	Column 4:	Number of bytes in CAN data message (decimal)
 * 	Column 5..12 	Data bytes (variable number printed)
 * 	Last two columns	Timestamps, milliseconds
 */ 	

extern int peak_can_verbose;	/// defined in net_peak_can.c

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
extern int peak_can_read_line(FILE *fp, unsigned long *id, 
	unsigned char *extended, unsigned char *data,
	int *ts_sec, int *ts_msec);

/** Print the data returned by peak_can_read_line
 */
extern void peak_can_print_line(FILE *fp, unsigned long id, 
        unsigned char extended, unsigned char *data,
        int ts_sec, int ts_msec, int num_bytes, int do_hex);

/** Interpret and print the error codes returned by peak_can_read_line
 */
extern void peak_can_print_error (int val);

/**	Error codes from peak_can_read_line; no error is returned if
 * 	there is a problem reading the timestamp fields.
 */
#define PEAK_CAN_EOF		-1 /// could also be an error from fgets
#define PEAK_CAN_BAD_CODE	-2
#define PEAK_CAN_BAD_FRAME_T	-3
#define PEAK_CAN_BAD_ID		-4
#define PEAK_CAN_BAD_COUNT	-5
#define PEAK_CAN_BAD_DATA	-6

/** 
 * 	Simple utility functiones used in grabbing the column fields
 * 	from a buffer containing a line of data returned by fgets.
 * 	Functions modify the buffer to have end-of-string '\0' at
 * 	the end of each field, and return start and end of string
 * 	to calling program.
 */
#define PEAK_MAXLINE	1024	/// size of buffer used to hold input line

/**
 * 	skip_blanks is used to skip over blanks and find next field
 */
static inline int skip_blanks(char *buf, int i)
{
	while (1) {
		if (i == PEAK_MAXLINE) return -1;
		if (buf[i] == '\0') return -1;
		if (buf[i] != ' ') return i;
		i++;
	}
}

/**
 * 	 mark_field_end finds end of string (next blank)
 * 	 and fills it with '\0'.
 */
static inline int mark_field_end(char *buf, int i)
{
	// assertion below should always be false when this is called
	if ((i >= PEAK_MAXLINE) || (buf[i] == '\0') || (buf[i] == ' ')) 
		return -1;
	while ((buf[i] != ' ') && (buf[i] != '\0')) {
		i++;
		if (i == PEAK_MAXLINE) return -1;
	} 
	buf[i] = '\0';
	return i;
}

/**
 * 	get_field_index returns TRUE if successful, FALSE on error,
 * 	and, if successful, set 'pstart' and 'pstop' to the beginning
 * 	and ending indices of the field string within the line buffer
 * 	array 'buf'. The beginning index is a non-blank character, the
 * 	ending index is that of the array element that has been set to '\0'.
 * 	
 * 	When called, 'pstop' must point to a value one less than the
 * 	place in the array where you want to start searching; this is
 * 	typically the value that was put in 'pstop' on the last call. 
 */

static inline int get_field_index(char *buf, int *pstart, int *pstop)
{
	int cur = (*pstop) + 1;		/// will have the start value at end
	int nxt;			/// will have the stop value at end
	if ((cur = skip_blanks(buf,cur)) == -1) return 0;
	if ((nxt = mark_field_end(buf, cur)) == -1) return 0;
	*pstart = cur;
	*pstop = nxt;
	if (peak_can_verbose) printf("%s ", &buf[cur]);
	return 1;
}
