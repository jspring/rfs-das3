/**
 *      Additional variables derived from DB VAR fields that
 *      are part of the output column specification
 */

#include <db_include.h>
#include <db_utils.h>
#include <path_gps_lib.h>
#include <evt300.h>
#include <data_log.h>
#include <db_sync.h>
#include <uimu.h>
#include "altima.h"

/// These variables require processing other than DB reads done by wrfiles_nt.c
double seconds_since_midnight = 0.0;    // from hh:mm.ss.sss in column 1
double seconds_since_start = 0.0;       // local time since start of run
double seconds_last_curl = 0.0;         // seconds since midnight, last curl 
double gps_utc_seconds = 0.0;           // local UTC seconds since midnight
double clock_gps_read_seconds = 0.0;    // gps read time, seconds since midnight
double local_clock_seconds = 0.0;       // local time seconds since midnight


float gps_formatted_utc_time = 0.0;    // hhmmss.ss 

/// All these global variables must have extern statements in wrfiles_nt.h
/// They correspond to DB variables that are read.
evt300_radar_typ evt300a;
alt_cruise_control_for_tm_t ccftm;
alt_engine_t alt_eng;
alt_gear_indication_t alt_gi;
alt_vehicle_speed_t alt_vs;
alt_front_wiping_brake_switch_t alt_fwbs;
alt_turn_signal_ignition_t alt_tsi;
uimu_typ uimu;
sync_record_typ video;
path_gps_point_t gps_point; // on-vehicle GPS
char * not_implemented = "9999";

/** Add lines here when new DB variables are referenced in the tables.
 */
db_var_spec_t db_vars[] =
{
        {DB_EVT300_RADAR1_VAR, sizeof(evt300_radar_typ), &evt300a},
        {DB_GPS_PT_LCL_VAR, sizeof(path_gps_point_t), &gps_point},
        {DB_SYNC_RECORD_VAR, sizeof(sync_record_typ), &video},
	{DB_ALT_CCFTM_VAR, sizeof(alt_cruise_control_for_tm_t), &ccftm},
	{DB_ALT_ENG_VAR, sizeof(alt_engine_t), &alt_eng},
	{DB_ALT_GI_VAR, sizeof(alt_gear_indication_t), &alt_gi},
	{DB_ALT_VS_VAR, sizeof(alt_vehicle_speed_t), &alt_vs},
	{DB_ALT_FWBS_VAR, sizeof(alt_front_wiping_brake_switch_t), &alt_fwbs},
	{DB_ALT_TSI_VAR, sizeof(alt_turn_signal_ignition_t), &alt_tsi},
        {DB_UIMU_VAR, sizeof(uimu_typ), &uimu},
};

int num_db_vars = (sizeof(db_vars)/sizeof(db_var_spec_t));

/** The following array is used to specify the output format of the "d" file
 *  for the Nissan Altima  -- vehicle code "g".
 *  The first column of the file is always an hh:mm:ss.sss timestamp,
 *  the table begins with the second column.
 */
data_log_column_spec_t file_specd[] =
{
        {"%.3lf ", &seconds_since_midnight, BASE_DOUBLE, REPLAY_NO},    // 2
        {"%.3lf ", &seconds_since_start, BASE_DOUBLE, REPLAY_TIME},
        {"%hhd ", &alt_tsi.ignition, BASE_INT, REPLAY_USE},
        {"%hhd ", &alt_fwbs.brake_switch, BASE_INT, REPLAY_USE},	//5
        {"%6.3lf ", &alt_eng.pct_throttle, BASE_DOUBLE, REPLAY_USE},	
        {"%hhd ", &ccftm.code, BASE_INT, REPLAY_USE},	
        {"%6.3lf ", &alt_vs.vehicle_speed, BASE_DOUBLE, REPLAY_USE},	
        {"%hhd ", &alt_gi.code, BASE_INT, REPLAY_USE},	
        {"%6.3lf ", &alt_eng.rpm, BASE_DOUBLE, REPLAY_USE},		//10
        {"%hhd ", &alt_tsi.turn_signal, BASE_INT, REPLAY_USE},	
        {"%hhd ", &alt_fwbs.front_wiping, BASE_INT, REPLAY_USE},	
        {"%hd ", &uimu.xaccel, BASE_INT, REPLAY_USE},          
        {"%hd ", &uimu.yaccel, BASE_INT, REPLAY_USE},          
        {"%hd ", &uimu.zaccel, BASE_INT, REPLAY_USE}, 			//15    
        {"%hd ", &uimu.xgyro, BASE_INT, REPLAY_USE},          
        {"%hd ", &uimu.ygyro, BASE_INT, REPLAY_USE},          
        {"%hd ", &uimu.zgyro, BASE_INT, REPLAY_USE}, 			    
        {"%9.2f ", &gps_utc_seconds, BASE_DOUBLE, REPLAY_USE},           
        {"%06d ", &gps_point.date, BASE_INT, REPLAY_USE},		//20
        {"%13.8lf ", &gps_point.longitude, BASE_DOUBLE, REPLAY_USE},
        {"%13.8lf ", &gps_point.latitude, BASE_DOUBLE, REPLAY_USE},	
        {"%6.3lf ", &gps_point.speed, BASE_DOUBLE, REPLAY_USE},                 
        {"%6.3f ", &gps_point.heading, BASE_FLOAT, REPLAY_USE},                 
        {"%6.2f ", &gps_point.altitude, BASE_FLOAT, REPLAY_USE},	//25
        {"%d ", &gps_point.num_sats, BASE_INT, REPLAY_USE},
        {"%d ", &gps_point.pos, BASE_INT, REPLAY_USE},		
        {"%6.3f ", &gps_point.hdop, BASE_FLOAT, REPLAY_USE},                    
};

int num_dfile_columns = sizeof(file_specd)/sizeof(data_log_column_spec_t);

void save_altima(FILE *fout, timestamp_t timestamp,
                        int use_memory, buff_typ *pbuff) {

        save_to_spec (fout, timestamp, use_memory, pbuff, num_dfile_columns,
                &file_specd[0]);
}
