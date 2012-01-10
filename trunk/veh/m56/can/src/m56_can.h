#include <komodo.h>

#ifndef M56_CAN_H
#define M56_CAN_H

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

#define DB_M56_ITSCAN_MSG52b_TYPE	5019
#define DB_M56_ITSCAN_MSG52c_TYPE	5020
#define DB_M56_ITSCAN_MSG52d_TYPE	5021
#define DB_M56_ITSCAN_MSG27A_TYPE	5022
#define DB_M56_IGNITION_TYPE		5023

#define DB_M56_VCAN2_MSG210_TYPE		5024
#define DB_M56_VCAN2_MSG211_TYPE		5025
#define DB_M56_VCAN2_MSG212_TYPE		5026
#define DB_M56_VCAN2_MSG213_TYPE		5027
#define DB_M56_VCAN2_MSG214_TYPE		5028
#define DB_M56_VCAN2_MSG215_TYPE		5029
#define DB_M56_VCAN2_MSG216_TYPE		5030
#define DB_M56_VCAN2_MSG217_TYPE		5031
#define DB_M56_VCAN2_MSG218_TYPE		5032
#define DB_M56_VCAN2_MSG219_TYPE		5033
#define DB_M56_VCAN2_MSG21a_TYPE		5034
#define DB_M56_VCAN2_MSG21b_TYPE		5035
#define DB_M56_VCAN2_MSG21c_TYPE		5036
#define DB_M56_VCAN2_MSG21d_TYPE		5037
#define DB_M56_VCAN2_MSG21e_TYPE		5038
#define DB_M56_VCAN2_MSG21f_TYPE		5039
#define DB_M56_VCAN2_MSG289_TYPE		5040
#define DB_M56_VCAN2_MSG28a_TYPE		5041

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

#define DB_M56_ITSCAN_MSG52b_VAR 	DB_M56_ITSCAN_MSG52b_TYPE
#define DB_M56_ITSCAN_MSG52c_VAR 	DB_M56_ITSCAN_MSG52c_TYPE
#define DB_M56_ITSCAN_MSG52d_VAR 	DB_M56_ITSCAN_MSG52d_TYPE
#define DB_M56_ITSCAN_MSG27A_VAR	DB_M56_ITSCAN_MSG27A_TYPE
#define DB_M56_IGNITION_VAR		DB_M56_IGNITION_TYPE

#define DB_M56_VCAN2_MSG210_VAR 	DB_M56_VCAN2_MSG210_TYPE
#define DB_M56_VCAN2_MSG211_VAR 	DB_M56_VCAN2_MSG211_TYPE
#define DB_M56_VCAN2_MSG212_VAR 	DB_M56_VCAN2_MSG212_TYPE
#define DB_M56_VCAN2_MSG213_VAR 	DB_M56_VCAN2_MSG213_TYPE
#define DB_M56_VCAN2_MSG214_VAR 	DB_M56_VCAN2_MSG214_TYPE
#define DB_M56_VCAN2_MSG215_VAR 	DB_M56_VCAN2_MSG215_TYPE
#define DB_M56_VCAN2_MSG216_VAR 	DB_M56_VCAN2_MSG216_TYPE
#define DB_M56_VCAN2_MSG217_VAR 	DB_M56_VCAN2_MSG217_TYPE
#define DB_M56_VCAN2_MSG218_VAR 	DB_M56_VCAN2_MSG218_TYPE
#define DB_M56_VCAN2_MSG219_VAR 	DB_M56_VCAN2_MSG219_TYPE
#define DB_M56_VCAN2_MSG21a_VAR 	DB_M56_VCAN2_MSG21a_TYPE
#define DB_M56_VCAN2_MSG21b_VAR 	DB_M56_VCAN2_MSG21b_TYPE
#define DB_M56_VCAN2_MSG21c_VAR 	DB_M56_VCAN2_MSG21c_TYPE
#define DB_M56_VCAN2_MSG21d_VAR 	DB_M56_VCAN2_MSG21d_TYPE
#define DB_M56_VCAN2_MSG21e_VAR 	DB_M56_VCAN2_MSG21e_TYPE
#define DB_M56_VCAN2_MSG21f_VAR 	DB_M56_VCAN2_MSG21f_TYPE
#define DB_M56_VCAN2_MSG289_VAR 	DB_M56_VCAN2_MSG289_TYPE
#define DB_M56_VCAN2_MSG28a_VAR 	DB_M56_VCAN2_MSG28a_TYPE

#define MASK_b0	 0x01
#define MASK_b01 0x03
#define MASK_b02 0x07
#define MASK_b03 0x0F
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
#define M56_IGNITION_MASK 0X01

