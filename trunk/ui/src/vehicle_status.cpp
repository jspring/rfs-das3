/**\file
 *
 * vehicle_status.cpp:  This program provides an engineering display of 
 *			vehicle status and experiment status for several
 *			vehicles and several experiments.  It is run on	
 *			the engineering computer, and the screen output
 *			is piped to the video computer to be recorded as
 *			1 of the 4 video inputs.  This program provides
 *			for time and date stamping on the video, as well as
 *			an idea of what the vehicle is currently doing.
 *		
 * This display much be started with a flag specifying the target vehicle:
 * (-c altima) Nissan Altimas
 * (-c audi) Audi A3s
 *
 */


// Always Include (C++ Headers)
#include <sys_os.h>
#include <tilcon_utils.h>

extern "C" {
// Always Include (C Headers)
#include <sys_rt.h>
#include <db_clt.h>
#include <db_utils.h>
#include <timestamp.h>

// Includes C Headers That Provide Specific Data Definitions For This App
#include <vehicle_status.h>
#include <evt300.h>
#include <path_gps_lib.h>
#include <uimu.h>
}


/**\ Tilcon Application Defaults */
char *main_window_file = "vehicle_status";
char *main_window_id = "vehicle_status";
char *start_kernel_string = "vehicle_status";
char *app_tilcon_dir = "/home/das3/ui/twd";
static int vehicle_platform = 0;


/**\ Application Constants
 *
 * Format: #define VariableName Value
 * Format: char *VariableName = "Text";
 *
 */
#define UNKNOWN 0
#define ALTIMA 1
#define AUDI 2

#define MPS2MPH(x)	((x)*2.236936)
#define MPH2MPS(x)	((x)/2.236936)
#define KPH2MPH(x)	((x)*0.62137119)

/**\ Custom Color Definitions for this Application Only
 *
 * Color definitons common to all aps go in '/home/path/tilcon/widget.h'
 * and include the following common colors:
 *
 * Basic Color Definitions
 #define AMBER			TRT_RGB(255,190,0)
 #define BLACK			TRT_RGB(0,0,0)
 #define BLUE255		TRT_RGB(0,0,255)
 #define GREEN255		TRT_RGB(0,255,0)
 #define GREEN128		TRT_RGB(0,128,0)
 #define MAROON			TRT_RGB(128,0,0)
 #define RED255			TRT_RGB(255,0,0)
 #define WHITE			TRT_RGB(255,255,255)
 #define SPEEDOMETER_ORANGE	TRT_RGB(255,65,0)
 #define TRANSPARENT		TRT_Transparent
 *
 * Common Greyscale Definitions
 #define GREY32                  TRT_RGB(32,32,32)	// Really Dark Grey
 #define GREY69                  TRT_RGB(69,69,69)	// Dark Grey
 #define GREY162                 TRT_RGB(162,162,162)	// Background Grey
 #define GREY192                 TRT_RGB(192,192,192)	// Button Grey
 *
 * Enter Any Custom Color Definitions for this app only below.
 *
 */


static jmp_buf exit_env;

static int sig_list[]= {
	SIGINT,
	SIGQUIT,
	SIGTERM,
	SIGALRM,	// for timer
	ERROR
};

static void sig_hand( int code )
{
	if (code == SIGALRM)
		return;
	else
		longjmp( exit_env, code );
}


/** Function Declares */

// Always Needed for Tilcon
static void init_widgets(pid_t cid);
static void application_set_tilcon(pid_t cid, void *data);

// Application Specific Functions
static int set_vehicle_platform(char *user_input);
static int get_timeout_counter(float newvalue, float oldvalue, int oldcount);


/** Widgets used in this application */

// Dashboard
tilcon_widget_t radar_w;
tilcon_widget_t throttle_w;
tilcon_widget_t cruise_w;

tilcon_widget_t vehicle_w;
tilcon_widget_t veh_error_w;
tilcon_widget_t ignition_w;
tilcon_widget_t turn_signal_left_w;
tilcon_widget_t turn_signal_right_w;
tilcon_widget_t speedometer_body_w;
tilcon_widget_t speed_w;
tilcon_widget_t gear_w;
tilcon_widget_t brake_w;

