/**\file
 *	
 *	Gets synchronization record from engineering computer as UDP message.	
 *	Write to DB server for video recorder to read.
 *	If it is a shutdown message, writes a stop record synchronization
 *	record, waits an interval, and then shutdowns the processes and
 *	the system.
 *	
 */

#include <db_include.h>
#include <db_utils.h>
#include <udp_utils.h>
#include <db_sync.h>
#include "vid_comm.h"

#define RBUFSIZE 1500

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


int main(int argc, char **argv)
{
        db_clt_typ *pclt = NULL;
        char hostname[MAXHOSTNAMELEN + 1];
        char *domain = DEFAULT_SERVICE;

	int sd = -1;		// socket for receive
	struct sockaddr_in snd_addr;
	char rcv_buffer[RBUFSIZE];	
	int bytes_received;	// received from a call to recv 
	int num_items;		// returned from sscanf
	int port = VID_RCV_PORT;
	int opt;
	int use_db = 1;
        sync_record_typ video;
	int verbose = FALSE;
	int seconds_to_wait = 5;	//after stop record before shutdown 
	int do_shutdown = FALSE;

        while ((opt = getopt(argc, argv, "p:vm:d:")) != -1) {
                switch (opt) {
		case 'p':
                        port = atoi(optarg);
                        break;
		case 'v':
                        verbose = TRUE;
                        break;
		case 'd':
                        use_db = atoi(optarg);
                        break;
		default:
			printf("Usage: %s -p <port> -d (0=do not use DB, 1=use DB (default) -v \n", argv[0]);
			break;
		}
	}

        if(use_db) {
                get_local_name(hostname, MAXHOSTNAMELEN);
                pclt = db_list_init(argv[0], hostname, domain, COMM_OS_XPORT,
                        NULL, 0, NULL, 0);
        }
        if( setjmp( exit_env ) != 0 ) {
                db_list_done( pclt, NULL, 0, NULL, 0);
                exit( EXIT_SUCCESS );
        }
        else
                sig_ign( sig_list, sig_hand );
		

	if ((sd = udp_allow_all(port)) < 0){
		printf("%s: receive socket create or bind failed\n", argv[0]);
		exit(1);
	}
	printf("%s receiving on socket %d, port %d\n", argv[0], sd, port);

	for (;;) {
		unsigned int socklen = sizeof(snd_addr);
		int origin;

		memset(&snd_addr, 0, socklen);
		if ((bytes_received = recvfrom(sd, 
				&rcv_buffer, RBUFSIZE-1, 0, 
				(struct sockaddr *) &snd_addr,
				&socklen))
			      		<= 0) {
			perror("recvfrom failed");
			break;
		}	

		origin = ntohl(snd_addr.sin_addr.s_addr);

		num_items = sscanf(rcv_buffer,"%d %d %d %d %d %d", 
			&video.flag, 
			&video.month, 
			&video.day, 
			&video.seq_num, 
			&video.trip_num,
			&video.time_duration);

		// ignore message if bad decode
		if (num_items != 6) {
			printf("Error: num_items %d != 6\n",
				num_items);
//			continue;
		}
                if (verbose) 
		{
                        printf("Received %d bytes from 0x%8x, port %d ",
				bytes_received, origin, snd_addr.sin_port);
			printf("Receive buffer %s\n", rcv_buffer);
			printf("video.flag %d month %d day %d seq_num %d trip_num %d time_duration %d\n",
				video.flag,
				video.month,
				video.day,
				video.seq_num,
				video.trip_num,
				video.time_duration);

                }

		if (video.flag == VIDEO_SHUTDOWN) {
			do_shutdown = TRUE;
			video.flag = VIDEO_STOP_RECORD;
		}
		/// write stop record to video process before shutdown
		if(use_db) {
			if(verbose)
				printf("Writing to DB\n");
			db_clt_write(pclt, DB_SYNC_RECORD_VAR, 
				sizeof(sync_record_typ), &video);
		}
		if (do_shutdown) {
			sleep(seconds_to_wait);
			system("killall video");
			system("killall db_slv");
			system("shutdown -t 5 now"); 
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}
