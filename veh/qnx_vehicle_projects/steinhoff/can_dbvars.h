#pragma once
#define	DB_INPUT_TYPE				1000
#define	DB_OUTPUT_TYPE				2000
#define	DB_STEINHOFF_MSG_TYPE		3000
#define	DB_STEINHOFF_BRAKE_OUT_TYPE	4000
#define	DB_STEINHOFF_ACCEL_OUT_TYPE	5000

#define	DB_INPUT_VAR				DB_INPUT_TYPE
#define	DB_OUTPUT_VAR				DB_OUTPUT_TYPE
#define	DB_STEINHOFF_MSG_VAR		DB_STEINHOFF_MSG_TYPE
#define	DB_STEINHOFF_BRAKE_OUT_VAR	DB_STEINHOFF_BRAKE_OUT_TYPE
#define	DB_STEINHOFF_ACCEL_OUT_VAR	DB_STEINHOFF_ACCEL_OUT_TYPE
#define BRAKE_PORT	(char)1
#define ACCEL_PORT	(char)2

typedef struct{
	unsigned long id;
	unsigned char data[8];
} IS_PACKED db_steinhoff_msg_t;

typedef struct{
	unsigned long id;
	unsigned char data[8];
	unsigned char size;
	unsigned char port;
} IS_PACKED db_steinhoff_out_t;

typedef struct {
	float vehicle_speed_mps;	//- Longitudinal speed
	float vehicle_accel_mps2;	//- Longitudinal acceleration
	float torque;			//- Applied torque (if available)
	char gear;			//- Transmission gear
	float prec_veh_dist_meter;	//- Relative distance to target vehicle
	float prec_veh_rel_speed_mps;	//- Relative speed to target vehicle
	float yaw_rate_dps;		//- Yaw rate (if available)
	float steering_angle_deg;	//- Steering angle (if available)
	char system_status;		//- Any type of system status (e.g. ACC mode on)
} input_t;

typedef struct {
	float throttle_pct;		//- Throttle percentage
	float decel_request;		//- Desired deceleration (for braking) 
	float brake_level;		//- Brake level (applies only for Accord)
} output_t;
