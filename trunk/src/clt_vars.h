/*\file
 * clt_vars.h  This version was developed for the Intersection Decidion
 *              Support (IDS) project, includes variables as yet
 *		unused for CICAS project
 *
 * Copyright (c) 2005-7  Regents of the University of California
 *
 *
 *	As a convention, the variable name/type space is partitioned as
 *	follows:
 *
 *  0    to 99     Used by the system.
 *  100  to 199    Reserved.
 *  200  to 299    Permanent IDS variables.
 *  300  to 399    Additional series of permanent IDS variables.
 *  400  to 499	   Variables compatible with GM CCW
 *  500  to 599    Comm variables
 *  600  to 699	   Used by experimental control, see cicas_trial.h
 *  770 to 779     Tilcon interface variables   -- Added by Swe-Kuang Tan
 *  1000 to 1099   Temporary variables.
 */

#include "atsc_clt_vars.h"

/** TYPE definitions are given first, all VAR definitions are the
 *  same as TYPE and are given at the end.
 */

/*  Sensor and output variables
 */

#define DB_DII_OUT_TYPE             200  /* dii_out_typ */
#define DB_VEH_INPUT_SENSORS_TYPE   220  /* analog input sensors on vehicle */
#define DB_SV_DATA_TYPE		    221  /* Output from in-veh fusion */

#define DB_PED_IN_TYPE		    285  /* ped_in_typ (Jeff) */
#define DB_TAURUS_SPEED_TYPE	    286  /* taurus_speed_typ */ 


/* Eyetracker variable
 */
#define DB_EYETRACK_TYPE	301

/* Joel's variables from exp and fusion modules
 */

#define DB_FUSION_OUTPUT_TYPE	    303  /* fusion_output_typ */
#define DB_POV_SIGNAL_TYPE	    304  /* pov_signal_typ */
#define DB_FAKE_POV_TYPE	    305  /* target_typ */
#define DB_FAKE_SV_TYPE             306  /* target_typ */
#define DB_POV_D2I_TYPE	            307  /* fusion_double_typ */
#define DB_SV_D2I_TYPE	            308  /* fusion_double_typ */
#define DB_OBSERVED_BUFFER_TYPE	    309  /* fusion_double_typ */
#define DB_BUFFER_BACK_TYPE	    310  /* fusion_double_typ */
#define DB_BUFFER_FRONT_TYPE	    311  /* fusion_double_typ */
#define DB_DVI_OUT_TYPE	    	    312  /* dvi_out_typ */
#define DB_ALERT_ACTUATION_TYPE	    313  /* alert_actuation_typ */
#define DB_ALERT_PARAM1_TYPE	    314  /* alert_param1_typ */
#define DB_ALERT_PARAM2_TYPE	    315  /* alert_param2_typ */
#define DB_TRIAL_TYPE	            316  /* trial_typ */
#define DB_TRIAL_PARAM_TYPE	    317  /* trial_param_typ */
#define DB_ALERT_PARAM_TYPE	    318  /* alert_param_typ (TOO BIG)*/
#define DB_VIDEO_FLAGS_TYPE         321  /* video_flags_typ */

/** Communication variables
 */

/**
 * Use message type from cicas_msg.h to compute offsets.
 * A different DB VAR is needed for each message type to
 * track receptions in case of difficulties.
 */
#define DB_CICAS_TX_HDR_BASE_TYPE   530  /// document packet reception 
#define DB_CICAS_RX_HDR_BASE_TYPE   560  /// document packet transmission 

/** VAR definitions start here
 */

#define DB_DII_OUT_VAR              DB_DII_OUT_TYPE
#define DB_VEH_INPUT_SENSORS_VAR    DB_VEH_INPUT_SENSORS_TYPE
#define DB_SV_DATA_VAR        	    DB_SV_DATA_TYPE  

#define DB_PED_IN_VAR	DB_PED_IN_TYPE
#define DB_TAURUS_SPEED_VAR	DB_TAURUS_SPEED_TYPE
#define DB_RCV_GPS_GGA_VAR	DB_RCV_GPS_GGA_TYPE
#define DB_RCV_GPS_VTG_VAR	DB_RCV_GPS_VTG_TYPE

#define DB_EYETRACK_VAR	DB_EYETRACK_TYPE

#define DB_FUSION_OUTPUT_VAR	DB_FUSION_OUTPUT_TYPE
#define DB_POV_SIGNAL_VAR	DB_POV_SIGNAL_TYPE
#define DB_FAKE_POV_VAR	DB_FAKE_POV_TYPE
#define DB_FAKE_SV_VAR	DB_FAKE_SV_TYPE
#define DB_POV_D2I_VAR	DB_POV_D2I_TYPE
#define DB_SV_D2I_VAR	DB_SV_D2I_TYPE
#define DB_OBSERVED_BUFFER_VAR	DB_OBSERVED_BUFFER_TYPE
#define DB_BUFFER_BACK_VAR	DB_BUFFER_BACK_TYPE
#define DB_BUFFER_FRONT_VAR	DB_BUFFER_FRONT_TYPE
#define DB_DVI_OUT_VAR	DB_DVI_OUT_TYPE
#define DB_ALERT_ACTUATION_VAR	DB_ALERT_ACTUATION_TYPE
#define DB_ALERT_PARAM1_VAR	DB_ALERT_PARAM1_TYPE
#define DB_ALERT_PARAM2_VAR	DB_ALERT_PARAM2_TYPE
#define DB_TRIAL_VAR	DB_TRIAL_TYPE
#define DB_TRIAL_PARAM_VAR	DB_TRIAL_PARAM_TYPE
#define DB_ALERT_PARAM_VAR	DB_ALERT_PARAM_TYPE
#define DB_VIDEO_FLAGS_VAR	DB_VIDEO_FLAGS_TYPE

#define DB_CICAS_TX_HDR_BASE_VAR	DB_CICAS_TX_HDR_BASE_TYPE   
#define DB_CICAS_RX_HDR_BASE_VAR	DB_CICAS_RX_HDR_BASE_TYPE   
