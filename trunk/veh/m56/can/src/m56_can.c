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
        {DB_M56_VCAN2_MSG239_VAR, sizeof(m56_pedal_position_t)},
        {DB_M56_VCAN2_MSG284_VAR, sizeof(m56_wheel_speed_front_t)},
        {DB_M56_VCAN2_MSG285_VAR, sizeof(m56_wheel_speed_rear_t)},
        {DB_M56_VCAN2_MSG292_VAR, sizeof(m56_acceleration_t)},
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

	m56_engine_rpm_t m56_engine_rpm;
	m56_pedal_position_t m56_pedal_position;
	m56_wheel_speed_front_t m56_wheel_speed_front;
	m56_wheel_speed_rear_t m56_wheel_speed_rear;
        m56_steering_t m56_steering;
        m56_acceleration_t m56_acceleration;

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

	for(;;) {
	   db_clt_read(pclt, DB_KOMODO_VAR, sizeof(db_komodo_t), &db_kom);
	   switch(db_kom.id) {
		case 0x002:
		    get_m56_steering(db_kom.msg, &m56_steering);
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG002_VAR, sizeof(m56_steering_t), &m56_steering); 
		    printf("steering_angle %f steering_velocity %f\n", 
			m56_steering.steering_angle, 
			m56_steering.steering_velocity);
		    break;
		case 0x160:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG160_VAR, sizeof(msg), &msg); 
		    break;
		case 0x174:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG174_VAR, sizeof(msg), &msg); 
		    break;
		case 0x177:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG177_VAR, sizeof(msg), &msg); 
		    break;
		case 0x180:
		    get_m56_engine_rpm(db_kom.msg, &m56_engine_rpm);
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG180_VAR, sizeof(m56_engine_rpm_t), &m56_engine_rpm); 
		    printf("engine rpm %f\n", m56_engine_rpm.engine_rpm);
		    break;
		case 0x1c3:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG1c3_VAR, sizeof(msg), &msg); 
		    break;
		case 0x239:
		    get_m56_pedal_position(db_kom.msg, &m56_pedal_position);
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG239_VAR, sizeof(m56_pedal_position_t), &m56_pedal_position); 
		    printf("pedal position %f%%\n", m56_pedal_position.pedal_position);
		    break;
		case 0x245:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG245_VAR, sizeof(msg), &msg); 
		    break;
		case 0x284:
		    get_m56_wheel_speed_front(db_kom.msg, &m56_wheel_speed_front);
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG284_VAR, sizeof(m56_wheel_speed_front_t), &m56_wheel_speed_front); 
		    printf("wheel_speed_front_right %f wheel_speed_front_left %f vehicle_speed_copy %f \n", 
			m56_wheel_speed_front.wheel_speed_front_right, 
			m56_wheel_speed_front.wheel_speed_front_left, 
			m56_wheel_speed_front.vehicle_speed_copy);
		    break;
		case 0x285:
		    get_m56_wheel_speed_rear(db_kom.msg, &m56_wheel_speed_rear);
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG285_VAR, sizeof(m56_wheel_speed_rear_t), &m56_wheel_speed_rear); 
		    printf("wheel_speed_rear_right %f wheel_speed_rear_left %f\n", 
			m56_wheel_speed_rear.wheel_speed_rear_right, 
			m56_wheel_speed_rear.wheel_speed_rear_left);
		    break;
		case 0x292:
		    get_m56_acceleration(db_kom.msg, &m56_acceleration);
	   	    db_clt_write(pclt,DB_M56_VCAN2_MSG292_VAR, sizeof(m56_acceleration_t), &m56_acceleration); 
		    printf("long_accel_proc_02 %f transverse_accel_proc_02 %f yaw_rate_02 %f\n", 
			m56_acceleration.long_accel_proc_02, 
			m56_acceleration.transverse_accel_proc_02, 
			m56_acceleration.yaw_rate_02);
		    break;
		case 0x2aa:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG2aa_VAR, sizeof(msg), &msg); 
		    break;
		case 0x2b0:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG2b0_VAR, sizeof(msg), &msg); 
		    break;
		case 0x2b3:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG2b3_VAR, sizeof(msg), &msg); 
		    break;
		case 0x354:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG354_VAR, sizeof(msg), &msg); 
		    break;
		case 0x358:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG358_VAR, sizeof(msg), &msg); 
		    break;
		case 0x421:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG421_VAR, sizeof(msg), &msg); 
		    break;
		case 0x5b0:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG5b0_VAR, sizeof(msg), &msg); 
		    break;
		case 0x625:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG625_VAR, sizeof(msg), &msg); 
		    break;
	}
	   if(print_msg)
		printmsg(&db_kom);
	   if(verbose)
		printcan(&db_kom);
	}
	return 0;
}
