/**\file
 * rdlidar.c  Reads a message from the Denso Lidar
 *                  and saves data in the database
 *                  (This is a Denso second-generation lidar)
 *
 *
 * Copyright (c) 2006   Regents of the University of California
 *
 *
 *  Process to communicate with the Denso Lidar.  This process
 *  reads the message from the lidar and puts the data into the database.
 *
 *  The signals SIGINT, SIGQUIT, and SIGTERM are trapped, and cause the
 *  process to terminate.  Upon termination log out of the database.
 *
 */


#include <sys_os.h>
#include <sys_list.h>
#include "sys_rt.h"
#include "db_clt.h"
#include "db_utils.h"
#include "densolidar.h"

#define DO_TRACE

jmp_buf env;

static void sig_hand( int sig);
static bool_typ ser_driver_read( gen_mess2_typ *pMessagebuff);

static int sig_list[] = 
{
	SIGINT,
	SIGQUIT,
	SIGTERM,
	ERROR,
};

int status;
db_clt_typ *pclt;              /* Database client pointer */
db_data_typ db_data;
gen_mess2_typ now_message;


static char CheckSum( gen_mess2_typ message)
{
	char sum = 0;
	int i;

	for( i=0; i< 145; i++)
		sum += message.data[i];
	if ( sum != message.data[145] )
	    sum = 0x00;

/* Print error if checksum is not correct */
	if (sum != message.data[145])
	{
	printf("rdlidar1 checksum error:  ");
	for(i=0; i<146; i++)
		printf("%x ",message.data[i]);
	printf("\n");
	}

	return (sum);
}

/** Possible to do all four at once by setting -o to 15, or
 *  any two, e.g, 3 for TRACE_FILE | USE_DB will both write a
 *  trace file and write the DB server.
 */
#define TRACE_FILE      1
#define USE_DB          2
#define USE_MYSQL       4
#define INIT_DB_VARS    8

static db_id_t db_vars_list[] = {
        {DB_LONG_LIDARA_VAR, sizeof( long_lidarA_typ )},
        {DB_LONG_LIDARB_VAR, sizeof( long_lidarB_typ )}

};

#define NUM_DB_VARS     sizeof(db_vars_list)/sizeof(db_id_t)


