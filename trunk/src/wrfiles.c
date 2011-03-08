/**\file
 * wrfiles_skel.c    Skeleton File to save the data from the sensors
 *              for the CICAS intersection experiments:
 *              Default time for saving data is
 *              every 75 msec.  
 *
 *              Every so often (according to a switch received in
 *              the startup line) the files will be closed and a new
 *              set of files opened.
 *
 *		This code has been extensivley rewritten (Sue, May 2009)
 *		to make	it easier to add and delete DB VARs and columns,
 *		and to allow data to be saved in memory between
 *		file writes if desired, instead of writing a line
 *		at a time. Specification for files that show data
 *		from many different DB VARs are now in cab_tables.c		
 *
 *
 *  Usage: wrfiles -d DOMAIN -t INTERVAL -m MINUTES -l LINES_TO_SAVE
 *
 *  where DOMAIN is the name of the database domain,
 *  INTERVAL is the number of milliseconds between data saves,
 *  MINUTES is the number of minutes before closing a file
 *  and opening a new one.
 *  LINES_TO_SAVE is the maximum number of output lines that can
 *	be saved when saving data in memory rather than writing
 *	a line at a time.
 *
 *
 * Copyright (c) 2010-2019   Regents of the University of California
 *
 *
 */

/*

Want to have a skeleton wrfiles that 
	1. Logs into the database
	2. Starts ptimer
	3. Opens data log files (from a list or array?)
	4. Initializes buffers for memory writing of data, if that's selected
	5. Sets up setjmp exit block

In the infinite while loop, the following tasks are performed:
	6. get_current_timestamp
	7. Write data to file(s)
	8. Check for expiration of file time, and
		a. Close current files and reopen new ones
		b. Signal video collection program to close its file and open
			another one

*/
#include "wrfiles_lib.h"
#include <db_utils.h>
#include <path_gps_lib.h>
#include <sys_ini.h>
#include "clt_vars.h"
#include "alert_vars.h"
#include "expctl_vars.h"
#include "ids_io.h"
#include "gpio.h"
#include "cicas_trial.h"
#include "cicas_msg.h"
#include "cab_tables.h"
#include "altima_tables.h"

int sig_list[] = 
{
	SIGINT,
	SIGQUIT,
	SIGTERM,
	SIGALRM,
	ERROR,
};

jmp_buf exit_env;

void sig_hand(int code)
{
	if (code == SIGALRM)
		return;
	else
		longjmp(exit_env, code);
}

/**
 *	File pointers used for each file saved.
 */
FILE *f_evt300A = NULL;
FILE *f_evt300B = NULL;
FILE *f_sms = NULL;
FILE *f_comm = NULL;
FILE *f_experiment = NULL;
buff_typ *pbuff_evt300A;
buff_typ *pbuff_evt300B;
buff_typ *pbuff_sms;
buff_typ *pbuff_comm;
buff_typ *pbuff_experiment;

void do_buff_inits(int lines_to_save,
                int do_evt300, int do_experiment, 
		int do_comm, int do_sms,
                buff_typ **ppbuff_evt300A, buff_typ **ppbuff_evt300B,
                buff_typ **ppbuff_experiment, buff_typ **ppbuff_comm,
		buff_typ **ppbuff_sms)
{
        if (do_evt300) {
                *ppbuff_evt300A = buff_init(f_evt300A, lines_to_save);
                *ppbuff_evt300B = buff_init(f_evt300B, lines_to_save);
        }
        if (do_experiment)
                *ppbuff_experiment = buff_init(f_experiment, lines_to_save);
        if (do_comm)
                *ppbuff_comm = buff_init(f_comm, lines_to_save);
        if (do_sms)
                *ppbuff_sms = buff_init(f_sms, lines_to_save);
}
 
