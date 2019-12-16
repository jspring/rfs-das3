#include "db_include.h"
#include "accord_can.h"
#include "das3.h"
#include "clt_vars_accord.h"
#include "can_dbvars.h"

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

const char *usage = "-v verbose -a <acceleration> -b <braking pct>";

int steinhoff_trig_list[] =  {
        DB_STEINHOFF_MSG_VAR,
		DB_OUTPUT_VAR
};

int num_steinhoff_trig_variables = sizeof(steinhoff_trig_list)/sizeof(int);

int main(int argc, char *argv[]) {
	int verbose = 0;
	int veryverbose = 0;
	int print_msg = 0;
	int option;
	int count = 0;
	int create_db_vars = 0;
	float acceleration = 0;
	float deceleration = 0;

        char hostname[MAXHOSTNAMELEN];
        char *domain = DEFAULT_SERVICE; /// on Linux sets DB q-file directory
        db_clt_typ *pclt;               /// data server client pointer
        int xport = COMM_OS_XPORT;      /// value set correctly in sys_os.h
	posix_timer_typ *ptimer;
	int ipc_message_error_ctr = 0;
	trig_info_typ trig_info;
	int recv_type;

	db_steinhoff_msg_t db_steinhoff_msg;
	db_steinhoff_out_t db_steinhoff_brake_out;
	db_steinhoff_out_t db_steinhoff_accel_out;
	input_t input;
	output_t output;
	timestamp_t ts;
	int ts_ms;
	int ts_now;
	int ts_sav;

	accord_accel_cmd_t accord_accel_cmd;
	accord_brake_cmd_t accord_brake_cmd;
	accord_vehicle_speed_t accord_vehicle_speed;
	accord_torque_t  accord_torque;
	accord_PRNDL_Pos_t  accord_PRNDL_Pos;

        while ((option = getopt(argc, argv, "vwa:b:")) != EOF) {
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
                case 'b':
                        deceleration = atof(optarg);
                        break;
                default:
                        printf("Usage: %s %s\n", argv[0], usage);
                        exit(EXIT_FAILURE);
                        break;
                }
        }

	get_local_name(hostname, MAXHOSTNAMELEN);
	if ( (pclt = db_list_init(argv[0], hostname, domain, xport,
//			NULL, 0, steinhoff_trig_list, num_steinhoff_trig_variables))
			NULL, 0, NULL, 0))
		== NULL) {
			exit(EXIT_FAILURE);
	}

	if (clt_trig_set( pclt, DB_STEINHOFF_MSG_VAR, DB_STEINHOFF_MSG_TYPE) == FALSE )
		exit(EXIT_FAILURE);

