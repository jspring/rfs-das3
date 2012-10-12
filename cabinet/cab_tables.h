/**\file
 *
 *	Tables for DB variables and column specification for logging
 *	and replay for Intersection Main Cabinet
 */	

/**  DB VARs read, declared global so that the variable addresses will
 *   be available to initialize the DB variable and column specification arrays.
 */
extern cicas_msg_hdr_t rx_sv_data_hdr;                 // sent from Taurus
extern cicas_msg_hdr_t rx_sv_ct_hdr;           // sent from Taurus
extern cicas_msg_hdr_t rx_pov1_ct_hdr;         // sent from POV1
extern cicas_msg_hdr_t rx_pov2_ct_hdr;         // sent from POV2
extern cicas_msg_hdr_t rx_sv_ct_hdr;           // sent from Taurus
extern cicas_msg_hdr_t tx_dvi_data_hdr;                // sent to Taurus
extern cicas_msg_hdr_t tx_signal_phase_hdr;            // sent to Taurus
extern cicas_msg_hdr_t tx_cab_ct_hdr;        // sent to Taurus
extern cicas_trial_t cab_trial;
extern cicas_trial_t sv_trial;
extern cicas_trial_t pov1_trial;
extern cicas_trial_t pov2_trial;
extern gpio_dig_in_t dig_in;
extern dii_out_typ dii_out;
extern dvi_out_typ dvi_out;
extern fusion_output_typ f_o;
extern fusion_double_typ buffer_back;
extern fusion_double_typ buffer_front;
extern evt300_radar_typ evt300a;
extern evt300_radar_typ evt300b;
extern path_gps_point_t sv_gps;                // sent from SV Taurus
extern path_gps_point_t cabinet_gps;           // GPS in cabinet
extern path_gps_point_t pov1_gps;
extern path_gps_point_t pov2_gps;
extern sv_data_t sv_data;
extern trial_typ trial;
extern trial_typ trial;                        // legacy for IDS demo
extern trial_param_typ trial_param;
extern traffic_signal_typ sig;
extern taurus_speed_typ taurus_speed;          // legacy for IDS demo

/**
 *      Additional variables derived from DB VAR fields that
 *      are part of the output column specification
 */
extern timestamp_t cabinet_ts;    	// cabinet HH:MM:SS.SSS
extern double seconds_since_midnight;    // cabinet UTC seconds since midnight
extern double sv_utc_seconds;            // SV UTC seconds since midnight
extern double pov1_utc_seconds;          // POV1 UTC seconds since midnight
extern double pov2_utc_seconds;          // POV2 UTC seconds since midnight
extern double seconds_since_start;       // seconds since start of run
extern unsigned char ped_warn;             //DIG_IN 1
extern unsigned char lightwave_west;       //DIG_IN 2
extern unsigned char lightwave_south;      //DIG_IN 3
extern unsigned char lightwave_east;       //DIG_IN 7 (remapped from 4)
extern unsigned char lightwave_north;      //DIG_IN 5

extern db_var_spec_t db_vars[];
extern int num_db_vars;
extern data_log_column_spec_t experiment_spec[];
extern int num_efile_columns;
extern data_log_column_spec_t comm_spec[]; 
extern int num_qfile_columns;