/*******************************************************************************
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
 *
 *	message_counter
 *      Byte Position   4
 *      Bit Position    3
 *      Bit Length      4
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float steering_angle;
	float steering_velocity;
	unsigned char message_counter;
} m56_steering_t;

static inline void get_m56_steering(unsigned char *data, m56_steering_t *p) {
	p->steering_angle = ((signed short)((data[0] + (data[1] << 8)))) * 
		steering_angle_res;
	p->steering_velocity = data[2] * steering_velocity_res;
	p->message_counter = data[4] & MASK_b03;
}

/*******************************************************************************
 *      m56_gear
 *      Message ID      0x174
 *      Transmitted every 10 ms
 *
 *	current_gear
 *      Byte Position   3
 *      Bit Position    0-3
 *      Bit Length      4
 *
 *	next_gear
 *      Byte Position   3
 *      Bit Position    4-7
 *      Bit Length      4
 *
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char current_gear;
	unsigned char next_gear;
} m56_gear_t;

static inline void get_m56_gear(unsigned char *data, m56_gear_t *p) {
	p->current_gear = data[3] & MASK_b03;
	p->next_gear = (data[3] & MASK_b47) >> 4;
}

/*******************************************************************************
 *      m56_engine_rpm
 *      Message ID      0x180
 *      Transmitted every 10 ms
 *
 *	engine_rpm
 *      Byte Position   0-1
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *	mean_effective_torque
 *      Byte Position   2-3
 *      Bit Position    0-11
 *      Bit Length      12
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float engine_rpm;
	float mean_effective_torque;
} m56_engine_rpm_t;

static inline void get_m56_engine_rpm(unsigned char *data, m56_engine_rpm_t *p) {
	p->engine_rpm = ((data[0] << 8) + data[1]) * rpm_res;
	p->mean_effective_torque = (((data[2] << 4) + ((data[3]& MASK_b47) >> 4)) * mean_eff_tq_res) - mean_eff_tq_off;
}

/*******************************************************************************
 *      m56_its_alive
 *      Message ID      0x1c3
 *      Transmitted every 10 ms
 *
 *	its_target_pressure
 *      Byte Position   0-1
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *	its_alive_flag
 *      Byte Position   1
 *      Bit Position    4
 *      Bit Length      1
 *
 *	acc_request_flag
 *      Byte Position   1
 *      Bit Position    3
 *      Bit Length      1
 *
 *	message_counter
 *      Byte Position   5
 *      Bit Position    1
 *      Bit Length      2
 *
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float its_target_pressure;
	unsigned char its_alive_flag;
	unsigned char acc_request_flag;
	unsigned char message_counter;
} m56_its_alive_t;

static inline void get_m56_its_alive(unsigned char *data, m56_its_alive_t *p) {
        p->its_target_pressure = ((data[0] << 3) + (data[1] * MASK_b02)) * its_target_pressure_res;
        p->its_alive_flag = (data[1] & MASK_b4) >> 4;
        p->acc_request_flag = (data[1] & MASK_b3) >> 3;
        p->message_counter = data[5] & MASK_b01;
}

/*******************************************************************************
 *      m56_pedal_position
 *      Message ID      0x239
 *      Transmitted every 20 ms
 *
 *	acc_inhibit
 *      Byte Position   2
 *      Bit Position    7
 *      Bit Length      1
 *
 *	acc_control_requested
 *      Byte Position   2
 *      Bit Position    5
 *      Bit Length      1
 *
 *	temporary_accel_flag
 *      Byte Position   2
 *      Bit Position    2
 *      Bit Length      1
 *
 *	resume_sw
 *      Byte Position   3
 *      Bit Position    4
 *      Bit Length      1
 *
 *	acc_set_sw
 *      Byte Position   3
 *      Bit Position    3
 *      Bit Length      1
 *
 *	following_dist_sw	
 *      Byte Position   3
 *      Bit Position    2
 *      Bit Length      1
 *
 *	cancel_sw
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
 *	message_counter
 *      Byte Position   4
 *      Bit Position    1
 *      Bit Length      2
 *
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float pedal_position;
	unsigned char acc_inhibit;
	unsigned char acc_control_requested;
	unsigned char temporary_accel_flag;
	unsigned char resume_sw;
	unsigned char acc_set_sw;
	unsigned char following_dist_sw;
	unsigned char cancel_sw;
	unsigned char main_sw;
	unsigned char acc_can_fail_flag;
	unsigned char brake_nc_sw;
	unsigned char brake_no_sw;
	unsigned char message_counter;
} m56_pedal_position_t;

static inline void get_m56_pedal_position(unsigned char *data, m56_pedal_position_t *p) {
	p->pedal_position = data[0] * pedal_pos_res;
	p->acc_inhibit = (data[2] & MASK_b7) >> 7;
	p->acc_control_requested = (data[2] & MASK_b5) >> 5;
	p->temporary_accel_flag = (data[2] & MASK_b2) >> 2;
	p->resume_sw = (data[3] & MASK_b4) >> 4;
	p->acc_set_sw = (data[3] & MASK_b3) >> 3;
	p->following_dist_sw = (data[3] & MASK_b2) >> 2;
	p->cancel_sw = (data[3] & MASK_b1) >> 1;
	p->main_sw = data[3] & MASK_b0;
	p->acc_can_fail_flag = (data[4] & MASK_b7) >> 7;
	p->brake_nc_sw = (data[4] & MASK_b6) >> 6;
	p->brake_no_sw = (data[4] & MASK_b5) >> 5;
	p->message_counter = data[4] & MASK_b01;
}

/*******************************************************************************
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
 *
 *      message_counter
 *      Byte Position   6
 *      Bit Position    7
 *      Bit Length      8
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float wheel_speed_front_right;
	float wheel_speed_front_left;
	float vehicle_speed_copy;
	unsigned char message_counter;
} m56_wheel_speed_front_t;

static inline void get_m56_wheel_speed_front(unsigned char *data, m56_wheel_speed_front_t *p) {
	p->wheel_speed_front_right = ((data[0] << 8) + data[1]) * wheel_speed_res;
	p->wheel_speed_front_left = ((data[2] << 8) + data[3]) * wheel_speed_res;
	p->vehicle_speed_copy = ((data[4] << 8) + data[5]) * vehicle_speed_res;
	p->message_counter = data[6];
}

/*******************************************************************************
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
 *
 *      message_counter
 *      Byte Position   6
 *      Bit Position    7
 *      Bit Length      8
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float wheel_speed_rear_right;
	float wheel_speed_rear_left;
	unsigned char message_counter;
} m56_wheel_speed_rear_t;

static inline void get_m56_wheel_speed_rear(unsigned char *data, m56_wheel_speed_rear_t *p) {
	p->wheel_speed_rear_right = ((data[0] << 8) + data[1]) * wheel_speed_res;
	p->wheel_speed_rear_left = ((data[2] << 8) + data[3]) * wheel_speed_res;
	p->message_counter = data[6];
}

/*******************************************************************************
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
 *
 *      message_counter
 *      Byte Position   7
 *      Bit Position    1
 *      Bit Length      2
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float long_accel_proc_02;
	float transverse_accel_proc_02;
	float yaw_rate_02;
	unsigned char pressure_sensor_02;
	unsigned char message_counter;
} m56_acceleration_t;

static inline void get_m56_acceleration(unsigned char *data, m56_acceleration_t *p) {
	p->long_accel_proc_02 = (((data[0] << 4) + (data[1] >> 4)) * acceleration_res) + acceleration_offset;
	p->transverse_accel_proc_02 = ((((data[1] & MASK_b03) << 8) + data[2]) * acceleration_res) + acceleration_offset;
	p->yaw_rate_02 = (((data[3] << 4) + (data[4] & MASK_b03)) * yaw_rate_res) + yaw_rate_offset;
	p->pressure_sensor_02 = data[6];
	p->message_counter = data[7] & MASK_b01;
}

/*******************************************************************************
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
 *	message_counter
 *      Byte Position   6
 *      Bit Position    3
 *      Bit Length      4
 *
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float estimated_pressure_value;
	unsigned char release_sw;
	unsigned char pbfs_nc;
	unsigned char pbfs_no;
	unsigned char acc_enable;
	unsigned char acc_status;
	unsigned char acc_alive;
	unsigned char message_counter;
} m56_acc_status_t;

static inline void get_m56_acc_status(unsigned char *data, m56_acc_status_t *p) {
        p->estimated_pressure_value = ((data[0] << 3) + (data[1] & MASK_b02)) * estimated_pressure_res;
        p->release_sw = (data[1] & MASK_b4) >> 4;
        p->pbfs_nc = (data[1] & MASK_b3) >> 3;
        p->pbfs_no = (data[1] & MASK_b2) >> 2;
        p->acc_enable = (data[1] & MASK_b1) >> 1;
        p->acc_status = (data[2] & MASK_b5) >> 5;
        p->acc_alive = (data[2] & MASK_b1) >> 1;
        p->message_counter = data[6] & MASK_b03;
}

/*******************************************************************************
 *      m56_eng_tq_acc_and_brake_flags
 *      Message ID      0x2b0
 *      Transmitted every 10 ms
 *
 *	target_engine_torque_main_cpu
 *      Byte Position   0-1
 *      Bit Position    0-7,0-3
 *      Bit Length      12
 *
 *	target_engine_torque_sub_cpu
 *      Byte Position   1-2
 *      Bit Position    4-7,0-7
 *      Bit Length      12
 *
 *	driver_brake_nc
 *      Byte Position   3
 *      Bit Position    7
 *      Bit Length      1
 *
 *	driver_brake_no
 *      Byte Position   3
 *      Bit Position    6
 *      Bit Length      1
 *
 *	acc_main_sw
 *      Byte Position   3
 *      Bit Position    5
 *      Bit Length      1
 *
 *	od_off_flag
 *      Byte Position   3
 *      Bit Position    1
 *      Bit Length      1
 *
 *	acc_fail_flag
 *      Byte Position   3
 *      Bit Position    0
 *      Bit Length      1
 *
 *	control_autostop_flag
 *      Byte Position   4
 *      Bit Position    7
 *      Bit Length      1
 *
 *	acc_active_flag_for_ecm
 *      Byte Position   4
 *      Bit Position    6
 *      Bit Length      1
 *
 *	acc_cruise_flag
 *      Byte Position   4
 *      Bit Position    5
 *      Bit Length      1
 *
 *	virtual_accelerator_angle
 *      Byte Position   5
 *      Bit Position    0-7
 *      Bit Length      8
 *
 *	message_counter
 *      Byte Position   6
 *      Bit Position    4-7
 *      Bit Length      4
 *
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	float target_engine_torque_main_cpu;
	float target_engine_torque_sub_cpu;
	unsigned char driver_brake_nc;
	unsigned char driver_brake_no;
	unsigned char acc_main_sw;
	unsigned char od_off_flag;
	unsigned char acc_fail_flag;
	unsigned char control_autostop_flag;
	unsigned char acc_active_flag_for_ecm;
	unsigned char acc_cruise_flag;
	float virtual_accelerator_angle;
	unsigned char message_counter;
} m56_eng_tq_acc_and_brake_flags_t;

static inline void get_m56_eng_tq_acc_and_brake_flags(unsigned char *data, 
	m56_eng_tq_acc_and_brake_flags_t *p) {

        p->target_engine_torque_main_cpu = 
		((signed short)((data[0] + ((data[1] & MASK_b47) << 4)))) * 
			targ_eng_tq_res;
        p->target_engine_torque_sub_cpu = 
		((signed short)(((data[1] & MASK_b03) + (data[2] << 4)))) * 
			targ_eng_tq_res;
        p->driver_brake_nc = (data[3] & MASK_b7) >> 7;
        p->driver_brake_no = (data[3] & MASK_b6) >> 6;
        p->acc_main_sw = (data[3] & MASK_b5) >> 5;
        p->od_off_flag = (data[3] & MASK_b1) >> 1;
        p->acc_fail_flag = data[3] & MASK_b0;
        p->control_autostop_flag = (data[4] & MASK_b7) >> 7;
        p->acc_active_flag_for_ecm = (data[4] & MASK_b6) >> 6;
        p->acc_cruise_flag = (data[4] & MASK_b5) >> 5;
        p->virtual_accelerator_angle = data[5] * virtual_accelerator_angle_res;
        p->message_counter = (data[6] & MASK_b47) >> 4;
}


/*******************************************************************************
 *      m56_dashboard_indicators
 *      Message ID      0x2b3
 *      Transmitted every 20 ms
 *
 *	main_sw
 *      Byte Position   0
 *      Bit Position    7
 *      Bit Length      1
 *
 *	target_lock
 *      Byte Position   0
 *      Bit Position    5
 *      Bit Length      1
 *
 *	target_approach_warning
 *      Byte Position   0
 *      Bit Position    4
 *      Bit Length      2
 *
 *	blink_at_target_icon
 *      Byte Position   0
 *      Bit Position    2
 *      Bit Length      1
 *
 *	segment_car_space
 *      Byte Position   0
 *      Bit Position    1
 *      Bit Length      2
 *
 *	oneself
 *      Byte Position   1
 *      Bit Position    7
 *      Bit Length      1
 *
 *	auto_brake
 *      Byte Position   1
 *      Bit Position    6
 *      Bit Length      1
 *
 *	dash_dash_indicator_signal
 *      Byte Position   1
 *      Bit Position    5
 *      Bit Length      1
 *
 *	kph_indicator_signal
 *      Byte Position   1
 *      Bit Position    4
 *      Bit Length      1
 *
 *	acc_buzzer_signal
 *      Byte Position   1
 *      Bit Position    1
 *      Bit Length      1
 *
 *	pbs2_warning
 *      Byte Position   1
 *      Bit Position    0
 *      Bit Length      1
 *
 *	speed_set_driver
 *      Byte Position   2
 *      Bit Position    7
 *      Bit Length      8
 *
 *	acc_buzzer_3rd
 *      Byte Position   3
 *      Bit Position    6
 *      Bit Length      1
 *
 *	acc_buzzer_2nd
 *      Byte Position   3
 *      Bit Position    5
 *      Bit Length      1
 *
 *	booster_active_reverse_bit
 *      Byte Position   3
 *      Bit Position    3
 *      Bit Length      1
 *
 *	booster_active
 *      Byte Position   3
 *      Bit Position    2
 *      Bit Length      1
 *
 *	pbs2_off
 *      Byte Position   3
 *      Bit Position    1
 *      Bit Length      1
 *
 *	acc_bulb_check
 *      Byte Position   3
 *      Bit Position    0
 *      Bit Length      1
 *
 *	acc_system_fail_1_invert
 *      Byte Position   4
 *      Bit Position    7
 *      Bit Length      1
 *
 *	acc_system_fail_1
 *      Byte Position   4
 *      Bit Position    6
 *      Bit Length      1
 *
 *	trouble_trigger_code
 *      Byte Position   5
 *      Bit Position    7
 *      Bit Length      8
 *
 */

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char main_sw;
	unsigned char target_lock;
	unsigned char target_approach_warning;
	unsigned char blink_at_target_icon;
	unsigned char segment_car_space;
	unsigned char oneself;
	unsigned char auto_brake;
	unsigned char dash_dash_indicator_signal;
	unsigned char kph_indicator_signal;
	unsigned char acc_buzzer_signal;
	unsigned char pbs2_warning;
	unsigned char speed_set_driver;
	unsigned char acc_buzzer_3rd;
	unsigned char acc_buzzer_2nd;
	unsigned char booster_active_reverse_bit;
	unsigned char booster_active;
	unsigned char pbs2_off;
	unsigned char acc_bulb_check;
	unsigned char acc_system_fail_1_invert;
	unsigned char acc_system_fail_1;
	unsigned char trouble_trigger_code;
} m56_dashboard_indicators_t;