printf("accord_can: clt_trig_set OK for DB_STEINHOFF_MSG_VAR %d\n", DB_STEINHOFF_MSG_VAR);
        if (setjmp(exit_env) != 0) {
        	accord_brake_cmd.brake_cmd = 0;
			db_steinhoff_brake_out.port = BRAKE_PORT;
			db_steinhoff_brake_out.id = 0x99;
			db_steinhoff_brake_out.size = 6;
			set_accord_brake_cmd(db_steinhoff_brake_out.data, &accord_brake_cmd);
			db_clt_write(pclt, DB_STEINHOFF_BRAKE_OUT_VAR, sizeof(db_steinhoff_out_t), &db_steinhoff_brake_out);

			sleep(0.02);

			accord_accel_cmd.accel_cmd = 0;
			db_steinhoff_accel_out.port = ACCEL_PORT;
			db_steinhoff_accel_out.id = 0x98;
			db_steinhoff_accel_out.size = 1;
			set_accord_brake_cmd(db_steinhoff_accel_out.data, &accord_accel_cmd);
			db_clt_write(pclt, DB_STEINHOFF_ACCEL_OUT_VAR, sizeof(db_steinhoff_out_t), &db_steinhoff_accel_out);

        	db_list_done(pclt, NULL, 0, steinhoff_trig_list, num_steinhoff_trig_variables);
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
	memset(&accord_accel_cmd, 0, sizeof(accord_accel_cmd));
	memset(&accord_brake_cmd, 0, sizeof(accord_brake_cmd));
	memset(&accord_vehicle_speed, 0, sizeof(accord_vehicle_speed_t));
	memset(&accord_torque, 0, sizeof(accord_torque_t));
	memset(&accord_PRNDL_Pos, 0, sizeof(accord_PRNDL_Pos_t));

	accord_accel_cmd.two_message_periods = 40; 		// 2*20 msec
	accord_brake_cmd.two_message_periods = 40; 		// 2*20 msec
	accord_vehicle_speed.two_message_periods = 80;
	accord_torque.two_message_periods = 80;
	accord_PRNDL_Pos.two_message_periods = 80;


	db_clt_write(pclt, DB_ACCORD_MSG98_VAR, sizeof(accord_accel_cmd_t), &accord_accel_cmd); 
	db_clt_write(pclt, DB_ACCORD_MSG99_VAR, sizeof(accord_brake_cmd_t), &accord_brake_cmd); 
	db_clt_write(pclt, DB_ACCORD_MSG158_VAR, sizeof(accord_vehicle_speed_t), &accord_vehicle_speed);
	db_clt_write(pclt, DB_ACCORD_MSG530_VAR, sizeof(accord_torque_t), &accord_torque);
	db_clt_write(pclt, DB_ACCORD_MSG392_VAR, sizeof(accord_PRNDL_Pos_t), &accord_PRNDL_Pos);
	if(acceleration == 0)
		accord_accel_cmd.accel_cmd = 0;
	if(deceleration == 0)
		accord_brake_cmd.brake_cmd = 0;
	get_current_timestamp(&ts);
	ts_now = TS_TO_MS(&ts);
	ts_sav = ts_now;

	for(;;) {
	
		/* Now wait for a trigger. If the trigger is from the Komodo, read and parse the message. 
		** If the trigger is from the timer, it's time to send the acceleration message */
	
		recv_type= clt_ipc_receive(pclt, &trig_info, sizeof(trig_info));
		if( DB_TRIG_VAR(&trig_info) == DB_STEINHOFF_MSG_VAR ) {
			count++;
			memset(&db_steinhoff_msg.data[0], 0, 8);
			db_clt_read(pclt, DB_STEINHOFF_MSG_VAR, sizeof(db_steinhoff_msg_t), &db_steinhoff_msg);
			get_current_timestamp(&ts);
			ts_ms = TS_TO_MS(&ts);
			switch(db_steinhoff_msg.id) {
				case 0x158:
					get_accord_vehicle_speed(db_steinhoff_msg.data, &accord_vehicle_speed);
					check_msg_timeout(ts_ms, &accord_vehicle_speed.ts_ms, 
						&accord_vehicle_speed.two_message_periods, 
						&accord_vehicle_speed.message_timeout_counter); 
					input.vehicle_speed_mps = accord_vehicle_speed.vehicle_speed_CAN2_MPS;
					db_clt_write(pclt,DB_INPUT_VAR, sizeof(input_t), &input); 
					db_clt_read(pclt, DB_OUTPUT_VAR, sizeof(output_t), &output);
					if(verbose)
						printf("Accord vehicle speed %.2f output.brake_level %.2f output.throttle_pct %.2f\n", input.vehicle_speed_mps, output.brake_level,output.throttle_pct);
					break;
				case 0x530:
					get_accord_torque(db_steinhoff_msg.data, &accord_torque);
					check_msg_timeout(ts_ms, &accord_torque.ts_ms, 
						&accord_torque.two_message_periods, 
						&accord_torque.message_timeout_counter); 
					input.torque = accord_torque.generator_torque_CAN2_nm;
					db_clt_write(pclt,DB_INPUT_VAR, sizeof(input_t), &input); 
					if(verbose)
						printf("Accord generator torque %.2f motor torque %.2f\n",
							accord_torque.generator_torque_CAN2_nm,
							accord_torque.motor_torque_CAN2_nm
						);
					break;
				case 0x392:
					get_accord_PRNDL_Pos(db_steinhoff_msg.data, &accord_PRNDL_Pos);
					check_msg_timeout(ts_ms, &accord_PRNDL_Pos.ts_ms, 
						&accord_PRNDL_Pos.two_message_periods, 
						&accord_PRNDL_Pos.message_timeout_counter); 
					input.gear = accord_PRNDL_Pos.prndl;
					db_clt_write(pclt,DB_INPUT_VAR, sizeof(input_t), &input); 
					if(verbose)
						printf("Accord PRNDL position %hhu\n",
							accord_PRNDL_Pos.prndl
						);
					break;
				default:
					printf("Unknown message %#hx received\n");
					break;
			}
		}

		get_current_timestamp(&ts);
		ts_now = TS_TO_MS(&ts);

		if(ts_now - ts_sav >= 20){
			ts_sav = ts_now;

			db_clt_read(pclt, DB_OUTPUT_VAR, sizeof(output_t), &output);

			memset(&db_steinhoff_brake_out, 0, sizeof(db_steinhoff_out_t));
			if(deceleration > 0)
				accord_brake_cmd.brake_cmd = deceleration;
			else
				accord_brake_cmd.brake_cmd = output.brake_level;
			if(accord_brake_cmd.brake_cmd > 0)
				output.throttle_pct = 0;		//if braking is requested, set throttle to 0
			db_steinhoff_brake_out.port = BRAKE_PORT;
			db_steinhoff_brake_out.id = 0x99;
			db_steinhoff_brake_out.size = 6;
			set_accord_brake_cmd(db_steinhoff_brake_out.data, &accord_brake_cmd);
			printf("accord_can: db_steinhoff_out.data[2] %hhx\n", db_steinhoff_brake_out.data[2]);
			db_clt_write(pclt, DB_STEINHOFF_BRAKE_OUT_VAR, sizeof(db_steinhoff_out_t), &db_steinhoff_brake_out);

			memset(&db_steinhoff_accel_out, 0, sizeof(db_steinhoff_out_t));
			if(acceleration > 0) {
				accord_accel_cmd.accel_cmd = acceleration;
				accord_brake_cmd.brake_cmd = 0;
			}
			else
				accord_accel_cmd.accel_cmd = output.throttle_pct;
			db_steinhoff_accel_out.port = ACCEL_PORT;
			db_steinhoff_accel_out.id = 0x98;
			db_steinhoff_accel_out.size = 1;
			set_accord_accel_cmd(db_steinhoff_accel_out.data, &accord_accel_cmd);
			printf("accord_can: db_steinhoff_out.data[0] %hhx acceleration %.2f\n", db_steinhoff_accel_out.data[0], accord_accel_cmd.accel_cmd);
			db_clt_write(pclt, DB_STEINHOFF_ACCEL_OUT_VAR, sizeof(db_steinhoff_out_t), &db_steinhoff_accel_out);

			TIMER_WAIT (ptimer);
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
