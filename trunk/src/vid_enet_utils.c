/**
 * 	Function to send video sync record to the remote video system
 *	as a string using UDP
 */
#include <sys_os.h>
#include <db_sync.h>
#include <db_clt.h>
#include "vid_comm.h"

void send_video_sync(int sd, struct sockaddr_in *paddr, sync_record_typ *video,
	int verbose)
{
	static char snd_buffer[RBUFSIZE];
	int bytes_sent = 0;	// returned from sendto 

	sprintf(snd_buffer, "%d %d %d %d %d %d", 
		video->flag,
		video->month,
		video->day,
		video->seq_num,
		video->trip_num,
		video->time_duration);
	snd_buffer[RBUFSIZE] = '\0'; //mark end of string

	if(verbose) {
		printf("video.flag %d video.month %d video.day %d video.seq_num %d video.trip_num %d video.time_duration %d\n",
			video->flag,
			video->month,
			video->day,
			video->seq_num,
			video->trip_num,
			video->time_duration);
		printf("string sent: %s\n", snd_buffer);
	}
 
	bytes_sent = sendto(sd, snd_buffer, strlen(snd_buffer)+1, 0,
			(struct sockaddr *) paddr,
			sizeof(struct sockaddr_in)); 
	if (bytes_sent < 0)
		perror("vid_enet_srv");
	if (verbose && (bytes_sent != (strlen(snd_buffer) + 1)))
		printf("Send request %d, sent %d\n",
			strlen(snd_buffer) + 1, bytes_sent);
}