static inline void get_m56_dashboard_indicators(unsigned char *data, 
	m56_dashboard_indicators_t *p) {

        p->main_sw = (data[0] & MASK_b7) >> 7;
        p->target_lock = (data[0] & MASK_b5) >> 5;
        p->target_approach_warning = (data[0] & MASK_b34) >> 3;
        p->blink_at_target_icon = (data[0] & MASK_b2) >> 2;
        p->segment_car_space = data[0] & MASK_b01;
        p->oneself = (data[1] & MASK_b7) >> 7;
        p->auto_brake = (data[1] & MASK_b6) >> 6;
        p->dash_dash_indicator_signal = (data[1] & MASK_b5) >> 5;
        p->kph_indicator_signal = (data[1] & MASK_b4) >> 4;
        p->acc_buzzer_signal = (data[1] & MASK_b1) >> 1;
        p->pbs2_warning = data[1] & MASK_b0;
        p->speed_set_driver = data[2];
        p->acc_buzzer_3rd = (data[3] & MASK_b6) >> 6;
        p->acc_buzzer_2nd = (data[3] & MASK_b5) >> 5;
        p->booster_active_reverse_bit = (data[3] & MASK_b3) >> 3;
        p->booster_active = (data[3] & MASK_b2) >> 2;
        p->pbs2_off = (data[3] & MASK_b1) >> 1;
        p->acc_bulb_check = data[3] & MASK_b0;
        p->acc_system_fail_1_invert = (data[4] & MASK_b7) >> 7;
        p->acc_system_fail_1 = (data[4] & MASK_b6) >> 6;
        p->trouble_trigger_code = data[5];
}

