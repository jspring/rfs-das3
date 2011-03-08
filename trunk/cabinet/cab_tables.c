/**\file
 *
 *	Tables for DB variables and column specification for logging
 *	and replay for Intersection Main Cabinet
 */	
#include <db_include.h>
#include <sys_buff.h>
#include <db_utils.h>
#include <path_gps_lib.h>
#include <evt300.h>
#include "clt_vars.h"
#include "data_log.h"
#include "alert_vars.h"
#include "expctl_vars.h"
#include "ids_io.h"
#include "sms_lib.h"
#include "gpio.h"
#include "wvtrnx.h"
#include "cicas_trial.h"
#include "cicas_msg.h"

/**  DB VARs read, declared global so that the variable addresses will
 *   be available to initialize the DB variable and column specification arrays.
 */
cicas_msg_hdr_t rx_sv_data_hdr;     		// sent from Taurus
cicas_msg_hdr_t rx_pov1_data_hdr;    	// sent from POV1
cicas_msg_hdr_t rx_pov2_data_hdr;    	// sent from POV2
cicas_msg_hdr_t rx_sv_ct_hdr;    	// sent from Taurus
cicas_msg_hdr_t rx_pov1_ct_hdr;    	// sent from POV1
cicas_msg_hdr_t rx_pov2_ct_hdr;    	// sent from POV2
cicas_msg_hdr_t tx_dvi_data_hdr;        	// sent to Taurus
cicas_msg_hdr_t tx_signal_phase_hdr;        	// sent to Taurus
cicas_msg_hdr_t tx_cab_ct_hdr;        // sent to Taurus
cicas_trial_t cab_trial;
cicas_trial_t sv_trial;
cicas_trial_t pov1_trial;
cicas_trial_t pov2_trial;
gpio_dig_in_t dig_in;
dii_out_typ dii_out;
dvi_out_typ dvi_out;
fusion_output_typ f_o;
fusion_double_typ buffer_back;
fusion_double_typ buffer_front;
evt300_radar_typ evt300a;
evt300_radar_typ evt300b;
path_gps_point_t sv_gps; 		// sent from SV Taurus
path_gps_point_t cabinet_gps; 		// GPS in cabinet
path_gps_point_t pov1_gps;
path_gps_point_t pov2_gps;
sv_data_t sv_data;
trial_typ trial;			// legacy for IDS demo
trial_param_typ trial_param;
traffic_signal_typ sig;
taurus_speed_typ taurus_speed;		// legacy for IDS demo 

/**
 *	Additional variables derived from DB VAR fields that
 *	are part of the output column specification
 */
timestamp_t cabinet_ts;			// used when reading back in
double seconds_since_midnight = 0.0;	// cabinet UTC seconds since midnight 
double sv_utc_seconds = 0.0;		// SV UTC seconds since midnight
double pov1_utc_seconds = 0.0;		// POV1 UTC seconds since midnight
double pov2_utc_seconds = 0.0;		// POV2 UTC seconds since midnight
double seconds_since_start = 0.0;	// seconds since start of run
unsigned char ped_warn = 0;		//DIG_IN 1
unsigned char lightwave_west = 0;	//DIG_IN 2
unsigned char lightwave_south = 0;	//DIG_IN 3
unsigned char lightwave_east = 0;	//DIG_IN 7 (remapped from 4)
unsigned char lightwave_north = 0;	//DIG_IN 5

/**
 *	This array is used to specify how to read in the DB vars.
 */
