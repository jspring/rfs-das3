#include <komodo.h>

#ifndef M56_CAN_H
#define M56_CAN_H

//Define some resolutions and offsets
#define steering_angle_res  0.1 //deg
#define steering_velocity_res  4 //deg/sec
#define rpm_res  0.125
#define pedal_pos_res  0.392
#define wheel_speed_res  0.04166666
#define vehicle_speed_res  0.01
#define acceleration_res  0.001
#define acceleration_offset  -2.048
#define yaw_rate_res  0.1
#define yaw_rate_offset  -204.8
#define estimated_pressure_res 0.05

#endif

#define DB_M56_VCAN2_MSG002_TYPE	5000
#define DB_M56_VCAN2_MSG160_TYPE	5001
#define DB_M56_VCAN2_MSG174_TYPE	5002
#define DB_M56_VCAN2_MSG177_TYPE	5003
#define DB_M56_VCAN2_MSG180_TYPE	5004
#define DB_M56_VCAN2_MSG1c3_TYPE	5005
#define DB_M56_VCAN2_MSG239_TYPE	5006
#define DB_M56_VCAN2_MSG245_TYPE	5007
#define DB_M56_VCAN2_MSG284_TYPE	5008
#define DB_M56_VCAN2_MSG285_TYPE	5009
#define DB_M56_VCAN2_MSG292_TYPE	5010
#define DB_M56_VCAN2_MSG2aa_TYPE	5011
#define DB_M56_VCAN2_MSG2b0_TYPE	5012
#define DB_M56_VCAN2_MSG2b3_TYPE	5013
#define DB_M56_VCAN2_MSG354_TYPE	5014
#define DB_M56_VCAN2_MSG358_TYPE	5015
#define DB_M56_VCAN2_MSG421_TYPE	5016
#define DB_M56_VCAN2_MSG5b0_TYPE	5017
#define DB_M56_VCAN2_MSG625_TYPE	5018

#define DB_M56_ITSCAN_MSG52B_TYPE	5019
#define DB_M56_ITSCAN_MSG52C_TYPE	5020
#define DB_M56_ITSCAN_MSG52D_TYPE	5021
#define DB_M56_ITSCAN_MSG27A_TYPE	5022

#define DB_M56_VCAN2_MSG002_VAR 	DB_M56_VCAN2_MSG002_TYPE
#define DB_M56_VCAN2_MSG160_VAR 	DB_M56_VCAN2_MSG160_TYPE
#define DB_M56_VCAN2_MSG174_VAR 	DB_M56_VCAN2_MSG174_TYPE
#define DB_M56_VCAN2_MSG177_VAR 	DB_M56_VCAN2_MSG177_TYPE
#define DB_M56_VCAN2_MSG180_VAR 	DB_M56_VCAN2_MSG180_TYPE
#define DB_M56_VCAN2_MSG1c3_VAR 	DB_M56_VCAN2_MSG1c3_TYPE
#define DB_M56_VCAN2_MSG239_VAR 	DB_M56_VCAN2_MSG239_TYPE
#define DB_M56_VCAN2_MSG245_VAR 	DB_M56_VCAN2_MSG245_TYPE
#define DB_M56_VCAN2_MSG284_VAR 	DB_M56_VCAN2_MSG284_TYPE
#define DB_M56_VCAN2_MSG285_VAR 	DB_M56_VCAN2_MSG285_TYPE
#define DB_M56_VCAN2_MSG292_VAR 	DB_M56_VCAN2_MSG292_TYPE
#define DB_M56_VCAN2_MSG2aa_VAR 	DB_M56_VCAN2_MSG2aa_TYPE
#define DB_M56_VCAN2_MSG2b0_VAR 	DB_M56_VCAN2_MSG2b0_TYPE
#define DB_M56_VCAN2_MSG2b3_VAR 	DB_M56_VCAN2_MSG2b3_TYPE
#define DB_M56_VCAN2_MSG354_VAR 	DB_M56_VCAN2_MSG354_TYPE
#define DB_M56_VCAN2_MSG358_VAR 	DB_M56_VCAN2_MSG358_TYPE
#define DB_M56_VCAN2_MSG421_VAR 	DB_M56_VCAN2_MSG421_TYPE
#define DB_M56_VCAN2_MSG5b0_VAR 	DB_M56_VCAN2_MSG5b0_TYPE
#define DB_M56_VCAN2_MSG625_VAR 	DB_M56_VCAN2_MSG625_TYPE