/*******************************************************************************
 *      m56_abs_status
 *      Message ID      0x354
 *      Transmitted every 40 ms
 *
 *      message_counter
 *      Byte Position   5
 *      Bit Position    4
 *      Bit Length      2
 *
 *      abs_malfunction
 *      Byte Position   6
 *      Bit Position    7
 *      Bit Length      1
 *
 *      abs_in_regulation
 *      Byte Position   6
 *      Bit Position    6
 *      Bit Length      1
 *
 *      close_active_brake_switch_abs
 *      Byte Position   6
 *      Bit Position    5
 *      Bit Length      1
 *
*/

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
        unsigned char message_counter;
        unsigned char abs_malfunction;
        unsigned char abs_in_regulation;
        unsigned char close_active_brake_switch_abs;
} m56_abs_status_t;


static inline void get_m56_abs_status(unsigned char *data, 
	m56_abs_status_t *p) {

        p->message_counter = (data[5] & MASK_b34) >> 3;
        p->abs_malfunction = (data[6] & MASK_b7) >> 7;
        p->abs_in_regulation = (data[6] & MASK_b6) >> 6;
        p->close_active_brake_switch_abs = (data[6] & MASK_b45) >> 4;
}

/*******************************************************************************
 *      m56_turn_switch_status 
 *      Message ID      0x358
 *      Transmitted every 100 ms + event
 *
 *      turn_switch_status
 *      Byte Position   2
 *      Bit Position    2
 *      Bit Length      2
 *
*/

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
        unsigned char turn_switch_status;
} m56_turn_switch_status_t;

