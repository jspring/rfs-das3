/**\file
 * 	Test program for PATH PEAK CAN-to-USB.
 * 	echos data returned by peak_can_read_line
 */
#include <sys_os.h>
#include <local.h>
#include <sys_rt.h>
#include "nt_peak_can.h"

static jmp_buf exit_env;
static int sig_list[] = {
        SIGINT,
        SIGQUIT,
        SIGTERM,
        SIGALRM,
        ERROR,
};
static void sig_hand(int code)
{
        if (code == SIGALRM)
                return;
        else
                longjmp(exit_env, code);
}

int main(int argc, char **argv)
{
	int option;	/// for getopt
	int count = 0;	/// number of PEAK CAN messages received, no error
	int num_bytes;	/// number of data bytes in the current CAN message
	unsigned long can_id;		/// CAN ID of the current CAN message
	unsigned char can_extended;	/// 1 if extended header, 0 if standard
	unsigned char can_data[8];	/// CAN data bytes, up to 8
	int peak_ts_sec;	/// seconds timestamp from Peak CAN input line
	int peak_ts_msec;	/// millisecons timestamp from Peak CAN
	int verbose = 0;	/// use to generate output, else just counts
	int do_hex = 0;		/// print CAN data using hexadecimal numbers

        while ((option = getopt(argc, argv, "hvw")) != EOF) {
                switch(option) {
                case 'h':
			do_hex = 1;
			break;
                case 'v':
			verbose = 1;
			break;
		case 'w':
                        peak_can_verbose = 1;  // in nt_peak_can.c 
                        break;
		default:
			printf("Usage: %s -v (verbose)\n", argv[0]);
			exit(EXIT_FAILURE);
			break;
		}
	}

        if (setjmp(exit_env) != 0) {
		printf("%s: received %d CAN messages\n", argv[0], count);
                exit(EXIT_SUCCESS);
        } else
               sig_ign(sig_list, sig_hand);

	while (1) {
                num_bytes = peak_can_read_line(stdin, &can_id,
			&can_extended, can_data, &peak_ts_sec, &peak_ts_msec);
		if (num_bytes < 0) {
			if (num_bytes == PEAK_CAN_EOF) longjmp(exit_env, 1);
			peak_can_print_error(num_bytes);
		} else {
			if (verbose) 
				peak_can_print_line(stdout, can_id, 
					can_extended, can_data, 
					peak_ts_sec, peak_ts_msec, 
					num_bytes, do_hex);
			count++;
		}
	}
}
