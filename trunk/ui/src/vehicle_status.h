/**\file
 *
 *  vehicle_status.h
 *
 *  Created by Christopher Nowakowski on 6/15/10.
 *  Copyright 2010 California PATH, UC Berkeley. All rights reserved.
 *
 *	Structure and constant definitions for the Tilcon vehicle_status.c app
 *
 */


#include <db_clt.h>
#include <tilcon_utils.h>

// Vehicle Dependent Data Formatted for Widget Display
typedef struct {
	double throttle;		// 0 to 100%
	unsigned char cc;		// 0 UNK | 1 Off | 2 On
	unsigned char ign;		// 0 UNK | 1 On  | 2 Off
	unsigned char left_turn_sig;	// 0 Off | 1 On
	unsigned char right_turn_sig;	// 0 Off | 1 On
	double speed;			// mph
	char gear;			// 1 Character to Display
	unsigned char brake;		// 0 UNK | 1 Off | 2 On
} tilcon_veh_status_t;


/** Vehicle Function Declarations */
extern tilcon_veh_status_t get_altima_vehicle_status(db_clt_typ *pclt);
extern tilcon_veh_status_t get_audi_vehicle_status(db_clt_typ *pclt);