static inline void get_m56_turn_switch_status(unsigned char *data, m56_turn_switch_status_t *p) {
        p->turn_switch_status = (data[2] & MASK_b12) >> 1;
}

/*******************************************************************************
 *      m56_atcvt (Automatic Transmission Continuously Variable Transmission)
 *      Message ID      0x421
 *      Transmitted every 60 ms + event
 *
 *      virtual_gear
 *      Byte Position   0
 *      Bit Position    7
 *      Bit Length      8
 *
*/

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
        unsigned char virtual_gear;
} m56_atcvt_t;

static inline void get_m56_atcvt(unsigned char *data, m56_atcvt_t *p) {
        p->virtual_gear = data[0] & MASK_b03;
}

/*******************************************************************************
 *      m56_transmission_mode
 *      Message ID      0x5b0
 *      Transmitted every 100 ms
 *
 *      snow_mode_sw_status
 *      Byte Position   0
 *      Bit Position    7
 *      Bit Length      2
 *
 *      eco_mode_sw_status
 *      Byte Position   0
 *      Bit Position    5
 *      Bit Length      2
 *
 *      standard_mode_sw_status
 *      Byte Position   0
 *      Bit Position    3
 *      Bit Length      2
 *
 *      sport_mode_sw_status
 *      Byte Position   0
 *      Bit Position    1
 *      Bit Length      2
 *
*/

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
        unsigned char snow_mode_sw_status;
        unsigned char eco_mode_sw_status;
        unsigned char standard_mode_sw_status;
        unsigned char sport_mode_sw_status;
} m56_transmission_mode_t;

static inline void get_m56_transmission_mode(unsigned char *data, 
	m56_transmission_mode_t *p) {

        p->snow_mode_sw_status = (data[0] & MASK_b67) >> 6;
        p->eco_mode_sw_status = (data[0] & MASK_b45) >> 4;
        p->standard_mode_sw_status = (data[0] & MASK_b23) >> 2;
        p->sport_mode_sw_status = data[0] & MASK_b01;
}


/*******************************************************************************
 *      m56_front_wiper_status
 *      Message ID      0x625
 *      Transmitted every 100 ms + event
 *
 *      front_wiper_status
 *      Byte Position   2
 *      Bit Position    3
 *      Bit Length      2
 *
*/

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
        unsigned char front_wiper_status;
} m56_front_wiper_status_t;

static inline void get_m56_front_wiper_status(unsigned char *data, 
	m56_front_wiper_status_t *p) {

        p->front_wiper_status = (data[2] & MASK_b23) >> 2;
}

/*******************************************************************************
 *      m56_lidar_target
 *      Message ID      0x52b
 *      Transmitted every 100 ms
 *
 *	distance_to_target
 *      Byte Position   0-1
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *	relative_speed_to_target
 *      Byte Position   2-3
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *	object_type
 *      Byte Position   4
 *      Bit Position    1
 *      Bit Length      1
 *
 *	object_data_valid
 *      Byte Position   4
 *      Bit Position    0
 *      Bit Length      1
 *
*/

typedef struct {
        int ts_ms;
        unsigned char two_message_periods;
        unsigned int message_timeout_counter;
	float distance_to_target;
	float relative_speed_to_target;
        unsigned char object_type;
        unsigned char object_data_valid;
} m56_lidar_target_t;


static inline void get_m56_lidar_target(unsigned char *data, 
	m56_lidar_target_t *p) {

        p->distance_to_target = ((signed short)((data[0] + (data[1] << 8)))) * lidar_res;
        p->relative_speed_to_target = ((signed short)((data[2] + (data[3] << 8)))) * lidar_res;
        p->object_type = (data[4] & MASK_b1) >> 1;
        p->object_data_valid = data[4] & MASK_b0;
}

