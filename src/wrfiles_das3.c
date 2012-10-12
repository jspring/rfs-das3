/**\file
 * wrfiles_cacc3.c    File to save the data from the CAN and gps
 *              for the CACC selfs:
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
 *		from many different DB VARs are now in cacc3_tables.c		
 *
 *
 * Copyright (c) 2000-2009   Regents of the University of California
 *
 *
 */
#include <db_include.h>
#include <db_utils.h>
#include <path_gps_lib.h>
//#include <m56_can.h>
#include <evt300.h>
#include "data_log.h"
#include "db_sync.h"
#include "das3.h"

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

#define IGNITION_OFF 255
#define IGN_CTR_MAX 100

/// Codes used in synchronization record sent to video recorder
#define VIDEO_STOP_RECORD	1
#define VIDEO_START_RECORD	2
#define VIDEO_SHUTDOWN		4


/**
 *	File pointers used for each file saved.
 */
FILE *f_a = NULL;
FILE *f_b = NULL;
FILE *f_c = NULL;
FILE *f_d = NULL;
FILE *f_e = NULL;
FILE *f_f = NULL;
FILE *f_g = NULL;
FILE *f_evt300 = NULL;

buff_typ *pfirst_buff;
buff_typ *pbuff_a;
buff_typ *pbuff_b;
buff_typ *pbuff_c;
buff_typ *pbuff_d;
buff_typ *pbuff_e;
buff_typ *pbuff_f;
buff_typ *pbuff_g;
buff_typ *pbuff_evt300;

extern timestamp_t timestamp;                 // used when reading back in
extern double utc_seconds_since_midnight;    // UTC seconds since midnight
extern double seconds_since_start;       // seconds since start of run

extern db_var_spec_t db_vars[];
extern int num_db_vars;
extern db_var_spec_t expt_db_vars[];
extern int num_expt_db_vars;
extern path_gps_point_t my_gps;
//extern m56_ignition_status_t m56_ignition_status;
evt300_radar_typ evt300a;

extern data_log_column_spec_t file_speca[];
extern int num_afile_columns;
extern data_log_column_spec_t file_specb[];
extern int num_bfile_columns;
extern data_log_column_spec_t file_specc[];
extern int num_cfile_columns;
extern data_log_column_spec_t file_specd[];
extern int num_dfile_columns;
extern data_log_column_spec_t file_spece[];
extern int num_efile_columns;
extern data_log_column_spec_t file_specf[];
extern int num_ffile_columns;
extern data_log_column_spec_t file_specg[];
extern int num_gfile_columns;

path_gps_point_t cabinet_gps; 		// GPS in cabinet

void do_buff_inits(int lines_to_save,
                int do_filea, int do_fileb, int do_filec, int do_filed,
                int do_filee, int do_filef, int do_fileg, int do_evt300,
                buff_typ **ppbuff_a, buff_typ **ppbuff_b, 
		buff_typ **ppbuff_c, buff_typ **ppbuff_d, 
		buff_typ **ppbuff_e, buff_typ **ppbuff_f, 
		buff_typ **ppbuff_g, buff_typ **ppbuff_evt300)
{
        if (do_filed)
                *ppbuff_d = buff_init(f_d, lines_to_save);
        if (do_filea)
                *ppbuff_a = buff_init(f_a, lines_to_save);
        if (do_fileb)
                *ppbuff_b = buff_init(f_b, lines_to_save);
        if (do_filec)
                *ppbuff_c = buff_init(f_c, lines_to_save);
        if (do_filee)
                *ppbuff_e = buff_init(f_e, lines_to_save);
        if (do_filef)
                *ppbuff_f = buff_init(f_f, lines_to_save);
        if (do_fileg)
                *ppbuff_g = buff_init(f_g, lines_to_save);
        if (do_evt300)
                *ppbuff_evt300 = buff_init(f_evt300, lines_to_save);
	
}
 