db_var_spec_t db_vars[] =
{
	{DB_BUFFER_BACK_VAR, sizeof(fusion_double_typ), &buffer_back},
	{DB_BUFFER_FRONT_VAR, sizeof(fusion_double_typ), &buffer_front},
        {DB_CAB_CICAS_TRIAL_VAR, sizeof(cicas_trial_t), &cab_trial},
        {DB_CICAS_RX_HDR_BASE_VAR + MSG_SV_DATA, sizeof(cicas_msg_hdr_t), &rx_sv_data_hdr},
        {DB_CICAS_RX_HDR_BASE_VAR + MSG_CICAS_SV_TRIAL_DATA, sizeof(cicas_msg_hdr_t), &rx_sv_ct_hdr},
        {DB_CICAS_RX_HDR_BASE_VAR + MSG_FIRST_POV_DATA, sizeof(cicas_msg_hdr_t), &rx_pov1_data_hdr},
        {DB_CICAS_RX_HDR_BASE_VAR + MSG_CICAS_POV1_TRIAL_DATA, sizeof(cicas_msg_hdr_t), &rx_pov1_ct_hdr},
        {DB_CICAS_RX_HDR_BASE_VAR + MSG_SECOND_POV_DATA, sizeof(cicas_msg_hdr_t), &rx_pov2_data_hdr},
        {DB_CICAS_RX_HDR_BASE_VAR + MSG_CICAS_POV2_TRIAL_DATA, sizeof(cicas_msg_hdr_t), &rx_pov2_ct_hdr},
        {DB_CICAS_TX_HDR_BASE_VAR + MSG_DVI_DATA, sizeof(cicas_msg_hdr_t), &tx_dvi_data_hdr},
        {DB_CICAS_TX_HDR_BASE_VAR + MSG_SIGNAL_PHASE, sizeof(cicas_msg_hdr_t), &tx_signal_phase_hdr},
        {DB_CICAS_TX_HDR_BASE_VAR + MSG_CICAS_CAB_TRIAL_DATA, sizeof(cicas_msg_hdr_t), &tx_cab_ct_hdr},
        {DB_DIG_IN_VAR, sizeof(gpio_dig_in_t), &dig_in},
	{DB_DII_OUT_VAR, sizeof(dii_out_typ), &dii_out},
	{DB_DVI_OUT_VAR, sizeof(dvi_out_typ), &dvi_out},
	{DB_EVT300_RADAR1_VAR, sizeof(evt300_radar_typ), &evt300a},
	{DB_EVT300_RADAR2_VAR, sizeof(evt300_radar_typ), &evt300b},
	{DB_FUSION_OUTPUT_VAR, sizeof(fusion_output_typ), &f_o},
	{DB_GPS_PT_RCV_VAR, sizeof(path_gps_point_t), &sv_gps}, 
	{DB_GPS_PT_LCL_VAR, sizeof(path_gps_point_t), &cabinet_gps}, 
	{DB_GPS_PT_RCV_VAR + 1, sizeof(path_gps_point_t), &pov1_gps}, 
	{DB_GPS_PT_RCV_VAR + 2, sizeof(path_gps_point_t), &pov2_gps}, 
	{DB_SV_DATA_VAR, sizeof(sv_data_t),  &sv_data},
	{DB_TAURUS_SPEED_VAR, sizeof(taurus_speed_typ), &taurus_speed},
	{DB_TRAFFIC_SIGNAL_VAR, sizeof(traffic_signal_typ), &sig},
	{DB_TRIAL_VAR, sizeof(trial_typ), &trial},
	{DB_TRIAL_PARAM_VAR, sizeof(trial_param_typ), &trial_param},
};

int num_db_vars = (sizeof(db_vars)/sizeof(db_var_spec_t));

/** This array is used to specify the output format of the "xe" file.
 */