tilcon_widget_t gps_heading_w;
tilcon_widget_t gps_status_w;
tilcon_widget_t yaw_rate_w;

// Timestamp Panel
tilcon_widget_t date_w;
tilcon_widget_t timestamp_w;

/* used in all functions, set in main; for debugging */
static int verbose = 0;

/* Global because it must be accessed by the callback function 
 * which has a fixed calling sequence.
 */
db_clt_typ *pclt;

static db_id_t db_vars_list[] = {
        };

#define NUM_DB_VARS sizeof(db_vars_list)/sizeof(db_id_t)

int main(int argc, char *argv[])
{

	int errorcode = 0;
	char *domain = DEFAULT_SERVICE;
	char hostname[MAXHOSTNAMELEN +1];		
	pid_t tilcon_cid;	//channel id for connection with Tilcon kernel
	tilcon_callback_t veh_stat_callback; 
	int trt_val;	// returned by wait on TRT_GetInput (Tilcon receive)
	TRT_ReceiveData	rec_data;       
	long blocking_flag = TRT_BLOCK;	// make non-blocking and set our timer?
	long full_queue	= FALSE;
	long *trt_list = (long int *) NULL; // semaphore list, not used on QNX6
	long list_size		= 0;
	char *buff = (char *) NULL; // holds message if non-Tilcon message rec'd
	long buff_size		= 0;
	int option;
	char *veh_str = "unknown";
	char *exp_str = "none";
	
	/* Read and interpret any user switches. */

	while ((option = getopt(argc, argv, "c:d:e:f:i:p:v")) != EOF) {
		switch(option) {
		case 'c':
			veh_str = strdup(optarg);
			set_vehicle_platform(veh_str);
			break;
		case 'd':
			domain = strdup(optarg);
			break;
		case 'f':
			main_window_file = strdup(optarg);
			break;
		case 'i':
			main_window_id = strdup(optarg);
			break;
		case 'p':
			app_tilcon_dir = strdup(optarg);
			break;
		case 'v':
			verbose = 1;
			break;
	        default:
			printf( "Usage %s: -d domain -f twd file name ",
				argv[0]);
			printf( "-w main window ID -i image directory\n");
			exit(EXIT_FAILURE);
	        }
	}

	if ((tilcon_cid =tilcon_start_kernel(start_kernel_string, argv[0], 0)) == -1)
		exit(EXIT_FAILURE);

	veh_stat_callback.set_values = application_set_tilcon;

	veh_stat_callback.data = NULL;

	if (errorcode = tilcon_init_app(tilcon_cid, 2, app_tilcon_dir, 
				main_window_file, main_window_id, 0, 3)) {

		printf("Failed to initialized Tilcon application. error code %d\n", 
		       errorcode);
		exit(EXIT_FAILURE);
	}

	get_local_name(hostname, MAXHOSTNAMELEN);
        pclt = db_list_init( argv[0], hostname, domain, COMM_OS_XPORT, 
			    db_vars_list, NUM_DB_VARS, (int *)NULL, 0);

       /* exit environment set up after Tilcon initialization */

        if (setjmp(exit_env) != 0) {		
		if (pclt != NULL)
			db_list_done(pclt, db_vars_list, NUM_DB_VARS, 
				     (int *)NULL, 0);
			clt_logout(pclt);
		errorcode =tilcon_exit(tilcon_cid, main_window_id);
		printf("%s exiting, Tilcon error %d\n", argv[0], errorcode);
                exit(EXIT_SUCCESS);
        } else
                sig_ign(sig_list, sig_hand);

	init_widgets(tilcon_cid);
	if (verbose) { 
		printf("%s : initialization completed\n", argv[0]);
		fflush(stdout);
	}

	/** Check TRT_GetInput() to see if a Tilcon event occurred, if
	 * a semaphore was changed, or if a message was received from
	 * another process (e.g. a database trigger or a timer). 
	 * Break out of loop on error.
	 */

	while (TRUE) {
		trt_val = TRT_GetInput(trt_list, list_size, buff, buff_size, 
				&rec_data, blocking_flag);

		/** For a 'notification' from the Tilcon Kernel, c=0.  */

		if (trt_val == 0) {
			if (!tilcon_process_notify(tilcon_cid, &rec_data, 
				&full_queue, &errorcode, &veh_stat_callback,
				main_window_id))
				break;
		} else if ( trt_val == -1 ) {
			/** if c=-1, an error occurred if blocking
			  * (or nothing was waiting, for TRT_NO_BLOCK) 
			  */

			if (blocking_flag == TRT_BLOCK)
				break;

		} else {

		/** Otherwise, a message was received from another process or
		 *if 1, TRT_GetInput took care of calling a callback 
		 * otherwise trt_val is channel id of message 
		 * No action on this branch for now; later, we may learn
		 * how to use Tilcon callbacks or handle timers here.
		 */
			printf("Unknown message received, trt_val %d\n",
				 trt_val);
		}
	}	// end of main loop //
	longjmp(exit_env,1);
	return 0;
}

