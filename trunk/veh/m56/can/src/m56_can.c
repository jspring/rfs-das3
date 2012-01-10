#include "db_include.h"
#include "komodo.h"
#include "m56_can.h"

static jmp_buf exit_env;
static int sig_list[] = {
        SIGINT,
        SIGQUIT,
        SIGTERM,
        SIGALRM,
        ERROR,
};
static void sig_hand(int code)
{
        if (code == SIGALRM)
                return;
        else
                longjmp(exit_env, code);
}

const char *usage = "-v verbose";

db_id_t db_vars_list[] =  {
        {DB_M56_VCAN2_MSG002_VAR, sizeof(m56_steering_t)},
        {DB_M56_VCAN2_MSG174_VAR, sizeof(m56_gear_t)},
        {DB_M56_VCAN2_MSG180_VAR, sizeof(m56_engine_rpm_t)},
        {DB_M56_VCAN2_MSG1c3_VAR, sizeof(m56_its_alive_t)},
        {DB_M56_VCAN2_MSG239_VAR, sizeof(m56_pedal_position_t)},
        {DB_M56_VCAN2_MSG284_VAR, sizeof(m56_wheel_speed_front_t)},
        {DB_M56_VCAN2_MSG285_VAR, sizeof(m56_wheel_speed_rear_t)},
        {DB_M56_VCAN2_MSG292_VAR, sizeof(m56_acceleration_t)},
        {DB_M56_VCAN2_MSG2aa_VAR, sizeof(m56_acc_status_t)},
        {DB_M56_VCAN2_MSG2b0_VAR, sizeof(m56_eng_tq_acc_and_brake_flags_t)},
        {DB_M56_VCAN2_MSG2b3_VAR, sizeof(m56_dashboard_indicators_t)},
        {DB_M56_VCAN2_MSG354_VAR, sizeof(m56_abs_status_t)},
        {DB_M56_VCAN2_MSG358_VAR, sizeof(m56_turn_switch_status_t)},
        {DB_M56_VCAN2_MSG421_VAR, sizeof(m56_atcvt_t)},
        {DB_M56_VCAN2_MSG5b0_VAR, sizeof(m56_transmission_mode_t)},
        {DB_M56_VCAN2_MSG625_VAR, sizeof(m56_front_wiper_status_t)},
        {DB_M56_ITSCAN_MSG52b_VAR, sizeof(m56_lidar_target_t)},
        {DB_M56_ITSCAN_MSG52c_VAR, sizeof(m56_yaw_rate_t)},
        {DB_M56_ITSCAN_MSG52d_VAR, sizeof(m56_lidar_status_t)},
	{DB_M56_IGNITION_VAR, sizeof(m56_ignition_status_t)},
        {DB_M56_VCAN2_MSG210_VAR, sizeof(m56_vdne491_m210_t)},
        {DB_M56_VCAN2_MSG211_VAR, sizeof(m56_vdne491_m211_t)},
        {DB_M56_VCAN2_MSG212_VAR, sizeof(m56_vdne491_m212_t)},
        {DB_M56_VCAN2_MSG213_VAR, sizeof(m56_vdne491_m213_t)},
        {DB_M56_VCAN2_MSG214_VAR, sizeof(m56_vpro4_m214_t)},
        {DB_M56_VCAN2_MSG215_VAR, sizeof(m56_vpro4_m215_t)},
        {DB_M56_VCAN2_MSG216_VAR, sizeof(m56_vpro4_m216_t)},
        {DB_M56_VCAN2_MSG217_VAR, sizeof(m56_vpro4_m217_t)},
        {DB_M56_VCAN2_MSG218_VAR, sizeof(m56_vdnc304_m218_t)},
        {DB_M56_VCAN2_MSG219_VAR, sizeof(m56_vdnc304_m219_t)},
        {DB_M56_VCAN2_MSG21a_VAR, sizeof(m56_vdnc304_m21a_t)},
        {DB_M56_VCAN2_MSG21b_VAR, sizeof(m56_vdnc304_m21b_t)},
        {DB_M56_VCAN2_MSG21c_VAR, sizeof(m56_vpro4_m21c_t)},
        {DB_M56_VCAN2_MSG21d_VAR, sizeof(m56_vpro4_m21d_t)},
        {DB_M56_VCAN2_MSG21e_VAR, sizeof(m56_vpro4_m21e_t)},
        {DB_M56_VCAN2_MSG21f_VAR, sizeof(m56_vpro4_m21f_t)},
        {DB_M56_VCAN2_MSG289_VAR, sizeof(m56_adas_289_t)},
        {DB_M56_VCAN2_MSG28a_VAR, sizeof(m56_adas_28a_t)},
};

