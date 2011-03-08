/* \file
 * 	Header file for wireless communication in CICAS project. 
 *
 *	Messages are sent as UDP to DSRC radio units (SOBUs, Densos
 *	or MCNUs) and forwarded over the WAVE Short Message Protocol 
 */

#ifndef CICAS_MSG_H
#define CICAS_MSG_H

#define CICAS_MSG_MAX_DATA_SIZE 256	

// For setting the message_type field in cicas_msg_t
// First four messages are the only ones used when doing the IDS demo. 
// Next two are for the POVs in the SLTA human factors experiments.
// The first three should also be used in those experiments, and
// extended if possible so that the IDS demo can continue to run
// with the same message passing set-up as the human factors experiments.

#define MSG_DVI_DATA 1		// info from cabinet needed by SV DVI 
#define	MSG_SIGNAL_PHASE 2 	// traffic signal phase and countdown
#define	MSG_SV_DATA	3	// info from Subject Vehicle
#define	MSG_PED_WARN	4	// pedestrian warning from electric eye
#define	MSG_FIRST_POV_DATA 5	// info from first Principal Other Vehicle
#define	MSG_SECOND_POV_DATA 6 	// info from second POV 
#define	MSG_CICAS_CAB_TRIAL_DATA 7	// sent between vehicles and cabinet
#define	MSG_CICAS_SV_TRIAL_DATA 8	// sent between vehicles and cabinet
#define	MSG_CICAS_POV1_TRIAL_DATA 9	// sent between vehicles and cabinet
#define	MSG_CICAS_POV2_TRIAL_DATA 10	// sent between vehicles and cabinet
#define	MSG_CICAS_MAX_TYPE 11	// set to 1 more than last used

typedef unsigned char cicas_msg_type_t;

typedef struct {
        unsigned short sequence_number;  /// increment after each send 
        cicas_msg_type_t message_type;       /// for use with cabinet messages
	int byte_count;		/// actual size of bytes, array not always full
        int src;        	///IP4 address
        timestamp_t ts; 	/// hour, min, second, millisec -- 4 bytes
} IS_PACKED cicas_msg_hdr_t;

typedef struct {
	cicas_msg_hdr_t hdr;
        unsigned char bytes[CICAS_MSG_MAX_DATA_SIZE];
} IS_PACKED cicas_msg_t;

/** Alter what messages are sent and the send schedule by changing the
 *  specification in the send list. Typically the assemble routine
 *  for each message type will choose data out of the DB data server,
 *  based only the type of the message, but occasionally extra data
 *  known only to the sending process may be included.
 */
typedef struct {
        cicas_msg_type_t msg_type;   // message type
        int modulus;    // multiple of basic timer_interval for sending packet
        int start;      // index within modulus for send
	int (*assemble)(db_clt_typ *pclt, unsigned char *bytes, 
			void *extra_data, int verbose);
} cicas_msg_send_spec_t;

/** Specify what messages to receive and what to do on reception 
 *  in a receive list. Typically the receive routine will write
 *  to the DB data server based only on the message type, but
 *  occasionally other information known only to the receiving process
 *  may affect what is written. 
 */
typedef struct {
        cicas_msg_type_t msg_type;   // message type
	void (*receive)(db_clt_typ *pclt, unsigned char *bytes, 
			void *extra_data, int verbose);
} cicas_msg_receive_t;

/** 
 *	Prints header.  Prints hex dump of data bytes when verbose.
 */
extern void cicas_msg_print(FILE *fp, cicas_msg_t *p, int verbose);

/**
 *	Receive functions, used by more than one receiver,
 *	in cicas_msg_utils.c 
 */
extern void cicas_receive_signal_phase(db_clt_typ *pclt, unsigned char *pbytes,
                 void *extra_data, int verbose);
extern void cicas_receive_trial_data(db_clt_typ *pclt, unsigned char *pbytes,
                 void *extra_data, int verbose);

/**
 *	Assemble functions, used by more than one sender,
 *	in cicas_msg_utils.c 
 */
extern int cicas_assemble_trial_data(db_clt_typ *pclt, unsigned char *pbytes,
                 void *extra_data, int verbose);

/**
 *	Message type specific print utilties.
 */
extern void cicas_print_trial_data(FILE *fpout, cicas_trial_t *pt);
extern void cicas_print_sv_data(FILE *fpout, sv_data_t *psv);
extern void cicas_print_dvi_data(FILE *fpout, dvi_data_t *pdvi);
extern void cicas_print_signal_phase(FILE *fpout, traffic_signal_typ *ptsig);
#endif
