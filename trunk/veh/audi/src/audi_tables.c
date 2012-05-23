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
#include "audi_can.h"
#include "uimu.h"

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
uimu_typ uimu;
sync_record_typ video;
path_gps_point_t my_gps; // on-vehicle GPS
char * not_implemented = "9999";
audi_t	audi;

/** Add lines here when new DB variables are referenced in the tables.
 */
db_var_spec_t audi_db_vars[] =
{
        {DB_EVT300_RADAR1_VAR, sizeof(evt300_radar_typ), &evt300a},
        {DB_GPS_PT_LCL_VAR, sizeof(path_gps_point_t), &my_gps},
        {DB_SYNC_RECORD_VAR, sizeof(sync_record_typ), &video},
        {DB_UIMU_VAR, sizeof(uimu_typ), &uimu},
        {DB_AUDI_VAR, sizeof(audi_t), &audi},
};

int num_audi_db_vars = (sizeof(audi_db_vars)/sizeof(db_var_spec_t));

/** The following array is used to specify the output format of the "d" file
 *  for the Volkswagen Audi - vehicle code 'h'.
 *  The first column of the file is always an hh:mm:ss.sss timestamp,
 *  the table begins with the second column.
 */
data_log_column_spec_t audi_data_spec[] =
{
        {"%.3lf ", &seconds_since_midnight, BASE_DOUBLE, REPLAY_NO},    // 2
        {"%.3lf ", &seconds_since_start, BASE_DOUBLE, REPLAY_TIME},
        {"%hhd ", &audi.brake, BASE_INT, REPLAY_USE},          
        {"%hhd ", &audi.turn_lights, BASE_INT, REPLAY_USE},		//5
        {"%hhd ", &audi.cc, BASE_INT, REPLAY_USE},          
        {"%hhd ", &audi.gear, BASE_INT, REPLAY_USE},          
        {"%hhd ", &audi.turn_signal, BASE_INT, REPLAY_USE},          
        {"%hhd ", &audi.wiper, BASE_INT, REPLAY_USE},          
        {"%hhd ", &audi.ignition.digin, BASE_INT, REPLAY_USE},		//10
        {"%.3f ", &audi.brake_pressure, BASE_DOUBLE, REPLAY_USE},          
        {"%.3f ", &audi.lat_acc, BASE_DOUBLE, REPLAY_USE},          
        {"%.3f ", &audi.long_acc, BASE_DOUBLE, REPLAY_USE},          
        {"%.3f ", &audi.throttle, BASE_DOUBLE, REPLAY_USE},          
        {"%.3f ", &audi.steering_angle, BASE_DOUBLE, REPLAY_USE},	//15
        {"%.3f ", &audi.veh_speed, BASE_DOUBLE, REPLAY_USE},          
        {"%.3f ", &audi.yaw, BASE_DOUBLE, REPLAY_USE},          
        {"%hd ", &uimu.xaccel, BASE_INT, REPLAY_USE},          
        {"%hd ", &uimu.yaccel, BASE_INT, REPLAY_USE},          
        {"%hd ", &uimu.zaccel, BASE_INT, REPLAY_USE}, 			//20    
        {"%hd ", &uimu.xgyro, BASE_INT, REPLAY_USE},          
        {"%hd ", &uimu.ygyro, BASE_INT, REPLAY_USE},          
        {"%hd ", &uimu.zgyro, BASE_INT, REPLAY_USE}, 			    
        {"%9.2f ", &gps_utc_seconds, BASE_DOUBLE, REPLAY_USE},           
        {"%06d ", &my_gps.date, BASE_INT, REPLAY_USE},		//25
        {"%13.8lf ", &my_gps.longitude, BASE_DOUBLE, REPLAY_USE},
        {"%13.8lf ", &my_gps.latitude, BASE_DOUBLE, REPLAY_USE},	
        {"%6.3lf ", &my_gps.speed, BASE_DOUBLE, REPLAY_USE},                 
        {"%6.3f ", &my_gps.heading, BASE_FLOAT, REPLAY_USE},                 
        {"%6.2f ", &my_gps.altitude, BASE_FLOAT, REPLAY_USE},	//30
        {"%d ", &my_gps.num_sats, BASE_INT, REPLAY_USE},
        {"%d ", &my_gps.pos, BASE_INT, REPLAY_USE},		
        {"%6.3f ", &my_gps.hdop, BASE_FLOAT, REPLAY_USE},                    
};

int num_jdfile_col = sizeof(audi_data_spec)/sizeof(data_log_column_spec_t);

void save_audi(FILE *fout, timestamp_t timestamp,
                        int use_memory, buff_typ *pbuff,
                        int num_columns) {

        save_to_spec (fout, timestamp, use_memory, pbuff, num_jdfile_col,
                &audi_data_spec[0]);
}
