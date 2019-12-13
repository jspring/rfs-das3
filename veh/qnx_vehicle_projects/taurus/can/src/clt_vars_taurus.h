#include <db_include.h>
#include <db_utils.h>
#include <path_gps_lib.h>
#include "data_log.h"
#include "taurus_can.h"
#include "veh_trk.h"

#define DB_TAURUS_MSG98_TYPE     0x98
#define DB_TAURUS_MSG99_TYPE     0x99
#define DB_TAURUS_MSGAA_TYPE     0xAA
#define DB_TAURUS_MSGB4_TYPE     0xB4
#define DB_TAURUS_MSG228_TYPE    0x228
#define DB_TAURUS_MSG343_TYPE    0x343
#define DB_TAURUS_MSG399_TYPE    0x399
#define DB_LONG_OUTPUT_TYPE	8000

#define DB_TAURUS_MSG98_VAR      DB_TAURUS_MSG98_TYPE
#define DB_TAURUS_MSG99_VAR      DB_TAURUS_MSG99_TYPE
#define DB_TAURUS_MSGAA_VAR      DB_TAURUS_MSGAA_TYPE
#define DB_TAURUS_MSGB4_VAR      DB_TAURUS_MSGB4_TYPE
#define DB_TAURUS_MSG228_VAR     DB_TAURUS_MSG228_TYPE
#define DB_TAURUS_MSG343_VAR     DB_TAURUS_MSG343_TYPE
#define DB_TAURUS_MSG399_VAR     DB_TAURUS_MSG399_TYPE
#define DB_LONG_OUTPUT_VAR	DB_LONG_OUTPUT_TYPE


db_id_t db_vars_list[] =  {
	{DB_TAURUS_MSG98_VAR, sizeof(taurus_accel_cmd_t)},
	{DB_TAURUS_MSG99_VAR, sizeof(taurus_accel_cmd_t)},
	{DB_TAURUS_MSGAA_VAR, sizeof(taurus_wheel_speed_t)},
	{DB_TAURUS_MSGB4_VAR, sizeof(taurus_vehicle_speed_t)},
	{DB_TAURUS_MSG228_VAR, sizeof(taurus_long_lat_accel_t)},
	{DB_TAURUS_MSG343_VAR, sizeof(taurus_accel_cmd_status_t)},
	{DB_TAURUS_MSG399_VAR, sizeof(taurus_cruise_control_state_t)},
	{DB_LONG_OUTPUT_VAR, sizeof(long_output_typ)},
};
#define NUM_DB_VARS (sizeof(db_vars_list)/sizeof(db_id_t))
