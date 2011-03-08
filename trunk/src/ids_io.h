/* \file
 *      ids_io.h    Version for the CICAS project.
 *
 *	Copyright (c) 2003-9   Regents of the University of California
 *
 *	Updated to remove obsolete data types. -- Sue
 *
 *
 */
#ifndef __IDS_IO_H__
#define __IDS_IO_H__

typedef struct
{
	int state;                
} IS_PACKED  display_typ;

/**
 *	The DII is the Driver Infrastructure Information sign,
 *	which shows a "no left turn" symbol that is lighted
 *	and pulsed when the sign receives a digital I/O signal.
 */
typedef struct
{
	int dii_flag;                /* Bits to send to DII */
} IS_PACKED dii_out_typ;


typedef struct {
	float speed1;
	float speed2;
	short lowword;
	short highword;
} IS_PACKED taurus_speed_typ;

/** Used for data from SV to cabinet
 */
typedef struct {
        path_gps_point_t gps;
        double revised_lat;
        double revised_long;
        double revised_heading;
        double speed;
        char right_turn_signal;
        char left_turn_signal;
        char brakes;
} IS_PACKED sv_data_t;

/** Used for data from cabinet to SV
 */
typedef struct {
        fusion_output_typ fusion;
        trial_typ trial;
} IS_PACKED dvi_data_t;

/* Used for pedestrian warning
 */
typedef struct
{
        int state;                /* On (1) or Off (0) */
} IS_PACKED ped_in_typ;

#endif