int main(int argc, char *argv[])
{
	int option;
	double start_time;
	db_clt_typ *pclt;
	char hostname[MAXHOSTNAMELEN+1];
	int old_fileday = 99;	/// originally set to bad value to force search
	int serial_num;		/// set in open_data_log	
	char id_string[80];

	timestamp_t timestamp;	/// hour,min,sec, millisec for data save 
	int file_time = 15;     /// Number of minutes to record to a file 
	int interval = 75;	/// Number of milliseconds between saves 
	int lines_to_save = 100000;	/// when using memory; about 2 hours
	posix_timer_typ *ptimer;       /* Timing proxy */
	char *domain = DEFAULT_SERVICE; // usually no need to change this 
	int xport = COMM_OS_XPORT;	// set correct for OS in sys_os.h 
	bool_typ do_evt300;
	bool_typ do_sms;
	bool_typ do_comm;
	bool_typ do_experiment;
	bool_typ use_memory;
	bool_typ use_audi_spec;
	bool_typ use_altima_spec;
	FILE *first_file;
	char *first_file_str;
	char *ini_file = "wrfiles.ini";
	FILE *pfin1 = NULL;
	char *config_file_section;
	int i;

	/* Read and interpret any user switches. */
	while ((option = getopt(argc, argv, "d:c:x:el:m:qrst:")) != EOF) {
		switch(option) {
		case 'd':
			domain = strdup(optarg);
		case 'c':
			ini_file = strdup(optarg);
		case 'x':
			config_file_section = strdup(optarg);
	        case 'e':
			do_experiment = FALSE; 
			break;
	        case 'l':
			lines_to_save = atoi(optarg);
			break;
	        case 'm':
			file_time = atoi(optarg);
			break;
	        case 'q':
			do_comm = FALSE; 
			break;
	        case 'r':
			do_evt300 = FALSE; 
			break;
	        case 's':
			do_sms = FALSE; 
			break;
	        case 't':
			interval = atoi(optarg); 
			break;
	        case 'u':
			use_memory = TRUE; 
			break;
	        default:
			printf("Invalid switch in wrfiles.\n");
			exit(EXIT_FAILURE);
	        }
	}

        /* Read from CommandTestType section */
        if ((pfin1 = get_ini_section(ini_file, config_file_section)) == NULL)
            {
                printf("LONG_TRK.C:Cannot get ini file %s, section %s\n",
                   ini_file, config_file_section);
                fflush(stdout);
                return 0;
            }


    do_sms = (unsigned char)get_ini_bool(pfin1, "DoSMS", FALSE);
    do_evt300 = (unsigned char)get_ini_bool(pfin1, "DoEVT300", FALSE);
    do_comm = (unsigned char)get_ini_bool(pfin1, "DoComm", FALSE);
    do_experiment = (unsigned char)get_ini_bool(pfin1, "DoExperiment", FALSE);
    use_memory = (unsigned char)get_ini_bool(pfin1, "UseMemory", FALSE);
    use_audi_spec = (unsigned char)get_ini_bool(pfin1, "UseAudiSpec", FALSE);
    use_altima_spec = (unsigned char)get_ini_bool(pfin1, "UseAltimaSpec", FALSE);
//    config.max_spd=(float)get_ini_double(pfin1, "MaxSpeed", 15.0 );
//    config.static_run = get_ini_bool( pfin1, "StaticRun", FALSE );

	printf("%s:  do_comm %d do_experiment %d ",
		 argv[0],do_comm,do_experiment);
	printf(" do_sms %d do_evt300 %d \n",
		do_sms, do_evt300);

	/* Log in to the database (shared global memory).  Default to the
	 * the current host. Assumes other processes that create variables
	 * are already running, since list is NULL.
	 */
	get_local_name(hostname, MAXHOSTNAMELEN);
	if ((pclt = db_list_init(argv[0], hostname, domain, xport, 
			NULL, 0, NULL, 0)) == NULL) {
		printf("Database initialization error in %s.\n", argv[0]);
		exit(EXIT_FAILURE);
	}
        
	/* Setup a timer for every 'interval' msec. */
	if ((ptimer = timer_init(interval, DB_CHANNEL(pclt) )) == NULL) {
		printf("Unable to initialize wrfiles timer\n");
		exit(EXIT_FAILURE);
	}
       /* Open a set of files for recording data. Set up value of "firstfile"
	 * that will be used to handle timestamp and name set-up handling on
	 * reopens
	 */
        if (do_evt300) {
                open_data_log(&f_evt300A, "/big/data/xa", ".dat",
                         &start_time, &old_fileday, &serial_num, id_string);
                first_file = f_evt300A;
                first_file_str = "/big/data/xa";
                open_another_file(&f_evt300B, "/big/data/xb", id_string, ".dat");
        }
        if (do_experiment) {
                if (first_file == NULL) {
                        open_data_log(&f_experiment, "/big/data/xe", ".dat",
                         &start_time, &old_fileday, &serial_num, id_string);
                        first_file = f_experiment;
                        first_file_str = "/big/data/xe";
                } else {
                        open_another_file(&f_experiment, "/big/data/xe",
                                  id_string, ".dat");
                }
        }
        if (do_comm) {
                if (first_file == NULL) {
                        open_data_log(&f_comm, "/big/data/xq", ".dat",
                         &start_time, &old_fileday, &serial_num, id_string);
                        first_file = f_comm;
                        first_file_str = "/big/data/xq";
                } else {
                        open_another_file(&f_comm, "/big/data/xq",
                                  id_string, ".dat");
                }
        }
        if (do_sms) {
                if (first_file == NULL) {
                        open_data_log(&f_sms, "/big/data/xs", ".dat",
                         &start_time, &old_fileday, &serial_num, id_string);
                        first_file = f_sms;
                        first_file_str = "/big/data/xs";
                } else {
                        open_another_file(&f_sms, "/big/data/xs",
                                  id_string, ".dat");
                }
        }
        if (use_memory)
                do_buff_inits(lines_to_save, do_evt300, do_experiment,
			do_comm, do_sms,
                        &pbuff_evt300A, &pbuff_evt300B,
                        &pbuff_experiment, &pbuff_comm, &pbuff_sms);

	    

	if(setjmp(exit_env) != 0) {
		if (use_memory) {
			if (do_evt300) {
				buff_done(pbuff_evt300A);
				buff_done(pbuff_evt300B);
			}
			if (do_experiment)
				buff_done(pbuff_experiment);
			if (do_comm)
				buff_done(pbuff_comm);
			if (do_sms)
				buff_done(pbuff_sms);
		}
		if (f_evt300A)
			fclose(f_evt300A);
		if (f_evt300A)
			fclose(f_evt300B);
		if (f_experiment)
			fclose(f_experiment);
		if (f_comm)
			fclose(f_comm);
		if (f_sms)
			fclose(f_sms);
		db_list_done(pclt, NULL, 0, NULL, 0);
		exit(EXIT_SUCCESS);
	} else
		sig_ign(sig_list, sig_hand);


	for(;;) {
	/* Read the time of day.  This will be used as the "official
	 * timestamp" in all of the files. */
		get_current_timestamp(&timestamp);

                /* Read in all DB vars, whether or not the associated files
                 * are being written
                 */
                for (i = 0; i < num_db_vars; i++)
                        db_clt_read(pclt,
                                db_vars[i].db_id_num,
                                db_vars[i].size,
                                db_vars[i].var_pointer);

		seconds_since_midnight = TS_TO_SEC(&cabinet_gps.utc_time);	
		sv_utc_seconds = TS_TO_SEC(&sv_gps.utc_time);	
		pov1_utc_seconds = TS_TO_SEC(&pov1_gps.utc_time);	
		pov2_utc_seconds = TS_TO_SEC(&pov2_gps.utc_time);	
		seconds_since_start = seconds_since_midnight - start_time; 
		ped_warn = GPIO_DIG_IN(dig_in.dig_in, GPIO_DIG_IN_1);
		lightwave_west = GPIO_DIG_IN(dig_in.dig_in, GPIO_DIG_IN_2);
		lightwave_south = GPIO_DIG_IN(dig_in.dig_in, GPIO_DIG_IN_3);
		lightwave_east = GPIO_DIG_IN(dig_in.dig_in, GPIO_DIG_IN_7);
		lightwave_north = GPIO_DIG_IN(dig_in.dig_in, GPIO_DIG_IN_5);

                if (do_evt300) {
                        save_evt300(f_evt300A, &evt300a, timestamp, use_memory,
                                pbuff_evt300A);
                        save_evt300(f_evt300B, &evt300b, timestamp, use_memory,
                                pbuff_evt300B);
		}

		// SMS save routine reads its own DB VARs
		if (do_sms)
                        save_sms(pclt, f_sms, timestamp, use_memory,
                                pbuff_sms);

		if (use_altima_spec) {
                        save_to_spec(f_experiment, timestamp, use_memory,
                                pbuff_experiment, num_efile_columns,
                                &altima_data_spec[0]);

                }
		if (do_experiment) {
                        save_to_spec(f_experiment, timestamp, use_memory,
                                pbuff_experiment, num_efile_columns,
                                &experiment_spec[0]);

                }
                if (do_comm) {
                        save_to_spec(f_comm, timestamp, use_memory,
                                pbuff_comm, num_qfile_columns,
                                &comm_spec[0]);

                }

		/** Check if time to close and reopen data logs 
		  */

               if (reopen_data_log(&first_file, file_time, first_file_str,
                                ".dat", &start_time, &old_fileday, &serial_num,
                                id_string, pbuff_evt300A)) {
                        // done for first file in reopen_data_log
                        if (do_evt300) {
                                reopen_another_file(&f_evt300B, "/big/data/xb",
                                         id_string, ".dat", pbuff_evt300B);
                        }
                        if (do_experiment && do_evt300) {
                                reopen_another_file(&f_experiment,
                                        "/big/data/xe", id_string,
                                        ".dat", pbuff_experiment);
                        }
                        if (do_comm && (do_evt300 || do_experiment)){
                                reopen_another_file(&f_comm, "/big/data/xq",
                                        id_string, ".dat", pbuff_comm);

                        }
                        if (do_sms && (do_evt300 || do_experiment ||
					do_comm))
                                reopen_another_file(&f_sms, "/big/data/xs",
                                        id_string, ".dat", pbuff_sms);

                        if (use_memory)
                                do_buff_inits(lines_to_save,
                                        do_evt300, do_experiment, do_comm,
                                        do_sms, &pbuff_evt300A, &pbuff_evt300B,
                                        &pbuff_experiment, &pbuff_comm,
					&pbuff_sms);

                }

		TIMER_WAIT(ptimer);
	}
}
