/**\file
 * 	Receive Altima CAN data from Peak CAN to USB converter stream.	
 *	Write data  to the DB data server.
 */
#include <sys_os.h>
#include <local.h>
#include <sys_rt.h>
#include <db_clt.h>
#include <db_utils.h>
#include "nt_peak_can.h"
#include "timestamp.h"
#include "altima.h"
#include "das3.h"

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

/** Switch statement used because few messages, for many more,
 *  set up array with function pointers and data variable sizes
 *  as for J1939 code in the California PATH can repository, jbus 
 *  directory.
 */
void altima_db_write(db_clt_typ *pclt, unsigned long id, unsigned char *data)
{
	alt_cruise_control_for_tm_t alt_ccftm;
	alt_cruise_control_for_display_t alt_ccfd;
	alt_engine_t alt_eng;
	alt_gear_indication_t alt_gi;
	alt_vehicle_speed_t alt_vs;
	alt_front_wiping_brake_switch_t alt_fwbs;
	alt_turn_signal_ignition_t alt_tsi;
	das3_ignition_status_t das3_ignition_status;
	obd2_maf_t obd2_maf; 
	obd2_cer_t obd2_cer; 
	timestamp_t turn_signal_ts;
	int curr_ms;

#define OBD2_POLL_TIMEOUT	100

	switch (id) {
	case OBD2_ECM_MSG_ID:
		switch(data[2]) {
			case OBD2_MAF_MSG_ID:
				get_obd_maf(data, &obd2_maf);
				obd2_maf.fuel_rate = obd2_maf.maf / obd2_cer.cer;
				db_clt_write(pclt, DB_OBD2_MAF_VAR, 
					sizeof(obd2_maf), (void *) &obd2_maf);
				break;
			case OBD2_CER_MSG_ID:
				get_obd_cer(data, &obd2_cer);
				db_clt_write(pclt, DB_OBD2_CER_VAR, 
					sizeof(obd2_cer), (void *) &obd2_cer);
				break;
			default:	// do nothing for unknown ECM OBD2 IDs
				break;
		}
		break;
	case ALT_CCFTM_MSG_ID:
		get_alt_ccftm(data, &alt_ccftm);
		db_clt_write(pclt, DB_ALT_CCFTM_VAR, 
			sizeof(alt_ccftm), (void *) &alt_ccftm);
		break;
	case ALT_CCFD_MSG_ID:
		get_alt_ccfd(data, &alt_ccfd);
		db_clt_write(pclt, DB_ALT_CCFD_VAR, 
			sizeof(alt_ccfd), (void *) &alt_ccfd);
		break;
	case ALT_ENG_MSG_ID:
		get_alt_eng(data, &alt_eng);
		db_clt_write(pclt, DB_ALT_ENG_VAR, 
			sizeof(alt_eng), (void *) &alt_eng);
		break;
	case ALT_GI_MSG_ID:
		get_alt_gi(data, &alt_gi);
		db_clt_write(pclt, DB_ALT_GI_VAR, 
			sizeof(alt_gi), (void *) &alt_gi);
		break;
	case ALT_VS_MSG_ID:
		get_alt_vs(data, &alt_vs);
		db_clt_write(pclt, DB_ALT_VS_VAR, 
			sizeof(alt_vs), (void *) &alt_vs);
		break;
	case ALT_FWBS_MSG_ID:
		get_alt_fwbs(data, &alt_fwbs);
		db_clt_write(pclt, DB_ALT_FWBS_VAR, 
			sizeof(alt_fwbs), (void *) &alt_fwbs);
		break;
	case ALT_TSI_MSG_ID:
		get_alt_tsi(data, &alt_tsi);

		// Do the turn signal filtering here
		// Wait for 750 ms after an OFF signal before reporting OFF
		// to the filtered turn signal db var
		get_current_timestamp(&turn_signal_ts);
		curr_ms = TS_TO_MS(&turn_signal_ts);
		if(alt_tsi.turn_signal) {
			alt_tsi.turn_signal_filt = alt_tsi.turn_signal;
			alt_tsi.ms_since_last_on = curr_ms;
		}
		else {
			if( (curr_ms - alt_tsi.ms_since_last_on) > TURNSIG_TIMEOUT)
				alt_tsi.turn_signal_filt = alt_tsi.turn_signal;
		}
		das3_ignition_status.ignition_status = alt_tsi.ignition;
		db_clt_write(pclt, DB_ALT_TSI_VAR, 
			sizeof(alt_tsi), (void *) &alt_tsi);
		db_clt_write(pclt, DB_DAS3_IGNITION_VAR, 
			sizeof(das3_ignition_status_t), (void *) &das3_ignition_status);
		break;
	default:	// do nothing for unknown CAN IDs
		break;
	}
}

/** May want to move variable create to separate process with other
 *  creates. Harmless to leave a copy of this list here, and just
 *  replace its use with NULL and num_db_variables with 0 in
 *  db_list_init and db_list_done.
 */
db_id_t db_vars_list[] =  {
	{DB_ALT_CCFTM_VAR, sizeof(alt_cruise_control_for_tm_t)},
	{DB_ALT_CCFD_VAR,  sizeof(alt_cruise_control_for_display_t)},
	{DB_ALT_ENG_VAR, sizeof(alt_engine_t)},
	{DB_ALT_GI_VAR, sizeof(alt_gear_indication_t)},
	{DB_ALT_VS_VAR, sizeof(alt_vehicle_speed_t)},
	{DB_ALT_FWBS_VAR, sizeof(alt_front_wiping_brake_switch_t)},
	{DB_ALT_TSI_VAR, sizeof(alt_turn_signal_ignition_t)},
	{DB_DAS3_IGNITION_VAR, sizeof(das3_ignition_status_t)},
};