/**\ Widget Initialization
 *
 * Notes on object parameters:
 *
 * tilcon_init_button(cid, &objectname_w, "objectname", "button text", 
 *		      in_fill_color, out_fill_color);
 *
 * tilcon_init_drawing(cid, &objectname_w, "objectname", fill_color, line_color);
 *
 * tilcon_init_meter(cid, &objectname_w, "objectname", value, precision,
 *                   indicator_fill_color);
 * 
 * tilcon_init_meter_alarm(cid, &objectname_w, "objectname", low_color, 
 *                         mid_color, high_color, start_at, low_to, mid_to, 
 *                         high_to, precision);
 *
 * tilcon_init_multistate(cid, &objectname_w, "objectname", value);
 * 
 * tilcon_init_text(cid, &objectname_w, "objectname", "Char");
 *
 * tilcon_init_dbl_text(cid, &objectname_w, "objectname", value, format, 
 *                      precision);
 *
 * tilcon_init_int_text(cid, &objectname_w, "objectname", value, format);
 *
 * Note: Needles are treated as meters with TRANSPARENT as Indicator Fill
 * Note: Treat Colorstate Objects as Multistate Ones
 *
 * Format: %5.1f = 5 characters total with 1 digit shown after the decimel
 * Example: "Leading Text  %5.1f Trailing Text"
 *
 */
	 
static void init_widgets(pid_t cid)
{
	
	// Dashboard
	tilcon_init_multistate(cid, &radar_w, "radar", 0);
	tilcon_init_meter(cid, &throttle_w, "throttle", 100.0, 0.1, GREEN128);
	tilcon_init_multistate(cid, &cruise_w, "cruise", 2);
	
	tilcon_init_text(cid, &vehicle_w,"vehicle", "Vehicle Status");
	tilcon_init_text(cid, &veh_error_w, "veh_error", 
			 "Vehicle Platform Unknown");
	tilcon_init_multistate(cid, &ignition_w, "ignition", 2);
	tilcon_init_multistate(cid, &turn_signal_left_w, "turn_signal_left", 0);
	tilcon_init_multistate(cid, &turn_signal_right_w, 
			       "turn_signal_right", 0);
	tilcon_init_meter_alarm(cid, &speedometer_body_w, "speedometer_body",
				BLACK,BLACK,BLACK,0,0,0,0,1);
	tilcon_init_meter(cid, &speed_w, "speed", 100.0, 1.0, TRANSPARENT);
	tilcon_init_text(cid, &gear_w, "gear", "P");
	tilcon_init_multistate(cid, &brake_w, "brake", 2);
	
	tilcon_init_meter(cid, &gps_heading_w, "gps_heading", 
			  90, 1, TRANSPARENT);
	tilcon_init_multistate(cid, &gps_status_w, "gps_status", 0);
	tilcon_init_meter(cid, &yaw_rate_w, "yaw_rate", 
			  60.0, 1.0, TRANSPARENT);
	
	// Timestamp Panel
	tilcon_init_text(cid, &date_w, "date", "00/00/00");
	tilcon_init_text(cid, &timestamp_w, "timestamp", "00:00:00.0");
	
}


