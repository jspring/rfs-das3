/**\file
 *
 *	Structure and constant definitions for the Altima 2008 CAN
 *
 *	This header file contains Nissan proprietary information.
 * 
 */

/** Messages with fields used for California PATH Networked Traveler
 */
#define ALT_CCFTM_MSG_ID	0x160	/// CruiseControl_ForTM
#define ALT_CCFD_MSG_ID 	0x551	/// CruiseControl_ForDisplay
#define ALT_ENG_MSG_ID		0x180	/// Engine RPM/Acceleration 
#define ALT_GI_MSG_ID		0x421	/// GearIndication 
#define ALT_VS_MSG_ID		0x355	/// VehicleSpeed
#define ALT_FWBS_MSG_ID		0x35D	/// FrontWiping, BrakeSwitch	
#define ALT_TSI_MSG_ID		0x60D	/// TurnSignal, Ignition 
#define OBD2_ECM_MSG_ID		0x07E8	/// On-Board Diagnostic, version 2 (OBD2)
					/// response from Engine Control Module (ECM)
#define OBD2_MAF_MSG_ID		0x010	/// OBD2 message ID from Mass AirFlow sensor (MAF)
#define OBD2_CER_MSG_ID		0x044	/// OBD2 message ID for Commanded Equivalence Ratio (CER)

/** Corresponding DB variables for use with PATH's DB server.
 *  Check to make sure DB_ALTIMA_BASE does not overlap the number space
 *  of other DB variables being used on the system.
 */
#define DB_ALTIMA_BASE		900
#define DB_ALT_CCFTM_VAR	901
#define DB_ALT_CCFD_VAR		902
#define DB_ALT_ENG_VAR		903
#define DB_ALT_GI_VAR		904
#define DB_ALT_VS_VAR		905
#define DB_ALT_FWBS_VAR		906
#define DB_ALT_TSI_VAR		907
#define DB_OBD2_MAF_VAR		908
#define DB_OBD2_CER_VAR		909

#define DB_ALT_CCFTM_TYPE	DB_ALT_CCFTM_VAR
#define DB_ALT_CCFD_TYPE	DB_ALT_CCFD_VAR
#define DB_ALT_ENG_TYPE		DB_ALT_ENG_VAR
#define DB_ALT_GI_TYPE		DB_ALT_GI_VAR
#define DB_ALT_VS_TYPE		DB_ALT_VS_VAR
#define DB_ALT_FWBS_TYPE	DB_ALT_FWBS_VAR
#define DB_ALT_TSI_TYPE		DB_ALT_TSI_VAR
#define DB_OBD2_MAF_TYPE	DB_OBD2_MAF_VAR	
#define DB_OBD2_CER_TYPE	DB_OBD2_CER_VAR

/**
 *	ALT CruiseControl_ForTM
 *	Message ID	160
 *	Byte Position	4
 *	Bit Position	1
 *	Bit Length	2
 *	Transmitted every 10 ms
 */
typedef struct {
	timestamp_t ts;
	unsigned char code;
} alt_cruise_control_for_tm_t;

#define CCFTM_STANDBY 		0 /// CC and SL OFF, in standby or inactive
#define CCFTM_PEDAL_RECOVERY	1
#define CCFTM_ACTIVE		2 /// CC or SL active
#define CCFTM_UNUSED		3

static inline void get_alt_ccftm(unsigned char *data, 
				alt_cruise_control_for_tm_t *p)
{ 
	p->code = data[4] & (0x03);
}

/**
 *	ALT CruiseControl_ForDisplay
 *	Message ID	0x551
 *	Byte Position 	5
 *	Bit Position	6
 *	Bit Length	3
 *	Transmitted every 100 ms
 */

typedef struct {
	timestamp_t ts;
	unsigned char code;
	unsigned char on;
} alt_cruise_control_for_display_t;

#define CCFD_STANDBY		0 /// Cruise Control (CC), Speed Limit (SL) OFF
#define CCFD_SL_ACTIVE		1	
#define CCFD_SL_ON_INACTIVE	2 /// (SL on and inactive) or suspended
#define CCFD_SL_FAILURE		3 /// SL requested and in failure
#define CCFD_CC_ACTIVE		4	
#define CCFD_CC_ON_INACTIVE	5 /// (CC on and inactive) or suspended
#define CCFD_CC_FAILURE		6 /// CC requested and in failure
#define CCFD_CC_SL_NA		7 /// vehicle not equipped with CC and SL

static inline void get_alt_ccfd(unsigned char *data, 
				alt_cruise_control_for_display_t *p)
{ 
	p->code = (data[5] & (0x70)) >> 4;
	p->on = (p->code & CCFD_CC_ACTIVE) || (p->code & CCFD_CC_ON_INACTIVE); 
}

/**
 *	ALT Engine RPM/Acceleration	
 *	Message ID 180
 *	Transmitted every 10 ms
 */
