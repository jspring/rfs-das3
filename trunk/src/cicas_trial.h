/**\file
 *	Header file for data structure that will be written by
 *	experimental control and sent between vehicles and cabinet.
 *	DB variable names indicate the source of the information.
 *	On the sender side, this variable will be written by the
 *	experimental control process and read by the sending process.
 *	On the receiver side this will be written by the receiver
 *	process, and read primarily by user interface processes.
 *
 */

#define DB_SV_CICAS_TRIAL_VAR	601	// Subject Vehicle
#define DB_SV_CICAS_TRIAL_TYPE	DB_SV_CICAS_TRIAL_VAR	
#define DB_POV1_CICAS_TRIAL_VAR	602	// First Principal Other Vehicle	
#define DB_POV1_CICAS_TRIAL_TYPE	DB_POV1_CICAS_TRIAL_VAR	
#define DB_POV2_CICAS_TRIAL_VAR	603	// Second Principal Other Vehicle	
#define DB_POV2_CICAS_TRIAL_TYPE	DB_POV2_CICAS_TRIAL_VAR	
#define DB_CAB_CICAS_TRIAL_VAR	604	// Cabinet Experimental Control	
#define DB_CAB_CICAS_TRIAL_TYPE	DB_CAB_CICAS_TRIAL_VAR	

/** Definitions for setting source byte 
 */
#define CICAS_TRIAL_SOURCE_SV	0x01
#define CICAS_TRIAL_SOURCE_POV1	0x02
#define CICAS_TRIAL_SOURCE_POV2	0x04
#define CICAS_TRIAL_SOURCE_CAB	0x08

/** Definitions for setting vehicle_state byte
 */
#define CICAS_TRIAL_SV_IS_READY	0x01
#define CICAS_TRIAL_POV1_IS_READY	0x02
#define CICAS_TRIAL_POV2_IS_READY	0x04
#define CICAS_TRIAL_SV_ABORT	0x08
#define CICAS_TRIAL_POV1_ABORT	0x10
#define CICAS_TRIAL_POV2_ABORT	0x20

/** Definitions for setting experimental control byte
 */
#define CICAS_TRIAL_CTRL_SV_GO	0x01	
#define CICAS_TRIAL_CTRL_POV1_GO	0x02	
#define CICAS_TRIAL_CTRL_POV2_GO	0x04	
#define CICAS_TRIAL_CTRL_ABORT	0x08
#define CICAS_TRIAL_CTRL_RESTART	0x10

/** Definitions for setting alert state byte
 */
#define CICAS_TRIAL_ALERT_DVI_ON	0x01	
#define CICAS_TRIAL_ALERT_DII_ON	0x02	

/** Definitions for setting configuration byte
 */
#define CICAS_TRIAL_CONFIG_NS	0x01	
#define CICAS_TRIAL_CONFIG_EW	0x02	

typedef struct {
	timestamp_t ts;			// time written to DB data server
	/** Static per-trial information
	 */
	unsigned char source;		// entity filling in info
	unsigned short trial_number;
	unsigned char configuration;	// NS or EW, other info?
	float target_pov_speed;		// speed to maintain on approach 
	float target_pov_gap;		// gap between vehicles to maintain 
	float target_trailing_buffer;	// goal for SV/POV proximity

	/** Dynamic trial state information; for bits it doesn't set,
	 *  each entity reflects what it has heard from others
	 */
	unsigned char vehicle_state;	// each vehicle sets its own bit
	unsigned char control_state;	// set by control on cabinet
	unsigned char alert_state;	// set by control on cabinet
} cicas_trial_t;