#define DB_M56_ITSCAN_MSG52B_VAR 	DB_M56_ITSCAN_MSG52B_TYPE
#define DB_M56_ITSCAN_MSG52C_VAR 	DB_M56_ITSCAN_MSG52C_TYPE
#define DB_M56_ITSCAN_MSG52D_VAR 	DB_M56_ITSCAN_MSG52D_TYPE
#define DB_M56_ITSCAN_MSG27A_VAR	DB_M56_ITSCAN_MSG27A_TYPE

#define MASK_b0	0x01
#define MASK_b1	0x02
#define MASK_b2	0x04
#define MASK_b3	0x08
#define MASK_b4	0x10
#define MASK_b5	0x20
#define MASK_b6	0x40
#define MASK_b7	0x80

/*****************************************************************************************
 *      m56_steering
 *      Message ID      0x002
 *      Transmitted every 10 ms
 *
 *	steering_angle
 *      Byte Position   0-1
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *	steering_velocity
 *      Byte Position   2-3
 *      Bit Position    0-7
 *      Bit Length      8
 */

typedef struct {
	timestamp_t ts;
	float steering_angle;
	float steering_velocity;
} m56_steering_t;

static inline void get_m56_steering(unsigned char *data, m56_steering_t *p) {
	p->steering_angle = ((data[0] << 8) + data[1]) * steering_angle_res;
	p->steering_velocity = data[2]  * steering_velocity_res;
}

/*****************************************************************************************
 *      m56_engine_rpm
 *      Message ID      0x180
 *      Byte Position   ?
 *      Bit Position    ?
 *      Bit Length      ?
 *      Transmitted every 10 ms
 */

typedef struct {
	timestamp_t ts;
	float engine_rpm;
} m56_engine_rpm_t;

static inline void get_m56_engine_rpm(unsigned char *data, m56_engine_rpm_t *p) {
	p->engine_rpm = ( (data[0] << 8) + data[1]) * rpm_res;
}

/*****************************************************************************************
 *      m56_pedal_position
 *      Message ID      0x239
 *      Transmitted every 20 ms
 *
 *	acc_inhibit
 *      Byte Position   2
 *      Bit Position    7
 *      Bit Length      1
 *
 *	resume_sw
 *      Byte Position   2
 *      Bit Position    7
 *      Bit Length      1
 *
 *	acc_set_sw
 *      Byte Position   3
 *      Bit Position    3
 *      Bit Length      1
 *
 *	following_dist_sw	
 *      Byte Position   3
 *      Bit Position    3
 *      Bit Length      1
 *
 *	can_sw
 *      Byte Position   3
 *      Bit Position    1
 *      Bit Length      1
 *
 *	main_sw
 *      Byte Position   3
 *      Bit Position    0
 *      Bit Length      1
 *
 *	acc_can_fail_flag
 *      Byte Position   4
 *      Bit Position    7
 *      Bit Length      1
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
 */

typedef struct {
	timestamp_t ts;
	float pedal_position;
	unsigned char acc_inhibit;
	unsigned char resume_sw;
	unsigned char acc_set_sw;
	unsigned char following_dist_sw;
	unsigned char can_sw;
	unsigned char main_sw;
	unsigned char acc_can_fail_flag;
	unsigned char brake_nc_sw;
	unsigned char brake_no_sw;
} m56_pedal_position_t;

static inline void get_m56_pedal_position(unsigned char *data, m56_pedal_position_t *p) {
	p->pedal_position = data[0] * pedal_pos_res;
	p->acc_inhibit = (data[2] & MASK_b7) >> 7;
	p->resume_sw = (data[3] & MASK_b4) >> 4;
	p->acc_set_sw = (data[3] & MASK_b3) >> 3;
	p->following_dist_sw = (data[3] & MASK_b2) >> 2;
	p->can_sw = (data[3] & MASK_b1) >> 1;
	p->main_sw = data[3] & MASK_b0;
	p->acc_can_fail_flag = (data[4] & MASK_b7) >> 7;
	p->brake_nc_sw = (data[4] & MASK_b6) >> 6;
	p->brake_no_sw = (data[4] & MASK_b5) >> 5;
}

/*****************************************************************************************
 *      m56_wheel_speed_front
 *      Message ID      0x284
 *      Transmitted every 20 ms
 *
 *      wheel_speed_front_right
 *      Byte Position   0-1
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *      wheel_speed_front_left
 *      Byte Position   2-3
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *      vehicle_speed_copy
 *      Byte Position   4-5
 *      Bit Position    0-15
 *      Bit Length      16
 */

typedef struct {
	timestamp_t ts;
	float wheel_speed_front_right;
	float wheel_speed_front_left;
	float vehicle_speed_copy;
} m56_wheel_speed_front_t;

