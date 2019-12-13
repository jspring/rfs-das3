#include "db_include.h"
#include "komodo.h"
#include "taurus_can.h"
#include "das3.h"
#include "clt_vars_taurus.h"

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

const char *usage = "-v verbose -a <acceleration>";

int komodo_trig_list[] =  {
        DB_KOMODO_VAR
};

int num_komodo_trig_variables = sizeof(komodo_trig_list)/sizeof(int);

int main(int argc, char *argv[]) {
	int verbose = 0;
	int veryverbose = 0;
	int print_msg = 0;
	int option;
	int count = 0;
	int create_db_vars = 0;
	float acceleration = 0;

        char hostname[MAXHOSTNAMELEN];
        char *domain = DEFAULT_SERVICE; /// on Linux sets DB q-file directory
        db_clt_typ *pclt;               /// data server client pointer
        int xport = COMM_OS_XPORT;      /// value set correctly in sys_os.h
	posix_timer_typ *ptimer;
	int ipc_message_error_ctr = 0;
	trig_info_typ trig_info;
	int recv_type;

	db_komodo_t db_kom;
	timestamp_t ts;
	int ts_ms;

        taurus_accel_cmd_status_t taurus_accel_cmd_status;
        taurus_accel_cmd_t taurus_accel_cmd;
	taurus_cruise_control_state_t taurus_cruise_control_state;
	taurus_vehicle_speed_t taurus_vehicle_speed;
	taurus_wheel_speed_t taurus_wheel_speed;
	taurus_long_lat_accel_t taurus_long_lat_accel;

        while ((option = getopt(argc, argv, "vwa:")) != EOF) {
                switch(option) {
                case 'v':
                        verbose = 1;
                        break;
                case 'w':
                        verbose = 1;
                        veryverbose = 1;
                        break;
                case 'a':
                        acceleration = atof(optarg);
                        break;
                default:
                        printf("Usage: %s %s\n", argv[0], usage);
                        exit(EXIT_FAILURE);
                        break;
                }
        }

	get_local_name(hostname, MAXHOSTNAMELEN);
	if ( (pclt = db_list_init(argv[0], hostname, domain, xport,
		NULL, 0, komodo_trig_list, num_komodo_trig_variables))
//		NULL, 0, NULL, 0))
		== NULL) {
			exit(EXIT_FAILURE);
	}
//	if (clt_trig_set( pclt, DB_KOMODO_VAR, DB_KOMODO_TYPE) == FALSE )
//		exit(EXIT_FAILURE);

printf("taurus_can: clt_trig_set OK for DB_KOMODO_VAR %d\n", DB_KOMODO_VAR);
        if (setjmp(exit_env) != 0) {
                db_list_done(pclt, db_vars_list, NUM_DB_VARS, NULL, 0);
                printf("%s: received %d CAN messages %d IPC message errors\n", 
			argv[0], count, ipc_message_error_ctr);
                exit(EXIT_SUCCESS);
        } else
               sig_ign(sig_list, sig_hand);

        if ((ptimer = timer_init( 20, ChannelCreate(0) )) == NULL) {
                fprintf(stderr, "Unable to initialize delay timer\n");
                exit(EXIT_FAILURE);
        }

	/* Zero data structures */
	memset(&taurus_accel_cmd, 0, sizeof(taurus_accel_cmd));
	memset(&taurus_accel_cmd_status, 0, sizeof(taurus_accel_cmd_status_t));
	memset(&taurus_cruise_control_state, 0, sizeof(taurus_cruise_control_state_t));
	memset(&taurus_vehicle_speed, 0, sizeof(taurus_vehicle_speed_t));
	memset(&taurus_wheel_speed, 0, sizeof(taurus_wheel_speed_t));
	memset(&taurus_long_lat_accel, 0, sizeof(taurus_long_lat_accel_t));

	taurus_accel_cmd.two_message_periods = 80; 		// 2*10 msec
	taurus_accel_cmd_status.two_message_periods = 80; 		// 2*10 msec
	taurus_cruise_control_state.two_message_periods = 80;
	taurus_vehicle_speed.two_message_periods = 80;
	taurus_wheel_speed.two_message_periods = 80;
	taurus_long_lat_accel.two_message_periods = 80;


	db_clt_write(pclt, DB_TAURUS_MSG99_VAR, sizeof(taurus_accel_cmd_t), &taurus_accel_cmd); 
	db_clt_write(pclt, DB_TAURUS_MSG343_VAR, sizeof(taurus_accel_cmd_status_t), &taurus_accel_cmd_status); 
	db_clt_write(pclt, DB_TAURUS_MSG343_VAR, sizeof(taurus_cruise_control_state_t), &taurus_cruise_control_state);
	db_clt_write(pclt, DB_TAURUS_MSG343_VAR, sizeof(taurus_vehicle_speed_t), &taurus_vehicle_speed);
	db_clt_write(pclt, DB_TAURUS_MSG343_VAR, sizeof(taurus_wheel_speed_t), &taurus_wheel_speed);
	db_clt_write(pclt, DB_TAURUS_MSG343_VAR, sizeof(taurus_long_lat_accel_t), &taurus_long_lat_accel);

	for(;;) {
	
		/* Now wait for a trigger. If the trigger is from the Komodo, read and parse the message. 
		** If the trigger is from the timer, it's time to send the acceleration message */
	
		recv_type= clt_ipc_receive(pclt, &trig_info, sizeof(trig_info));
		if( DB_TRIG_VAR(&trig_info) == DB_KOMODO_VAR ) {
			count++;
			db_clt_read(pclt, DB_KOMODO_VAR, sizeof(db_komodo_t), &db_kom);
			get_current_timestamp(&ts);
			ts_ms = TS_TO_MS(&ts);
			switch(db_kom.id) {
				case 0xAA:
					get_taurus_wheel_speed(db_kom.msg, &taurus_wheel_speed);
					check_msg_timeout(ts_ms, &taurus_wheel_speed.ts_ms, 
						&taurus_wheel_speed.two_message_periods, 
						&taurus_wheel_speed.message_timeout_counter); 
					db_clt_write(pclt,DB_TAURUS_MSGAA_VAR, sizeof(taurus_wheel_speed_t), &taurus_wheel_speed); 
					if(verbose)
						print_wheel_speed(&taurus_wheel_speed);
					break;
				case 0xB4:
					get_taurus_vehicle_speed(db_kom.msg, &taurus_vehicle_speed);
					check_msg_timeout(ts_ms, &taurus_vehicle_speed.ts_ms, 
						&taurus_vehicle_speed.two_message_periods, 
						&taurus_vehicle_speed.message_timeout_counter); 
					db_clt_write(pclt,DB_TAURUS_MSGB4_VAR, sizeof(taurus_vehicle_speed_t), &taurus_vehicle_speed); 
					if(verbose)
						print_vehicle_speed(&taurus_vehicle_speed);
					break;
				case 0x228:
					get_taurus_long_lat_accel(db_kom.msg, &taurus_long_lat_accel);
					check_msg_timeout(ts_ms, &taurus_long_lat_accel.ts_ms, 
						&taurus_long_lat_accel.two_message_periods, 
						&taurus_long_lat_accel.message_timeout_counter); 
					db_clt_write(pclt,DB_TAURUS_MSG228_VAR, sizeof(taurus_long_lat_accel), &taurus_long_lat_accel); 
					if(verbose)
						print_long_lat_accel(&taurus_long_lat_accel);
					break;
					break;
				case 0x343:
					get_taurus_accel_cmd_status(db_kom.msg, &taurus_accel_cmd_status);
					check_msg_timeout(ts_ms, &taurus_accel_cmd_status.ts_ms, 
						&taurus_accel_cmd_status.two_message_periods, 
						&taurus_accel_cmd_status.message_timeout_counter); 
					db_clt_write(pclt,DB_TAURUS_MSG343_VAR, sizeof(taurus_accel_cmd_status_t), &taurus_accel_cmd_status); 
					if(verbose)
						print_accel_cmd_status(&taurus_accel_cmd_status);
					break;
				case 0x399:
					get_taurus_cruise_control_state(db_kom.msg, &taurus_cruise_control_state);
					check_msg_timeout(ts_ms, &taurus_cruise_control_state.ts_ms, 
						&taurus_cruise_control_state.two_message_periods, 
						&taurus_cruise_control_state.message_timeout_counter); 
					db_clt_write(pclt,DB_TAURUS_MSG343_VAR, sizeof(taurus_cruise_control_state), &taurus_cruise_control_state); 
					if(verbose)
						print_cruise_control_state(&taurus_cruise_control_state);
					break;
				default:
//					printf("Unknown message %#hx received\n");
					break;
			}
			if(print_msg)
				printmsg(&db_kom);
			if(veryverbose) {
				printcan(&db_kom);
				printmsg(&db_kom);
			}
		}	
		else {
			db_clt_read(pclt,DB_TAURUS_MSG99_VAR, sizeof(taurus_accel_cmd_t), &taurus_accel_cmd); 
			db_clt_write(pclt,DB_TAURUS_MSG99_VAR, sizeof(taurus_accel_cmd_t), &taurus_accel_cmd); 
			TIMER_WAIT (ptimer);
			ipc_message_error_ctr++;
		}
	}
	return 0;
}

void check_msg_timeout(int curr_ts_ms, int *prev_ts_ms, 
	unsigned char *two_message_periods, 
	unsigned int *message_timeout_counter) {
	if( (curr_ts_ms - *prev_ts_ms) > *two_message_periods ) {
	   ++*message_timeout_counter;
	   *prev_ts_ms = curr_ts_ms;
	}
}