int main( int argc, char *argv[] )
{
	gen_mess2_typ    readBuff;
	char hostname[MAXHOSTNAMELEN+1];
	long_lidarA_typ long_lidarA;
	long_lidarB_typ long_lidarB;
	lidar2_mess_typ *plidar2_mess;
	struct timeb timeptr_raw;
	struct tm time_converted;
	int option;
        int output_mask = 0;    // 1 trace, 2 DB server, 4 MySQL
        char verbose = 0;

	while ((option = getopt(argc, argv, "o:hv")) != EOF) {
		switch(option) {
        		case 'o':
               		        output_mask = atoi(optarg);     
		                break;
        		case 'v':
               		        verbose = 1;     
		                break;
			case 'h':
			default:
				printf("Usage: %s [OPTIONS] < serial device\n",argv[0]);
				printf("OPTIONS:\t-v verbose\n\t\t-o output mask (1=trace,2=DB,4=MySQL,8=init DB vars)\n");
				exit(EXIT_FAILURE);
				break;
			}
		}
        if (output_mask & USE_DB) {
                get_local_name(hostname, MAXHOSTNAMELEN);
                if (output_mask & INIT_DB_VARS) {
                        if ((pclt = db_list_init(argv[0], hostname, DEFAULT_SERVICE, 
                                COMM_OS_XPORT, db_vars_list, NUM_DB_VARS, NULL, 0)) 
                                == NULL) {
                                exit(EXIT_FAILURE);
                                }
                            }
                else {
                        if ((pclt = db_list_init(argv[0], hostname, DEFAULT_SERVICE, 
                                COMM_OS_XPORT, NULL, 0, NULL, 0)) == NULL) {
                                exit(EXIT_FAILURE);
                                }
                        }
                }

	/*	set jmp */
	if ( setjmp(env) != 0)
	    {
	    /* Log out from the database. */
	    if (pclt != NULL)
	        clt_logout( pclt );

		exit( EXIT_SUCCESS);
	}
	else 
		sig_ign( sig_list, sig_hand);

	for (;;)
	    {

	    if ( ser_driver_read ( &readBuff ))
	        {
	        /* Get time of day and save in the database. */
	        ftime ( &timeptr_raw );
#ifdef __QNXNTO__
	        _localtime ( &timeptr_raw.time, &time_converted );
#else
			localtime_r ( &timeptr_raw.time, &time_converted );
#endif	
		long_lidarA.hour = time_converted.tm_hour;
	        long_lidarA.min = time_converted.tm_min;
	        long_lidarA.sec = time_converted.tm_sec;
	        long_lidarA.millisec = timeptr_raw.millitm;
			
			/* Move data from message into database.  */
	        plidar2_mess = (lidar2_mess_typ *) &readBuff;
	        long_lidarA.h_latpos_1 = plidar2_mess->h_latpos_1;
	        long_lidarA.l_latpos_1 = plidar2_mess->l_latpos_1;
	        long_lidarA.vert_pos_1 = plidar2_mess->vert_pos_1;
	        long_lidarA.h_dist_1 = plidar2_mess->h_dist_1;
	        long_lidarA.l_dist_1 = plidar2_mess->l_dist_1;
	        long_lidarA.lanerate_1 = plidar2_mess->lanerate_1;
	        long_lidarA.veh_rate_1 = plidar2_mess->veh_rate_1;
	        long_lidarA.targ_stat_1 = plidar2_mess->targ_stat_1;
	        long_lidarA.lat_vel_1 = plidar2_mess->lat_vel_1;
	        long_lidarA.h_velocity_1 = plidar2_mess->h_velocity_1;
	        long_lidarA.l_velocity_1 = plidar2_mess->l_velocity_1;
	        long_lidarA.h_width_1 = plidar2_mess->h_width_1;
	        long_lidarA.l_width_1 = plidar2_mess->l_width_1;
	        long_lidarA.height_1 = plidar2_mess->height_1;
	        long_lidarA.h_depth_1 = plidar2_mess->h_depth_1;
	        long_lidarA.l_depth_1 = plidar2_mess->l_depth_1;
	        long_lidarA.rel_acc_1 = plidar2_mess->rel_acc_1;
	        long_lidarA.h_latpos_2 = plidar2_mess->h_latpos_2;
	        long_lidarA.l_latpos_2 = plidar2_mess->l_latpos_2;
	        long_lidarA.vert_pos_2 = plidar2_mess->vert_pos_2;
	        long_lidarA.h_dist_2 = plidar2_mess->h_dist_2;
	        long_lidarA.l_dist_2 = plidar2_mess->l_dist_2;
	        long_lidarA.lanerate_2 = plidar2_mess->lanerate_2;
	        long_lidarA.veh_rate_2 = plidar2_mess->veh_rate_2;
	        long_lidarA.targ_stat_2 = plidar2_mess->targ_stat_2;
	        long_lidarA.lat_vel_2 = plidar2_mess->lat_vel_2;
	        long_lidarA.h_velocity_2 = plidar2_mess->h_velocity_2;
	        long_lidarA.l_velocity_2 = plidar2_mess->l_velocity_2;
	        long_lidarA.h_width_2 = plidar2_mess->h_width_2;
	        long_lidarA.l_width_2 = plidar2_mess->l_width_2;
	        long_lidarA.height_2 = plidar2_mess->height_2;
	        long_lidarA.h_depth_2 = plidar2_mess->h_depth_2;
	        long_lidarA.l_depth_2 = plidar2_mess->l_depth_2;
	        long_lidarA.rel_acc_2 = plidar2_mess->rel_acc_2;

	        long_lidarA.h_latpos_3 = plidar2_mess->h_latpos_3;
	        long_lidarA.l_latpos_3 = plidar2_mess->l_latpos_3;
	        long_lidarA.vert_pos_3 = plidar2_mess->vert_pos_3;
	        long_lidarA.h_dist_3 = plidar2_mess->h_dist_3;
	        long_lidarA.l_dist_3 = plidar2_mess->l_dist_3;
	        long_lidarA.lanerate_3 = plidar2_mess->lanerate_3;
	        long_lidarA.veh_rate_3 = plidar2_mess->veh_rate_3;
	        long_lidarA.targ_stat_3 = plidar2_mess->targ_stat_3;
	        long_lidarA.lat_vel_3 = plidar2_mess->lat_vel_3;
	        long_lidarA.h_velocity_3 = plidar2_mess->h_velocity_3;
	        long_lidarA.l_velocity_3 = plidar2_mess->l_velocity_3;
	        long_lidarA.h_width_3 = plidar2_mess->h_width_3;
	        long_lidarA.l_width_3 = plidar2_mess->l_width_3;
	        long_lidarA.height_3 = plidar2_mess->height_3;
	        long_lidarA.h_depth_3 = plidar2_mess->h_depth_3;
	        long_lidarA.l_depth_3 = plidar2_mess->l_depth_3;
	        long_lidarA.rel_acc_3 = plidar2_mess->rel_acc_3;

	        long_lidarA.h_latpos_4 = plidar2_mess->h_latpos_4;
	        long_lidarA.l_latpos_4 = plidar2_mess->l_latpos_4;
	        long_lidarA.vert_pos_4 = plidar2_mess->vert_pos_4;
	        long_lidarA.h_dist_4 = plidar2_mess->h_dist_4;
	        long_lidarA.l_dist_4 = plidar2_mess->l_dist_4;
	        long_lidarA.lanerate_4 = plidar2_mess->lanerate_4;
	        long_lidarA.veh_rate_4 = plidar2_mess->veh_rate_4;
	        long_lidarA.targ_stat_4 = plidar2_mess->targ_stat_4;
	        long_lidarA.lat_vel_4 = plidar2_mess->lat_vel_4;
	        long_lidarA.h_velocity_4 = plidar2_mess->h_velocity_4;
	        long_lidarA.l_velocity_4 = plidar2_mess->l_velocity_4;
	        long_lidarA.h_width_4 = plidar2_mess->h_width_4;
	        long_lidarA.l_width_4 = plidar2_mess->l_width_4;
	        long_lidarA.height_4 = plidar2_mess->height_4;
	        long_lidarA.h_depth_4 = plidar2_mess->h_depth_4;
	        long_lidarA.l_depth_4 = plidar2_mess->l_depth_4;
	        long_lidarA.rel_acc_4 = plidar2_mess->rel_acc_4;

	        long_lidarB.h_latpos_5 = plidar2_mess->h_latpos_5;
	        long_lidarB.l_latpos_5 = plidar2_mess->l_latpos_5;
	        long_lidarB.vert_pos_5 = plidar2_mess->vert_pos_5;
	        long_lidarB.h_dist_5 = plidar2_mess->h_dist_5;
	        long_lidarB.l_dist_5 = plidar2_mess->l_dist_5;
	        long_lidarB.lanerate_5 = plidar2_mess->lanerate_5;
	        long_lidarB.veh_rate_5 = plidar2_mess->veh_rate_5;
	        long_lidarB.targ_stat_5 = plidar2_mess->targ_stat_5;
	        long_lidarB.lat_vel_5 = plidar2_mess->lat_vel_5;
	        long_lidarB.h_velocity_5 = plidar2_mess->h_velocity_5;
	        long_lidarB.l_velocity_5 = plidar2_mess->l_velocity_5;
	        long_lidarB.h_width_5 = plidar2_mess->h_width_5;
	        long_lidarB.l_width_5 = plidar2_mess->l_width_5;
	        long_lidarB.height_5 = plidar2_mess->height_5;
	        long_lidarB.h_depth_5 = plidar2_mess->h_depth_5;
	        long_lidarB.l_depth_5 = plidar2_mess->l_depth_5;
	        long_lidarB.rel_acc_5 = plidar2_mess->rel_acc_5;

	        long_lidarB.h_latpos_6 = plidar2_mess->h_latpos_6;
	        long_lidarB.l_latpos_6 = plidar2_mess->l_latpos_6;
	        long_lidarB.vert_pos_6 = plidar2_mess->vert_pos_6;
	        long_lidarB.h_dist_6 = plidar2_mess->h_dist_6;
	        long_lidarB.l_dist_6 = plidar2_mess->l_dist_6;
	        long_lidarB.lanerate_6 = plidar2_mess->lanerate_6;
	        long_lidarB.veh_rate_6 = plidar2_mess->veh_rate_6;
	        long_lidarB.targ_stat_6 = plidar2_mess->targ_stat_6;
	        long_lidarB.lat_vel_6 = plidar2_mess->lat_vel_6;
	        long_lidarB.h_velocity_6 = plidar2_mess->h_velocity_6;
	        long_lidarB.l_velocity_6 = plidar2_mess->l_velocity_6;
	        long_lidarB.h_width_6 = plidar2_mess->h_width_6;
	        long_lidarB.l_width_6 = plidar2_mess->l_width_6;
	        long_lidarB.height_6 = plidar2_mess->height_6;
	        long_lidarB.h_depth_6 = plidar2_mess->h_depth_6;
	        long_lidarB.l_depth_6 = plidar2_mess->l_depth_6;
	        long_lidarB.rel_acc_6 = plidar2_mess->rel_acc_6;

	        long_lidarB.h_latpos_7 = plidar2_mess->h_latpos_7;
	        long_lidarB.l_latpos_7 = plidar2_mess->l_latpos_7;
	        long_lidarB.vert_pos_7 = plidar2_mess->vert_pos_7;
	        long_lidarB.h_dist_7 = plidar2_mess->h_dist_7;
	        long_lidarB.l_dist_7 = plidar2_mess->l_dist_7;
	        long_lidarB.lanerate_7 = plidar2_mess->lanerate_7;
	        long_lidarB.veh_rate_7 = plidar2_mess->veh_rate_7;
	        long_lidarB.targ_stat_7 = plidar2_mess->targ_stat_7;
	        long_lidarB.lat_vel_7 = plidar2_mess->lat_vel_7;
	        long_lidarB.h_velocity_7 = plidar2_mess->h_velocity_7;
	        long_lidarB.l_velocity_7 = plidar2_mess->l_velocity_7;
	        long_lidarB.h_width_7 = plidar2_mess->h_width_7;
	        long_lidarB.l_width_7 = plidar2_mess->l_width_7;
	        long_lidarB.height_7 = plidar2_mess->height_7;
	        long_lidarB.h_depth_7 = plidar2_mess->h_depth_7;
	        long_lidarB.l_depth_7 = plidar2_mess->l_depth_7;
	        long_lidarB.rel_acc_7 = plidar2_mess->rel_acc_7;

	        long_lidarB.h_latpos_8 = plidar2_mess->h_latpos_8;
	        long_lidarB.l_latpos_8 = plidar2_mess->l_latpos_8;
	        long_lidarB.vert_pos_8 = plidar2_mess->vert_pos_8;
	        long_lidarB.h_dist_8 = plidar2_mess->h_dist_8;
	        long_lidarB.l_dist_8 = plidar2_mess->l_dist_8;
	        long_lidarB.lanerate_8 = plidar2_mess->lanerate_8;
	        long_lidarB.veh_rate_8 = plidar2_mess->veh_rate_8;
	        long_lidarB.targ_stat_8 = plidar2_mess->targ_stat_8;
	        long_lidarB.lat_vel_8 = plidar2_mess->lat_vel_8;
	        long_lidarB.h_velocity_8 = plidar2_mess->h_velocity_8;
	        long_lidarB.l_velocity_8 = plidar2_mess->l_velocity_8;
	        long_lidarB.h_width_8 = plidar2_mess->h_width_8;
	        long_lidarB.l_width_8 = plidar2_mess->l_width_8;
	        long_lidarB.height_8 = plidar2_mess->height_8;
	        long_lidarB.h_depth_8 = plidar2_mess->h_depth_8;
	        long_lidarB.l_depth_8 = plidar2_mess->l_depth_8;
	        long_lidarB.rel_acc_8 = plidar2_mess->rel_acc_8;

	        long_lidarB.curve_h = plidar2_mess->curve_h;
	        long_lidarB.curve_l = plidar2_mess->curve_l;
		if(verbose)
		   printf("%f %f %f %f %f %f %f %f %#0x %#0x %#0x %#0x %#0x %#0x %#0x %#0x\n",
			((long_lidarA.h_dist_1 << 8) | long_lidarA.l_dist_1)*0.005,
			((long_lidarA.h_dist_2 << 8) | long_lidarA.l_dist_2)*0.005,
			((long_lidarA.h_dist_3 << 8) | long_lidarA.l_dist_3)*0.005,
			((long_lidarA.h_dist_4 << 8) | long_lidarA.l_dist_4)*0.005,
			((long_lidarB.h_dist_5 << 8) | long_lidarB.l_dist_5)*0.005,
			((long_lidarB.h_dist_6 << 8) | long_lidarB.l_dist_6)*0.005,
			((long_lidarB.h_dist_7 << 8) | long_lidarB.l_dist_7)*0.005,
			((long_lidarB.h_dist_8 << 8) | long_lidarB.l_dist_8)*0.005,
			long_lidarA.h_dist_1,
			long_lidarA.h_dist_2,
			long_lidarA.h_dist_3,
			long_lidarA.h_dist_4,
			long_lidarB.h_dist_5,
			long_lidarB.h_dist_6,
			long_lidarB.h_dist_7,
			long_lidarB.h_dist_8
			);


		if (output_mask & USE_DB) {
			if( clt_update( pclt, DB_LONG_LIDARA_VAR,
				DB_LONG_LIDARA_TYPE, sizeof( long_lidarA_typ ),
				(void *) &long_lidarA ) == FALSE )
				fprintf( stderr, "clt_update( DB_LONG_LIDARA_VAR )\n" );
			if( clt_update( pclt, DB_LONG_LIDARB_VAR,
				DB_LONG_LIDARB_TYPE, sizeof( long_lidarB_typ ),
				(void *) &long_lidarB ) == FALSE )
				fprintf( stderr, "clt_update( DB_LONG_LIDARB_VAR )\n" );
			}
		}
	    }
}

