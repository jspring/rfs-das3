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
        {DB_M56_VCAN2_MSG5b0_VAR, sizeof(m56_transmission_mode_t)},
        {DB_M56_VCAN2_MSG625_VAR, sizeof(m56_front_wiper_status_t)},
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

        char hostname[MAXHOSTNAMELEN];
        char *domain = DEFAULT_SERVICE; /// on Linux sets DB q-file directory
        db_clt_typ *pclt;               /// data server client pointer
        int xport = COMM_OS_XPORT;      /// value set correctly in sys_os.h
	db_komodo_t db_kom;
	timestamp_t ts;
	int ts_ms;

	m56_engine_rpm_t m56_engine_rpm;
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
	m56_transmission_mode_t m56_transmission_mode;
	m56_front_wiper_status_t m56_front_wiper_status;

        while ((option = getopt(argc, argv, "v")) != EOF) {
                switch(option) {
                case 'v':
                        verbose = 1;
                        break;
                default:
                        printf("Usage: %s %s\n", argv[0], usage);
                        exit(EXIT_FAILURE);
                        break;
                }
        }
        get_local_name(hostname, MAXHOSTNAMELEN);
        if ((pclt = db_list_init(argv[0], hostname, domain, xport,
	    db_vars_list, num_db_variables, db_trig_list, num_trig_variables)) == NULL) {
                printf("Database initialization error in %s\n", argv[0]);
                exit(EXIT_FAILURE);
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
	memset(&m56_its_alive, 0, sizeof(m56_its_alive_t));
	memset(&m56_pedal_position, 0, sizeof(m56_pedal_position_t));
	memset(&m56_wheel_speed_front, 0, sizeof(m56_wheel_speed_front_t));
	memset(&m56_wheel_speed_rear, 0, sizeof(m56_wheel_speed_rear_t));
	memset(&m56_acceleration, 0, sizeof(m56_acceleration_t));
	memset(&m56_acc_status, 0, sizeof(m56_acc_status_t));
	memset(&m56_eng_tq_acc_and_brake_flags, 0, sizeof(m56_eng_tq_acc_and_brake_flags_t));
	memset(&m56_dashboard_indicators, 0, sizeof(m56_dashboard_indicators_t));
	memset(&m56_abs_status, 0, sizeof(m56_abs_status_t));
	memset(&m56_transmission_mode, 0, sizeof(m56_transmission_mode_t));
	memset(&m56_front_wiper_status, 0, sizeof(m56_front_wiper_status_t));

	m56_steering.two_message_periods = 20; 		/ 2*10 msec
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
	m56_turn_switch_status.two_message_periods = 200; // 2*100 msec
	m56_transmission_mode.two_message_periods = 200; // 2*100 msec
	m56_front_wiper_status.two_message_periods = 200; // 2*100 msec

	for(;;) {
	   db_clt_read(pclt, DB_KOMODO_VAR, sizeof(db_komodo_t), &db_kom);
	   get_current_timestamp(&ts);
	   ts_ms = TS_TO_MS(&ts);
	   switch(db_kom.id) {
		case 0x002:
		    get_m56_steering(db_kom.msg, &m56_steering);
		    if( (ts_ms - m56_steering.ts_ms) > m56_steering.two_message_periods )
			++m56_steering.message_timeout_counter;
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG002_VAR, 
			sizeof(m56_steering_t), &m56_steering); 
		    break;
		case 0x160:
		    break;
		case 0x174:
		    break;
		case 0x177:
		    break;
		case 0x180:
		    get_m56_engine_rpm(db_kom.msg, &m56_engine_rpm);
		    if( (ts_ms - m56_steering.ts_ms) > m56_steering.two_message_periods )
			++m56_steering.message_timeout_counter;
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG180_VAR, 
			sizeof(m56_engine_rpm_t), &m56_engine_rpm); 
		    break;
		case 0x1c3:
		    get_m56_its_alive(db_kom.msg, &m56_its_alive);
		    if( (ts_ms - m56_pedal_position.ts_ms) > m56_pedal_position.two_message_periods )
			++m56_pedal_position.message_timeout_counter;
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG1c3_VAR, 
			sizeof(m56_its_alive_t), &m56_its_alive); 
		    break;
		case 0x239:
		    get_m56_pedal_position(db_kom.msg, &m56_pedal_position);
		    if( (ts_ms - m56_pedal_position.ts_ms) > m56_pedal_position.two_message_periods )
			++m56_pedal_position.message_timeout_counter;
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG239_VAR, 
			sizeof(m56_pedal_position_t), &m56_pedal_position); 
		    break;
		case 0x245:
		    break;
		case 0x284:
		    get_m56_wheel_speed_front(db_kom.msg,&m56_wheel_speed_front);
		    if( (ts_ms - m56_wheel_speed_front.ts_ms) > m56_wheel_speed_front.two_message_periods )
			++m56_wheel_speed_front.message_timeout_counter;
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG284_VAR, 
		      sizeof(m56_wheel_speed_front_t), &m56_wheel_speed_front); 
		    break;
		case 0x285:
		    get_m56_wheel_speed_rear(db_kom.msg, &m56_wheel_speed_rear);
		    if( (ts_ms - m56_wheel_speed_rear.ts_ms) > m56_wheel_speed_rear.two_message_periods )
			++m56_wheel_speed_rear.message_timeout_counter;
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG285_VAR, 
			sizeof(m56_wheel_speed_rear_t), &m56_wheel_speed_rear); 
		    break;
		case 0x292:
		    get_m56_acceleration(db_kom.msg, &m56_acceleration);
		    if( (ts_ms - m56_acceleration.ts_ms) > m56_acceleration.two_message_periods )
			++m56_acceleration.message_timeout_counter;
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG292_VAR, 
			sizeof(m56_acceleration_t), &m56_acceleration); 
		    break;
		case 0x2aa:
		    get_m56_acc_status(db_kom.msg, &m56_acc_status);
		    if( (ts_ms - m56_acc_status.ts_ms) > m56_acc_status.two_message_periods )
			++m56_acc_status.message_timeout_counter;
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG2aa_VAR, 
			sizeof(m56_acc_status_t), &m56_acc_status); 
		    break;
		case 0x2b0:
                    get_m56_eng_tq_acc_and_brake_flags(db_kom.msg, 
			&m56_eng_tq_acc_and_brake_flags);
		    if( (ts_ms - m56_eng_tq_acc_and_brake_flags.ts_ms) > m56_eng_tq_acc_and_brake_flags.two_message_periods )
			++m56_eng_tq_acc_and_brake_flags.message_timeout_counter;
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG2b0_VAR, 
			sizeof(m56_eng_tq_acc_and_brake_flags_t), 
			&m56_eng_tq_acc_and_brake_flags); 
		    break;
		case 0x2b3:
		    get_m56_dashboard_indicators(db_kom.msg,
			&m56_dashboard_indicators);
		    if( (ts_ms - m56_dashboard_indicators.ts_ms) > m56_dashboard_indicators.two_message_periods )
			++m56_dashboard_indicators.message_timeout_counter;
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG2b3_VAR, 
			sizeof(m56_dashboard_indicators_t), &m56_dashboard_indicators); 
		    break;
		case 0x354:
                    get_m56_abs_status(db_kom.msg,
			&m56_abs_status);
		    if( (ts_ms - m56_abs_status.ts_ms) > m56_abs_status.two_message_periods )
			++m56_abs_status.message_timeout_counter;
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG354_VAR, sizeof(m56_abs_status_t), &m56_abs_status); 
		    break;
		case 0x358:
                    get_m56_turn_switch_status(db_kom.msg,
			&m56_turn_switch_status);
		    if( (ts_ms - m56_turn_switch_status.ts_ms) > m56_turn_switch_status.two_message_periods )
			++m56_turn_switch_status.message_timeout_counter;
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG358_VAR, 
			sizeof(m56_turn_switch_status_t), &m56_turn_switch_status); 
		    break;
		case 0x421:
		    break;
		case 0x5b0:
                    get_m56_transmission_mode(db_kom.msg,
			&m56_transmission_mode);
		    if( (ts_ms - m56_transmission_mode.ts_ms) > m56_transmission_mode.two_message_periods )
			++m56_transmission_mode.message_timeout_counter;
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG5b0_VAR, 
			sizeof(m56_transmission_mode_t), &m56_transmission_mode); 
		    break;
		case 0x625:
                    get_m56_front_wiper_status(db_kom.msg,
			&m56_front_wiper_status);
		    if( (ts_ms - m56_front_wiper_status.ts_ms) > m56_front_wiper_status.two_message_periods )
			++m56_front_wiper_status.message_timeout_counter;
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG625_VAR, 
			sizeof(m56_front_wiper_status_t), &m56_front_wiper_status); 
		    break;
	}
	   if(print_msg)
		printmsg(&db_kom);
	   if(verbose)
		printcan(&db_kom);
	}
	return 0;
}