static inline void get_m56_wheel_speed_front(unsigned char *data, m56_wheel_speed_front_t *p) {
	p->wheel_speed_front_right = ((data[0] << 8) + data[1]) * wheel_speed_res;
	p->wheel_speed_front_left = ((data[2] << 8) + data[3]) * wheel_speed_res;
	p->vehicle_speed_copy = ((data[4] << 8) + data[5]) * vehicle_speed_res;
}

typedef struct {
	timestamp_t ts;
	float wheel_speed_rear_right;
	float wheel_speed_rear_left;
} m56_wheel_speed_rear_t;

/**
 *      m56_wheel_speed_rear
 *      Message ID      0x285
 *      Transmitted every 20 ms
 *
 *      wheel_speed_front_right
 *      Byte Position   0-1
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *      wheel_speed_front_left
 *      Byte Position   2-3
 *      Bit Position    0-15
 *      Bit Length      16
 */

static inline void get_m56_wheel_speed_rear(unsigned char *data, m56_wheel_speed_rear_t *p) {
	p->wheel_speed_rear_right = ((data[0] << 8) + data[1]) * wheel_speed_res;
	p->wheel_speed_rear_left = ((data[2] << 8) + data[3]) * wheel_speed_res;
}

/*****************************************************************************************
 *      m56_acceleration
 *      Message ID      0x292
 *      Transmitted every 20 ms
 *
 *      long_accel_proc_02
 *      Byte Position   0
 *      Bit Position    0-7
 *      Byte Position   1
 *      Bit Position    4-7
 *      Bit Length      12
 *
 *      transverse_accel_proc_02
 *      Byte Position   1
 *      Bit Position    0-3
 *      Byte Position   2
 *      Bit Position    0-7
 *      Bit Length      12
 *
 *      yaw_rate_02
 *      Byte Position   3
 *      Bit Position    0-7
 *      Byte Position   4
 *      Bit Position    4-7
 *      Bit Length      12
 */

typedef struct {
	timestamp_t ts;
	float long_accel_proc_02;
	float transverse_accel_proc_02;
	float yaw_rate_02;
	unsigned char pressure_sensor_02;
} m56_acceleration_t;

static inline void get_m56_acceleration(unsigned char *data, m56_acceleration_t *p) {
	p->long_accel_proc_02 = (((data[0] << 4) + (data[1] >> 4)) * acceleration_res) + acceleration_offset;
	p->transverse_accel_proc_02 = (((data[1] << 8) + data[2]) * acceleration_res) + acceleration_offset;
	p->yaw_rate_02 = (((data[3] << 4) + (data[4] >> 4)) * yaw_rate_res) + yaw_rate_offset;
	p->pressure_sensor_02 = data[6];
}

/*****************************************************************************************
 *      m56_acc_status
 *      Message ID      0x2aa
 *      Transmitted every 20 ms
 *
 *	estimated_pressure_value
 *      Byte Position   0
 *      Bit Position    7
 *      Bit Length      8
 *
 *	release_sw
 *      Byte Position   1
 *      Bit Position    4
 *      Bit Length      1
 *
 *	pbfs_nc
 *      Byte Position   1
 *      Bit Position    3
 *      Bit Length      1
 *
 *	pbfs_no
 *      Byte Position   1
 *      Bit Position    2
 *      Bit Length      1
 *
 *	acc_enable
 *      Byte Position   1
 *      Bit Position    1
 *      Bit Length      1
 *
 *	acc_status
 *      Byte Position   2
 *      Bit Position    5
 *      Bit Length      1
 *
 *	acc_alive
 *      Byte Position   2
 *      Bit Position    1
 *      Bit Length      1
 *
 */

typedef struct {
	timestamp_t ts;
	float estimated_pressure_value;
	unsigned char release_sw;
	unsigned char pbfs_nc;
	unsigned char pbfs_no;
	unsigned char acc_enable;
	unsigned char acc_status;
	unsigned char acc_alive;
} m56_acc_status_t;

static inline void get_m56_acc_status(unsigned char *data, m56_acc_status_t *p) {
        p->estimated_pressure_value = data[0] * estimated_pressure_res;
        p->release_sw = (data[1] & MASK_b4) >> 4;
        p->pbfs_nc = (data[1] & MASK_b3) >> 3;
        p->pbfs_no = (data[1] & MASK_b2) >> 2;
        p->acc_enable = (data[1] & MASK_b1) >> 1;
        p->acc_status = (data[2] & MASK_b5) >> 5;
        p->acc_alive = (data[2] & MASK_b1) >> 1;
}

/*
** printcan.c - prints 8-byte CAN message to stdout
*/
int printcan(db_komodo_t *db_kom);

/* TODO
** printmsg - prints parsed contents of M56 CAN message to stdout
*/
int printmsg(db_komodo_t *db_kom);