static bool_typ ser_driver_read( gen_mess2_typ *pMessagebuff) 
{
unsigned char msgbuf [150];
int i;
unsigned char csum;

	/* Read from serial port. */
	/* Blocking read is used, so control doesn't return unless data is
	 * available.  Keep reading until the beginning of a message is 
	 * determined by reading the two start of message bytes 0xff, and 0xff,
	 * followed by the function code 0xfd.  */
	memset( msgbuf, 0x0, 150 );

	while ( !( msgbuf[0] == 0xff) || !(msgbuf[1] == 0xff ) ||
	       !( msgbuf[2] == 0xfd) )
	    {
	    msgbuf[0] = msgbuf[1];
	    msgbuf[1] = msgbuf[2];
	    read ( STDIN_FILENO, &msgbuf[2], 1);
//printf("%x\n",msgbuf[2]);
//printf("%x %x %x\n",msgbuf[0],msgbuf[1],msgbuf[2]);
	    }

	/* Header found, now read remainder of message. */
	for ( i=3; i<146; i++ )
	    read ( STDIN_FILENO, &msgbuf[i], 1);

	memcpy( pMessagebuff->data, &msgbuf[0], 146);

	csum = CheckSum( *pMessagebuff );
	if( csum != msgbuf[145])
	    {
#ifdef DO_TRACE
	    printf( "Checksum error, lidar #1.\n" );
#endif
	    return (FALSE);
	    }
	else
	    {
	    return (TRUE);
	    }
}

static void sig_hand( int sig)
{
	longjmp( env, 1);
}
