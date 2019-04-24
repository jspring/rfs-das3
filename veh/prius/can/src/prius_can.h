#pragma once

#include <komodo.h>

#ifndef PRIUS_CAN_H
#define PRIUS_CAN_H

//Define some resolutions and offsets
#define steering_angle_res  0.1 //deg
#define steering_velocity_res  4 //deg/sec
#define rpm_res  0.125
#define mean_eff_tq_res 0.5
#define mean_eff_tq_off 400
#define pedal_pos_res  0.392
#define wheel_speed_res  0.04166666
#define vehicle_speed_res  0.01
#define acceleration_res  0.001
#define acceleration_offset  -2.048
#define yaw_rate_res  0.1
#define yaw_rate_offset  -204.8
#define estimated_pressure_res 0.05
#define its_target_pressure_res 0.05
#define targ_eng_tq_res 0.4
#define virtual_accelerator_angle_res 0.392
#define lidar_res 0.1
#define yaw_rate_sensor_res 0.050
#endif

#define MASK_b0	 0x01
#define MASK_b01 0x03
#define MASK_b02 0x07
#define MASK_b03 0x0F
#define MASK_b04 0x1F
#define MASK_b07 0xFF
#define MASK_b1	 0x02
#define MASK_b12 0x06
#define MASK_b2	 0x04
#define MASK_b23 0x0C
#define MASK_b3	 0x08
#define MASK_b34 0x18
#define MASK_b4	 0x10
#define MASK_b45 0x30
#define MASK_b47 0xF0
#define MASK_b5	 0x20
#define MASK_b6	 0x40
#define MASK_b67 0xC0
#define MASK_b7	 0x80
#define PRIUS_IGNITION_MASK 0X01
#define SHORT2FLOAT(low,high)	((float)((signed short)((low) + (high << 8))))
#define CHAR2FLOAT(low)	((float)((signed char)(low)))

/*******************************************************************************
 *      prius_accel_cmd
 *      Message ID      0x99
 *      Transmitted every 20 ms
 *
 *	accel_cmd
 *      Byte Position   0-1
 *      Bit Position    0
 *      Bit Length      16
 *
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float accel_cmd;
} prius_accel_cmd_t;

static inline void set_prius_accel_cmd(unsigned char data[], prius_accel_cmd_t *p) {
	short accel_cmd_short;

	accel_cmd_short =  (short)(p->accel_cmd / acceleration_res);
	data[0] = (accel_cmd_short & 0xf0) >> 8;
	data[1] = accel_cmd_short & 0x0f;
}

/*******************************************************************************
 *      prius_wheel_speed
 *      Message ID      0xAA
 *      Transmitted every 40 ms
 *
 *	dbvar = DB_PRIUS_MSGAA_VAR
 *
 *	veh_wheel_spd_FR_CAN1_kph
 *      Byte Position   0-1
 *      Bit Position    0
 *      Bit Length      16
 *
 *	veh_wheel_spd_FL_CAN1_kph
 *      Byte Position   2-3
 *      Bit Position    0
 *      Bit Length      16
 *
 *	veh_wheel_spd_FR_CAN1_kph
 *      Byte Position   4-5
 *      Bit Position    0
 *      Bit Length      16
 *
 *	veh_wheel_spd_RL_CAN1_kph
 *      Byte Position   6-7
 *      Bit Position    0
 *      Bit Length      16
 *
 */

#define WHEEL_SPEED_RES		0.01
#define WHEEL_SPEED_OFFSET	67.67

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float veh_wheel_spd_FR_CAN1_kph;
	float veh_wheel_spd_FL_CAN1_kph;
	float veh_wheel_spd_RR_CAN1_kph;
	float veh_wheel_spd_RL_CAN1_kph;
} prius_wheel_speed_t;

static inline void get_prius_wheel_speed(unsigned char *data, prius_wheel_speed_t *p) {
	p->veh_wheel_spd_FR_CAN1_kph = (float)((short)(((data[0] << 8) + data[1]) * WHEEL_SPEED_RES) - WHEEL_SPEED_OFFSET);
	p->veh_wheel_spd_FL_CAN1_kph = (float)((short)(((data[2] << 8) + data[3]) * WHEEL_SPEED_RES) - WHEEL_SPEED_OFFSET);
	p->veh_wheel_spd_RR_CAN1_kph = (float)((short)(((data[4] << 8) + data[5]) * WHEEL_SPEED_RES) - WHEEL_SPEED_OFFSET);
	p->veh_wheel_spd_RL_CAN1_kph = (float)((short)(((data[6] << 8) + data[7]) * WHEEL_SPEED_RES) - WHEEL_SPEED_OFFSET);
}

/*******************************************************************************
 *      prius_vehicle_speed
 *      Message ID      0xB4
 *      Transmitted every 40 ms
 *
 *	dbvar = DB_PRIUS_MSGB4_VAR
 *
 *	veh_spd_CAN1_kph
 *      Byte Position   6-7
 *      Bit Position    0
 *      Bit Length      16
 *
 */