/*******************************************************************************
 *      m56_yaw_rate
 *      Message ID      0x52c
 *      Transmitted every 100 ms
 *
 *	yaw_rate
 *      Byte Position   0-1
 *      Bit Position    0-15
 *      Bit Length      16
 *
 *	yaw_rate_sensor_value
 *      Byte Position   5-6
 *      Bit Position    0-15
 *      Bit Length      16
 *
*/

typedef struct {
        int ts_ms;
        unsigned char two_message_periods;
        unsigned int message_timeout_counter;
	float yaw_rate;
	float yaw_rate_sensor_value;
} m56_yaw_rate_t;


static inline void get_m56_yaw_rate(unsigned char *data, 
	m56_yaw_rate_t *p) {

        p->yaw_rate = ((signed short)((data[0] + (data[1] << 8)))) * yaw_rate_sensor_res;
        p->yaw_rate_sensor_value = ((signed short)((data[5] + (data[6] << 8)))) * yaw_rate_sensor_res;
}

/*******************************************************************************
 *      m56_lidar_status
 *      Message ID      0x52d
 *      Transmitted every 100 ms
 *
 *	laser_operating_flag
 *      Byte Position   1
 *      Bit Position    4
 *      Bit Length      1
 *
 *	laser_fail
 *      Byte Position   1
 *      Bit Position    0
 *      Bit Length      1
 *
*/

typedef struct {
        int ts_ms;
        unsigned char two_message_periods;
        unsigned int message_timeout_counter;
        unsigned char laser_operating_flag;
        unsigned char laser_fail;
} m56_lidar_status_t;


static inline void get_m56_lidar_status(unsigned char *data, 
	m56_lidar_status_t *p) {

        p->laser_operating_flag = (data[1] & MASK_b4) >> 4;
        p->laser_fail = data[1] & MASK_b0;
}

typedef struct {
	unsigned char ignition_status;
} m56_ignition_status_t;

/*
** printcan.c - prints 8-byte CAN message to stdout
*/
int printcan(db_komodo_t *db_kom);

/* TODO
** printmsg - prints parsed contents of M56 CAN message to stdout
*/
int printmsg(db_komodo_t *db_kom);

void check_msg_timeout(int curr_ts_ms, int *prev_ts_ms,
        unsigned char *two_message_periods,
        unsigned int *message_timeout_counter);

/*
** Communication data between vehicles
** 
** DNE491 - Silver M56-S
** DNC304 - Black exterior, gray interior
** PRO4 -   Black exterior, black interior M56-S
*/ 
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID;
	unsigned char MSGCNT_01;
	float v_VSP_491;
	float VSPCOMN_491;
	float ACVCOMO_491;
} m56_vdne491_m210_t;
    
static inline void get_m56_vdne491_m210(unsigned char *data, 
	m56_vdne491_m210_t *p) {
	p->ID = data[0];
	p->MSGCNT_01 = data[1];
	p->v_VSP_491 = (float)(0.1 * (data[2] + (data[3] << 8)));
	p->VSPCOMN_491 = (float)(0.1 * (data[4] + (data[5] << 8)));
	p->ACVCOMO_491 = (float)(0.1 * (data[6] + (data[7] << 8)));
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID;
	unsigned char MSGCNT_02;
	float XG_491;
	float vDISTANCE_491;
	float vVR_491;
	unsigned char fBRAKE_SE_491;
	unsigned char fACCEL_SE_491;
	unsigned char fACC_CRUISE_491;
	unsigned char fSPORTSMODESW_491;
	unsigned char fAUTOMODESW_491;
	unsigned char fSTATE_LOCK_491;
	unsigned char fACC_LMT_CACC_491;
} m56_vdne491_m211_t;
    
static inline void get_m56_vdne491_m211(unsigned char *data, 
	m56_vdne491_m211_t *p) {
	p->ID = data[0];
	p->MSGCNT_02 = data[1];
	p->XG_491 = (float)(0.1 * (data[2]));
	p->vDISTANCE_491 = (float)(0.1 * (data[3] + (data[4] << 8)));
	p->vVR_491 = (float)(0.1 * (data[5] + (data[6] << 8)));
        p->fBRAKE_SE_491 = data[7] & MASK_b0;
        p->fACCEL_SE_491 = data[7] & MASK_b1 >> 1;
        p->fACC_CRUISE_491 = data[7] & MASK_b2 >> 2;
        p->fSPORTSMODESW_491 = data[7] & MASK_b3 >> 3;
        p->fAUTOMODESW_491 = data[7] & MASK_b4 >> 4;
        p->fSTATE_LOCK_491 = data[7] & MASK_b5 >> 5;
        p->fACC_LMT_CACC_491 = data[7] & MASK_b6 >> 6;
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID;
	unsigned char MSGCNT_03;
	float vSET_VSP_491;
} m56_vdne491_m212_t;
    
static inline void get_m56_vdne491_m212(unsigned char *data, 
	m56_vdne491_m212_t *p) {
	p->ID = data[0];
	p->MSGCNT_03 = data[1];
	p->vSET_VSP_491 = (float)(0.1 * (data[2]));
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID;
	unsigned char MSGCNT_04;
} m56_vdne491_m213_t;
    
    
static inline void get_m56_vdne491_m213(unsigned char *data, 
	m56_vdne491_m213_t *p) {
	p->ID = data[0];
	p->MSGCNT_04 = data[1];
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID;
	unsigned char MSGCNT01_PRO4;
	float v_VSP_PRO4;
	float VSPCOMN_PRO4;
	float ACVCOMO_PRO4;
} m56_vpro4_m214_t;
    