data_log_column_spec_t experiment_spec[] = 
{
	{"HH:MM:SS.SSS ", &cabinet_ts, BASE_TIMESTAMP, REPLAY_TIME},	
	{"%d ", &trial.number, BASE_INT, REPLAY_USE},	
	{"%s ", &trial_param.specID, BASE_STRING, REPLAY_USE},	
	{"%d ", &trial.sv_stage, BASE_INT, REPLAY_USE},	
	{"%d ", &trial.pov_stage, BASE_INT, REPLAY_USE},	
	{"%d ", &trial.sv_lane, BASE_INT, REPLAY_USE},	
	//southbound	
	{"%hhd ", &f_o.direction[0].d2i.exists, BASE_CHAR, REPLAY_USE},	
	{"%6.2lf ", &f_o.direction[0].d2i.value, BASE_DOUBLE, REPLAY_USE},	
	{"%hhd ", &f_o.direction[0].speed.exists, BASE_CHAR, REPLAY_USE},
	{"%6.2lf ", &f_o.direction[0].speed.value, BASE_DOUBLE, REPLAY_USE},
	{"%hhd ", &f_o.direction[0].accel.exists, BASE_CHAR, REPLAY_USE},
	{"%6.2lf ", &f_o.direction[0].accel.value, BASE_DOUBLE, REPLAY_USE},	
	//westbound	
	{"%hhd ", &f_o.direction[1].d2i.exists, BASE_CHAR, REPLAY_USE},	
	{"%6.2lf ", &f_o.direction[1].d2i.value, BASE_DOUBLE, REPLAY_USE},
	{"%hhd ", &f_o.direction[1].speed.exists, BASE_CHAR, REPLAY_USE},
	{"%6.2lf ", &f_o.direction[1].speed.value, BASE_DOUBLE, REPLAY_USE},
	{"%hhd ", &f_o.direction[1].accel.exists, BASE_CHAR, REPLAY_USE},
	{"%6.2lf ", &f_o.direction[1].accel.value, BASE_DOUBLE, REPLAY_USE},
	//northbound	
	{"%hhd ", &f_o.direction[2].d2i.exists, BASE_CHAR, REPLAY_USE},
	{"%6.2lf ", &f_o.direction[2].d2i.value, BASE_DOUBLE, REPLAY_USE},
	{"%hhd ", &f_o.direction[2].speed.exists, BASE_CHAR, REPLAY_USE},
	{"%6.2lf ", &f_o.direction[2].speed.value, BASE_DOUBLE, REPLAY_USE},
	{"%hhd ", &f_o.direction[2].accel.exists, BASE_CHAR, REPLAY_USE},
	{"%6.2lf ", &f_o.direction[2].accel.value, BASE_DOUBLE, REPLAY_USE},
	//eastbound	
	{"%hhd ", &f_o.direction[3].d2i.exists, BASE_CHAR, REPLAY_USE},	
	{"%6.2lf ", &f_o.direction[3].d2i.value, BASE_DOUBLE, REPLAY_USE},
	{"%hhd ", &f_o.direction[3].speed.exists, BASE_CHAR, REPLAY_USE},
	{"%6.2lf ", &f_o.direction[3].speed.value, BASE_DOUBLE, REPLAY_USE},
	{"%hhd ", &f_o.direction[3].accel.exists, BASE_CHAR, REPLAY_USE},
	{"%6.2lf ", &f_o.direction[3].accel.value, BASE_DOUBLE, REPLAY_USE},
	{"%d ", &dii_out.dii_flag, BASE_INT, REPLAY_USE},	
	{"%d ", &dvi_out.dvi_flag, BASE_INT, REPLAY_USE},	
	{"%hhd ", &buffer_back.exists, BASE_CHAR, REPLAY_USE},	
	{"%6.2lf ", &buffer_back.value, BASE_DOUBLE, REPLAY_USE},	
	{"%hhd ", &buffer_front.exists, BASE_CHAR, REPLAY_USE},	
	{"%6.2lf ", &buffer_front.value, BASE_DOUBLE, REPLAY_USE},	
	{"%9.2lf ", &sv_utc_seconds, BASE_DOUBLE, REPLAY_USE},
	{"%13.7lf ", &sv_gps.latitude, BASE_DOUBLE, REPLAY_USE},
	{"%13.7lf ", &sv_gps.longitude, BASE_DOUBLE, REPLAY_USE},
	{"%hhd ", &sig.ring_phase[1].phase, BASE_CHAR, REPLAY_USE}, // phase 2
	{"%.1f ", &sig.ring_phase[1].time_used, BASE_FLOAT, REPLAY_USE},	
	{"%.1f ", &sig.ring_phase[1].time_left, BASE_FLOAT, REPLAY_USE},	
	{"%hhd ", &sig.ring_phase[3].phase, BASE_CHAR, REPLAY_USE}, // phase 4
	{"%.1f ", &sig.ring_phase[3].time_used, BASE_FLOAT, REPLAY_USE},	
	{"%.1f ", &sig.ring_phase[3].time_left, BASE_FLOAT, REPLAY_USE},	
	{"%d ", &sv_gps.num_sats, BASE_INT, REPLAY_USE},
	{"%6.3f ", &sv_gps.hdop, BASE_FLOAT, REPLAY_USE},
	{"%9.2lf ", &pov1_utc_seconds, BASE_DOUBLE, REPLAY_USE},
	{"%13.7lf ", &pov1_gps.latitude, BASE_DOUBLE, REPLAY_USE},
	{"%13.7lf ", &pov1_gps.longitude, BASE_DOUBLE, REPLAY_USE},
	{"%d ", &pov1_gps.num_sats, BASE_INT, REPLAY_USE},
	{"%6.3f ", &pov1_gps.hdop, BASE_FLOAT, REPLAY_USE},
	{"%9.2lf ", &pov2_utc_seconds, BASE_DOUBLE, REPLAY_USE},
	{"%13.7lf ", &pov2_gps.latitude, BASE_DOUBLE, REPLAY_USE},
	{"%13.7lf ", &pov2_gps.longitude, BASE_DOUBLE, REPLAY_USE},
	{"%d ", &pov2_gps.num_sats, BASE_INT, REPLAY_USE},
	{"%6.3f ", &pov2_gps.hdop, BASE_FLOAT, REPLAY_USE},
        {"%13.8lf ", &sv_data.revised_long, BASE_DOUBLE, REPLAY_USE},   
        {"%13.8lf ", &sv_data.revised_lat, BASE_DOUBLE, REPLAY_USE},
        {"%6.3lf ", &sv_data.revised_heading, BASE_DOUBLE, REPLAY_USE},
	{"%6.3f ", &sv_data.speed, BASE_DOUBLE, REPLAY_NO},
	{"%hhu ", &sv_data.right_turn_signal, BASE_CHAR, REPLAY_NO},
	{"%hhu ", &sv_data.left_turn_signal, BASE_CHAR, REPLAY_NO},
	{"%hhu ", &sv_data.brakes, BASE_CHAR, REPLAY_NO},
	{"%hhu ", &lightwave_west, BASE_CHAR, REPLAY_NO},
	{"%hhu ", &lightwave_south, BASE_CHAR, REPLAY_NO},
	{"%hhu ", &lightwave_east, BASE_CHAR, REPLAY_NO},
	{"%hhu ", &lightwave_north, BASE_CHAR, REPLAY_NO},
};

