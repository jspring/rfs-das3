#include <db_include.h>
#include <db_utils.h>
#include <path_gps_lib.h>
#include "data_log.h"
#include "accord_can.h"
#include "can_dbvars.h"

#define DB_ACCORD_MSG98_TYPE     0x98
#define DB_ACCORD_MSG99_TYPE     0x99
#define DB_ACCORD_MSG158_TYPE	0x158
#define DB_ACCORD_MSG392_TYPE	0x392
#define DB_ACCORD_MSG530_TYPE	0x530


#define DB_ACCORD_MSG98_VAR	DB_ACCORD_MSG98_TYPE
#define DB_ACCORD_MSG99_VAR	DB_ACCORD_MSG99_TYPE
#define DB_ACCORD_MSG158_VAR	DB_ACCORD_MSG158_TYPE
#define DB_ACCORD_MSG392_VAR	DB_ACCORD_MSG392_TYPE
#define DB_ACCORD_MSG530_VAR	DB_ACCORD_MSG530_TYPE

db_id_t db_vars_list[] =  {
	{DB_ACCORD_MSG98_VAR, sizeof(accord_accel_cmd_t)},
	{DB_ACCORD_MSG99_VAR, sizeof(accord_brake_cmd_t)},
	{DB_ACCORD_MSG158_VAR, sizeof(accord_vehicle_speed_t)},
	{DB_ACCORD_MSG392_VAR, sizeof(accord_PRNDL_Pos_t)},
	{DB_ACCORD_MSG530_VAR, sizeof(accord_torque_t)},
	{DB_INPUT_VAR, sizeof(input_t)},
	{DB_OUTPUT_VAR, sizeof(output_t)},
};
#define NUM_DB_VARS (sizeof(db_vars_list)/sizeof(db_id_t))
