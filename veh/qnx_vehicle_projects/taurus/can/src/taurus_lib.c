/*
** m56_lib.c - contains function definitions for m56_can.c
*/

#include <db_include.h>
#include <komodo.h>
#include <taurus_can.h>

//taurus_ignition_status_t taurus_ignition_status;

int printmsg(db_komodo_t *db_kom) {
	int i;
}

int printcan(db_komodo_t *db_kom){
	int i;

	printf("CAN ID: %#03x msg: ", db_kom->id);
	for(i=0 ; i<8; i++)
		printf("%#02x ", db_kom->msg[i]);
	printf("\n");
	return 0;
}

int print_accel_cmd(taurus_accel_cmd_t *taurus_accel_cmd) {
	printf("taurus_accel_cmd:  acceleration %.3f\n",
		taurus_accel_cmd->accel_cmd
	);
}

int print_wheel_speed(taurus_wheel_speed_t *taurus_wheel_speed) {
	printf("taurus_wheel_speed: front right %.2f front left %.2f rear right %.2f rear left %.2f\n",
		taurus_wheel_speed->veh_wheel_spd_FR_CAN1_kph,
		taurus_wheel_speed->veh_wheel_spd_FL_CAN1_kph,
		taurus_wheel_speed->veh_wheel_spd_RR_CAN1_kph,
		taurus_wheel_speed->veh_wheel_spd_RL_CAN1_kph
	);
}

int print_vehicle_speed(taurus_vehicle_speed_t *taurus_vehicle_speed) {
	printf("taurus_vehicle_speed:  vehicle speed %.3f\n",
		taurus_vehicle_speed->veh_spd_CAN1_kph
	);
}

int print_long_lat_accel(taurus_long_lat_accel_t *taurus_long_lat_accel) {
	printf("taurus_long_lat_accel:  longitudinal acceleration %.3f latitudinal acceleration %.3f\n",
		taurus_long_lat_accel->long_accel,
		taurus_long_lat_accel->lat_accel
	);
}

int print_accel_cmd_status(taurus_accel_cmd_status_t *taurus_accel_cmd_status) {
	printf("taurus_accel_cmd_status:  set_me_x3  %#hhx distance %#hhx mini_car %#hhx set_me_x01 %#hhx cancel_req %#hhx set_me_1 %#hhx release_standstill %#hhx checksum %#hhx checksum_check %#hhx\n",
		taurus_accel_cmd_status->set_me_x3,
		taurus_accel_cmd_status->distance,
		taurus_accel_cmd_status->mini_car,
		taurus_accel_cmd_status->set_me_x01,
		taurus_accel_cmd_status->cancel_req,
		taurus_accel_cmd_status->set_me_1,
		taurus_accel_cmd_status->release_standstill,
		taurus_accel_cmd_status->checksum,
		taurus_accel_cmd_status->checksum_check
	);
}

int print_cruise_control_state(taurus_cruise_control_state_t *taurus_cruise_control_state) {
	printf("taurus_cruise_control_state:  cruise_main_on_CAN1 %#hhx cruise_control_state_CAN1 %#hhx cruise_dash_set_speed_CAN1 %#hhx\n",
		taurus_cruise_control_state->cruise_main_on_CAN1,
		taurus_cruise_control_state->cruise_control_state_CAN1,
		taurus_cruise_control_state->cruise_dash_set_speed_CAN1
	);
}