#define NUM_EFILE_COLUMNS sizeof(experiment_spec)/sizeof(data_log_column_spec_t) 
int num_efile_columns = sizeof(experiment_spec)/sizeof(data_log_column_spec_t); 

/** The following logging specification is for monitoring and debugging
 *  communications between the SV and the cabinet. It includes message
 *  header record for every message type that is sent and received, 
 *  and all data server variables written for messages received (except
 *  for sv and gps point structures and in vehicle fusion data, which
 *  are part of the e file) and any fields from the data
 *  structures for messages sent that are not already in the efile. 
 */
data_log_column_spec_t comm_spec[] = 
{
	{"HH:MM:SS.SSS ", &cabinet_ts, BASE_TIMESTAMP, REPLAY_TIME},	
	{"%.3lf ", &seconds_since_midnight, BASE_DOUBLE, REPLAY_NO}, 	// 2
	{"%.3lf ", &seconds_since_start, BASE_DOUBLE, REPLAY_TIME},
	{"%9.2lf ", &sv_utc_seconds, BASE_DOUBLE, REPLAY_NO},
	// legacy sent by cabinet DVI_DATA
	{"%hu ", &tx_dvi_data_hdr.sequence_number, BASE_SHORT, REPLAY_NO},
	{"%hhu ", &tx_dvi_data_hdr.message_type, BASE_CHAR, REPLAY_NO},
	{"%d ", &tx_dvi_data_hdr.byte_count, BASE_INT, REPLAY_NO},
	{"0x%08x ", &tx_dvi_data_hdr.src, BASE_HEX_INT, REPLAY_NO},
	{"%.3lf ", &tx_dvi_data_hdr.ts, BASE_TIMESTAMP, REPLAY_NO},
	{"%d ", &trial.number, BASE_INT, REPLAY_COMM},
	{"%d ", &trial.sv_lane, BASE_INT, REPLAY_COMM},
	{"%d ", &trial.dii_state, BASE_INT, REPLAY_COMM},
	{"%d ", &trial.dvi_state, BASE_INT, REPLAY_COMM},
	{"%d ", &trial.sv_stage, BASE_INT, REPLAY_COMM},
	{"%d ", &trial.pov_stage, BASE_INT, REPLAY_COMM},
	{"%6.3f ", &trial.target_pov_speed, BASE_FLOAT, REPLAY_COMM},
	{"%6.3f ", &trial.target_buffer, BASE_FLOAT, REPLAY_COMM},
	{"%6.3f ", &trial.predicted_buffer, BASE_FLOAT, REPLAY_COMM},
	//south
	{"%hhd ", &f_o.direction[0].d2i.exists, BASE_CHAR, REPLAY_COMM},	
	{"%6.2lf ", &f_o.direction[0].d2i.value, BASE_DOUBLE, REPLAY_COMM},	
	{"%d ", &f_o.direction[0].speed.exists, BASE_CHAR, REPLAY_COMM},
	{"%6.2lf ", &f_o.direction[0].speed.value, BASE_DOUBLE, REPLAY_COMM},
	{"%d ", &f_o.direction[0].accel.exists, BASE_CHAR, REPLAY_COMM},
	{"%6.2lf ", &f_o.direction[0].accel.value, BASE_DOUBLE, REPLAY_COMM},	
	//west
	{"%d ", &f_o.direction[1].d2i.exists, BASE_CHAR, REPLAY_COMM},	
	{"%6.2lf ", &f_o.direction[1].d2i.value, BASE_DOUBLE, REPLAY_COMM},
	{"%d ", &f_o.direction[1].speed.exists, BASE_CHAR, REPLAY_COMM},
	{"%6.2lf ", &f_o.direction[1].speed.value, BASE_DOUBLE, REPLAY_COMM},
	{"%d ", &f_o.direction[1].accel.exists, BASE_CHAR, REPLAY_COMM},
	{"%6.2lf ", &f_o.direction[1].accel.value, BASE_DOUBLE, REPLAY_COMM},
	//north
	{"%d ", &f_o.direction[2].d2i.exists, BASE_CHAR, REPLAY_COMM},
	{"%6.2lf ", &f_o.direction[2].d2i.value, BASE_DOUBLE, REPLAY_COMM},
	{"%d ", &f_o.direction[2].speed.exists, BASE_CHAR, REPLAY_COMM},
	{"%6.2lf ", &f_o.direction[2].speed.value, BASE_DOUBLE, REPLAY_COMM},
	{"%d ", &f_o.direction[2].accel.exists, BASE_CHAR, REPLAY_COMM},
	{"%6.2lf ", &f_o.direction[2].accel.value, BASE_DOUBLE, REPLAY_COMM},
	//east
	{"%d ", &f_o.direction[3].d2i.exists, BASE_CHAR, REPLAY_COMM},	
	{"%6.2lf ", &f_o.direction[3].d2i.value, BASE_DOUBLE, REPLAY_COMM},
	{"%d ", &f_o.direction[3].speed.exists, BASE_CHAR, REPLAY_COMM},
	{"%6.2lf ", &f_o.direction[3].speed.value, BASE_DOUBLE, REPLAY_COMM},
	{"%d ", &f_o.direction[3].accel.exists, BASE_CHAR, REPLAY_COMM},
	{"%6.2lf ", &f_o.direction[3].accel.value, BASE_DOUBLE, REPLAY_COMM},
	// SIGNAL_PHASE, sent by cabinet
	{"%hu ", &tx_signal_phase_hdr.sequence_number, BASE_SHORT, REPLAY_NO},
	{"%hhu ", &tx_signal_phase_hdr.message_type, BASE_CHAR, REPLAY_NO},
	{"%d ", &tx_signal_phase_hdr.byte_count, BASE_INT, REPLAY_NO},
	{"0x%08x ", &tx_signal_phase_hdr.src, BASE_HEX_INT, REPLAY_NO},
	{"%.3lf ", &tx_signal_phase_hdr.ts, BASE_TIMESTAMP, REPLAY_NO},
	{"%d ", &sig.ring_phase[1].phase, BASE_CHAR, REPLAY_COMM}, // phase 2
	{"%.1f ", &sig.ring_phase[1].time_used, BASE_FLOAT, REPLAY_COMM},	
	{"%.1f ", &sig.ring_phase[1].time_left, BASE_FLOAT, REPLAY_COMM},	
	{"%d ", &sig.ring_phase[3].phase, BASE_CHAR, REPLAY_COMM}, // phase 4
	{"%.1f ", &sig.ring_phase[3].time_used, BASE_FLOAT, REPLAY_COMM},	
	{"%.1f ", &sig.ring_phase[3].time_left, BASE_FLOAT, REPLAY_COMM},	
	// CICAS_TRIAL_DATA sent by  cabinet
	{"%hu ", &tx_cab_ct_hdr.sequence_number, BASE_SHORT, REPLAY_NO},
	{"%hhu ", &tx_cab_ct_hdr.message_type, BASE_CHAR, REPLAY_NO},
	{"%d ", &tx_cab_ct_hdr.byte_count, BASE_INT, REPLAY_NO},
	{"0x%08x ", &tx_cab_ct_hdr.src, BASE_HEX_INT, REPLAY_NO},
	{"%.3lf ", &tx_cab_ct_hdr.ts, BASE_TIMESTAMP, REPLAY_NO},
        {" %hhu ", &cab_trial.source, BASE_CHAR, REPLAY_COMM},
        {"%hu ", &cab_trial.trial_number, BASE_SHORT, REPLAY_COMM},
        {"%hhu ", &cab_trial.configuration, BASE_CHAR, REPLAY_COMM},
        {"%.2f ", &cab_trial.target_pov_speed, BASE_FLOAT, REPLAY_COMM},
        {"%.2f ", &cab_trial.target_pov_gap, BASE_FLOAT, REPLAY_COMM},
        {"%.2f ", &cab_trial.target_trailing_buffer, BASE_FLOAT, REPLAY_COMM},
        {"%hhu ", &cab_trial.vehicle_state, BASE_CHAR, REPLAY_COMM},
        {"%hhu ", &cab_trial.control_state, BASE_CHAR, REPLAY_COMM},
        {"%hhu ", &cab_trial.alert_state, BASE_CHAR, REPLAY_COMM},
	// CICAS_TRIAL_DATA from SV
	{"%hu ", &rx_sv_ct_hdr.sequence_number, BASE_SHORT, REPLAY_NO},
	{"%hhu ", &rx_sv_ct_hdr.message_type, BASE_CHAR, REPLAY_NO},
	{"%d ", &rx_sv_ct_hdr.byte_count, BASE_INT, REPLAY_NO},
	{"0x%08x ", &rx_sv_ct_hdr.src, BASE_HEX_INT, REPLAY_NO},
	{"%.3lf ", &rx_sv_ct_hdr.ts, BASE_TIMESTAMP, REPLAY_NO},
        {" %hhu ", &sv_trial.source, BASE_CHAR, REPLAY_COMM},
        {"%hu ", &sv_trial.trial_number, BASE_SHORT, REPLAY_COMM},
        {"%hhu ", &sv_trial.configuration, BASE_CHAR, REPLAY_COMM},
        {"%.2f ", &sv_trial.target_pov_speed, BASE_FLOAT, REPLAY_COMM},
        {"%.2f ", &sv_trial.target_pov_gap, BASE_FLOAT, REPLAY_COMM},
        {"%.2f ", &sv_trial.target_trailing_buffer, BASE_FLOAT, REPLAY_COMM},
        {"%hhu ", &sv_trial.vehicle_state, BASE_CHAR, REPLAY_COMM},
        {"%hhu ", &sv_trial.control_state, BASE_CHAR, REPLAY_COMM},
        {"%hhu ", &sv_trial.alert_state, BASE_CHAR, REPLAY_COMM},
	// SV_DATA hdr from SV
	{"%hu ", &rx_sv_data_hdr.sequence_number, BASE_SHORT, REPLAY_NO},
	{"%hhu ", &rx_sv_data_hdr.message_type, BASE_CHAR, REPLAY_NO},
	{"%d ", &rx_sv_data_hdr.byte_count, BASE_INT, REPLAY_NO},
	{"0x%08x ", &rx_sv_data_hdr.src, BASE_HEX_INT, REPLAY_NO},
	{"%.3lf ", &rx_sv_data_hdr.ts, BASE_TIMESTAMP, REPLAY_NO},
	// CICAS_TRIAL_DATA from POV1
	{"%hu ", &rx_pov1_ct_hdr.sequence_number, BASE_SHORT, REPLAY_NO},
	{"%hhu ", &rx_pov1_ct_hdr.message_type, BASE_CHAR, REPLAY_NO},
	{"%d ", &rx_pov1_ct_hdr.byte_count, BASE_INT, REPLAY_NO},
	{"0x%08x ", &rx_pov1_ct_hdr.src, BASE_HEX_INT, REPLAY_NO},
	{"%.3lf ", &rx_pov1_ct_hdr.ts, BASE_TIMESTAMP, REPLAY_NO},
        {" %hhu ", &pov1_trial.source, BASE_CHAR, REPLAY_COMM},
        {"%hu ", &pov1_trial.trial_number, BASE_SHORT, REPLAY_COMM},
        {"%hhu ", &pov1_trial.configuration, BASE_CHAR, REPLAY_COMM},
        {"%.2f ", &pov1_trial.target_pov_speed, BASE_FLOAT, REPLAY_COMM},
        {"%.2f ", &pov1_trial.target_pov_gap, BASE_FLOAT, REPLAY_COMM},
        {"%.2f ", &pov1_trial.target_trailing_buffer, BASE_FLOAT, REPLAY_COMM},
        {"%hhu ", &pov1_trial.vehicle_state, BASE_CHAR, REPLAY_COMM},
        {"%hhu ", &pov1_trial.control_state, BASE_CHAR, REPLAY_COMM},
        {"%hhu ", &pov1_trial.alert_state, BASE_CHAR, REPLAY_COMM},
	// CICAS_TRIAL_DATA from POV2
	{"%hu ", &rx_pov2_ct_hdr.sequence_number, BASE_SHORT, REPLAY_NO},
	{"%hhu ", &rx_pov2_ct_hdr.message_type, BASE_CHAR, REPLAY_NO},
	{"%d ", &rx_pov2_ct_hdr.byte_count, BASE_INT, REPLAY_NO},
	{"0x%08x ", &rx_pov2_ct_hdr.src, BASE_HEX_INT, REPLAY_NO},
	{"%.3lf ", &rx_pov2_ct_hdr.ts, BASE_TIMESTAMP, REPLAY_NO},
        {" %hhu ", &pov2_trial.source, BASE_CHAR, REPLAY_COMM},
        {"%hu ", &pov2_trial.trial_number, BASE_SHORT, REPLAY_COMM},
        {"%hhu ", &pov2_trial.configuration, BASE_CHAR, REPLAY_COMM},
        {"%.2f ", &pov2_trial.target_pov_speed, BASE_FLOAT, REPLAY_COMM},
        {"%.2f ", &pov2_trial.target_pov_gap, BASE_FLOAT, REPLAY_COMM},
        {"%.2f ", &pov2_trial.target_trailing_buffer, BASE_FLOAT, REPLAY_COMM},
        {"%hhu ", &pov2_trial.vehicle_state, BASE_CHAR, REPLAY_COMM},
        {"%hhu ", &pov2_trial.control_state, BASE_CHAR, REPLAY_COMM},
        {"%hhu ", &pov2_trial.alert_state, BASE_CHAR, REPLAY_COMM},
	// GPS sequence numbers, to check against those sent for timing
	{"%hu ", &sv_data.gps.sequence_no, BASE_SHORT, REPLAY_NO},
	{"%hu ", &pov1_gps.sequence_no, BASE_SHORT, REPLAY_NO},
	{"%hu ", &pov2_gps.sequence_no, BASE_SHORT, REPLAY_NO},
};

int num_qfile_columns = sizeof(comm_spec)/sizeof(data_log_column_spec_t); 