typedef struct {
	timestamp_t ts;
	unsigned short raw_rpm;	/// Byte 0 high, Byte 1 low
	double rpm;	
	unsigned short acceleration;	/// Byte 5 high, Byte 6, bits 7-6 low
	double pct_throttle;
} alt_engine_t;

/**	Maximum value 65534 (as short), 8191.75 RPM, minimum value 0
 */
static inline double scale_alt_rpm(unsigned short rpm)
{
	return (rpm * 0.125);
}
/**	Maximum value 800 (as short), 100% 
 */
static inline double scale_alt_acceleration(unsigned short acceleration)
{
	return (acceleration * 0.125);
}

static inline void get_alt_eng(unsigned char *data, alt_engine_t *p)
{ 
	p->raw_rpm = (data[0] << 8) | (data[1] & 0xff); 
	p->rpm = scale_alt_rpm(p->raw_rpm);	
	p->acceleration = (data[5] << 2) | ((data[6] & 0xc0) >> 6); 
	p->pct_throttle = scale_alt_acceleration(p->acceleration);
}

/**
 *	ALT GearIndication
 *	Message ID 421
 *	Byte Position	0
 *	Bit Position 7
 *	Bit Length 5
 *	Transmitted 60ms after event
 */
typedef struct {
	timestamp_t ts;
	unsigned char code;
} alt_gear_indication_t;

#define GI_OFF		0
#define GI_PRANGE	1
#define GI_RRANGE	2
#define GI_NRANGE	3
#define GI_DRANGE	4
#define GI_SRANGE	5
#define GI_LRANGE	6
#define GI_BRANGE	7
#define GI_1RANGE	8
#define GI_2RANGE	9
#define GI_3RANGE	10
#define GI_4RANGE	11
#define GI_5RANGE	12
#define GI_6RANGE	13
#define GI_RES1		14
#define GI_RES2		15
#define GI_MANUAL1	16
#define GI_MANUAL2	17
#define GI_MANUAL3	18
#define GI_MANUAL4	19
#define GI_MANUAL5	20
#define GI_MANUAL6	21
#define GI_MANUAL7	22
#define GI_MANUAL8	23
#define GI_AUTO1	24
#define GI_AUTO2	25
#define GI_AUTO3	26
#define GI_AUTO4	27
#define GI_AUTO5	28
#define GI_AUTO6	29
#define GI_RES3		30
#define GI_RES4		31

static inline void get_alt_gi(unsigned char *data, 
				alt_gear_indication_t *p)
{ 
	p->code = ((data[0] & (0xF8)) >> 3) & 0x1F;
}

/**
 *	ALT VehicleSpeed
 *	Message ID 0x355
 *	Transmitted 60ms after event
 */
typedef struct {
	timestamp_t ts;
	unsigned short raw_vehicle_speed;	/// Byte 0 High Byte 1 Low
	double vehicle_speed;	/// km/hour 
} alt_vehicle_speed_t;

/**	Maximum value 65534 (as short), 655.34 km/hour 
 * 	(may want to change to scale meters/second)
 */
static inline double scale_alt_vehicle_speed(unsigned short vehicle_speed)
{
	return (vehicle_speed * 0.01);
}

static inline void get_alt_vs(unsigned char *data, 
				alt_vehicle_speed_t *p)
{ 
	p->raw_vehicle_speed = (data[0] << 8) | (data[1] & 0xff); 
	p->vehicle_speed = scale_alt_vehicle_speed(p->raw_vehicle_speed);	
}


/**
 *	ALT FrontWiping, BrakeSwitch
 *	Message ID 0x35D
 *	Transmitted 100 ms after event
 */
typedef struct {
	timestamp_t ts;
	unsigned char front_wiping;	/// Byte 2, bits 7-5
	unsigned char brake_switch;	/// Byte 4, bits 5-4 
} alt_front_wiping_brake_switch_t;

#define FW_STOP_POSITION	0	/// front wiper in stop position
#define FW_FORCED_STOP		1	/// front wiper foreced to stop
#define FW_ONE_WIPE_LOW		2	/// one low speed wiping requested
#define FW_ONE_WIPE_HI		3	/// one high speed wiping requested
#define FW_RES1			4	/// invalid
#define FW_RES2			5	/// invalid
#define FW_LOW_REQUEST		6	/// low speed wiping requested
#define FW_HI_REQUEST		7	/// hi speed wiping requested

#define BS_NOT_ACTIVATED	0	/// brake not activated
#define BS_ACTIVATED		1	/// brake activated
#define BS_RES1			2	/// unused
#define BS_RES2			3	/// invalid

static inline void get_alt_fwbs(unsigned char *data, 
				alt_front_wiping_brake_switch_t *p)
{ 
	p->front_wiping = ((data[2] & 0xE0) >> 5) & 0x07; 
	p->brake_switch = ((data[4] & 0x30) >> 4) & 0x03; 
}

/**
 *	ALT Turn Signal, Ignition
 *	Message ID 0x60D
 *	Transmitted 100 ms after event
 */
