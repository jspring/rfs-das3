/**\file
 *
 * can_tx.c
 *
 * Periodically sends a message to the specified CAN port. 
 * Messages have ID sent from the command line and data that
 * is just an incrementing integer.
 *
 * For SSV_CAN or ECAN, sample usage:
 *
 * can_tx -p /dev/can1 -i <integer id>  -t <seconds (flost)>
 *	  -e (if uses extended frames) -v debugging information
 *
 * For Steinhoff driver, sample usage:
 *
 * can_tx -p 1 -i <integer id>  -t <seconds (flost)>
 *	  -e (if uses extended frames) -v debugging information
 *
 * Code is built with different libraries to match the kind of
 * CAN card on the system. You must change the Makefile flags
 * for this to happen. 
 */

#include <db_include.h>
#include <sys_os.h>
#include "db_clt.h"
#include "sys_rt.h"
#include "timestamp.h"
#include "can_defs.h"
#include "can_client.h"
#include "can_dbvars.h"

/** global definitions for signal handling */
static int sig_list[] =
{
        SIGINT,
        SIGQUIT,
        SIGTERM,
        SIGALRM,
        ERROR,
};

static jmp_buf exit_env;

static void sig_hand(int code)
{
        if (code == SIGALRM)
                return;
        else
                longjmp(exit_env, code);
}

static db_id_t db_steinhoff_vars_list[] = {
        {DB_STEINHOFF_OUT_VAR, sizeof(db_steinhoff_out_t)},
};
#define NUM_STEINHOFF_VARS (sizeof(db_steinhoff_vars_list)/sizeof(db_id_t))

int main(int argc, char **argv)
{

	char hostname[MAXHOSTNAMELEN];
	char *domain = DEFAULT_SERVICE; /// on Linux sets DB q-file directory
	db_clt_typ *pclt;               /// data server client pointer
	int xport = COMM_OS_XPORT;      /// value set correctly in sys_os.h

	float secs = 1.0;
	unsigned long id = 0;  
	unsigned char extended = 0;
	unsigned char data[20];	
	long count=0;
	int fd_brake;
	int fd_accel;
	char *port_brake = "2";
	char *port_accel = "1";
	db_steinhoff_out_t db_steinhoff_out;  
	int opt;
	int verbose = 0;	// by default silent
	int nmax = 0; // if zero, run forever
	int millisecs = 1000;	// timer interval is in milliseconds
	int repetitions = 1;
	posix_timer_typ *ptmr;	
	int i;
	int use_db = 1;
	int create_db_vars = 0;
	float Acceleration = 0; //+ for acceleration, 0x98 message; - for deceleration/braking, 0x99 message
        while ((opt = getopt(argc, argv, "A:a:b:e:i:n:t:vc")) != -1) {
		switch (opt) {
			case 'A':
				Acceleration = atof(optarg);
				break;
			case 'e':
				extended = 1;
				break;
			case 'a':
				port_accel = strdup(optarg);
				break;
			case 'b':
				port_brake = strdup(optarg);
				break;
			case 'i':
				id = atoi(optarg);
				break;
			case 'n':
				nmax = atoi(optarg);
				break;
			case 't':
				secs = atof(optarg);
				millisecs = secs*1000.0;
				if (millisecs < 1) {
					millisecs = 1;
					repetitions = (1.0/(secs * 1000.0) + 0.5);
				} else {
					millisecs = secs * 1000.0 + 0.5;
				}
			   break;
			case 'v':
				verbose = 1;
				break;
			case 'c':
				create_db_vars = 1;
				break;
			case 'd':
				use_db = 0;
				break;
			default:
				printf("Usage: %s -p <port> ", argv[0]);
				printf("-i <ID> -t <seconds> -e <extended frames>\n");
				printf("example: %s -p /dev/can -i 1000 -t 0.1\n",
						argv[0]);
				exit(1);
                }
        }
        if(Acceleration != 0.0) {
        	use_db = 0;
        	create_db_vars = 0;
        }
	fd_accel = can_open(port_accel,O_WRONLY);
	fd_brake = can_open(port_brake,O_WRONLY);

	if(fd_accel == -1) {
		printf("error opening accel port %s\n", port_accel);
		exit(EXIT_FAILURE);
	} else {
		printf("program %s, device name %s, fd_accel : %d, extended %hhd\n",
			argv[0], port_accel, fd_accel, extended);
		printf("interval %d ms, %d repetitions\n",
			 millisecs, repetitions);
		fflush(stdout);
	}

	if(fd_brake == -1) {
		printf("error opening brake port %s\n", port_brake);
		exit(EXIT_FAILURE);
	} else {
		printf("program %s, device name %s, fd: %d, extended %hhd\n",
			argv[0], port_brake, fd_brake, extended);
		printf("interval %d ms, %d repetitions\n",
			 millisecs, repetitions);
		fflush(stdout);
	}
        if(use_db != 0){
                get_local_name(hostname, MAXHOSTNAMELEN);
                if(create_db_vars) {
                        if ( (pclt = db_list_init(argv[0], hostname, domain, xport,
                                db_steinhoff_vars_list, NUM_STEINHOFF_VARS, NULL, 0))
                                == NULL) {
                                        exit(EXIT_FAILURE);
                        }
                }
                else {
                        if ( (pclt = db_list_init(argv[0], hostname, domain, xport,
                                NULL, 0, NULL, 0))
                                == NULL) {
                                        exit(EXIT_FAILURE);
                        }

                }
        }

	// second parameter of timer_init is no longer used
	if ((ptmr = timer_init(millisecs, 0))== NULL) {
                printf("timer_init failed in %s.\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        /* exit code on receiving signal */
        if (setjmp(exit_env) != 0) {
                if(create_db_vars != 0)
                        db_list_done(pclt, db_steinhoff_vars_list, NUM_STEINHOFF_VARS, NULL, 0);
                else
                if(use_db != 0)
                        db_list_done(pclt, NULL, 0, NULL, 0);

		fprintf(stderr, "%s exiting, send count %ld\n",
			argv[0], count);
		fflush(stdout);
		exit(EXIT_SUCCESS);
        } else
                sig_ign(sig_list, sig_hand);
        //Send 0 to enable control
		id = 0x99;
		extended = 0;
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		data[3] = 0;
		data[4] = 0;
		data[5] = 0;
		can_write(fd_brake, 0x98, 0, data, 6);

	for(;;) {
		if(use_db)
			db_clt_read(pclt, DB_STEINHOFF_OUT_VAR, sizeof(db_steinhoff_out_t), &db_steinhoff_out);
		if(db_steinhoff_out.port == BRAKE_PORT){
			can_write(fd_brake, db_steinhoff_out.id, 0, db_steinhoff_out.data, db_steinhoff_out.size);
		}
		else
			if(db_steinhoff_out.port == ACCEL_PORT)
				can_write(fd_accel, db_steinhoff_out.id, 0, db_steinhoff_out.data, db_steinhoff_out.size);
		if (verbose) { 
			timestamp_t ts;
			get_current_timestamp(&ts);
			print_timestamp(stdout, &ts);
			printf(" %ld ", db_steinhoff_out.id);
			for (i = 0; i < db_steinhoff_out.size; i++)
				printf("%hhx ", db_steinhoff_out.data[i]);
			printf("\n");
			fflush(stdout);
		}
		
		if(count>nmax && nmax!=0)
			longjmp(exit_env, 2);

		TIMER_WAIT(ptmr);
		
	}

	return 0;

}