int num_db_variables = sizeof(db_vars_list)/sizeof(db_id_t);

int main(int argc, char **argv)
{
	int option;	/// for getopt
	int count = 0;	/// number of PEAK CAN messages received, no error
	int num_bytes;	/// number of data bytes in the current CAN message
	unsigned long can_id;		/// CAN ID of the current CAN message
	unsigned char can_extended;	/// 1 if extended header, 0 if standard
	unsigned char can_data[8];	/// CAN data bytes, up to 8
	int peak_ts_msec;	/// millisec timestamp from Peak CAN input line
	int peak_ts_usec;	/// microseconds? not sure, not using 
	int ms_since_last_obd2_poll = 0;
	timestamp_t obd2_poll_ts;
	int curr_ms;

	int verbose = 0;	/// use to generate output, else just counts
	int do_hex = 0;		/// print CAN data using hexadecimal numbers
	FILE *fpout;
	int ret;

	/// variables for use with PATA data server
        char hostname[MAXHOSTNAMELEN];
        char *domain = DEFAULT_SERVICE; /// on Linux sets DB q-file directory
        db_clt_typ *pclt;       	/// data server client pointer
        int xport = COMM_OS_XPORT;      /// value set correctly in sys_os.h 
	int no_db = 0;
	int toggle = 0;

	/// when desk checking, may want to simulate delays
	/// simple method (when arrival assumed much slower than read from
	/// file and associated parsing) is to keep last timestamp
	/// and nanosleep time difference
	int simulate_delay = 0;		/// by default, don't do this
	int last_ts_msec = 0;


        while ((option = getopt(argc, argv, "svwn")) != EOF) {
                switch(option) {
                case 's':
			simulate_delay = 1;
			break;
                case 'v':
			verbose = 1;
			break;
		case 'w':
                        peak_can_verbose = 1;  // in nt_peak_can.c 
                        break;
                case 'n':
			no_db = 1;
			break;
		default:
			printf("Usage: %s -v (verbose) -s (simulate delay) -w (peak_can_verbose) -n (no database)\n", argv[0]);
			exit(EXIT_FAILURE);
			break;
		}
	}
	if( !no_db) {
	        get_local_name(hostname, MAXHOSTNAMELEN);
	        if ((pclt = db_list_init(argv[0], hostname, domain, xport,
	                        db_vars_list, num_db_variables, NULL, 0)) == NULL) {
	                printf("Database initialization error in %s\n", argv[0]);
	                exit(EXIT_FAILURE);
	        }
	}

        if (setjmp(exit_env) != 0) {
		if( !no_db) 
	                db_list_done(pclt, db_vars_list, num_db_variables, NULL, 0);
		printf("%s: received %d CAN messages\n", argv[0], count);
                exit(EXIT_SUCCESS);
        } else
               sig_ign(sig_list, sig_hand);

	fpout = fopen("/dev/pcan32", "w+");
	if( fpout == NULL)
		perror("fopen /dev/pcan32");
	while (1) {
		get_current_timestamp(&obd2_poll_ts);
		curr_ms = TS_TO_MS(&obd2_poll_ts);

		if( (curr_ms - ms_since_last_obd2_poll) > OBD2_POLL_TIMEOUT) {
		    if(toggle == 0) {
			ret = peak_can_send_obd2_poll(fpout, OBD2_MAF_MSG_ID, verbose);
			if(ret < 0)
				printf("peak_can_send_obd2_poll: Error in MAF fwrite to pcan32\n");
			toggle = 1;
		    }
		    else {
			ret = peak_can_send_obd2_poll(fpout, OBD2_CER_MSG_ID, verbose);
			if(ret < 0)
				printf("peak_can_send_obd2_poll: Error in CER fwrite to pcan32\n");
			toggle = 0;
		    }
			ms_since_last_obd2_poll = curr_ms;
		}


                num_bytes = peak_can_read_line(fpout, &can_id,
			&can_extended, can_data, &peak_ts_msec, &peak_ts_usec);
		if (num_bytes < 0) {
			if (num_bytes == PEAK_CAN_EOF) longjmp(exit_env, 1);
			peak_can_print_error(num_bytes);
		} else {
			if (verbose) 
				peak_can_print_line(stdout, can_id, 
					can_extended, can_data, 
					peak_ts_msec, peak_ts_usec, 
					num_bytes, do_hex);
			if (simulate_delay) {
				int ms;
				struct timespec to_wait;
				struct timespec time_left; 
				if (count == 0) 
					last_ts_msec = peak_ts_msec - 100;
				ms = peak_ts_msec - last_ts_msec; 
				to_wait.tv_sec = ms / 1000;
				to_wait.tv_nsec = (ms % 1000) * 1000000;
				if (nanosleep(&to_wait, &time_left) == EINTR)
					longjmp(exit_env, 1);
				last_ts_msec = peak_ts_msec;
			}	
			if( !no_db) 
				altima_db_write(pclt, can_id, can_data);
			count++;
		}
	}
}
