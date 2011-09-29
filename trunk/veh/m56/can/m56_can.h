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

const float steering_angle_res = 0.1; //deg
const float steering_velocity_res = 4; //deg/sec
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

const float rpm_res = 0.125;
static inline void get_m56_engine_rpm(unsigned char *data, m56_engine_rpm_t *p) {
	p->engine_rpm = ( (data[0] << 8) + data[1]) * rpm_res;
}

/*****************************************************************************************
 *      m56_pedal_position
 *      Message ID      0x239
 *      Byte Position   ?
 *      Bit Position    ?
 *      Bit Length      ?
 *      Transmitted every 20 ms
 */

typedef struct {
	timestamp_t ts;
	float pedal_position;
} m56_pedal_position_t;

const float pedal_pos_res = 0.392;
static inline void get_m56_pedal_position(unsigned char *data, m56_pedal_position_t *p) {
	p->pedal_position = data[0] * pedal_pos_res;
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

const float wheel_speed_res = 0.04166666;
const float vehicle_speed_res = 0.01;
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

/*
** printcan.c - prints 8-byte CAN message to stdout
*/
int printcan(db_komodo_t *db_kom);

/* TODO
** printmsg - prints parsed contents of M56 CAN message to stdout
*/
int printmsg(db_komodo_t *db_kom);
