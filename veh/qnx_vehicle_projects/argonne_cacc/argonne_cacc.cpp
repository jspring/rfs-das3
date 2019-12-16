#include "argonne_cacc.hpp"

extern "C" {
#include "db_include.h"
#include <clt_vars_accord.h>
//#include <clt_vars_taurus.h>
//#include <clt_vars_prius.h>
}
static db_clt_typ *pclt;
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

int main(int argc, char *argv[])
{
	Initialization_task(argv);

	int a = 1;
	while(a==1) {
		if (!Read_inputs()){			
			break;
		}
		if (!Process_data()) {
			break;
		}			
		if (!Write_outputs()) {
			break;
		}
		// sleep
		sleep(0.001);
	}
	End_tasks();
	return 0;
}

void Initialization_task(char *argv[]) {

	char hostname[MAXHOSTNAMELEN];
	char *domain; /// on Linux sets DB q-file directory
	int xport = COMM_OS_XPORT;      /// value set correctly in sys_os.h

        get_local_name(hostname, MAXHOSTNAMELEN);
        if ( (pclt = db_list_init(argv[0], hostname, domain, xport,
                (db_id_t *)NULL, (int)0, (int *)NULL, (int)0))
                == NULL) {
                        exit(EXIT_FAILURE);
        }
        if (setjmp(exit_env) != 0) {
                db_list_done(pclt, (db_id_t *)NULL, (int)0, (int *)NULL, (int)0);
                exit(EXIT_SUCCESS);
        } else
               sig_ign(sig_list, sig_hand);

	control_mode = CRUISE;
	control_structure = new long_control(ACCORD, TS, control_mode);

	// Initialize database related variables

	return;
}

bool Read_inputs() {
	input_t input;
	// Read vehicle state variables from database
	db_clt_read(pclt,DB_INPUT_VAR, sizeof(input_t), &input);
	i_long_speed = input.vehicle_speed_mps;
	i_long_acceleration = input.vehicle_accel_mps2;
	printf("argonne_cacc IN: vehicle_speed_mps %.2f vehicle_accel_mps2 %.2f\n",
			i_long_speed,
			i_long_acceleration
		);

	switch (control_mode) {
	case(OPEN_LOOP):
		control_structure->Update_Open_loop_inputs(i_long_speed, i_long_acceleration, i_desired_acceleration);
		break;
	case(CRUISE):
		control_structure->Update_Cruise_inputs(i_long_speed, i_long_acceleration, i_setpoint_speed);
		break;
	case(ACC):
		break;
	case(CACC):
		break;
	}
	return true;
}

bool Process_data() {
	control_structure->Execute_control();
	o_throttle_command = control_structure->Get_throttle_command();
//	o_brake_command = control_structure->Get_brake_command();
	return true;
}

bool Write_outputs() {
	static int i = 0;
	static int test_mode = 1;
	output_t output;

	i++;
	// Write throttle and deceleration command in database
	if(test_mode == 1) {
		o_brake_command = 0;
		o_throttle_command = 0;
		if( (i > 50000) && (i_long_speed < 15) ){
			o_brake_command = 0;
			o_throttle_command = 30;
		}
		if(i > 100000) {
			o_brake_command = 60;
			o_throttle_command = 0;
			}
		if(	(i_long_speed < 0.1) && (i > 150000)) {
			o_brake_command = 0;
			o_throttle_command = 0;
			test_mode = 0;
			}
	}
	output.brake_level = o_brake_command;
	output.throttle_pct = o_throttle_command;
	db_clt_write(pclt,DB_OUTPUT_VAR, sizeof(output_t), &output);
	printf("argonne_cacc OUT: o_brake_command %.2f output.brake_level %.2f output.throttle_pct %.2f i %d i_long_speed %.2f test_mode %d\n",
			o_brake_command,
			output.brake_level,
			output.throttle_pct,
			i,
			i_long_speed,
			test_mode
		);

	// Receive and send variables to HMI program through socket
	return true;
}

void End_tasks() {
	return;
}
