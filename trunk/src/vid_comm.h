/**\file
 *
 * 	Definitions for communications between video computer and
 *	engineering computer
 */
#ifndef PATH_VID_COMM_H
#define PATH_VID_COMM_H

#define RBUFSIZE	1500
#define VID_RCV_PORT	7015
#define VID_RCV_IP "255.255.255.255"

/// Codes used in synchronization record sent to video recording computer
#define VIDEO_STOP_RECORD	1
#define VIDEO_START_RECORD	2
#define VIDEO_SHUTDOWN		4

extern void send_video_sync(int sd, struct sockaddr_in *paddr, 
	sync_record_typ *video, int verbose);

#endif