static inline void get_m56_vpro4_m214(unsigned char *data, 
	m56_vpro4_m214_t *p) {
	p->ID = data[0];
	p->MSGCNT01_PRO4 = data[1];
	p->v_VSP_PRO4 = (float)(0.1 * (data[2]) + (data[3] << 8));
	p->VSPCOMN_PRO4 = (float)(0.1 * (data[4] + (data[5] << 8)));
	p->ACVCOMO_PRO4 = (float)(0.1 * (data[6] + (data[7] << 8)));
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID;
	unsigned char MSGCNT_02_PRO4;
	float XG_PRO4;
	float vDISTANCE_PRO4;
	float vVR_PRO4;
	unsigned char fBRAKE_SE_PRO4;
	unsigned char fACCEL_SE_PRO4;
	unsigned char fACC_CRUISE_PRO4;
	unsigned char fSPORTSMODESW;
	unsigned char fAUTOMODESW;
	unsigned char fSTATE_LOCK_PRO4;
	unsigned char fACC_LMT_CACC_PRO4;
} m56_vpro4_m215_t;
    
static inline void get_m56_vpro4_m215(unsigned char *data, 
	m56_vpro4_m215_t *p) {
	p->ID = data[0];
	p->MSGCNT_02_PRO4 = data[1];
	p->XG_PRO4 = (float)(0.1 * (data[2]));
	p->vDISTANCE_PRO4 = (float)(0.1 * (data[3] + (data[4] << 8)));
	p->vVR_PRO4 = (float)(0.1 * (data[5] + (data[6] << 8)));
        p->fBRAKE_SE_PRO4 = data[7] & MASK_b0;
        p->fACCEL_SE_PRO4 = data[7] & MASK_b1 >> 1;
        p->fACC_CRUISE_PRO4 = data[7] & MASK_b2 >> 2;
        p->fSPORTSMODESW = data[7] & MASK_b3 >> 3;
        p->fAUTOMODESW = data[7] & MASK_b4 >> 4;
        p->fSTATE_LOCK_PRO4 = data[7] & MASK_b5 >> 5;
        p->fACC_LMT_CACC_PRO4 = data[7] & MASK_b6 >> 6;
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID;
	unsigned char MSGCNT_03_PRO4;
	float vSET_VSP_PRO4;
} m56_vpro4_m216_t;
    
static inline void get_m56_vpro4_m216(unsigned char *data, 
	m56_vpro4_m216_t *p) {
	p->ID = data[0];
	p->MSGCNT_03_PRO4 = data[1];
	p->vSET_VSP_PRO4 = (float)(0.1 * (data[2]));
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID;
	unsigned char MSGCNT_04;
} m56_vpro4_m217_t;
    
static inline void get_m56_vpro4_m217(unsigned char *data, 
	m56_vpro4_m217_t *p) {
	p->ID = data[0];
	p->MSGCNT_04 = data[1];
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID_01_304;
	unsigned char MSGNCT_01_304;
	float v_VSP_304;
	float VSPCOMN_304;
	float ACVCOMO_304;
} m56_vdnc304_m218_t;
    
static inline void get_m56_vdnc304_m218(unsigned char *data, 
	m56_vdnc304_m218_t *p) {
	p->ID_01_304 = data[0];
	p->MSGNCT_01_304 = data[1];
	p->v_VSP_304 = (float)(0.1 * (data[2]) + (data[3] << 8));
	p->VSPCOMN_304 = (float)(0.1 * (data[4] + (data[5] << 8)));
	p->ACVCOMO_304 = (float)(0.1 * (data[6] + (data[7] << 8)));
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID_02_304;
	unsigned char MSGCNT_02_304;
	float XG_304;
	float vDISTANCE_304;
	float vVR_304;
	unsigned char fBRAKE_SE_304;
	unsigned char fACCEL_SE_304;
	unsigned char fACC_CRUISE_304;
	unsigned char fSPORTSMODESW;
	unsigned char fAUTOMODESW;
	unsigned char fSTATE_LOCK_304;
	unsigned char fACC_LMT_CACC_304;
} m56_vdnc304_m219_t;
    
static inline void get_m56_vdnc304_m219(unsigned char *data, 
	m56_vdnc304_m219_t *p) {
	p->ID_02_304 = data[0];
	p->MSGCNT_02_304 = data[1];
	p->XG_304 = (float)(0.1 * (data[2]));
	p->vDISTANCE_304 = (float)(0.1 * (data[3] + (data[4] << 8)));
	p->vVR_304 = (float)(0.1 * (data[5] + (data[6] << 8)));
        p->fBRAKE_SE_304 = data[7] & MASK_b0;
        p->fACCEL_SE_304 = data[7] & MASK_b1 >> 1;
        p->fACC_CRUISE_304 = data[7] & MASK_b2 >> 2;
        p->fSPORTSMODESW = data[7] & MASK_b3 >> 3;
        p->fAUTOMODESW = data[7] & MASK_b4 >> 4;
        p->fSTATE_LOCK_304 = data[7] & MASK_b5 >> 5;
        p->fACC_LMT_CACC_304 = data[7] & MASK_b6 >> 6;
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID_03_304;
	unsigned char MSGCNT_03_304;
	float vSET_VSP_304;
} m56_vdnc304_m21a_t;
    
