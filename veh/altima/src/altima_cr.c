/* \file 
 *
 * 	Copyright (c) 2010   Regents of the University of California
 *
 */

#include <db_include.h>
#include <db_utils.h>
#include <path_gps_lib.h>
#include <evt300.h>
#include <db_sync.h>
#include "uimu.h"
#include "altima.h"
#include "das3.h"


/** Why are these variables global?
 */
evt300_radar_typ evt300a;
path_gps_point_t local_gps;              // on-vehicle GPS
uimu_typ uimu;
sync_record_typ video;
alt_turn_signal_ignition_t alt_tsi;
das3_ignition_status_t das3_ignition_status;

/** Output variables for the long_trk process are created with this list. 
 */
static db_id_t db_vars_list[] = {
        {DB_EVT300_RADAR1_VAR, sizeof(evt300_radar_typ)},
        {DB_GPS_PT_LCL_VAR, sizeof(path_gps_point_t)},
        {DB_SYNC_RECORD_VAR, sizeof(sync_record_typ)},
        {DB_UIMU_VAR, sizeof(uimu_typ)},
        {DB_ALT_CCFTM_VAR, sizeof(alt_cruise_control_for_tm_t)},
        {DB_ALT_CCFD_VAR,  sizeof(alt_cruise_control_for_display_t)},
        {DB_ALT_ENG_VAR, sizeof(alt_engine_t)},
        {DB_ALT_GI_VAR, sizeof(alt_gear_indication_t)},
        {DB_ALT_VS_VAR, sizeof(alt_vehicle_speed_t)},
        {DB_ALT_FWBS_VAR, sizeof(alt_front_wiping_brake_switch_t)},
        {DB_ALT_TSI_VAR, sizeof(alt_turn_signal_ignition_t)},
        {DB_OBD2_MAF_VAR, sizeof(obd2_maf_t)},
        {DB_OBD2_CER_VAR, sizeof(obd2_cer_t)},
        {DB_DAS3_IGNITION_VAR, sizeof(das3_ignition_status_t)},
};
#define NUM_DB_VARS	sizeof(db_vars_list)/sizeof(db_id_t)

static int sig_list[] = 
{
	SIGINT,
	SIGQUIT,
	SIGTERM,
	SIGALRM,
	ERROR,
};

static jmp_buf exit_env;

static void sig_hand(int code)
{
	if (code == SIGALRM)
		return;
	else
		longjmp(exit_env, code);
}


int main(int argc, char *argv[])
{
	db_clt_typ *pclt;              /* Database client pointer */
	char hostname[MAXHOSTNAMELEN+1];
        char *domain=DEFAULT_SERVICE;
        int xport = COMM_OS_XPORT;
	int option;
	posix_timer_typ *ptimer;
	int delay_ms = 1000;	// wake up once a second
	char dummy[MAX_DATA_SIZE];	// used when initializing variables
	int i;
	int id;
	int size;
	int verbose = 0;
	timestamp_t current_ts;
        while ((option = getopt(argc, argv, "t:v")) != EOF) {
                switch(option) {
		case 't':
			delay_ms = atoi(optarg);
			break;
		case 'v':
			verbose = 1;
			break;
		default:
			fprintf(stderr, "Usage %s -t <millisec> -v (verbose)\n",				argv[0]);
			exit(1);
			break;
                }
	}

	get_local_name(hostname, MAXHOSTNAMELEN);
	pclt = db_list_init(argv[0], hostname, domain, xport, db_vars_list, 
		NUM_DB_VARS, NULL, 0);

	/* Catch the signals SIGINT, SIGQUIT, and SIGTERM.  If signal occurs,
	 * log out from database and exit. */
	if (setjmp(exit_env) != 0) {
		if (pclt != NULL)
			db_list_done(pclt, db_vars_list, NUM_DB_VARS, NULL, 0);
		exit(EXIT_SUCCESS);
	} else
		sig_ign(sig_list, sig_hand);

        if ((ptimer = timer_init( delay_ms, ChannelCreate(0) )) == NULL)
        {
                fprintf(stderr, "Unable to initialize delay timer\n");
                exit(EXIT_FAILURE);
        }

	// Create and initialize additional variables  to 0
        for (i = 0; i < NUM_DB_VARS; i++) {
                id = db_vars_list[i].id;
		size = db_vars_list[i].size;
		clt_create(pclt, id, id, size);
        }
	memset(dummy, 0, MAX_DATA_SIZE);

        for (i = 0; i < NUM_DB_VARS; i++) {
                int id = db_vars_list[i].id;
		int size = db_vars_list[i].size;
		db_clt_write(pclt, id, size, (void *) dummy); 
        }
	/** Do special initializations
	 */
	alt_tsi.ignition = 1;	// assume on unless set off by driver
	das3_ignition_status.ignition_status = alt_tsi.ignition;
	db_clt_write(pclt, DB_ALT_TSI_VAR, sizeof(alt_tsi), (void *) &alt_tsi); 
	db_clt_write(pclt, DB_DAS3_IGNITION_VAR, sizeof(das3_ignition_status_t), (void *) &das3_ignition_status); 
	if (verbose)
		printf("Initializing alt_tsi.ignition and audi.ignition.digin to 1\n");

	// Loop forever doing nothing until terminated with signal
	// In verbose mode print timestamp to track that process is alive 
	while (TRUE) {
		if (verbose) {
                       get_current_timestamp(&current_ts);
                       print_timestamp(stdout,&current_ts);
                       printf("%s \n", argv[0]);
		}
		TIMER_WAIT (ptimer);
	}
}