/**\ application_set_tilcon()
 *
 * This function continually sets the values for Tilcon objects.
 *
 * Tilcon Commands Help
 *
 * tilcon_hide/unhide(cid, &name_w);
 * tilcon_dim/undim(cid, &name_w);
 * tilcon_set_type(cid, &name_w, parameters);
 *
 * Parameter List by Object Type:
 *
 * tilcon_set_button(cid, &name_w, label_char, in_fill_color, out_fill_color);
 * tilcon_set_drawing(cid, &name_w, fill_color, line_color);
 * tilcon_set_meter(cid, &name_w, value, indicator_fill_color);
 * tilcon_set_meter_alarm(cid, &name_w, low_color, mid_color, high_color, 
 *                        start_at, low_to, mid_to, high_to);
 * tilcon_set_multistate(cid, &name_w, value);
 * tilcon_set_text(cid, &name_w, char_array);
 * tilcon_set_dbl_text(cid, &name_w, value);
 * tilcon_set_int_text(cid, &name_w, value);
 *
 * Note: Needles use tilcon_set_meter with TRANSPARENT as Indicator Fill
 * Note: Colorstate Objects use tilcon_set_multistate();
 *
 */
static void application_set_tilcon(pid_t cid, void *data)
{

	/**\ Declarations Syntax
	 *
	 * (static) double name;
	 * (static) int name;
	 * (static) char name[length];
	 * struct_t db_name;
	 *
	 */
		
	// Time & Date
	char ts[80];
	int month;
	int day;
	int year;
	char date[80];
	timestamp_t now;	// path/local/timestamp.h
	
	// Radar
	static float last_radar_ts;
	static int radar_timeout=0;
	
	// GPS
	static float last_gps_ts;
	static int gps_timeout=0;
	
	// Platform-Specific Vehicle Data
	tilcon_veh_status_t db_veh;
	
	
	/** Datahub Variable Type Declarations */
	evt300_radar_typ db_evt300;	// path/sens/radar/evt300.h
	path_gps_point_t db_gps;	// path/sens/gps/path_gps_lib.h
	uimu_typ db_uimu;		// path/sens/gyro/memsense/src/uimu.h
	
	
	/** Time Reads */
	get_current_timestamp(&now);
	get_todays_date(&month, &day, &year);
	
	
	/** Datahub Reads */
	db_clt_read(pclt, DB_EVT300_RADAR1_TYPE, sizeof(db_evt300), &db_evt300);
	db_clt_read(pclt, DB_GPS_PT_LCL_VAR, sizeof(db_gps), &db_gps);
	db_clt_read(pclt, DB_UIMU_VAR, sizeof(db_uimu), &db_uimu);
	
	
	/** Update Timestamp Panel Widgets */
	
	// Date Display
	year = year - 2000;
	snprintf(date, 80, "%02d/%02d/%02d", month, day, year);
	tilcon_set_text(cid, &date_w, date);
	
	/* Timestamp Display
	 *
	 * Timestamp comes in a 13 character format of HH:MM:SS.XXX
	 * Only want to display the first 10 characters.
	 *
	 */
	timestamp2str(&now, ts);
	ts[10] = '\0';
	tilcon_set_text(cid, &timestamp_w, ts);
	
	
	/** Update Dashboard Panel Widgets that are not Vehicle Dependent */
	
	// Radar
	radar_timeout = get_timeout_counter(TS_TO_SEC(&db_evt300.ts), 
					    last_radar_ts, radar_timeout);
	last_radar_ts = TS_TO_SEC(&db_evt300.ts);
	if (radar_timeout < 20) {
		tilcon_set_multistate(cid, &radar_w, 1);
	} else {
		// No new data for 1 second
		tilcon_set_multistate(cid, &radar_w, 0);
	}
	
	// GPS / Satellite Counter / Heading
	// Check for Timeout
	gps_timeout = get_timeout_counter(TS_TO_SEC(&db_gps.utc_time), 
					  last_gps_ts, gps_timeout);
	last_gps_ts = TS_TO_SEC(&db_gps.utc_time);
	if (gps_timeout > 40) {
		// No new data for 2 seconds
		tilcon_set_multistate(cid, &gps_status_w, 0);
		tilcon_hide(cid, &gps_heading_w);
	} else if (db_gps.num_sats < 5) {
		// New data but poor gps coverage
		tilcon_set_multistate(cid, &gps_status_w, 1);
		tilcon_unhide(cid, &gps_heading_w);
	} else {
		// Good GPS
		tilcon_set_multistate(cid, &gps_status_w, 2);
		tilcon_unhide(cid, &gps_heading_w);
	}
	tilcon_set_meter(cid, &gps_heading_w, db_gps.heading, TRANSPARENT);
	
	// Yaw Rate
	tilcon_set_meter(cid, &yaw_rate_w, 
			 db_uimu.zgyro*6.8665*.001, TRANSPARENT);
	
	
	/** Update Vehicle Dependent Dashboard Panel Widgets */
	
	// Read Vehicle Dependent Data from the Datahub
	memset(&db_veh, 0, sizeof(tilcon_veh_status_t));
	switch (vehicle_platform) {
		case ALTIMA:
			db_veh = get_altima_vehicle_status(pclt);
			break;
		case AUDI:
			db_veh = get_audi_vehicle_status(pclt);
			break;
		case UNKNOWN:
		default:
			vehicle_platform = UNKNOWN;
			break;
	}
	
	// Corrections for Suspected CAN Read Errors
	if (db_veh.speed == 0) {
		db_veh.speed = MPS2MPH(db_gps.speed);
	}
	if (db_veh.gear == 0) {
		db_veh.gear = '?';
	}
	
	// Vehicle Platform Labels
	switch (vehicle_platform) {
		case ALTIMA:
			tilcon_set_text(cid, &vehicle_w, "Altima Status");
			break;
		case AUDI:
			tilcon_set_text(cid, &vehicle_w, "A3 Status");
			break;
		case UNKNOWN:
		default:
			tilcon_set_text(cid, &vehicle_w, "Unknown Car");
			break;
	}
		
	// Ignition & TS & Throttle & Cruise & Brake
	tilcon_set_multistate(cid, &ignition_w, db_veh.ign);
	tilcon_set_multistate(cid, &turn_signal_left_w, db_veh.left_turn_sig);
	tilcon_set_multistate(cid, &turn_signal_right_w, db_veh.right_turn_sig);
	tilcon_set_meter(cid, &throttle_w, db_veh.throttle, GREEN128);
	tilcon_set_multistate(cid, &cruise_w, db_veh.cc);
	tilcon_set_multistate(cid, &brake_w, db_veh.brake);
	
	// Speedometer & Gear Indicator
	tilcon_set_meter(cid, &speed_w, db_veh.speed, TRANSPARENT);
	tilcon_set_text(cid, &gear_w, &db_veh.gear);
	
}


/**\ Function set_vehicle_platform
 *
 * If a CLI -c flag is given, this function parses the user input.
 *  
 */
static int set_vehicle_platform(char *user_input)
{
	if (strcmp(user_input,"altima") == 0) {
		vehicle_platform = ALTIMA;
	} else if (strcmp(user_input,"audi") == 0) {
		vehicle_platform = AUDI;
	} else {
		vehicle_platform = UNKNOWN;
	}
	return vehicle_platform;
}


		
/**\ Function get_timeout_counter
 *
 * This function checks for a timeout event.  If it returns 0, then the data
 * is new.  Otherwise, the data is as old as the number of counts.
 */
static int get_timeout_counter(float newvalue, float oldvalue, int oldcount)
{
	int newcount=0;
	
	if (newvalue == oldvalue) {
		newcount = ((oldcount + 1) < 10000) ? (oldcount + 1) : 10000;
		return newcount;
	} else {
		return newcount;
	}
}