static inline void get_m56_vdnc304_m21a(unsigned char *data, 
	m56_vdnc304_m21a_t *p) {
	p->ID_03_304 = data[0];
	p->MSGCNT_03_304 = data[1];
	p->vSET_VSP_304 = (float)(0.1 * (data[2]));
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID_04_304;
	unsigned char MSGCNT_04_304;
} m56_vdnc304_m21b_t;
    
static inline void get_m56_vdnc304_m21b(unsigned char *data, 
	m56_vdnc304_m21b_t *p) {
	p->ID_04_304 = data[0];
	p->MSGCNT_04_304 = data[1];
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID_01_PRO4_2;
	unsigned char MSGNCT_01_PRO4;
	float v_VSP_PRO4_2;
	float VSPCOMN_PRO4_2;
	float ACVCOMO_PRO4_2;
} m56_vpro4_m21c_t;
    
static inline void get_m56_vpro4_m21c(unsigned char *data, 
	m56_vpro4_m21c_t *p) {
	p->ID_01_PRO4_2 = data[0];
	p->MSGNCT_01_PRO4 = data[1];
	p->v_VSP_PRO4_2 = (float)(0.1 * (data[2]) + (data[3] << 8));
	p->VSPCOMN_PRO4_2 = (float)(0.1 * (data[4] + (data[5] << 8)));
	p->ACVCOMO_PRO4_2 = (float)(0.1 * (data[6] + (data[7] << 8)));
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID_02_PRO4_2;
	unsigned char MSGCNT_02_PRO4_2;
	float XG_PRO4_2;
	float vDISTANCE_PRO4_2;
	float vVR_PRO4_2;
	unsigned char fBRAKE_SE_PRO4_2;
	unsigned char fACCEL_SE_PRO4_2;
	unsigned char fACC_CRUISE_PRO4_2;
	unsigned char fSPORTSMODESW;
	unsigned char fAUTOMODESW;
	unsigned char fSTATE_LOCK_PRO4_2;
	unsigned char fACC_LMT_CACC_PRO4_2;
} m56_vpro4_m21d_t;
    
static inline void get_m56_vpro4_m21d(unsigned char *data, 
	m56_vpro4_m21d_t *p) {
	p->ID_02_PRO4_2 = data[0];
	p->MSGCNT_02_PRO4_2 = data[1];
	p->XG_PRO4_2 = (float)(0.1 * (data[2]));
	p->vDISTANCE_PRO4_2 = (float)(0.1 * (data[3] + (data[4] << 8)));
	p->vVR_PRO4_2 = (float)(0.1 * (data[5] + (data[6] << 8)));
        p->fBRAKE_SE_PRO4_2 = data[7] & MASK_b0;
        p->fACCEL_SE_PRO4_2 = data[7] & MASK_b1 >> 1;
        p->fACC_CRUISE_PRO4_2 = data[7] & MASK_b2 >> 2;
        p->fSPORTSMODESW = data[7] & MASK_b3 >> 3;
        p->fAUTOMODESW = data[7] & MASK_b4 >> 4;
        p->fSTATE_LOCK_PRO4_2 = data[7] & MASK_b5 >> 5;
        p->fACC_LMT_CACC_PRO4_2 = data[7] & MASK_b6 >> 6;
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID_03_PRO4_2;
	unsigned char MSGCNT_03_PRO4_2;
	float vSET_VSP_PRO4_2;
} m56_vpro4_m21e_t;
    
static inline void get_m56_vpro4_m21e(unsigned char *data, 
	m56_vpro4_m21e_t *p) {
	p->ID_03_PRO4_2 = data[0];
	p->MSGCNT_03_PRO4_2 = data[1];
	p->vSET_VSP_PRO4_2 = (float)(0.1 * (data[2]));
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	unsigned char ID_04_PRO4_2;
	unsigned char MSGCNT_04_PRO4_2;
} m56_vpro4_m21f_t;
    
static inline void get_m56_vpro4_m21f(unsigned char *data, 
	m56_vpro4_m21f_t *p) {
	p->ID_04_PRO4_2 = data[0];
	p->MSGCNT_04_PRO4_2 = data[1];
}

typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	//From ADAS - Fanping wants this   
	float vACC_COM_LMT_z0;
	float vMDISTANCE_ADAS;
	float vvPRECEDING_SPEED_ADAS32;
	unsigned char fSTATE_LOCK_ADAS;
} m56_adas_289_t;
    
static inline void get_m56_adas_289(unsigned char *data, 
	m56_adas_289_t *p) {
	p->vACC_COM_LMT_z0 = 0.1 * data[0];
	p->vMDISTANCE_ADAS = (float)(0.1 * (data[2]) + (data[3] << 8));
	p->vvPRECEDING_SPEED_ADAS32 = 
		(float)(0.1 * (data[4] + (data[5] << 8)));
	p->fSTATE_LOCK_ADAS = data[6] & MASK_b0;
}
    
typedef struct {
	int ts_ms;
	unsigned char two_message_periods;
	unsigned int message_timeout_counter;
	//From ADAS - Fanping wants this   
	float vVSPCOMN;
	float vACVCOMO;
} m56_adas_28a_t;
    
static inline void get_m56_adas_28a(unsigned char *data, 
	m56_adas_28a_t *p) {
	p->vVSPCOMN = (float)(0.1 * (data[0]) + (data[1] << 8));
	p->vACVCOMO = (float)(0.1 * (data[2]) + (data[3] << 8));
}