#define VEH_SPEED_RES		0.01

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float veh_spd_CAN1_kph;
} prius_vehicle_speed_t;

static inline void get_prius_vehicle_speed(unsigned char *data, prius_vehicle_speed_t *p) { 
	p->veh_spd_CAN1_kph = (float)((short)(((data[6] << 8) + data[7]) * VEH_SPEED_RES));
}


/*******************************************************************************
 *      prius_long_lat_accel
 *      Message ID      0x228
 *      Transmitted every 40 ms
 *
 *	dbvar = DB_PRIUS_MSG228_VAR
 *
 *	long_accel
 *      Byte Position   1-2
 *      Bit Position    8
 *      Bit Length      15
 *
 *	lat_accel 
 *      Byte Position   3-4
 *      Bit Position    24
 *      Bit Length      15
 *
 */

#define LONG_LAT_ACCEL_RES	0.001
#define LONG_LAT_ACCEL_OFFSET	16.384

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float long_accel;
	float lat_accel;
} prius_long_lat_accel_t;

static inline void get_prius_long_lat_accel(unsigned char *data, prius_long_lat_accel_t *p) {
	p->long_accel = (float)((short)(((data[1] << 8) + data[2]) * LONG_LAT_ACCEL_RES) - LONG_LAT_ACCEL_OFFSET);
	p->lat_accel =  (float)((short)(((data[3] << 8) + data[4]) * LONG_LAT_ACCEL_RES) - LONG_LAT_ACCEL_OFFSET);
}

/*******************************************************************************
 *      prius_accel_cmd_status
 *      Message ID      0x343
 *      Transmitted every 40 ms
 *
 *	dbvar = DB_PRIUS_MSG343_VAR
 *
 *	message_counter
 *      Byte Position   0
 *      Bit Position    0
 *      Bit Length      8
 *
 *	accel_cmd
 *      Byte Position   1-2
 *      Bit Position    8
 *      Bit Length      16
 *
 *	brake_nc_sw
 *      Byte Position   4
 *      Bit Position    6
 *      Bit Length      1
 *
 *	brake_no_sw
 *      Byte Position   4
 *      Bit Position    5
 *      Bit Length      1
 *
 *
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float accel_cmd_status;
	unsigned char set_me_x3;
	unsigned char distance;
	unsigned char mini_car;
	unsigned char set_me_x01;
	unsigned char cancel_req;
	unsigned char set_me_1;
	unsigned char release_standstill;
	unsigned char checksum;
	unsigned char checksum_check;
} prius_accel_cmd_status_t;

static inline void get_prius_accel_cmd_status(unsigned char *data, prius_accel_cmd_status_t *p) {
	p->accel_cmd_status = (float)((short)((data[0] << 8) + data[1]) * acceleration_res);
	p->set_me_x3 = (data[2] & MASK_b03);
	p->distance = (data[2] & MASK_b4) >> 4;
	p->mini_car = (data[2] & MASK_b5) >> 5;
	p->set_me_x01 = (data[2] & MASK_b67) >> 6;
	p->cancel_req = (data[3] & MASK_b0) >> 0;
	p->set_me_1 = (data[3] & MASK_b6) >> 6;
	p->release_standstill = (data[3] & MASK_b7) >> 7;
	p->checksum = data[7];
	p->checksum_check  = (data[0] + data[1] + data[2] + data[3] + data[4] + data[5] + data[6] + 0x4e) & 0xff;
}

/*******************************************************************************
 *      prius_cruise_state
 *      Message ID      0x399
 *      Transmitted every 40 ms
 *
 *	dbvar = DB_PRIUS_MSG399_VAR
 *
 *	cruise_main_on_CAN1
 *      Byte Position   0
 *      Bit Position    4
 *      Bit Length      1
 *
 *	cruise_control_state_CAN1
 *	Byte Position   1
 *      Bit Position    0-4
 *      Bit Length      4
 *
 *	cruise_dash_set_speed_CAN1
 *	Byte Position   3
 *      Bit Position    0-7
 *      Bit Length      8
 *
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char	cruise_main_on_CAN1;
	unsigned char	cruise_control_state_CAN1;
	unsigned char	cruise_dash_set_speed_CAN1;
} prius_cruise_control_state_t;

static inline void get_prius_cruise_control_state(unsigned char *data, prius_cruise_control_state_t *p) {
	p->cruise_main_on_CAN1 = (data[0] >> 4) & 0x01;
	p->cruise_control_state_CAN1 = data[1] & 0x0F;
	p->cruise_dash_set_speed_CAN1 = data[3] & 0xFF;
}

/*
** printcan.c - prints 8-byte CAN message to stdout
*/
int printcan(db_komodo_t *db_kom);

/* TODO
** printmsg - prints parsed contents of PRIUS CAN message to stdout
*/
int printmsg(db_komodo_t *db_kom);

void check_msg_timeout(int curr_ts_ms, int *prev_ts_ms,
        unsigned char *two_message_periods,
        unsigned int *message_timeout_counter);