typedef struct {
	timestamp_t ts;
	unsigned char turn_signal;	// Byte 1, bits 7-5
	unsigned char turn_signal_filt;	// Filtered turn signal. ("turn_signal" 
				        // blinks ON/OFF with the state of the relay;
					// This signal filters out that blinking.)
	int ms_since_last_on;			
	unsigned char ignition;	/// Byte 1, bit 2 
} alt_turn_signal_ignition_t;

#define TURNSIG_TIMEOUT 750
#define TS_LR_OFF	0	/// left and right flashing indicators off
#define TS_LON_ROFF	1	/// left flashing indicator on and right off 
#define TS_LOFF_RON	2	/// left flashing indicator off and right ON 
#define TS_LR_ON	3	/// left and right on

#define FW_ONE_WIPE_HI		3	/// one high speed wiping requested
#define FW_RES1			4	/// invalid
#define FW_RES2			5	/// invalid
#define FW_LOW_REQUEST		6	/// low speed wiping requested
#define FW_HI_REQUEST		7	/// hi speed wiping requested

#define IGNITION_OFF		0	/// ignition supply off 
#define IGNITION_ON		1	/// ignition supply on

static inline void get_alt_tsi(unsigned char *data, 
				alt_turn_signal_ignition_t *p)
{ 
	p->turn_signal = ((data[1] & 0xE0) >> 5) & 0x07; 
	p->ignition = ((data[1] & 0x04) >> 2) & 0x01; 
}


/**
 *	OBD2 Commanded Equivalence Ratio poll
 *	ECM OBD message poll ID 0x07DF 
 *	Message ID (byte 2) 0x044
 *	Polled 
 */
typedef struct {
	unsigned short obd2_poll_id;// =0x07DF
	unsigned char num_more_bytes;// =0x02
	unsigned char mode;	// =0x01, current data
	unsigned char cer_pid;	// =0x44
	unsigned char padding[5]; //Padding to make this a 10-byte CAN message
} IS_PACKED obd2_cer_poll_t;

static inline void poll_obd_cer (obd2_cer_poll_t *p)
{ 
	p->obd2_poll_id = 0x07DF; 
	p->num_more_bytes = 2; 
	p->mode = 1; 
	p->cer_pid = 0x44; 
	p->padding[0] = 0; 
	p->padding[1] = 0; 
	p->padding[2] = 0; 
	p->padding[3] = 0; 
	p->padding[4] = 0; 
}

/**
 *	OBD2 Commanded Equivalence Ratio poll
 *	ECM OBD message ID 0x07E8 
 *	Message ID (byte 2) 0x044
 *	Polled 
 */
typedef struct {
	timestamp_t ts;
	unsigned char num_more_bytes;// =0x04
	unsigned char cer_pid;	// =0x44
	unsigned char mode;	// =0x41
	float cer;	/// Byte 3-4
} obd2_cer_t;

static inline void get_obd_cer(unsigned char *data, 
				obd2_cer_t *p)
{ 
	p->num_more_bytes = data[0]; 
	p->mode = data[1]; 
	p->cer_pid = data[2]; 
	p->cer = ((data[3] << 8) + data[4])/32768.0; 
}

/**
 *	OBD2 Mass AirFlow sensor poll
 *	ECM OBD message poll ID 0x07DF 
 *	Message ID (byte 2) 0x010
 *	Polled 
 */
typedef struct {
	unsigned short obd2_poll_id;// =0x07DF
	unsigned char num_more_bytes;// =0x02
	unsigned char mode;	// =0x01, current data
	unsigned char maf_pid;	// =0x10
	unsigned char padding[5]; //Padding to make this a 10-byte CAN message
} IS_PACKED obd2_maf_poll_t;

static inline void poll_obd_maf(obd2_maf_poll_t *p)
{ 
	p->obd2_poll_id = 0x07DF; 
	p->num_more_bytes = 2; 
	p->mode = 1; 
	p->maf_pid = 0x10; 
	p->padding[0] = 0; 
	p->padding[1] = 0; 
	p->padding[2] = 0; 
	p->padding[3] = 0; 
	p->padding[4] = 0; 
}

/**
 *	OBD2 Mass AirFlow sensor response
 *	ECM OBD message ID 0x07e8 
 *	Message ID (byte 2) 0x010
 *	Polled 
 */
typedef struct {
	timestamp_t ts;
	unsigned char num_more_bytes;// =0x04
	unsigned char maf_pid;	// =0x10
	unsigned char mode;	// =0x41
	float maf;	/// Byte 3-4
	float fuel_rate;/// grams fuel/second=MAF/CER
} obd2_maf_t;

static inline void get_obd_maf(unsigned char *data, 
				obd2_maf_t *p)
{ 
	p->num_more_bytes = data[0]; 
	p->mode = data[1]; 
	p->maf_pid = data[2]; 
	p->maf = ((data[3] << 8) + data[4])/100.0; 
}
