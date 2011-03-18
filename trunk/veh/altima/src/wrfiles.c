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
#include <db_include.h>
#include "wrfiles_lib.h"
#include <path_gps_lib.h>
#include <sys_ini.h>

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
FILE *f_altima = NULL;
buff_typ *pbuff_evt300A;
buff_typ *pbuff_altima;
extern db_var_spec_t db_vars[];
extern int num_db_vars;
extern void save_altima(FILE *fout, timestamp_t timestamp, 
	int use_memory, buff_typ *pbuff);
extern evt300_radar_typ evt300a;

void do_buff_inits(int lines_to_save, int do_evt300, int do_altima,
	buff_typ **ppbuff_evt300A, buff_typ **ppbuff_altima)
{
        if (do_evt300) {
                *ppbuff_evt300A = buff_init(f_evt300A, lines_to_save);
        }
        if (do_altima) {
                *ppbuff_altima = buff_init(f_altima, lines_to_save);
        }
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
	bool_typ do_evt300 = TRUE;
	bool_typ do_altima = TRUE;
	bool_typ use_memory = FALSE;
	FILE *first_file;
	char *first_file_str;
	char *ini_file = "wrfiles.ini";
	FILE *pfin1 = NULL;
	char *config_file_section = "altima";
	int i;

	/* Read and interpret any user switches. */
	while ((option = getopt(argc, argv, "d:c:x:al:m:rt:u")) != EOF) {
		switch(option) {
		case 'd':
			domain = strdup(optarg);
		case 'c':
			ini_file = strdup(optarg);
		case 'x':
			config_file_section = strdup(optarg);
	        case 'a':
			do_altima = FALSE; 
			break;
	        case 'l':
			lines_to_save = atoi(optarg);
			break;
	        case 'm':
			file_time = atoi(optarg);
			break;
	        case 'r':
			do_evt300 = FALSE; 
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
                printf("WRFILES.C:Cannot get ini file %s, section %s\n",
                   ini_file, config_file_section);
                fflush(stdout);
                return 0;
            }

	printf(" do_altima %d do_evt300 %d \n",
		do_altima, do_evt300);

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
                open_data_log(&f_evt300A, "/big/data/a", ".dat",
                         &start_time, &old_fileday, &serial_num, id_string);
                first_file = f_evt300A;
                first_file_str = "/big/data/a";
        }
        if (do_altima) {
                if (first_file == NULL) {
                        open_data_log(&f_altima, "/big/data/d", ".dat",
                         &start_time, &old_fileday, &serial_num, id_string);
                        first_file = f_altima;
                        first_file_str = "/big/data/d";
                } else {
                        open_another_file(&f_altima, "/big/data/d",
                                  id_string, ".dat");
                }
        }
        if (use_memory)
                do_buff_inits(lines_to_save, do_evt300, do_altima, 
			&pbuff_evt300A, &pbuff_altima);

	    

	if(setjmp(exit_env) != 0) {
		if (use_memory) {
			if (do_evt300) {
				buff_done(pbuff_evt300A);
			}
			if (do_altima)
				buff_done(pbuff_altima);
		}
		if (f_evt300A)
			fclose(f_evt300A);
		if (f_altima)
			fclose(f_altima);
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

                if (do_evt300) {
                        save_evt300(f_evt300A, &evt300a, timestamp, use_memory,
                                pbuff_evt300A);
		}

		if (do_altima) {
                        save_altima(f_altima, timestamp, use_memory,
                                pbuff_altima);
                }

		/** Check if time to close and reopen data logs 
		  */

               if (reopen_data_log(&first_file, file_time, first_file_str,
                                ".dat", &start_time, &old_fileday, &serial_num,
                                id_string, pbuff_evt300A)) {
                        // done for first file in reopen_data_log
                        if (do_evt300) {
                                reopen_another_file(&f_evt300A,
                                        "/big/data/a", id_string,
                                        ".dat", pbuff_evt300A);
                        }
                        if (do_altima) {
                                reopen_another_file(&f_altima,
                                        "/big/data/a", id_string,
                                        ".dat", pbuff_altima);
                        }
                        if (use_memory)
                                do_buff_inits(lines_to_save, do_evt300, 
					do_altima, &pbuff_evt300A, 
					&pbuff_altima);

                }

		TIMER_WAIT(ptimer);
	}
}
