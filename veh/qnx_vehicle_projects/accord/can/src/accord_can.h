#pragma once

#include <can_dbvars.h>

#ifndef ACCORD_CAN_H
#define ACCORD_CAN_H

//Define some resolutions and offsets
#define steering_angle_res  0.1 //deg
#define steering_velocity_res  4 //deg/sec
#define rpm_res  0.125
#define mean_eff_tq_res 0.5
#define mean_eff_tq_off 400
#define pedal_pos_res  0.392
#define wheel_speed_res  0.04166666
#define vehicle_speed_res  0.01
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
#define ACCORD_IGNITION_MASK 0X01
#define SHORT2FLOAT(low,high)	((float)((signed short)((low) + (high << 8))))
#define CHAR2FLOAT(low)	((float)((signed char)(low)))

/*******************************************************************************
 *      accord_accel_cmd
 *      Message ID      0x98
 *      Transmitted every 20 ms
 *
 *	accel_cmd
 *      Byte Position   0
 *      Bit Position    0
 *      Bit Length      8
 *
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float accel_cmd;
} accord_accel_cmd_t;

#define acceleration_res  0.46698
#define acceleration_offset  3.74

static inline void set_accord_accel_cmd(unsigned char data[], accord_accel_cmd_t *p) {
	char accel_cmd_char;
	//  % acceleration = raw_value * 0.46698 - 3.74 (From documentation)
	accel_cmd_char =  (char)( (p->accel_cmd + acceleration_offset) / acceleration_res);
	data[0] = accel_cmd_char & 0xff;
	printf("set_accord_accel_cmd: accel_cmd %.2f accel_cmd_char %hhd\n", p->accel_cmd, accel_cmd_char);
}

/*******************************************************************************
 *      accord_brake_cmd
 *      Message ID      0x99
 *      Transmitted every 20 ms
 *
 *	brake_override_cmd
 *      Byte Position   2
 *      Bit Position    16
 *      Bit Length	8 
 *
 */

#define deceleration_res  0.392157

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float brake_cmd;
} accord_brake_cmd_t;

static inline void set_accord_brake_cmd(unsigned char data[], accord_brake_cmd_t *p) {
	char brake_cmd_char;
	//  % deceleration = raw_value / 0.392157 (From documentation)
	brake_cmd_char =  (char)( p->brake_cmd * deceleration_res);
	data[0] = 0;
	data[1] = 0;
	data[2] = brake_cmd_char & 0xff;
	data[3] = 0;
	data[4] = 0;
	data[5] = 0;
	printf("set_accord_brake_cmd: brake_cmd %.2f brake_cmd_char %hhd\n", p->brake_cmd, brake_cmd_char);
}


/*******************************************************************************
 *      Vehicle_Speed_CAN2_MPH
 *      Message ID      0x158
 *      Transmitted every 40 ms
 *
 *	dbvar = DB_ACCORD_MSG158_VAR
 *
 *	Vehicle_Speed_CAN2_MPH
 *      Byte Position   0-1
 *      Bit Position    0
 *      Bit Length      16
 *
 */

#define WHEEL_SPEED_RES		0.00624
#define MPH_2_MPS		0.44704 

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float vehicle_speed_CAN2_MPS;
} accord_vehicle_speed_t;

static inline void get_accord_vehicle_speed(unsigned char *data, accord_vehicle_speed_t *p) {
	p->vehicle_speed_CAN2_MPS = (float)(((data[0] << 8) + data[1]) * WHEEL_SPEED_RES * MPH_2_MPS);
}

/*******************************************************************************
 *      Torque_CAN2_NM
 *      Message ID      0x530
 *      Transmitted every 40 ms
 *
 *	dbvar = DB_ACCORD_MSG530_VAR
 *
 *	Torque_CAN2_NM
 *      Byte Position   0-1
 *      Bit Position    0
 *      Bit Length      16
 *
 */

#define TORQUE_RES		0.02

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float generator_torque_CAN2_nm;
	float motor_torque_CAN2_nm;
} accord_torque_t;

static inline void get_accord_torque(unsigned char *data, accord_torque_t *p) {
	p->generator_torque_CAN2_nm = (float)(((data[0] << 8) + data[1]) * TORQUE_RES);
	p->motor_torque_CAN2_nm = (float)(((data[2] << 8) + data[3]) * TORQUE_RES);
}

/*******************************************************************************
 *	PRNDL_Pos_CAN2 
 *      Message ID      0x392
 *      Transmitted every 40 ms
 *
 *	dbvar = DB_ACCORD_MSG392_VAR
 *
 *      Byte Position   0-1
 *      Bit Position    0
 *      Bit Length      16
 *
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char prndl;
} accord_PRNDL_Pos_t;

static inline void get_accord_PRNDL_Pos(unsigned char *data, accord_PRNDL_Pos_t *p) {
	p->prndl = data[5] & 0x0F;
}


/*
** printcan.c - prints 8-byte CAN message to stdout
*/
int printcan(db_steinhoff_msg_t *steinhoff_msg);

int print_vehicle_speed(accord_vehicle_speed_t *accord_vehicle_speed);

void check_msg_timeout(int curr_ts_ms, int *prev_ts_ms,
        unsigned char *two_message_periods,
        unsigned int *message_timeout_counter);