int main(int argc, char *argv[])
{
	int option;
	int exitsig;
	double start_time;
	db_clt_typ *pclt;
	char hostname[MAXHOSTNAMELEN+1];
	int old_fileday = 99;	/// originally set to bad value to force search
	int serial_num;		/// set in open_data_log	
	char id_string[80];
	char monthday[80];
	char serialnum[80];
	char *vehicle_prefix = "m";

	int file_time = 15;     /// Number of minutes to record to a file 
	int interval = 50;	/// Number of milliseconds between saves 
	int lines_to_save = 100000;	/// when using memory; about 2 hours
	posix_timer_typ *ptimer;       /* Timing proxy */
	char *domain = DEFAULT_SERVICE; // usually no need to change this 
	int xport = COMM_OS_XPORT;	// set correct for OS in sys_os.h 
	int do_filea = FALSE;		// command flag will turn on
	int do_fileb = FALSE;		// command flag will turn on
	int do_filec = FALSE;		// command flag will turn on
	int do_filed = FALSE;		// command flag will turn on
	int do_filee = FALSE;		// command flag will turn on
	int do_filef = FALSE;		// command flag will turn on
	int do_fileg = FALSE;		// command flag will turn on
	int do_evt300= FALSE;		// command flag will turn on
	int do_video = TRUE;		// command flag will turn off
	int use_memory = FALSE;		// to save in memory, set to 1
	das3_ignition_status_t das3_ignition_status;
	int use_ignition_status = FALSE;
	int ign_ctr = IGN_CTR_MAX;
	FILE *first_file = NULL;
	char *first_file_str;
	char tripdir[80];
	char tripstr[80];
	char apre[80];
	char bpre[80];
	char cpre[80];
	char dpre[80];
	char epre[80];
	char fpre[80];
	char gpre[80];
	char rpre[80];
	int i;
	printf("%s:  do_filea %d  do_fileb %d do_filec %d do_filed %d do_filee %d do_filef %d do_fileg %d do_evt300 %d do_video %d\n",
		 argv[0],
		do_filea,
		do_fileb,
		do_filec,
		do_filed, 
		do_filee,
		do_filef,
		do_fileg,
		do_evt300,
		do_video);

	memset(id_string, 0, sizeof(id_string));
	memset(monthday, 0, sizeof(monthday));
	memset(serialnum, 0, sizeof(serialnum));
	memset(tripdir, 0, sizeof(tripdir));
	memset(tripstr, 0, sizeof(tripstr));
	memset(apre, 0, sizeof(apre));
	memset(bpre, 0, sizeof(bpre));
	memset(cpre, 0, sizeof(cpre));
	memset(dpre, 0, sizeof(dpre));
	memset(epre, 0, sizeof(epre));
	memset(fpre, 0, sizeof(fpre));
	memset(gpre, 0, sizeof(gpre));
	memset(rpre, 0, sizeof(rpre));

	/* Read and interpret any user switches. */
	while ((option = getopt(argc, argv, "d:l:m:ABCDEFGt:uic:rv")) != EOF) {
		switch(option) {
		case 'd':
			strcpy(tripdir, optarg);
			break;
	        case 'l':
			lines_to_save = atoi(optarg);
			break;
	        case 'm':
			file_time = atoi(optarg);
			if(file_time == 0)
			    file_time = 10000;
			break;
	        case 'A':
			do_filea = TRUE; 
			break;
	        case 'B':
			do_fileb = TRUE; 
			break;
	        case 'C':
			do_filec = TRUE; 
			break;
	        case 'D':
			do_filed = TRUE; 
			break;
	        case 'E':
			do_filee = TRUE; 
			break;
	        case 'F':
			do_filef = TRUE; 
			break;
	        case 'G':
			do_fileg = TRUE; 
			break;
	        case 't':
			interval = atoi(optarg); 
			break;
	        case 'u':
			use_memory = TRUE; 
			break;
	        case 'i':
			use_ignition_status = TRUE; 
			break;
	        case 'c':
			vehicle_prefix = strdup(optarg);
			break;
	        case 'r':
			do_evt300 = TRUE;
			break;
	        case 'v':
			do_video = FALSE; 
			break;
	        default:
			printf("Usage: %s\n", argv[0]); 
			printf("    -d <trip directory> \n");
			printf("    -c <vehicle prefix> \n");
			printf("    -m <file time in minutes> \n");
			printf("    -i (use ignition status to stop file writing) \n");
			printf("    -v (don't save video) \n");
			printf("    -r (save EVT300 radar data) \n");
			printf("    -l <no. lines to save to file> \n");
			printf("    -t <loop time in ms> \n");
			printf("    -u (use memory to log data, then write to file at end)\n");
			printf("    -ABCDEFG (don't save abcdefg-file(s))\n");
			exit(EXIT_FAILURE);
	        }
	}
	strcpy(tripstr, tripdir+17);
	printf("tripdir %s\n", tripdir);
	printf("tripstr as string %s as decimal %d\n", tripstr, atoi(tripstr));
	printf("vehicle_prefix %s\n", vehicle_prefix);
	printf(" afile columns %d\n", num_afile_columns);
	printf(" bfile columns %d\n", num_bfile_columns);
	printf(" cfile columns %d\n", num_cfile_columns);
	printf(" dfile columns %d\n", num_dfile_columns);
	printf(" efile columns %d\n", num_efile_columns);
	printf(" ffile columns %d\n", num_ffile_columns);
	printf(" gfile columns %d\n", num_gfile_columns);

	if(do_filea) { //This bit of nonsense is in case both radar and filea
	               // have been selected
		if(num_afile_columns == 0) 
			do_filea = 0; 
		else 
			do_filea = 1;
	}
	if(num_bfile_columns == 0) do_fileb = 0; 
	if(num_cfile_columns == 0) do_filec = 0;
	if(num_dfile_columns == 0) do_filed = 0;
	if(num_efile_columns == 0) do_filee = 0;
	if(num_ffile_columns == 0) do_filef = 0;
	if(num_gfile_columns == 0) do_fileg = 0;
	printf("%s:  do_filea %d  do_fileb %d do_filec %d do_filed %d do_filee %d do_filef %d do_fileg %d do_evt300 %d do_video %d\n",
		 argv[0],
		do_filea,
		do_fileb,
		do_filec,
		do_filed, 
		do_filee,
		do_filef,
		do_fileg,
		do_evt300,
		do_video);

        if(do_evt300 && do_filea) {
                printf("Error in file prefix choice: You cannot choose ");
                printf("to collect both evt300 data (file prefix \"a\" ");
                printf("and file_speca), and another file with prefix \"a\"\n");
                printf("Exiting wrfiles_das3\n");
                exit(EXIT_FAILURE);
        }

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

        if (do_filea) {
		strcpy(apre, tripdir);
		strcat(apre, "/");
		strcat(apre, vehicle_prefix);
		strcat(apre, "a");
                if (first_file == NULL) {
                        open_data_log_infix(&f_a, apre, ".dat",
                         &start_time, &old_fileday, &serial_num, monthday, serialnum, tripstr);
                        first_file = f_a;
                        first_file_str = apre;
			pfirst_buff = pbuff_a;
			sprintf(id_string, "%s%s%s", monthday, tripstr, serialnum);
                } else {
                        open_another_file(&f_a, apre,
                                  id_string, ".dat");
                }
        }

        if (do_fileb) {
		strcpy(bpre, tripdir);
		strcat(bpre, "/");
		strcat(bpre, vehicle_prefix);
		strcat(bpre, "b");
                if (first_file == NULL) {
                        open_data_log_infix(&f_b, bpre, ".dat",
                         &start_time, &old_fileday, &serial_num, monthday, serialnum, tripstr);
                        first_file = f_b;
                        first_file_str = bpre;
			pfirst_buff = pbuff_b;
			sprintf(id_string, "%s%s%s", monthday, tripstr, serialnum);
                } else {
                        open_another_file(&f_b, bpre,
                                  id_string, ".dat");
                }
        }
        if (do_filec) {
		strcpy(cpre, tripdir);
		strcat(cpre, "/");
		strcat(cpre, vehicle_prefix);
		strcat(cpre, "c");
                if (first_file == NULL) {
                        open_data_log_infix(&f_c, cpre, ".dat",
                         &start_time, &old_fileday, &serial_num, monthday, serialnum, tripstr);
                        first_file = f_c;
                        first_file_str = cpre;
			pfirst_buff = pbuff_c;
			sprintf(id_string, "%s%s%s", monthday, tripstr, serialnum);
                } else {
                        open_another_file(&f_c, cpre,
                                  id_string, ".dat");
                }
	}
        if (do_filed) {
		strcpy(dpre, tripdir);
		strcat(dpre, "/");
		strcat(dpre, vehicle_prefix);
		strcat(dpre, "d");
                if (first_file == NULL) {
                        open_data_log_infix(&f_d, dpre, ".dat",
                         &start_time, &old_fileday, &serial_num, monthday, serialnum, tripstr);
                        first_file = f_d;
                        first_file_str = dpre;
			pfirst_buff = pbuff_d;
			sprintf(id_string, "%s%s%s", monthday, tripstr, serialnum);
                } else {
                        open_another_file(&f_d, dpre,
                                  id_string, ".dat");
                }
        }

        if (do_filee) {
		strcpy(epre, tripdir);
		strcat(epre, "/");
		strcat(epre, vehicle_prefix);
		strcat(epre, "e");
                if (first_file == NULL) {
                        open_data_log_infix(&f_e, epre, ".dat",
                         &start_time, &old_fileday, &serial_num, monthday, serialnum, tripstr);
                        first_file = f_e;
                        first_file_str = epre;
			pfirst_buff = pbuff_e;
			sprintf(id_string, "%s%s%s", monthday, tripstr, serialnum);
                } else {
                        open_another_file(&f_e, epre,
                                  id_string, ".dat");
                }
        }

        if (do_filef) {
		strcpy(fpre, tripdir);
		strcat(fpre, "/");
		strcat(fpre, vehicle_prefix);
		strcat(fpre, "f");
                if (first_file == NULL) {
                        open_data_log_infix(&f_f, fpre, ".dat",
                         &start_time, &old_fileday, &serial_num, monthday, serialnum, tripstr);
                        first_file = f_f;
                        first_file_str = fpre;
			pfirst_buff = pbuff_f;
			sprintf(id_string, "%s%s%s", monthday, tripstr, serialnum);
                } else {
                        open_another_file(&f_f, fpre,
                                  id_string, ".dat");
                }
        }

        if (do_fileg) {
		strcpy(gpre, tripdir);
		strcat(gpre, "/");
		strcat(gpre, vehicle_prefix);
		strcat(gpre, "g");
                if (first_file == NULL) {
                        open_data_log_infix(&f_g, gpre, ".dat",
                         &start_time, &old_fileday, &serial_num, monthday, serialnum, tripstr);
                        first_file = f_g;
                        first_file_str = gpre;
			pfirst_buff = pbuff_g;
			sprintf(id_string, "%s%s%s", monthday, tripstr, serialnum);
                } else {
                        open_another_file(&f_g, gpre,
                                  id_string, ".dat");
                }
        }

        if (do_evt300) {
		strcpy(rpre, tripdir);
		strcat(rpre, "/");
		strcat(rpre, vehicle_prefix);
		strcat(rpre, "a");
                if (first_file == NULL) {
                        open_data_log_infix(&f_evt300, rpre, ".dat",
                         &start_time, &old_fileday, &serial_num, monthday, serialnum, tripstr);
                        first_file = f_evt300;
                        first_file_str = rpre;
			pfirst_buff = pbuff_evt300;
			sprintf(id_string, "%s%s%s", monthday, tripstr, serialnum);
                } else {
                        open_another_file(&f_evt300, rpre,
                                  id_string, ".dat");
                }
        }
        if (use_memory)
                do_buff_inits(lines_to_save,
			do_filea, do_fileb, do_filec, do_filed, do_filee, 
			do_filef, do_fileg, do_evt300,
			&pbuff_a, &pbuff_b, &pbuff_c, &pbuff_d, &pbuff_e, 
			&pbuff_f, &pbuff_g, &pbuff_evt300);


	if(( exitsig = setjmp(exit_env)) != 0) {
		if (use_memory) {
			if (do_filea) 
				buff_done(pbuff_a);
			if (do_fileb) 
				buff_done(pbuff_b);
			if (do_filec) 
				buff_done(pbuff_c);
			if (do_filed)
				buff_done(pbuff_d);
			if (do_filee) 
				buff_done(pbuff_e);
			if (do_filef) 
				buff_done(pbuff_f);
			if (do_fileg) 
				buff_done(pbuff_g);
			if (do_evt300) 
				buff_done(pbuff_evt300);
		}
		if (f_a)
			fclose(f_a);
		if (f_b)
			fclose(f_b);
		if (f_c)
			fclose(f_c);
		if (f_d)
			fclose(f_d);
		if (f_e)
			fclose(f_e);
		if (f_f)
			fclose(f_f);
		if (f_g)
			fclose(f_g);
		if (f_evt300)
			fclose(f_evt300);

		db_list_done(pclt, NULL, 0, NULL, 0);
	    if(exitsig == IGNITION_OFF) {
	    	system("echo 'Going down!' > /tmp/lcdtemp");
		printf("Ignition off!\n");
		sleep(5);
		system("/home/cacc3/test/stop_cacc3.sh ignorewrfiles");
	    }
	    printf("%s exiting with signal %d\n", argv[0], exitsig);
	    exit(EXIT_SUCCESS);
	} else
		sig_ign(sig_list, sig_hand);

	fflush(stdout);

	for(;;) {
	/* Read the time of day.  This will be used as the "official
	 * timestamp" in all of the files. */
		get_current_timestamp(&timestamp);

                /* Read in all DB vars, whether or not the associated files
                 * are being written
                 */
                for (i = 0; i < num_db_vars; i++){
                        db_clt_read(pclt,
                                db_vars[i].db_id_num,
                                db_vars[i].size,
                                db_vars[i].var_pointer);
		}
                for (i = 0; i < num_expt_db_vars; i++){
                        db_clt_read(pclt,
                                expt_db_vars[i].db_id_num,
                                expt_db_vars[i].size,
                                expt_db_vars[i].var_pointer);
		}

        	utc_seconds_since_midnight = TS_TO_SEC(&my_gps.utc_time);
                if (do_filea)
                        save_to_spec(f_a, timestamp, use_memory,
                                pbuff_a, num_afile_columns,
                                &file_speca[0]);

                if (do_fileb) 
                        save_to_spec(f_b, timestamp, use_memory,
                                pbuff_b, num_bfile_columns,
                                &file_specb[0]);

                if (do_filec) 
                        save_to_spec(f_c, timestamp, use_memory,
                                pbuff_c, num_cfile_columns,
                                &file_specc[0]);

		if (do_filed)
                        save_to_spec(f_d, timestamp, use_memory,
                                pbuff_d, num_dfile_columns,
                                &file_specd[0]);

                if (do_filee) 
                        save_to_spec(f_e, timestamp, use_memory,
                                pbuff_e, num_efile_columns,
                                &file_spece[0]);

                if (do_filef) 
                        save_to_spec(f_f, timestamp, use_memory,
                                pbuff_f, num_ffile_columns,
                                &file_specf[0]);

                if (do_fileg) 
                        save_to_spec(f_g, timestamp, use_memory,
                                pbuff_g, num_gfile_columns,
                                &file_specg[0]);
                if (do_evt300) {
                        save_evt300(f_evt300, &evt300a, timestamp, use_memory,
                                pbuff_evt300);
                }

		/** Check if time to close and reopen data logs 
		  */

               if (reopen_data_log_infix(&first_file, file_time, first_file_str,
                                ".dat", &start_time, &old_fileday, &serial_num,
                                monthday, serialnum, tripstr, pfirst_buff))  {
                        // done for first file in reopen_data_log

			sprintf(id_string, "%s%s%s", monthday, tripstr, serialnum);
			if (do_video) {
				struct tm synctime;
				struct timespec now;
				sync_record_typ sync;

				clock_gettime(CLOCK_REALTIME, &now);
				localtime_r(&now.tv_sec, &synctime);
				sync.month = atoi(monthday)/100;
				sync.day = atoi(monthday) % 100;
				sync.flag = VIDEO_START_RECORD;
				sync.seq_num = serial_num - 1;
				sync.trip_num = atoi(tripstr);
				sync.time_duration = file_time * 60;
 printf("sync.month %d sync.day %d sync.flag %d sync.seq_num %d sync.trip_num %d sync.time_duration %d\n", sync.month, sync.day, sync.flag, sync.seq_num, sync.trip_num, sync.time_duration);
				db_clt_write(pclt, DB_SYNC_RECORD_VAR, 
					sizeof(sync_record_typ), &sync);
			}
                        if (do_filea)
                                reopen_another_file(&f_a, apre,
                                        id_string, ".dat", pbuff_a);
                        if (do_fileb)
                                reopen_another_file(&f_b, bpre,
                                        id_string, ".dat", pbuff_b);
                        if (do_filec)
                                reopen_another_file(&f_c, cpre,
                                        id_string, ".dat", pbuff_c);
                        if (do_filed) 
                                reopen_another_file(&f_d, dpre, 
					id_string, ".dat", pbuff_d);
                        if (do_filee)
                                reopen_another_file(&f_e, epre,
                                        id_string, ".dat", pbuff_e);
                        if (do_filef)
                                reopen_another_file(&f_f, fpre,
                                        id_string, ".dat", pbuff_f);
                        if (do_fileg)
                                reopen_another_file(&f_g, gpre,
                                        id_string, ".dat", pbuff_g);
                        if (do_evt300)
                                reopen_another_file(&f_evt300, rpre,
                                        id_string, ".dat", pbuff_evt300);

                        }
                        if (use_memory)
                                do_buff_inits(lines_to_save,
                                        do_filea, do_fileb, do_filec, do_filed,
					do_filee, do_filef, do_fileg, do_evt300,
                                        &pbuff_a, &pbuff_b,  &pbuff_c, 
					&pbuff_d,  &pbuff_e,  &pbuff_f,  
					&pbuff_g,  &pbuff_evt300);
		if((das3_ignition_status.ignition_status == 1) && use_ignition_status) {
			ign_ctr--;
			if(ign_ctr == 0) {
				printf("Exiting due to ignition off\n");
				longjmp(exit_env, IGNITION_OFF);
			}
		}
		else
			ign_ctr = IGN_CTR_MAX;
		TIMER_WAIT(ptimer);
	}
}
