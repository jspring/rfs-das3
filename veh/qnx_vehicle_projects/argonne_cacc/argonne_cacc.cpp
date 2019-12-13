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
	Initialization_task();
	char hostname[MAXHOSTNAMELEN];
//	char *domain = "db_slv"; /// on Linux sets DB q-file directory
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
	}
	End_tasks();
	return 0;
}

void Initialization_task() {
	control_mode = CRUISE;
	control_structure = new long_control(ACCORD, TS, control_mode);

	// Initialize database related variables

	return;
}

bool Read_inputs() {
	// Read vehicle state variables from database

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
	o_brake_command = control_structure->Get_brake_command();
	return true;
}

bool Write_outputs() {
	// Write throttle and deceleration command in database

	// Receive and send variables to HMI program through socket
	return true;
}

void End_tasks() {
	return;
}
