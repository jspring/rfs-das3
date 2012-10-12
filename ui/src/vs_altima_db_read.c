/**\file
 *
 *  vs_altima_db_read.c
 *
 *  This function reads the PATH Datahub for Nissan Altima vehicle status
 *  information and converts it to formats that can be displayed in the 
 *  tilcon vehicle_status.cpp application.
 *  
 *	This header file may contain Nissan proprietary information.
 *
 */


#include <sys_os.h>
#include <sys_rt.h>

#include <db_clt.h>
#include <db_utils.h>

#include <vehicle_status.h>
#include <timestamp.h>
#include <altima.h>

#define KPH2MPH(x)	((x)*0.62137119)

tilcon_veh_status_t get_altima_vehicle_status(db_clt_typ *pclt)
{
	/** Local Variable Declarations */
	
	
	/** Return Variable Type Declaration */
	tilcon_veh_status_t veh;  // vehicle_status.h
	
	
	/** Datahub Variable Type Declarations (nt-onboard/can/altima.h) */
	alt_engine_t db_eng;
	alt_cruise_control_for_tm_t db_cc;
	alt_turn_signal_ignition_t	db_tsi;
	alt_vehicle_speed_t db_vs;
	alt_gear_indication_t db_gi;
	alt_front_wiping_brake_switch_t db_fwbs;
	
	
	/** Datahub Reads */
	db_clt_read(pclt, DB_ALT_ENG_VAR, sizeof(db_eng), &db_eng);
	db_clt_read(pclt, DB_ALT_CCFTM_VAR, sizeof(db_cc), &db_cc);
	db_clt_read(pclt, DB_ALT_TSI_VAR, sizeof(db_tsi), &db_tsi);
	db_clt_read(pclt, DB_ALT_VS_VAR, sizeof(db_vs), &db_vs);
	db_clt_read(pclt, DB_ALT_GI_VAR, sizeof(db_gi), &db_gi);
	db_clt_read(pclt, DB_ALT_FWBS_VAR, sizeof(db_fwbs), &db_fwbs);
	
	/** Process Data */
	
	// Throttle
	veh.throttle = db_eng.pct_throttle;
	if (veh.throttle > 100) {
		veh.throttle = 100;
	}
	if (veh.throttle < 0) {
		veh.throttle = 0;
	}
	
	// Cruise Control
	if (db_cc.code == 2) {
		veh.cc = 2;	// CC On
	} else { 
		veh.cc = 1;	// CC Off
	}
	
	// Ignition
	if (db_tsi.ignition == 1) {
		veh.ign = 1;	// IGN On
	} else {
		veh.ign = 2;	// IGN Off
	}
	
	// Turn Signals
	switch (db_tsi.turn_signal) {
		case 1:
			veh.left_turn_sig = 1;
			veh.right_turn_sig = 0;
			break;
		case 2:
			veh.left_turn_sig = 0;
			veh.right_turn_sig = 1;
			break;
		case 3:
			veh.left_turn_sig = 1;
			veh.right_turn_sig = 1;
			break;
		case 0:
		default:
			veh.left_turn_sig = 0;
			veh.right_turn_sig = 0;
			break;
	}
	if (db_tsi.turn_signal_filt == 3) {
		veh.hazard = 1;
	} else {
		veh.hazard = 0;
	}
		
	// Speed
	veh.speed = KPH2MPH(db_vs.vehicle_speed);
	if (veh.speed > 100) {
		veh.speed = 100;
	}
	if (veh.speed < 0) {
		veh.speed = 0;
	}
	
	
	// Brake
	if (db_fwbs.brake_switch == 1) {
		veh.brake = 2;	// Brake On
	} else {
		veh.brake = 1;	// Brake Off
	}
	
	// Gear Indicator
	switch (db_gi.code) {
		case 1:
			veh.gear = 'P';
			break;
		case 2:
			veh.gear = 'R';
			break;
		case 3:
			veh.gear = 'N';
			break;
		case 4:
			veh.gear = 'D';
			break;
		case 5:
			veh.gear = 'S';
			break;
		case 6:
			veh.gear = 'L';
			break;
		case 8:
		case 16:
		case 24:
			veh.gear = '1';
			break;
		case 9:
		case 17:
		case 25:
			veh.gear = '2';
			break;
		case 10:
		case 18:
		case 26:
			veh.gear = '3';
			break;
		case 11:
		case 19:
		case 27:
			veh.gear = '4';
			break;
		case 12:
		case 20:
		case 28:
			veh.gear = '5';
			break;
		case 13:
		case 21:
		case 29:
			veh.gear = '6';
			break;
		case 22:
			veh.gear = '7';
			break;
		case 23:
			veh.gear = '8';
			break;
		default:
			veh.gear = '?';
			break;
	}
	
	// Return
	return veh;

}

