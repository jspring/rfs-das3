/**
 * 	Send video sync to remote system, based either on trigger
 *	from DB variable, or on time interval (for testing) 
 */
#include <sys_os.h>
#include <db_include.h>
#include <db_utils.h>
#include <udp_utils.h>
#include <db_sync.h>
#include "vid_comm.h"

static int sig_list[] =
{
    SIGINT,
    SIGQUIT,
    SIGTERM,
    SIGALRM,
    ERROR,
};

static jmp_buf exit_env;

static void sig_hand( int code )
{
        if(code == SIGALRM)
                return;
    longjmp( exit_env, code );
}

static int trig_list[] = {
        DB_SYNC_RECORD_VAR
};

#define NUM_TRIG_VARS    sizeof(trig_list)/sizeof(int)

int main(int argc, char **argv)

{
        db_clt_typ *pclt = NULL;
        trig_info_typ trig_info;        /* Trigger info */
        char hostname[MAXHOSTNAMELEN + 1];
        char *domain = DEFAULT_SERVICE;
	int recv_type;
        posix_timer_typ *ptimer;       /* Timing proxy */
	struct timespec tm;
	struct tm *vidtime;

	int sd;
	struct sockaddr_in snd_addr;
	unsigned short snd_port = VID_RCV_PORT; 
	char *snd_ip = VID_RCV_IP;
	int interval = 0;	// send as fast as you can
	int opt;
	int verbose = FALSE;
        int use_db = 1;
	sync_record_typ video;

	while ((opt = getopt(argc, argv, "a:s:t:vd:")) != -1) {
                switch (opt)
                {
                  case 'a':
                        snd_ip = strdup(optarg);
                        break;
                  case 's':
                        snd_port = atoi(optarg);
                        break;
		  case 't':
			interval = atoi(optarg);
			break;
		  case 'v':
			verbose = TRUE; 
			break;
		  case 'd':
                        use_db = atoi(optarg);
                        break;
                  default:
                        printf("Usage: %s -a [dest IP] ", argv[0]);
			printf(" -d (0=do not use DB, 1=use DB (default)");
			printf(" -s [send port]");
			printf(" -t interval (sec)\n");
			printf(" -v verbose\n");
                        exit(1);
                }
        }
        if(use_db) {
                get_local_name(hostname, MAXHOSTNAMELEN);
                pclt = db_list_init(argv[0], hostname, domain, COMM_OS_XPORT,
                        NULL, 0, trig_list, NUM_TRIG_VARS);
        }
	else {
        /* Setup a timer for every interval sec. */
        	if ((ptimer = timer_init(interval*1000, DB_CHANNEL(pclt))) == NULL) {
        	        printf("Unable to initialize vid_enet_srv timer\n");
        	        exit(EXIT_FAILURE);
        	}
	}
        if( setjmp( exit_env ) != 0 ) {
                db_list_done( pclt, NULL, 0, trig_list, NUM_TRIG_VARS );
                exit( EXIT_SUCCESS );
        }
        else
                sig_ign( sig_list, sig_hand );

	sd = udp_unicast();

	memset(&video, 0, sizeof(sync_record_typ));
	memset(&snd_addr, 0, sizeof(snd_addr));
	snd_addr.sin_family = AF_INET;
	snd_addr.sin_addr.s_addr = inet_addr(snd_ip);
	snd_addr.sin_port = htons(snd_port);

        printf("send address to ip 0x%x, port %d initialized\n",
                        ntohl(snd_addr.sin_addr.s_addr),
                        ntohs(snd_addr.sin_port));

	while(1) {
		if(use_db) {
			recv_type = clt_ipc_receive(pclt,&trig_info, 
				sizeof(trig_info));
			db_clt_read(pclt, DB_SYNC_RECORD_VAR, 
				sizeof(sync_record_typ), &video);
		}
		else {
			video.flag = 2;
			video.seq_num++;
			video.time_duration = interval;
	        }

		if (clock_gettime(CLOCK_REALTIME, &tm) == -1 ) {
			 perror("clock gettime");
			 exit(1);
		}
		vidtime = localtime(&tm.tv_sec);
		video.month = vidtime->tm_mon+1;
		video.day = vidtime->tm_mday;
		
		send_video_sync(
			sd,
			&snd_addr,
			&video,
			verbose);
		if(!use_db)
			TIMER_WAIT(ptimer);

	}
	return 0;
}
