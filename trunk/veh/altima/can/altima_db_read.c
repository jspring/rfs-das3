/**\file
 *  	Example of reading Altima CAN data from data server 
 *  	and using the scaling functions to print in correct units
 */
#include <sys_os.h>
#include <local.h>
#include <sys_rt.h>
#include <db_clt.h>
#include <db_utils.h>
#include "nt_peak_can.h"
#include "timestamp.h"
#include "altima.h"

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
void altima_db_read(db_clt_typ *pclt, 
	alt_cruise_control_for_tm_t *palt_ccftm,
	alt_cruise_control_for_display_t *palt_ccfd,
	alt_engine_t *palt_eng,
	alt_gear_indication_t *palt_gi,
	alt_vehicle_speed_t *palt_vs,
	alt_front_wiping_brake_switch_t *palt_fwbs,
	alt_turn_signal_ignition_t *palt_tsi)
{
	db_clt_read(pclt, DB_ALT_CCFTM_VAR, 
		sizeof(alt_cruise_control_for_tm_t), (void *) palt_ccftm);
	db_clt_read(pclt, DB_ALT_CCFD_VAR, 
		sizeof(alt_cruise_control_for_display_t), (void *) palt_ccfd);
	db_clt_read(pclt, DB_ALT_ENG_VAR, 
		sizeof(alt_engine_t), (void *) palt_eng);
	db_clt_read(pclt, DB_ALT_GI_VAR, 
		sizeof(alt_gear_indication_t), (void *) palt_gi);
	db_clt_read(pclt, DB_ALT_VS_VAR, 
		sizeof(alt_vehicle_speed_t), (void *) palt_vs);
	db_clt_read(pclt, DB_ALT_FWBS_VAR, 
		sizeof(alt_front_wiping_brake_switch_t), (void *) palt_fwbs);
	db_clt_read(pclt, DB_ALT_TSI_VAR, 
		sizeof(alt_turn_signal_ignition_t), (void *) palt_tsi);
}

int main(int argc, char **argv)
{
	int option;	/// for getopt
	int count = 0;	/// number of PEAK CAN messages received, no error
	int max_count = 0;	/// if 0, run forever
	int verbose = 0;	/// use to generate output, else just counts

	/// variables for use with PATA data server
        char hostname[MAXHOSTNAMELEN];
        char *domain = DEFAULT_SERVICE; /// on Linux sets DB q-file directory
        db_clt_typ *pclt;       	/// data server client pointer
        int xport = COMM_OS_XPORT;      /// value set correctly in sys_os.h 
        alt_cruise_control_for_tm_t alt_ccftm;
        alt_cruise_control_for_display_t alt_ccfd;
        alt_engine_t alt_eng;
        alt_gear_indication_t alt_gi;
        alt_vehicle_speed_t alt_vs;
        alt_front_wiping_brake_switch_t alt_fwbs;
        alt_turn_signal_ignition_t alt_tsi;

	/// variables for use with Posix timer
        posix_timer_typ *ptmr;
        int interval = 500;	/// default 500 ms read 

        while ((option = getopt(argc, argv, "i:n:vw")) != EOF) {
                switch(option) {
		case 'i':	// specify interval of wait between reads
			interval = atoi(optarg);
			break;
                case 'n':	// specify total number of reads
			max_count = atoi(optarg);
			break;
                case 'v':
			verbose = 1;
			break;
		case 'w':
                        peak_can_verbose = 1;  // in nt_peak_can.c 
                        break;
		default:
			printf("Usage: %s -v (verbose) ", argv[0]);
			printf("-n number of reads -i timer interval ");
			printf(" -v verbose -w very verbose ");
			printf("\n");
			exit(EXIT_FAILURE);
			break;
		}
	}
	if ((ptmr = timer_init(interval, 0)) == NULL) {
                        printf("timer_init failed\n");
                        exit(EXIT_FAILURE);
	}

        get_local_name(hostname, MAXHOSTNAMELEN);
        if ((pclt = db_list_init(argv[0], hostname, domain, xport,
			NULL, 0, NULL, 0)) == NULL) {
                printf("Database initialization error in %s\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        if (setjmp(exit_env) != 0) {
		db_list_done(pclt, NULL, 0, NULL, 0);
		printf("%s: read %d times from DB server\n", argv[0], count);
                exit(EXIT_SUCCESS);
        } else
               sig_ign(sig_list, sig_hand);

	while (1) {
		altima_db_read(pclt, &alt_ccftm, &alt_ccfd, 
			&alt_eng, &alt_gi, &alt_vs, &alt_fwbs, &alt_tsi);
		if (verbose) {
			print_timestamp(stdout, &alt_tsi.ts);
			printf("%hhu ", alt_ccftm.code);
			printf("%hhu ", alt_ccfd.code);
			printf("%hhu ", alt_gi.code);
			printf("%7.2f ", scale_alt_rpm(alt_eng.rpm));
			printf("%7.2f ", 
				scale_alt_acceleration(alt_eng.acceleration));
			printf("%7.2f ", 
				scale_alt_vehicle_speed(alt_vs.vehicle_speed));
			printf("%hhu ", alt_fwbs.front_wiping);
			printf("%hhu ", alt_fwbs.brake_switch);
			printf("%hhu ", alt_tsi.turn_signal);
			printf("%hhu ", alt_tsi.ignition);
			printf("\n");
			fflush(stdout);
		}
			count++;
		if ((max_count != 0) && (count >= max_count))
			longjmp(exit_env, 1);
		TIMER_WAIT(ptmr);
	}
}