int num_db_variables = sizeof(db_vars_list)/sizeof(db_id_t);
int db_trig_list[] =  {
        DB_KOMODO_VAR
};

int num_trig_variables = sizeof(db_trig_list)/sizeof(db_id_t);

int main(int argc, char *argv[]) {
	int verbose = 0;
	int print_msg = 0;
	int option;
	int count = 0;
	int create_db_vars = 0;

        char hostname[MAXHOSTNAMELEN];
        char *domain = DEFAULT_SERVICE; /// on Linux sets DB q-file directory
        db_clt_typ *pclt;               /// data server client pointer
        int xport = COMM_OS_XPORT;      /// value set correctly in sys_os.h
	db_komodo_t db_kom;
	timestamp_t ts;
	int ts_ms;

	m56_engine_rpm_t m56_engine_rpm;
	m56_gear_t m56_gear;
	m56_its_alive_t m56_its_alive;
	m56_pedal_position_t m56_pedal_position;
	m56_wheel_speed_front_t m56_wheel_speed_front;
	m56_wheel_speed_rear_t m56_wheel_speed_rear;
        m56_steering_t m56_steering;
        m56_acceleration_t m56_acceleration;
        m56_acc_status_t m56_acc_status;
	m56_eng_tq_acc_and_brake_flags_t m56_eng_tq_acc_and_brake_flags;
	m56_dashboard_indicators_t m56_dashboard_indicators;
	m56_abs_status_t m56_abs_status;
	m56_turn_switch_status_t m56_turn_switch_status;
	m56_atcvt_t m56_atcvt;
	m56_transmission_mode_t m56_transmission_mode;
	m56_front_wiper_status_t m56_front_wiper_status;
	m56_lidar_target_t m56_lidar_target;
	m56_yaw_rate_t m56_yaw_rate;
	m56_lidar_status_t m56_lidar_status;
	m56_ignition_status_t m56_ignition_status;
	m56_vdne491_m210_t m56_vdne491_m210;
	m56_vdne491_m211_t m56_vdne491_m211;
	m56_vdne491_m212_t m56_vdne491_m212;
	m56_vdne491_m213_t m56_vdne491_m213;
	m56_vpro4_m214_t m56_vpro4_m214;
	m56_vpro4_m215_t m56_vpro4_m215;
	m56_vpro4_m216_t m56_vpro4_m216;
	m56_vpro4_m217_t m56_vpro4_m217;
	m56_vdnc304_m218_t m56_vdnc304_m218;
	m56_vdnc304_m219_t m56_vdnc304_m219;
	m56_vdnc304_m21a_t m56_vdnc304_m21a;
	m56_vdnc304_m21b_t m56_vdnc304_m21b;
	m56_vpro4_m21c_t m56_vpro4_m21c;
	m56_vpro4_m21d_t m56_vpro4_m21d;
	m56_vpro4_m21e_t m56_vpro4_m21e;
	m56_vpro4_m21f_t m56_vpro4_m21f;
	m56_adas_289_t m56_adas_289;
	m56_adas_28a_t m56_adas_28a;

        while ((option = getopt(argc, argv, "vc")) != EOF) {
                switch(option) {
                case 'v':
                        verbose = 1;
                        break;
                case 'c':
                        create_db_vars = 1;
                        break;
                default:
                        printf("Usage: %s %s\n", argv[0], usage);
                        exit(EXIT_FAILURE);
                        break;
                }
        }
        get_local_name(hostname, MAXHOSTNAMELEN);
        if ( create_db_vars && ((pclt = db_list_init(argv[0], hostname, domain, 
	    xport, db_vars_list, num_db_variables, db_trig_list, 
	    num_trig_variables)) == NULL)) 
	{
            exit(EXIT_FAILURE);
        } else {
            if ( (pclt = db_list_init(argv[0], hostname, domain, xport,
	        NULL, 0, db_trig_list, num_trig_variables)) 
		== NULL) {
                exit(EXIT_FAILURE);
	    }
	}
        if (setjmp(exit_env) != 0) {
                db_list_done(pclt, db_vars_list, num_db_variables, NULL, 0);
                printf("%s: received %d CAN messages\n", argv[0], count);
                exit(EXIT_SUCCESS);
        } else
               sig_ign(sig_list, sig_hand);

	/* Zero data structures */
	memset(&m56_steering, 0, sizeof(m56_steering_t));
	memset(&m56_engine_rpm, 0, sizeof(m56_engine_rpm_t));
	memset(&m56_gear, 0, sizeof(m56_gear_t));
	memset(&m56_its_alive, 0, sizeof(m56_its_alive_t));
	memset(&m56_pedal_position, 0, sizeof(m56_pedal_position_t));
	memset(&m56_wheel_speed_front, 0, sizeof(m56_wheel_speed_front_t));
	memset(&m56_wheel_speed_rear, 0, sizeof(m56_wheel_speed_rear_t));
	memset(&m56_acceleration, 0, sizeof(m56_acceleration_t));
	memset(&m56_acc_status, 0, sizeof(m56_acc_status_t));
	memset(&m56_eng_tq_acc_and_brake_flags, 0, 
		sizeof(m56_eng_tq_acc_and_brake_flags_t));
	memset(&m56_dashboard_indicators, 0, 
		sizeof(m56_dashboard_indicators_t));
	memset(&m56_abs_status, 0, sizeof(m56_abs_status_t));
	memset(&m56_turn_switch_status, 0, sizeof(m56_turn_switch_status_t));
	memset(&m56_atcvt, 0, sizeof(m56_atcvt_t));
	memset(&m56_transmission_mode, 0, sizeof(m56_transmission_mode_t));
	memset(&m56_front_wiper_status, 0, sizeof(m56_front_wiper_status_t));
	memset(&m56_lidar_target, 0, sizeof(m56_lidar_target_t));
	memset(&m56_yaw_rate, 0, sizeof(m56_yaw_rate_t));
	memset(&m56_lidar_status, 0, sizeof(m56_lidar_status_t));
	memset(&m56_ignition_status, 0, sizeof(m56_ignition_status_t));
	memset(&m56_vdne491_m210, 0, sizeof(m56_vdne491_m210_t));
	memset(&m56_vdne491_m211, 0, sizeof(m56_vdne491_m211_t));
	memset(&m56_vdne491_m212, 0, sizeof(m56_vdne491_m212_t));
	memset(&m56_vdne491_m213, 0, sizeof(m56_vdne491_m213_t));
	memset(&m56_vpro4_m214, 0, sizeof(m56_vpro4_m214_t));
	memset(&m56_vpro4_m215, 0, sizeof(m56_vpro4_m215_t));
	memset(&m56_vpro4_m216, 0, sizeof(m56_vpro4_m216_t));
	memset(&m56_vpro4_m217, 0, sizeof(m56_vpro4_m217_t));
	memset(&m56_vdnc304_m218, 0, sizeof(m56_vdnc304_m218_t));
	memset(&m56_vdnc304_m219, 0, sizeof(m56_vdnc304_m219_t));
	memset(&m56_vdnc304_m21a, 0, sizeof(m56_vdnc304_m21a_t));
	memset(&m56_vdnc304_m21b, 0, sizeof(m56_vdnc304_m21b_t));
	memset(&m56_vpro4_m21c, 0, sizeof(m56_vpro4_m21c_t));
	memset(&m56_vpro4_m21d, 0, sizeof(m56_vpro4_m21d_t));
	memset(&m56_vpro4_m21e, 0, sizeof(m56_vpro4_m21e_t));
	memset(&m56_vpro4_m21f, 0, sizeof(m56_vpro4_m21f_t));
	memset(&m56_adas_289, 0, sizeof(m56_adas_289_t));
	memset(&m56_adas_28a, 0, sizeof(m56_adas_28a_t));

	m56_steering.two_message_periods = 20; 		// 2*10 msec
	m56_gear.two_message_periods = 20; 		// 2*10 msec
	m56_engine_rpm.two_message_periods = 20; 	// 2*10 msec
	m56_its_alive.two_message_periods = 20; 	// 2*10 msec
	m56_pedal_position.two_message_periods = 40; 	// 2*20 msec
	m56_wheel_speed_front.two_message_periods = 40; // 2*20 msec
	m56_wheel_speed_rear.two_message_periods = 40; 	// 2*20 msec
	m56_acceleration.two_message_periods = 40; 	// 2*20 msec
	m56_acc_status.two_message_periods = 40; 	// 2*20 msec
	m56_eng_tq_acc_and_brake_flags.two_message_periods = 20; // 2*10 msec
	m56_dashboard_indicators.two_message_periods = 40; // 2*20 msec
	m56_abs_status.two_message_periods = 80; 	// 2*40 msec
	m56_turn_switch_status.two_message_periods = 200;// 2*100 msec
	m56_atcvt.two_message_periods = 120;		// 2*60 msec
	m56_transmission_mode.two_message_periods = 200;// 2*100 msec
	m56_front_wiper_status.two_message_periods = 200; // 2*100 msec
	m56_lidar_target.two_message_periods = 200; 	// 2*100 msec
	m56_yaw_rate.two_message_periods = 200; 	// 2*100 msec
	m56_lidar_status.two_message_periods = 200; 	// 2*100 msec
	m56_vdne491_m210.two_message_periods = 200; 	// 2*100 msec
	m56_vdne491_m211.two_message_periods = 200; 	// 2*100 msec
	m56_vdne491_m212.two_message_periods = 200; 	// 2*100 msec
	m56_vdne491_m213.two_message_periods = 200; 	// 2*100 msec
	m56_vpro4_m214.two_message_periods = 200; 	// 2*100 msec
	m56_vpro4_m215.two_message_periods = 200; 	// 2*100 msec
	m56_vpro4_m216.two_message_periods = 200; 	// 2*100 msec
	m56_vpro4_m217.two_message_periods = 200; 	// 2*100 msec
	m56_vdnc304_m218.two_message_periods = 200; 	// 2*100 msec
	m56_vdnc304_m219.two_message_periods = 200; 	// 2*100 msec
	m56_vdnc304_m21a.two_message_periods = 200; 	// 2*100 msec
	m56_vdnc304_m21b.two_message_periods = 200; 	// 2*100 msec
	m56_vpro4_m21c.two_message_periods = 200; 	// 2*100 msec
	m56_vpro4_m21d.two_message_periods = 200; 	// 2*100 msec
	m56_vpro4_m21e.two_message_periods = 200; 	// 2*100 msec
	m56_vpro4_m21f.two_message_periods = 200; 	// 2*100 msec
	m56_adas_289.two_message_periods = 200; 	// 2*100 msec
	m56_adas_28a.two_message_periods = 200; 	// 2*100 msec

	db_clt_write(pclt,DB_M56_VCAN2_MSG002_VAR, 
		sizeof(m56_steering_t), &m56_steering); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG174_VAR, 
		sizeof(m56_gear_t), &m56_gear); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG180_VAR, 
		sizeof(m56_engine_rpm_t), &m56_engine_rpm); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG1c3_VAR, 
		sizeof(m56_its_alive_t), &m56_its_alive); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG239_VAR, 
		sizeof(m56_pedal_position_t), &m56_pedal_position); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG284_VAR, 
		sizeof(m56_wheel_speed_front_t), &m56_wheel_speed_front); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG285_VAR, 
		sizeof(m56_wheel_speed_rear_t), &m56_wheel_speed_rear); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG292_VAR, 
		sizeof(m56_acceleration_t), &m56_acceleration); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG2aa_VAR, 
		sizeof(m56_acc_status_t), &m56_acc_status); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG2b0_VAR, 
		sizeof(m56_eng_tq_acc_and_brake_flags_t), 
		&m56_eng_tq_acc_and_brake_flags); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG2b3_VAR, 
		sizeof(m56_dashboard_indicators_t), &m56_dashboard_indicators); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG354_VAR, 
		sizeof(m56_abs_status_t), &m56_abs_status); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG358_VAR, 
		sizeof(m56_turn_switch_status_t), &m56_turn_switch_status); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG421_VAR, 
		sizeof(m56_atcvt_t), &m56_atcvt); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG5b0_VAR, 
		sizeof(m56_transmission_mode_t), &m56_transmission_mode); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG625_VAR, 
		sizeof(m56_front_wiper_status_t), &m56_front_wiper_status); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG52b_VAR, 
		sizeof(m56_lidar_target_t), &m56_lidar_target); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG52c_VAR, 
		sizeof(m56_yaw_rate_t), &m56_yaw_rate); 
    	db_clt_write(pclt,DB_M56_ITSCAN_MSG52d_VAR, 
		sizeof(m56_lidar_status_t), &m56_lidar_status); 
    	db_clt_write(pclt,DB_M56_IGNITION_VAR, 
		sizeof(m56_ignition_status_t), &m56_ignition_status); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG210_VAR, 
		sizeof(m56_vdne491_m210_t), &m56_vdne491_m210); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG211_VAR, 
		sizeof(m56_vdne491_m211_t), &m56_vdne491_m211); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG212_VAR, 
		sizeof(m56_vdne491_m212_t), &m56_vdne491_m212); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG213_VAR, 
		sizeof(m56_vdne491_m213_t), &m56_vdne491_m213); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG214_VAR, 
		sizeof(m56_vpro4_m214_t), &m56_vpro4_m214); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG215_VAR, 
		sizeof(m56_vpro4_m215_t), &m56_vpro4_m215); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG216_VAR, 
		sizeof(m56_vpro4_m216_t), &m56_vpro4_m216); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG217_VAR, 
		sizeof(m56_vpro4_m217_t), &m56_vpro4_m217); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG218_VAR, 
		sizeof(m56_vdnc304_m218_t), &m56_vdnc304_m218); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG219_VAR, 
		sizeof(m56_vdnc304_m219_t), &m56_vdnc304_m219); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG21a_VAR, 
		sizeof(m56_vdnc304_m21a_t), &m56_vdnc304_m21a); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG21b_VAR, 
		sizeof(m56_vdnc304_m218_t), &m56_vdnc304_m21b); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG21c_VAR, 
		sizeof(m56_vpro4_m21c_t), &m56_vpro4_m21c); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG21d_VAR, 
		sizeof(m56_vpro4_m21d_t), &m56_vpro4_m21d); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG21e_VAR, 
		sizeof(m56_vpro4_m21e_t), &m56_vpro4_m21e); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG21f_VAR, 
		sizeof(m56_vpro4_m21f_t), &m56_vpro4_m21f); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG289_VAR, 
		sizeof(m56_adas_289_t), &m56_adas_289); 
	db_clt_write(pclt,DB_M56_VCAN2_MSG28a_VAR, 
		sizeof(m56_adas_28a_t), &m56_adas_28a); 

	for(;;) {
	   db_clt_read(pclt, DB_KOMODO_VAR, sizeof(db_komodo_t), &db_kom);
	   m56_ignition_status.ignition_status = db_kom.gpio & M56_IGNITION_MASK;
	   db_clt_write(pclt, DB_M56_IGNITION_VAR, sizeof(m56_ignition_status_t), &m56_ignition_status);
	   get_current_timestamp(&ts);
	   ts_ms = TS_TO_MS(&ts);
	   switch(db_kom.id) {
		case 0x002:
		    get_m56_steering(db_kom.msg, &m56_steering);
		    check_msg_timeout(ts_ms, &m56_steering.ts_ms, &m56_steering.two_message_periods, &m56_steering.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG002_VAR, 
			sizeof(m56_steering_t), &m56_steering); 
		    break;
		case 0x160:
		    break;
		case 0x174:
		    get_m56_gear(db_kom.msg, &m56_gear);
		    check_msg_timeout(ts_ms, &m56_gear.ts_ms, &m56_gear.two_message_periods, &m56_gear.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG174_VAR, 
			sizeof(m56_gear_t), &m56_gear); 
		    break;
		case 0x177:
		    break;
		case 0x180:
		    get_m56_engine_rpm(db_kom.msg, &m56_engine_rpm);
		    check_msg_timeout(ts_ms, &m56_engine_rpm.ts_ms, &m56_engine_rpm.two_message_periods, &m56_engine_rpm.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG180_VAR, 
			sizeof(m56_engine_rpm_t), &m56_engine_rpm); 
		    break;
		case 0x1c3:
		    get_m56_its_alive(db_kom.msg, &m56_its_alive);
		    check_msg_timeout(ts_ms, &m56_its_alive.ts_ms, &m56_its_alive.two_message_periods, &m56_its_alive.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG1c3_VAR, 
			sizeof(m56_its_alive_t), &m56_its_alive); 
		    break;
		case 0x239:
		    get_m56_pedal_position(db_kom.msg, &m56_pedal_position);
		    check_msg_timeout(ts_ms, &m56_pedal_position.ts_ms, &m56_pedal_position.two_message_periods, &m56_pedal_position.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG239_VAR, 
			sizeof(m56_pedal_position_t), &m56_pedal_position); 
		    break;
		case 0x245:
		    break;
		case 0x284:
		    get_m56_wheel_speed_front(db_kom.msg,&m56_wheel_speed_front);
		    check_msg_timeout(ts_ms, &m56_wheel_speed_front.ts_ms, &m56_wheel_speed_front.two_message_periods, &m56_wheel_speed_front.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG284_VAR, 
		      sizeof(m56_wheel_speed_front_t), &m56_wheel_speed_front); 
		    break;
		case 0x285:
		    get_m56_wheel_speed_rear(db_kom.msg, &m56_wheel_speed_rear);
		    check_msg_timeout(ts_ms, &m56_wheel_speed_rear.ts_ms, &m56_wheel_speed_rear.two_message_periods, &m56_wheel_speed_rear.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG285_VAR, 
			sizeof(m56_wheel_speed_rear_t), &m56_wheel_speed_rear); 
		    break;
		case 0x292:
		    get_m56_acceleration(db_kom.msg, &m56_acceleration);
		    check_msg_timeout(ts_ms, &m56_acceleration.ts_ms, &m56_acceleration.two_message_periods, &m56_acceleration.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG292_VAR, 
			sizeof(m56_acceleration_t), &m56_acceleration); 
		    break;
		case 0x2aa:
		    get_m56_acc_status(db_kom.msg, &m56_acc_status);
		    check_msg_timeout(ts_ms, &m56_acc_status.ts_ms, &m56_acc_status.two_message_periods, &m56_acc_status.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG2aa_VAR, 
			sizeof(m56_acc_status_t), &m56_acc_status); 
		    break;
		case 0x2b0:
                    get_m56_eng_tq_acc_and_brake_flags(db_kom.msg, 
			&m56_eng_tq_acc_and_brake_flags);
		    check_msg_timeout(ts_ms, &m56_eng_tq_acc_and_brake_flags.ts_ms, &m56_eng_tq_acc_and_brake_flags.two_message_periods, &m56_eng_tq_acc_and_brake_flags.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG2b0_VAR, 
			sizeof(m56_eng_tq_acc_and_brake_flags_t), 
			&m56_eng_tq_acc_and_brake_flags); 
		    break;
		case 0x2b3:
		    get_m56_dashboard_indicators(db_kom.msg,
			&m56_dashboard_indicators);
		    check_msg_timeout(ts_ms, &m56_dashboard_indicators.ts_ms, &m56_dashboard_indicators.two_message_periods, &m56_dashboard_indicators.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG2b3_VAR, 
			sizeof(m56_dashboard_indicators_t), &m56_dashboard_indicators); 
		    break;
		case 0x354:
                    get_m56_abs_status(db_kom.msg,
			&m56_abs_status);
		    check_msg_timeout(ts_ms, &m56_abs_status.ts_ms, &m56_abs_status.two_message_periods, &m56_abs_status.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG354_VAR, sizeof(m56_abs_status_t), &m56_abs_status); 
		    break;
		case 0x358:
                    get_m56_turn_switch_status(db_kom.msg,
			&m56_turn_switch_status);
		    check_msg_timeout(ts_ms, &m56_turn_switch_status.ts_ms, &m56_turn_switch_status.two_message_periods, &m56_turn_switch_status.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG358_VAR, 
			sizeof(m56_turn_switch_status_t), &m56_turn_switch_status); 
		    break;
		case 0x421:
                    get_m56_atcvt(db_kom.msg, &m56_atcvt);
		    check_msg_timeout(ts_ms, &m56_atcvt.ts_ms, &m56_atcvt.two_message_periods, &m56_atcvt.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG421_VAR, sizeof(m56_atcvt_t), &m56_atcvt); 
		    break;
		case 0x5b0:
                    get_m56_transmission_mode(db_kom.msg,
			&m56_transmission_mode);
		    check_msg_timeout(ts_ms, &m56_transmission_mode.ts_ms, &m56_transmission_mode.two_message_periods, &m56_transmission_mode.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG5b0_VAR, 
			sizeof(m56_transmission_mode_t), &m56_transmission_mode); 
		    break;
		case 0x625:
                    get_m56_front_wiper_status(db_kom.msg,
			&m56_front_wiper_status);
		    check_msg_timeout(ts_ms, &m56_front_wiper_status.ts_ms, &m56_front_wiper_status.two_message_periods, &m56_front_wiper_status.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG625_VAR, 
			sizeof(m56_front_wiper_status_t), &m56_front_wiper_status); 
		    break;
		case 0x52b:
                    get_m56_lidar_target(db_kom.msg,
			&m56_lidar_target);
		    check_msg_timeout(ts_ms, &m56_lidar_target.ts_ms, &m56_lidar_target.two_message_periods, &m56_lidar_target.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG52b_VAR, 
			sizeof(m56_lidar_target_t), &m56_lidar_target); 
		    break;
		case 0x52c:
                    get_m56_yaw_rate(db_kom.msg,
			&m56_yaw_rate);
		    check_msg_timeout(ts_ms, &m56_yaw_rate.ts_ms, &m56_yaw_rate.two_message_periods, &m56_yaw_rate.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG52c_VAR, 
			sizeof(m56_yaw_rate_t), &m56_yaw_rate); 
		    break;
		case 0x52d:
                    get_m56_lidar_status(db_kom.msg,
			&m56_lidar_status);
		    check_msg_timeout(ts_ms, &m56_lidar_status.ts_ms, &m56_lidar_status.two_message_periods, &m56_lidar_status.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG52d_VAR, 
			sizeof(m56_lidar_status_t), &m56_lidar_status); 
		    break;

		//Communication messages
		case 0x210:
                    get_m56_vdne491_m210(db_kom.msg, &m56_vdne491_m210);
		    check_msg_timeout(ts_ms, &m56_vdne491_m210.ts_ms, &m56_vdne491_m210.two_message_periods, &m56_vdne491_m210.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG210_VAR, 
			sizeof(m56_vdne491_m210_t), &m56_vdne491_m210); 
		    break;
		case 0x211:
                    get_m56_vdne491_m211(db_kom.msg, &m56_vdne491_m211);
		    check_msg_timeout(ts_ms, &m56_vdne491_m211.ts_ms, &m56_vdne491_m211.two_message_periods, &m56_vdne491_m211.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG211_VAR, 
			sizeof(m56_vdne491_m211_t), &m56_vdne491_m211); 
		    break;
		case 0x212:
                    get_m56_vdne491_m212(db_kom.msg, &m56_vdne491_m212);
		    check_msg_timeout(ts_ms, &m56_vdne491_m212.ts_ms, &m56_vdne491_m212.two_message_periods, &m56_vdne491_m212.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG212_VAR, 
			sizeof(m56_vdne491_m212_t), &m56_vdne491_m212); 
		    break;
		case 0x213:
                    get_m56_vdne491_m213(db_kom.msg, &m56_vdne491_m213);
		    check_msg_timeout(ts_ms, &m56_vdne491_m213.ts_ms, &m56_vdne491_m213.two_message_periods, &m56_vdne491_m213.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG213_VAR, 
			sizeof(m56_vdne491_m213_t), &m56_vdne491_m213); 
		    break;
		case 0x214:
                    get_m56_vpro4_m214(db_kom.msg, &m56_vpro4_m214);
		    check_msg_timeout(ts_ms, &m56_vpro4_m214.ts_ms, &m56_vpro4_m214.two_message_periods, &m56_vpro4_m214.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG214_VAR, 
			sizeof(m56_vpro4_m214_t), &m56_vpro4_m214); 
		    break;
		case 0x215:
                    get_m56_vpro4_m215(db_kom.msg, &m56_vpro4_m215);
		    check_msg_timeout(ts_ms, &m56_vpro4_m215.ts_ms, &m56_vpro4_m215.two_message_periods, &m56_vpro4_m215.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG215_VAR, 
			sizeof(m56_vpro4_m215_t), &m56_vpro4_m215); 
		    break;
		case 0x216:
                    get_m56_vpro4_m216(db_kom.msg, &m56_vpro4_m216);
		    check_msg_timeout(ts_ms, &m56_vpro4_m216.ts_ms, &m56_vpro4_m216.two_message_periods, &m56_vpro4_m216.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG216_VAR, 
			sizeof(m56_vpro4_m216_t), &m56_vpro4_m216); 
		    break;
		case 0x217:
                    get_m56_vpro4_m217(db_kom.msg, &m56_vpro4_m217);
		    check_msg_timeout(ts_ms, &m56_vpro4_m217.ts_ms, &m56_vpro4_m217.two_message_periods, &m56_vpro4_m217.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG217_VAR, 
			sizeof(m56_vpro4_m217_t), &m56_vpro4_m217); 
		    break;
		case 0x218:
                    get_m56_vdnc304_m218(db_kom.msg, &m56_vdnc304_m218);
		    check_msg_timeout(ts_ms, &m56_vdnc304_m218.ts_ms, &m56_vdnc304_m218.two_message_periods, &m56_vdnc304_m218.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG218_VAR, 
			sizeof(m56_vdnc304_m218_t), &m56_vdnc304_m218); 
		    break;
		case 0x219:
                    get_m56_vdnc304_m219(db_kom.msg, &m56_vdnc304_m219);
		    check_msg_timeout(ts_ms, &m56_vdnc304_m219.ts_ms, &m56_vdnc304_m219.two_message_periods, &m56_vdnc304_m219.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG219_VAR, 
			sizeof(m56_vdnc304_m219_t), &m56_vdnc304_m219); 
		    break;
		case 0x21a:
                    get_m56_vdnc304_m21a(db_kom.msg, &m56_vdnc304_m21a);
		    check_msg_timeout(ts_ms, &m56_vdnc304_m21a.ts_ms, &m56_vdnc304_m21a.two_message_periods, &m56_vdnc304_m21a.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG21a_VAR, 
			sizeof(m56_vdnc304_m21a_t), &m56_vdnc304_m21a); 
		    break;
		case 0x21b:
                    get_m56_vdnc304_m21b(db_kom.msg, &m56_vdnc304_m21b);
		    check_msg_timeout(ts_ms, &m56_vdnc304_m21b.ts_ms, &m56_vdnc304_m21b.two_message_periods, &m56_vdnc304_m21b.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG21b_VAR, 
			sizeof(m56_vdnc304_m21b_t), &m56_vdnc304_m21b); 
		    break;
		case 0x21c:
                    get_m56_vpro4_m21c(db_kom.msg, &m56_vpro4_m21c);
		    check_msg_timeout(ts_ms, &m56_vpro4_m21c.ts_ms, &m56_vpro4_m21c.two_message_periods, &m56_vpro4_m21c.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG21c_VAR, 
			sizeof(m56_vpro4_m21c_t), &m56_vpro4_m21c); 
		    break;
		case 0x21d:
                    get_m56_vpro4_m21d(db_kom.msg, &m56_vpro4_m21d);
		    check_msg_timeout(ts_ms, &m56_vpro4_m21d.ts_ms, &m56_vpro4_m21d.two_message_periods, &m56_vpro4_m21d.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG21d_VAR, 
			sizeof(m56_vpro4_m21d_t), &m56_vpro4_m21d); 
		    break;
		case 0x21e:
                    get_m56_vpro4_m21e(db_kom.msg, &m56_vpro4_m21e);
		    check_msg_timeout(ts_ms, &m56_vpro4_m21e.ts_ms, &m56_vpro4_m21e.two_message_periods, &m56_vpro4_m21e.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG21e_VAR, 
			sizeof(m56_vpro4_m21e_t), &m56_vpro4_m21e); 
		    break;
		case 0x21f:
                    get_m56_vpro4_m21f(db_kom.msg, &m56_vpro4_m21f);
		    check_msg_timeout(ts_ms, &m56_vpro4_m21f.ts_ms, &m56_vpro4_m21f.two_message_periods, &m56_vpro4_m21f.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG21f_VAR, 
			sizeof(m56_vpro4_m21f_t), &m56_vpro4_m21f); 
		    break;
	}
	   if(print_msg)
		printmsg(&db_kom);
	   if(verbose)
		printcan(&db_kom);
	}
	return 0;
}

void check_msg_timeout(int curr_ts_ms, int *prev_ts_ms, 
	unsigned char *two_message_periods, 
	unsigned int *message_timeout_counter) {
	if( (curr_ts_ms - *prev_ts_ms) > *two_message_periods ) {
	   ++*message_timeout_counter;
	   *prev_ts_ms = curr_ts_ms;
	}
}
