/**\file
 *
 *  vs_audi_db_read.c
 *
 *  This function reads the PATH Datahub for Audi A3 vehicle status
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
#include <audi_can.h>

#define KPH2MPH(x)	((x)*0.62137119)

tilcon_veh_status_t get_audi_vehicle_status(db_clt_typ *pclt)
{
	/** Local Variable Declarations */
	
	
	/** Return Variable Type Declaration */
	tilcon_veh_status_t veh;  // vehicle_status.h
	
	
	/** Datahub Variable Type Declarations 
	 *
	 * (nt-onboard/can/audi/cSlap-1.0.5-i386-Release/src/audi_can.h)
	 */
	audi_t db_audi;
	
	
	/** Datahub Reads */
	db_clt_read(pclt, DB_AUDI_VAR, sizeof(db_audi), &db_audi);
	
	
	/** Process Data */
	
	// Throttle (0 to 100)
	veh.throttle = db_audi.throttle*100;
	if (veh.throttle > 100) {
		veh.throttle = 100;
	}
	if (veh.throttle < 0) {
		veh.throttle = 0;
	}
	
	// Cruise Control
	if (db_audi.cc == 1) {
		veh.cc = 2;	// CC On
	} else { 
		veh.cc = 1;	// CC Off
	}
	
	// Ignition
	if (db_audi.ignition.digin == 1) {
		veh.ign = 1;	// IGN On
	} else {
		veh.ign = 2;	// IGN Off
	}
	
	// Turn Signals
	switch (db_audi.turn_lights) {
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
	
	// Speed
	veh.speed = KPH2MPH(db_audi.veh_speed);
	if (veh.speed > 100) {
		veh.speed = 100;
	}
	if (veh.speed < 0) {
		veh.speed = 0;
	}
	
	// Brake
	if (db_audi.brake == 1) {
		veh.brake = 2;	// Brake On
	} else {
		veh.brake = 1;	// Brake Off
	}
	
	// Gear Indicator
	switch (db_audi.gear) {
		default:
			veh.gear = '?';
			break;
	}
	
	// Return
	return veh;

}

