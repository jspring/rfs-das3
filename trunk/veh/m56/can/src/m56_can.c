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

        {DB_M56_ITSCAN_MSG200_VAR, sizeof(m56_m200_t)},
        {DB_M56_ITSCAN_MSG201_VAR, sizeof(m56_m201_t)},
        {DB_M56_ITSCAN_MSG202_VAR, sizeof(m56_m202_t)},
        {DB_M56_ITSCAN_MSG203_VAR, sizeof(m56_m203_t)},
        {DB_M56_ITSCAN_MSG650_VAR, sizeof(m56_m650_t)},

        {DB_M56_ITSCAN_MSG651_VAR, sizeof(m56_m651_t)},
        {DB_M56_ITSCAN_MSG652_VAR, sizeof(m56_m652_t)},
        {DB_M56_ITSCAN_MSG653_VAR, sizeof(m56_m653_t)},
        {DB_M56_ITSCAN_MSG654_VAR, sizeof(m56_m654_t)},
        {DB_M56_ITSCAN_MSG655_VAR, sizeof(m56_m655_t)},

        {DB_M56_ITSCAN_MSG656_VAR, sizeof(m56_m656_t)},
        {DB_M56_ITSCAN_MSG657_VAR, sizeof(m56_m657_t)},
        {DB_M56_ITSCAN_MSG658_VAR, sizeof(m56_m658_t)},
        {DB_M56_ITSCAN_MSG710_VAR, sizeof(m56_m710_t)},
        {DB_M56_ITSCAN_MSG711_VAR, sizeof(m56_m711_t)},

        {DB_M56_ITSCAN_MSG430_VAR, sizeof(m56_m4n0_t)},
        {DB_M56_ITSCAN_MSG440_VAR, sizeof(m56_m4n0_t)},
        {DB_M56_ITSCAN_MSG450_VAR, sizeof(m56_m4n0_t)},
        {DB_M56_ITSCAN_MSG460_VAR, sizeof(m56_m4n0_t)},
        {DB_M56_ITSCAN_MSG470_VAR, sizeof(m56_m4n0_t)},

        {DB_M56_ITSCAN_MSG431_VAR, sizeof(m56_m4n1_t)},
        {DB_M56_ITSCAN_MSG441_VAR, sizeof(m56_m4n1_t)},
        {DB_M56_ITSCAN_MSG451_VAR, sizeof(m56_m4n1_t)},
        {DB_M56_ITSCAN_MSG461_VAR, sizeof(m56_m4n1_t)},
        {DB_M56_ITSCAN_MSG471_VAR, sizeof(m56_m4n1_t)},

        {DB_M56_ITSCAN_MSG432_VAR, sizeof(m56_m4n2_t)},
        {DB_M56_ITSCAN_MSG442_VAR, sizeof(m56_m4n2_t)},
        {DB_M56_ITSCAN_MSG452_VAR, sizeof(m56_m4n2_t)},
        {DB_M56_ITSCAN_MSG462_VAR, sizeof(m56_m4n2_t)},
        {DB_M56_ITSCAN_MSG472_VAR, sizeof(m56_m4n2_t)},

        {DB_M56_ITSCAN_MSG433_VAR, sizeof(m56_m4n3_t)},
        {DB_M56_ITSCAN_MSG443_VAR, sizeof(m56_m4n3_t)},
        {DB_M56_ITSCAN_MSG453_VAR, sizeof(m56_m4n3_t)},
        {DB_M56_ITSCAN_MSG463_VAR, sizeof(m56_m4n3_t)},
        {DB_M56_ITSCAN_MSG473_VAR, sizeof(m56_m4n3_t)},

        {DB_M56_ITSCAN_MSG434_VAR, sizeof(m56_m4n4_t)},
        {DB_M56_ITSCAN_MSG444_VAR, sizeof(m56_m4n4_t)},
        {DB_M56_ITSCAN_MSG454_VAR, sizeof(m56_m4n4_t)},
        {DB_M56_ITSCAN_MSG464_VAR, sizeof(m56_m4n4_t)},
        {DB_M56_ITSCAN_MSG474_VAR, sizeof(m56_m4n4_t)},

        {DB_M56_ITSCAN_MSG435_VAR, sizeof(m56_m4n5_t)},
        {DB_M56_ITSCAN_MSG445_VAR, sizeof(m56_m4n5_t)},
        {DB_M56_ITSCAN_MSG455_VAR, sizeof(m56_m4n5_t)},
        {DB_M56_ITSCAN_MSG465_VAR, sizeof(m56_m4n5_t)},
        {DB_M56_ITSCAN_MSG475_VAR, sizeof(m56_m4n5_t)},

        {DB_M56_ITSCAN_MSG436_VAR, sizeof(m56_m4n6_t)},
        {DB_M56_ITSCAN_MSG446_VAR, sizeof(m56_m4n6_t)},
        {DB_M56_ITSCAN_MSG456_VAR, sizeof(m56_m4n6_t)},
        {DB_M56_ITSCAN_MSG466_VAR, sizeof(m56_m4n6_t)},
        {DB_M56_ITSCAN_MSG476_VAR, sizeof(m56_m4n6_t)},

        {DB_M56_ITSCAN_MSG437_VAR, sizeof(m56_m4n7_t)},
        {DB_M56_ITSCAN_MSG447_VAR, sizeof(m56_m4n7_t)},
        {DB_M56_ITSCAN_MSG457_VAR, sizeof(m56_m4n7_t)},
        {DB_M56_ITSCAN_MSG467_VAR, sizeof(m56_m4n7_t)},
        {DB_M56_ITSCAN_MSG477_VAR, sizeof(m56_m4n7_t)},

        {DB_M56_ITSCAN_MSG438_VAR, sizeof(m56_m4n8_t)},
        {DB_M56_ITSCAN_MSG448_VAR, sizeof(m56_m4n8_t)},
        {DB_M56_ITSCAN_MSG458_VAR, sizeof(m56_m4n8_t)},
        {DB_M56_ITSCAN_MSG468_VAR, sizeof(m56_m4n8_t)},
        {DB_M56_ITSCAN_MSG478_VAR, sizeof(m56_m4n8_t)},

        {DB_M56_ITSCAN_MSG480_VAR, sizeof(m56_m4n0_t)},
        {DB_M56_ITSCAN_MSG490_VAR, sizeof(m56_m4n0_t)},
        {DB_M56_ITSCAN_MSG4A0_VAR, sizeof(m56_m4n0_t)},
        {DB_M56_ITSCAN_MSG4B0_VAR, sizeof(m56_m4n0_t)},
        {DB_M56_ITSCAN_MSG4C0_VAR, sizeof(m56_m4n0_t)},

        {DB_M56_ITSCAN_MSG481_VAR, sizeof(m56_m4n1_t)},
        {DB_M56_ITSCAN_MSG491_VAR, sizeof(m56_m4n1_t)},
        {DB_M56_ITSCAN_MSG4A1_VAR, sizeof(m56_m4n1_t)},
        {DB_M56_ITSCAN_MSG4B1_VAR, sizeof(m56_m4n1_t)},
        {DB_M56_ITSCAN_MSG4C1_VAR, sizeof(m56_m4n1_t)},

        {DB_M56_ITSCAN_MSG482_VAR, sizeof(m56_m4n2_t)},
        {DB_M56_ITSCAN_MSG492_VAR, sizeof(m56_m4n2_t)},
        {DB_M56_ITSCAN_MSG4A2_VAR, sizeof(m56_m4n2_t)},
        {DB_M56_ITSCAN_MSG4B2_VAR, sizeof(m56_m4n2_t)},
        {DB_M56_ITSCAN_MSG4C2_VAR, sizeof(m56_m4n2_t)},

        {DB_M56_ITSCAN_MSG483_VAR, sizeof(m56_m4n3_t)},
        {DB_M56_ITSCAN_MSG493_VAR, sizeof(m56_m4n3_t)},
        {DB_M56_ITSCAN_MSG4A3_VAR, sizeof(m56_m4n3_t)},
        {DB_M56_ITSCAN_MSG4B3_VAR, sizeof(m56_m4n3_t)},
        {DB_M56_ITSCAN_MSG4C3_VAR, sizeof(m56_m4n3_t)},

        {DB_M56_ITSCAN_MSG484_VAR, sizeof(m56_m4n4_t)},
        {DB_M56_ITSCAN_MSG494_VAR, sizeof(m56_m4n4_t)},
        {DB_M56_ITSCAN_MSG4A4_VAR, sizeof(m56_m4n4_t)},
        {DB_M56_ITSCAN_MSG4B4_VAR, sizeof(m56_m4n4_t)},
        {DB_M56_ITSCAN_MSG4C4_VAR, sizeof(m56_m4n4_t)},

        {DB_M56_ITSCAN_MSG485_VAR, sizeof(m56_m4n5_t)},
        {DB_M56_ITSCAN_MSG495_VAR, sizeof(m56_m4n5_t)},
        {DB_M56_ITSCAN_MSG4A5_VAR, sizeof(m56_m4n5_t)},
        {DB_M56_ITSCAN_MSG4B5_VAR, sizeof(m56_m4n5_t)},
        {DB_M56_ITSCAN_MSG4C5_VAR, sizeof(m56_m4n5_t)},

        {DB_M56_ITSCAN_MSG486_VAR, sizeof(m56_m4n6_t)},
        {DB_M56_ITSCAN_MSG496_VAR, sizeof(m56_m4n6_t)},
        {DB_M56_ITSCAN_MSG4A6_VAR, sizeof(m56_m4n6_t)},
        {DB_M56_ITSCAN_MSG4B6_VAR, sizeof(m56_m4n6_t)},
        {DB_M56_ITSCAN_MSG4C6_VAR, sizeof(m56_m4n6_t)},

        {DB_M56_ITSCAN_MSG487_VAR, sizeof(m56_m4n7_t)},
        {DB_M56_ITSCAN_MSG497_VAR, sizeof(m56_m4n7_t)},
        {DB_M56_ITSCAN_MSG4A7_VAR, sizeof(m56_m4n7_t)},
        {DB_M56_ITSCAN_MSG4B7_VAR, sizeof(m56_m4n7_t)},
        {DB_M56_ITSCAN_MSG4C7_VAR, sizeof(m56_m4n7_t)},

        {DB_M56_ITSCAN_MSG488_VAR, sizeof(m56_m4n8_t)},
        {DB_M56_ITSCAN_MSG498_VAR, sizeof(m56_m4n8_t)},
        {DB_M56_ITSCAN_MSG4A8_VAR, sizeof(m56_m4n8_t)},
        {DB_M56_ITSCAN_MSG4B8_VAR, sizeof(m56_m4n8_t)},
        {DB_M56_ITSCAN_MSG4C8_VAR, sizeof(m56_m4n8_t)},

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
	posix_timer_typ *ptimer;
	int ipc_message_error_ctr = 0;
	trig_info_typ trig_info;
	int recv_type;

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

	m56_m200_t m56_m200;
	m56_m201_t m56_m201;
	m56_m202_t m56_m202;
	m56_m203_t m56_m203;

	m56_m650_t m56_m650;
	m56_m651_t m56_m651;
	m56_m652_t m56_m652;
	m56_m653_t m56_m653;
	m56_m654_t m56_m654;
	m56_m655_t m56_m655;
	m56_m656_t m56_m656;
	m56_m657_t m56_m657;
	m56_m658_t m56_m658;

	m56_m710_t m56_m710;
	m56_m711_t m56_m711;

	m56_m4n0_t m56_m430;
	m56_m4n0_t m56_m440;
	m56_m4n0_t m56_m450;
	m56_m4n0_t m56_m460;
	m56_m4n0_t m56_m470;

	m56_m4n1_t m56_m431;
	m56_m4n1_t m56_m441;
	m56_m4n1_t m56_m451;
	m56_m4n1_t m56_m461;
	m56_m4n1_t m56_m471;

	m56_m4n2_t m56_m432;
	m56_m4n2_t m56_m442;
	m56_m4n2_t m56_m452;
	m56_m4n2_t m56_m462;
	m56_m4n2_t m56_m472;

	m56_m4n3_t m56_m433;
	m56_m4n3_t m56_m443;
	m56_m4n3_t m56_m453;
	m56_m4n3_t m56_m463;
	m56_m4n3_t m56_m473;

	m56_m4n4_t m56_m434;
	m56_m4n4_t m56_m444;
	m56_m4n4_t m56_m454;
	m56_m4n4_t m56_m464;
	m56_m4n4_t m56_m474;

	m56_m4n5_t m56_m435;
	m56_m4n5_t m56_m445;
	m56_m4n5_t m56_m455;
	m56_m4n5_t m56_m465;
	m56_m4n5_t m56_m475;

	m56_m4n6_t m56_m436;
	m56_m4n6_t m56_m446;
	m56_m4n6_t m56_m456;
	m56_m4n6_t m56_m466;
	m56_m4n6_t m56_m476;

	m56_m4n7_t m56_m437;
	m56_m4n7_t m56_m447;
	m56_m4n7_t m56_m457;
	m56_m4n7_t m56_m467;
	m56_m4n7_t m56_m477;

	m56_m4n8_t m56_m438;
	m56_m4n8_t m56_m448;
	m56_m4n8_t m56_m458;
	m56_m4n8_t m56_m468;
	m56_m4n8_t m56_m478;

	m56_m4n0_t m56_m480;
	m56_m4n0_t m56_m490;
	m56_m4n0_t m56_m4A0;
	m56_m4n0_t m56_m4B0;
	m56_m4n0_t m56_m4C0;

	m56_m4n1_t m56_m481;
	m56_m4n1_t m56_m491;
	m56_m4n1_t m56_m4A1;
	m56_m4n1_t m56_m4B1;
	m56_m4n1_t m56_m4C1;

	m56_m4n2_t m56_m482;
	m56_m4n2_t m56_m492;
	m56_m4n2_t m56_m4A2;
	m56_m4n2_t m56_m4B2;
	m56_m4n2_t m56_m4C2;

	m56_m4n3_t m56_m483;
	m56_m4n3_t m56_m493;
	m56_m4n3_t m56_m4A3;
	m56_m4n3_t m56_m4B3;
	m56_m4n3_t m56_m4C3;

	m56_m4n4_t m56_m484;
	m56_m4n4_t m56_m494;
	m56_m4n4_t m56_m4A4;
	m56_m4n4_t m56_m4B4;
	m56_m4n4_t m56_m4C4;

	m56_m4n5_t m56_m485;
	m56_m4n5_t m56_m495;
	m56_m4n5_t m56_m4A5;
	m56_m4n5_t m56_m4B5;
	m56_m4n5_t m56_m4C5;

	m56_m4n6_t m56_m486;
	m56_m4n6_t m56_m496;
	m56_m4n6_t m56_m4A6;
	m56_m4n6_t m56_m4B6;
	m56_m4n6_t m56_m4C6;

	m56_m4n7_t m56_m487;
	m56_m4n7_t m56_m497;
	m56_m4n7_t m56_m4A7;
	m56_m4n7_t m56_m4B7;
	m56_m4n7_t m56_m4C7;

	m56_m4n8_t m56_m488;
	m56_m4n8_t m56_m498;
	m56_m4n8_t m56_m4A8;
	m56_m4n8_t m56_m4B8;
	m56_m4n8_t m56_m4C8;

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
	if (clt_trig_set( pclt, DB_KOMODO_VAR, DB_KOMODO_TYPE)
                         == FALSE )
                exit(EXIT_FAILURE);

        if (setjmp(exit_env) != 0) {
                db_list_done(pclt, db_vars_list, num_db_variables, NULL, 0);
                printf("%s: received %d CAN messages %d IPC message errors\n", 
			argv[0], count, ipc_message_error_ctr);
                exit(EXIT_SUCCESS);
        } else
               sig_ign(sig_list, sig_hand);

        if ((ptimer = timer_init( 1, ChannelCreate(0) )) == NULL) {
                fprintf(stderr, "Unable to initialize delay timer\n");
                exit(EXIT_FAILURE);
        }

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

	memset(&m56_m200, 0, sizeof(m56_m200_t));
	memset(&m56_m201, 0, sizeof(m56_m202_t));
	memset(&m56_m202, 0, sizeof(m56_m202_t));
	memset(&m56_m203, 0, sizeof(m56_m203_t));

	memset(&m56_m650, 0, sizeof(m56_m650_t));
	memset(&m56_m651, 0, sizeof(m56_m651_t));
	memset(&m56_m652, 0, sizeof(m56_m652_t));
	memset(&m56_m653, 0, sizeof(m56_m653_t));
	memset(&m56_m654, 0, sizeof(m56_m654_t));
	memset(&m56_m655, 0, sizeof(m56_m655_t));
	memset(&m56_m656, 0, sizeof(m56_m656_t));
	memset(&m56_m657, 0, sizeof(m56_m657_t));
	memset(&m56_m658, 0, sizeof(m56_m658_t));

	memset(&m56_m710, 0, sizeof(m56_m710_t));
	memset(&m56_m711, 0, sizeof(m56_m711_t));

	memset(&m56_m430, 0, sizeof(m56_m4n0_t));
	memset(&m56_m440, 0, sizeof(m56_m4n0_t));
	memset(&m56_m450, 0, sizeof(m56_m4n0_t));
	memset(&m56_m460, 0, sizeof(m56_m4n0_t));
	memset(&m56_m470, 0, sizeof(m56_m4n0_t));

	memset(&m56_m431, 0, sizeof(m56_m4n1_t));
	memset(&m56_m441, 0, sizeof(m56_m4n1_t));
	memset(&m56_m451, 0, sizeof(m56_m4n1_t));
	memset(&m56_m461, 0, sizeof(m56_m4n1_t));
	memset(&m56_m471, 0, sizeof(m56_m4n1_t));

	memset(&m56_m432, 0, sizeof(m56_m4n2_t));
	memset(&m56_m442, 0, sizeof(m56_m4n2_t));
	memset(&m56_m452, 0, sizeof(m56_m4n2_t));
	memset(&m56_m462, 0, sizeof(m56_m4n2_t));
	memset(&m56_m472, 0, sizeof(m56_m4n2_t));

	memset(&m56_m433, 0, sizeof(m56_m4n3_t));
	memset(&m56_m443, 0, sizeof(m56_m4n3_t));
	memset(&m56_m453, 0, sizeof(m56_m4n3_t));
	memset(&m56_m463, 0, sizeof(m56_m4n3_t));
	memset(&m56_m473, 0, sizeof(m56_m4n3_t));

	memset(&m56_m434, 0, sizeof(m56_m4n4_t));
	memset(&m56_m444, 0, sizeof(m56_m4n4_t));
	memset(&m56_m454, 0, sizeof(m56_m4n4_t));
	memset(&m56_m464, 0, sizeof(m56_m4n4_t));
	memset(&m56_m474, 0, sizeof(m56_m4n4_t));

	memset(&m56_m435, 0, sizeof(m56_m4n5_t));
	memset(&m56_m445, 0, sizeof(m56_m4n5_t));
	memset(&m56_m455, 0, sizeof(m56_m4n5_t));
	memset(&m56_m465, 0, sizeof(m56_m4n5_t));
	memset(&m56_m475, 0, sizeof(m56_m4n5_t));

	memset(&m56_m436, 0, sizeof(m56_m4n6_t));
	memset(&m56_m446, 0, sizeof(m56_m4n6_t));
	memset(&m56_m456, 0, sizeof(m56_m4n6_t));
	memset(&m56_m466, 0, sizeof(m56_m4n6_t));
	memset(&m56_m476, 0, sizeof(m56_m4n6_t));

	memset(&m56_m437, 0, sizeof(m56_m4n7_t));
	memset(&m56_m447, 0, sizeof(m56_m4n7_t));
	memset(&m56_m457, 0, sizeof(m56_m4n7_t));
	memset(&m56_m467, 0, sizeof(m56_m4n7_t));
	memset(&m56_m477, 0, sizeof(m56_m4n7_t));

	memset(&m56_m438, 0, sizeof(m56_m4n8_t));
	memset(&m56_m448, 0, sizeof(m56_m4n8_t));
	memset(&m56_m458, 0, sizeof(m56_m4n8_t));
	memset(&m56_m468, 0, sizeof(m56_m4n8_t));
	memset(&m56_m478, 0, sizeof(m56_m4n8_t));

	memset(&m56_m480, 0, sizeof(m56_m4n0_t));
	memset(&m56_m490, 0, sizeof(m56_m4n0_t));
	memset(&m56_m4A0, 0, sizeof(m56_m4n0_t));
	memset(&m56_m4B0, 0, sizeof(m56_m4n0_t));
	memset(&m56_m4C0, 0, sizeof(m56_m4n0_t));

	memset(&m56_m481, 0, sizeof(m56_m4n1_t));
	memset(&m56_m491, 0, sizeof(m56_m4n1_t));
	memset(&m56_m4A1, 0, sizeof(m56_m4n1_t));
	memset(&m56_m4B1, 0, sizeof(m56_m4n1_t));
	memset(&m56_m4C1, 0, sizeof(m56_m4n1_t));

	memset(&m56_m482, 0, sizeof(m56_m4n2_t));
	memset(&m56_m492, 0, sizeof(m56_m4n2_t));
	memset(&m56_m4A2, 0, sizeof(m56_m4n2_t));
	memset(&m56_m4B2, 0, sizeof(m56_m4n2_t));
	memset(&m56_m4C2, 0, sizeof(m56_m4n2_t));

	memset(&m56_m483, 0, sizeof(m56_m4n3_t));
	memset(&m56_m493, 0, sizeof(m56_m4n3_t));
	memset(&m56_m4A3, 0, sizeof(m56_m4n3_t));
	memset(&m56_m4B3, 0, sizeof(m56_m4n3_t));
	memset(&m56_m4C3, 0, sizeof(m56_m4n3_t));

	memset(&m56_m484, 0, sizeof(m56_m4n4_t));
	memset(&m56_m494, 0, sizeof(m56_m4n4_t));
	memset(&m56_m4A4, 0, sizeof(m56_m4n4_t));
	memset(&m56_m4B4, 0, sizeof(m56_m4n4_t));
	memset(&m56_m4C4, 0, sizeof(m56_m4n4_t));

	memset(&m56_m485, 0, sizeof(m56_m4n5_t));
	memset(&m56_m495, 0, sizeof(m56_m4n5_t));
	memset(&m56_m4A5, 0, sizeof(m56_m4n5_t));
	memset(&m56_m4B5, 0, sizeof(m56_m4n5_t));
	memset(&m56_m4C5, 0, sizeof(m56_m4n5_t));

	memset(&m56_m486, 0, sizeof(m56_m4n6_t));
	memset(&m56_m496, 0, sizeof(m56_m4n6_t));
	memset(&m56_m4A6, 0, sizeof(m56_m4n6_t));
	memset(&m56_m4B6, 0, sizeof(m56_m4n6_t));
	memset(&m56_m4C6, 0, sizeof(m56_m4n6_t));

	memset(&m56_m487, 0, sizeof(m56_m4n7_t));
	memset(&m56_m497, 0, sizeof(m56_m4n7_t));
	memset(&m56_m4A7, 0, sizeof(m56_m4n7_t));
	memset(&m56_m4B7, 0, sizeof(m56_m4n7_t));
	memset(&m56_m4C7, 0, sizeof(m56_m4n7_t));

	memset(&m56_m488, 0, sizeof(m56_m4n8_t));
	memset(&m56_m498, 0, sizeof(m56_m4n8_t));
	memset(&m56_m4A8, 0, sizeof(m56_m4n8_t));
	memset(&m56_m4B8, 0, sizeof(m56_m4n8_t));
	memset(&m56_m4C8, 0, sizeof(m56_m4n8_t));

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

	m56_m200.two_message_periods = 200; 	// 2*100 msec
	m56_m201.two_message_periods = 200; 	// 2*100 msec
	m56_m202.two_message_periods = 200; 	// 2*100 msec
	m56_m203.two_message_periods = 200; 	// 2*100 msec

	m56_m650.two_message_periods = 200; 	// 2*100 msec
	m56_m651.two_message_periods = 200; 	// 2*100 msec
	m56_m652.two_message_periods = 200; 	// 2*100 msec
	m56_m653.two_message_periods = 200; 	// 2*100 msec
	m56_m654.two_message_periods = 200; 	// 2*100 msec
	m56_m655.two_message_periods = 200; 	// 2*100 msec
	m56_m656.two_message_periods = 200; 	// 2*100 msec
	m56_m657.two_message_periods = 200; 	// 2*100 msec
	m56_m658.two_message_periods = 200; 	// 2*100 msec

	m56_m710.two_message_periods = 200; 	// 2*100 msec
	m56_m711.two_message_periods = 200; 	// 2*100 msec

	m56_m430.two_message_periods = 200; 	// 2*100 msec
	m56_m440.two_message_periods = 200; 	// 2*100 msec
	m56_m450.two_message_periods = 200; 	// 2*100 msec
	m56_m460.two_message_periods = 200; 	// 2*100 msec
	m56_m470.two_message_periods = 200; 	// 2*100 msec

	m56_m431.two_message_periods = 200; 	// 2*100 msec
	m56_m441.two_message_periods = 200; 	// 2*100 msec
	m56_m451.two_message_periods = 200; 	// 2*100 msec
	m56_m461.two_message_periods = 200; 	// 2*100 msec
	m56_m471.two_message_periods = 200; 	// 2*100 msec

	m56_m432.two_message_periods = 200; 	// 2*100 msec
	m56_m442.two_message_periods = 200; 	// 2*100 msec
	m56_m452.two_message_periods = 200; 	// 2*100 msec
	m56_m462.two_message_periods = 200; 	// 2*100 msec
	m56_m472.two_message_periods = 200; 	// 2*100 msec

	m56_m433.two_message_periods = 200; 	// 2*100 msec
	m56_m443.two_message_periods = 200; 	// 2*100 msec
	m56_m453.two_message_periods = 200; 	// 2*100 msec
	m56_m463.two_message_periods = 200; 	// 2*100 msec
	m56_m473.two_message_periods = 200; 	// 2*100 msec

	m56_m434.two_message_periods = 200; 	// 2*100 msec
	m56_m444.two_message_periods = 200; 	// 2*100 msec
	m56_m454.two_message_periods = 200; 	// 2*100 msec
	m56_m464.two_message_periods = 200; 	// 2*100 msec
	m56_m474.two_message_periods = 200; 	// 2*100 msec

	m56_m435.two_message_periods = 200; 	// 2*100 msec
	m56_m445.two_message_periods = 200; 	// 2*100 msec
	m56_m455.two_message_periods = 200; 	// 2*100 msec
	m56_m465.two_message_periods = 200; 	// 2*100 msec
	m56_m475.two_message_periods = 200; 	// 2*100 msec

	m56_m436.two_message_periods = 200; 	// 2*100 msec
	m56_m446.two_message_periods = 200; 	// 2*100 msec
	m56_m456.two_message_periods = 200; 	// 2*100 msec
	m56_m466.two_message_periods = 200; 	// 2*100 msec
	m56_m476.two_message_periods = 200; 	// 2*100 msec

	m56_m437.two_message_periods = 200; 	// 2*100 msec
	m56_m447.two_message_periods = 200; 	// 2*100 msec
	m56_m457.two_message_periods = 200; 	// 2*100 msec
	m56_m467.two_message_periods = 200; 	// 2*100 msec
	m56_m477.two_message_periods = 200; 	// 2*100 msec

	m56_m438.two_message_periods = 200; 	// 2*100 msec
	m56_m448.two_message_periods = 200; 	// 2*100 msec
	m56_m458.two_message_periods = 200; 	// 2*100 msec
	m56_m468.two_message_periods = 200; 	// 2*100 msec
	m56_m478.two_message_periods = 200; 	// 2*100 msec

	m56_m480.two_message_periods = 200; 	// 2*100 msec
	m56_m490.two_message_periods = 200; 	// 2*100 msec
	m56_m4A0.two_message_periods = 200; 	// 2*100 msec
	m56_m4B0.two_message_periods = 200; 	// 2*100 msec
	m56_m4C0.two_message_periods = 200; 	// 2*100 msec

	m56_m481.two_message_periods = 200; 	// 2*100 msec
	m56_m491.two_message_periods = 200; 	// 2*100 msec
	m56_m4A1.two_message_periods = 200; 	// 2*100 msec
	m56_m4B1.two_message_periods = 200; 	// 2*100 msec
	m56_m4C1.two_message_periods = 200; 	// 2*100 msec

	m56_m482.two_message_periods = 200; 	// 2*100 msec
	m56_m492.two_message_periods = 200; 	// 2*100 msec
	m56_m4A2.two_message_periods = 200; 	// 2*100 msec
	m56_m4B2.two_message_periods = 200; 	// 2*100 msec
	m56_m4C2.two_message_periods = 200; 	// 2*100 msec

	m56_m483.two_message_periods = 200; 	// 2*100 msec
	m56_m493.two_message_periods = 200; 	// 2*100 msec
	m56_m4A3.two_message_periods = 200; 	// 2*100 msec
	m56_m4B3.two_message_periods = 200; 	// 2*100 msec
	m56_m4C3.two_message_periods = 200; 	// 2*100 msec

	m56_m484.two_message_periods = 200; 	// 2*100 msec
	m56_m494.two_message_periods = 200; 	// 2*100 msec
	m56_m4A4.two_message_periods = 200; 	// 2*100 msec
	m56_m4B4.two_message_periods = 200; 	// 2*100 msec
	m56_m4C4.two_message_periods = 200; 	// 2*100 msec

	m56_m485.two_message_periods = 200; 	// 2*100 msec
	m56_m495.two_message_periods = 200; 	// 2*100 msec
	m56_m4A5.two_message_periods = 200; 	// 2*100 msec
	m56_m4B5.two_message_periods = 200; 	// 2*100 msec
	m56_m4C5.two_message_periods = 200; 	// 2*100 msec

	m56_m486.two_message_periods = 200; 	// 2*100 msec
	m56_m496.two_message_periods = 200; 	// 2*100 msec
	m56_m4A6.two_message_periods = 200; 	// 2*100 msec
	m56_m4B6.two_message_periods = 200; 	// 2*100 msec
	m56_m4C6.two_message_periods = 200; 	// 2*100 msec

	m56_m487.two_message_periods = 200; 	// 2*100 msec
	m56_m497.two_message_periods = 200; 	// 2*100 msec
	m56_m4A7.two_message_periods = 200; 	// 2*100 msec
	m56_m4B7.two_message_periods = 200; 	// 2*100 msec
	m56_m4C7.two_message_periods = 200; 	// 2*100 msec

	m56_m488.two_message_periods = 200; 	// 2*100 msec
	m56_m498.two_message_periods = 200; 	// 2*100 msec
	m56_m4A8.two_message_periods = 200; 	// 2*100 msec
	m56_m4B8.two_message_periods = 200; 	// 2*100 msec
	m56_m4C8.two_message_periods = 200; 	// 2*100 msec

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

	db_clt_write(pclt,DB_M56_ITSCAN_MSG200_VAR, 
		sizeof(m56_m200_t), &m56_m200); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG201_VAR, 
		sizeof(m56_m201_t), &m56_m201); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG202_VAR, 
		sizeof(m56_m202_t), &m56_m202); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG203_VAR, 
		sizeof(m56_m203_t), &m56_m203); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG650_VAR, 
		sizeof(m56_m650_t), &m56_m650); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG651_VAR, 
		sizeof(m56_m651_t), &m56_m651); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG652_VAR, 
		sizeof(m56_m652_t), &m56_m652); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG653_VAR, 
		sizeof(m56_m653_t), &m56_m653); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG654_VAR, 
		sizeof(m56_m654_t), &m56_m654); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG655_VAR, 
		sizeof(m56_m655_t), &m56_m655); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG656_VAR, 
		sizeof(m56_m656_t), &m56_m656); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG657_VAR, 
		sizeof(m56_m657_t), &m56_m657); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG658_VAR, 
		sizeof(m56_m658_t), &m56_m658); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG430_VAR, 
		sizeof(m56_m4n0_t), &m56_m430); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG440_VAR, 
		sizeof(m56_m4n0_t), &m56_m440); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG450_VAR, 
		sizeof(m56_m4n0_t), &m56_m450); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG460_VAR, 
		sizeof(m56_m4n0_t), &m56_m460); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG470_VAR, 
		sizeof(m56_m4n0_t), &m56_m470); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG431_VAR, 
		sizeof(m56_m4n1_t), &m56_m431); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG441_VAR, 
		sizeof(m56_m4n1_t), &m56_m441); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG451_VAR, 
		sizeof(m56_m4n1_t), &m56_m451); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG461_VAR, 
		sizeof(m56_m4n1_t), &m56_m461); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG471_VAR, 
		sizeof(m56_m4n1_t), &m56_m471); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG432_VAR, 
		sizeof(m56_m4n2_t), &m56_m432); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG442_VAR, 
		sizeof(m56_m4n2_t), &m56_m442); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG452_VAR, 
		sizeof(m56_m4n2_t), &m56_m452); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG462_VAR, 
		sizeof(m56_m4n2_t), &m56_m462); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG472_VAR, 
		sizeof(m56_m4n2_t), &m56_m472); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG433_VAR, 
		sizeof(m56_m4n3_t), &m56_m433); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG443_VAR, 
		sizeof(m56_m4n3_t), &m56_m443); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG453_VAR, 
		sizeof(m56_m4n3_t), &m56_m453); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG463_VAR, 
		sizeof(m56_m4n3_t), &m56_m463); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG473_VAR, 
		sizeof(m56_m4n3_t), &m56_m473); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG434_VAR, 
		sizeof(m56_m4n4_t), &m56_m434); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG444_VAR, 
		sizeof(m56_m4n4_t), &m56_m444); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG454_VAR, 
		sizeof(m56_m4n4_t), &m56_m454); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG464_VAR, 
		sizeof(m56_m4n4_t), &m56_m464); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG474_VAR, 
		sizeof(m56_m4n4_t), &m56_m474); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG435_VAR, 
		sizeof(m56_m4n5_t), &m56_m435); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG445_VAR, 
		sizeof(m56_m4n5_t), &m56_m445); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG455_VAR, 
		sizeof(m56_m4n5_t), &m56_m455); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG465_VAR, 
		sizeof(m56_m4n5_t), &m56_m465); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG475_VAR, 
		sizeof(m56_m4n5_t), &m56_m475); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG436_VAR, 
		sizeof(m56_m4n6_t), &m56_m436); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG446_VAR, 
		sizeof(m56_m4n6_t), &m56_m446); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG456_VAR, 
		sizeof(m56_m4n6_t), &m56_m456); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG466_VAR, 
		sizeof(m56_m4n6_t), &m56_m466); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG476_VAR, 
		sizeof(m56_m4n6_t), &m56_m476); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG437_VAR, 
		sizeof(m56_m4n7_t), &m56_m437); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG447_VAR, 
		sizeof(m56_m4n7_t), &m56_m447); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG457_VAR, 
		sizeof(m56_m4n7_t), &m56_m457); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG467_VAR, 
		sizeof(m56_m4n7_t), &m56_m467); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG477_VAR, 
		sizeof(m56_m4n7_t), &m56_m477); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG438_VAR, 
		sizeof(m56_m4n8_t), &m56_m438); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG448_VAR, 
		sizeof(m56_m4n8_t), &m56_m448); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG458_VAR, 
		sizeof(m56_m4n8_t), &m56_m458); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG468_VAR, 
		sizeof(m56_m4n8_t), &m56_m468); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG478_VAR, 
		sizeof(m56_m4n8_t), &m56_m478); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG480_VAR, 
		sizeof(m56_m4n0_t), &m56_m480); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG490_VAR, 
		sizeof(m56_m4n0_t), &m56_m490); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4A0_VAR, 
		sizeof(m56_m4n0_t), &m56_m4A0); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4B0_VAR, 
		sizeof(m56_m4n0_t), &m56_m4B0); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4C0_VAR, 
		sizeof(m56_m4n0_t), &m56_m4C0); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG481_VAR, 
		sizeof(m56_m4n1_t), &m56_m481); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG491_VAR, 
		sizeof(m56_m4n1_t), &m56_m491); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4A1_VAR, 
		sizeof(m56_m4n1_t), &m56_m4A1); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4B1_VAR, 
		sizeof(m56_m4n1_t), &m56_m4B1); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4C1_VAR, 
		sizeof(m56_m4n1_t), &m56_m4C1); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG481_VAR, 
		sizeof(m56_m4n1_t), &m56_m481); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG491_VAR, 
		sizeof(m56_m4n1_t), &m56_m491); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4A1_VAR, 
		sizeof(m56_m4n1_t), &m56_m4A1); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4B1_VAR, 
		sizeof(m56_m4n1_t), &m56_m4B1); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4C1_VAR, 
		sizeof(m56_m4n1_t), &m56_m4C1); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG482_VAR, 
		sizeof(m56_m4n2_t), &m56_m482); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG492_VAR, 
		sizeof(m56_m4n2_t), &m56_m492); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4A2_VAR, 
		sizeof(m56_m4n2_t), &m56_m4A2); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4B2_VAR, 
		sizeof(m56_m4n2_t), &m56_m4B2); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4C2_VAR, 
		sizeof(m56_m4n2_t), &m56_m4C2); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG483_VAR, 
		sizeof(m56_m4n3_t), &m56_m483); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG493_VAR, 
		sizeof(m56_m4n3_t), &m56_m493); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4A3_VAR, 
		sizeof(m56_m4n3_t), &m56_m4A3); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4B3_VAR, 
		sizeof(m56_m4n3_t), &m56_m4B3); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4C3_VAR, 
		sizeof(m56_m4n3_t), &m56_m4C3); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG484_VAR, 
		sizeof(m56_m4n4_t), &m56_m484); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG494_VAR, 
		sizeof(m56_m4n4_t), &m56_m494); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4A4_VAR, 
		sizeof(m56_m4n4_t), &m56_m4A4); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4B4_VAR, 
		sizeof(m56_m4n4_t), &m56_m4B4); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4C4_VAR, 
		sizeof(m56_m4n4_t), &m56_m4C4); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG485_VAR, 
		sizeof(m56_m4n5_t), &m56_m485); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG495_VAR, 
		sizeof(m56_m4n5_t), &m56_m495); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4A5_VAR, 
		sizeof(m56_m4n5_t), &m56_m4A5); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4B5_VAR, 
		sizeof(m56_m4n5_t), &m56_m4B5); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4C5_VAR, 
		sizeof(m56_m4n5_t), &m56_m4C5); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG486_VAR, 
		sizeof(m56_m4n6_t), &m56_m486); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG496_VAR, 
		sizeof(m56_m4n6_t), &m56_m496); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4A6_VAR, 
		sizeof(m56_m4n6_t), &m56_m4A6); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4B6_VAR, 
		sizeof(m56_m4n6_t), &m56_m4B6); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4C6_VAR, 
		sizeof(m56_m4n6_t), &m56_m4C6); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG487_VAR, 
		sizeof(m56_m4n7_t), &m56_m487); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG497_VAR, 
		sizeof(m56_m4n7_t), &m56_m497); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4A7_VAR, 
		sizeof(m56_m4n7_t), &m56_m4A7); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4B7_VAR, 
		sizeof(m56_m4n7_t), &m56_m4B7); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4C7_VAR, 
		sizeof(m56_m4n7_t), &m56_m4C7); 

	db_clt_write(pclt,DB_M56_ITSCAN_MSG488_VAR, 
		sizeof(m56_m4n8_t), &m56_m488); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG498_VAR, 
		sizeof(m56_m4n8_t), &m56_m498); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4A8_VAR, 
		sizeof(m56_m4n8_t), &m56_m4A8); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4B8_VAR, 
		sizeof(m56_m4n8_t), &m56_m4B8); 
	db_clt_write(pclt,DB_M56_ITSCAN_MSG4C8_VAR, 
		sizeof(m56_m4n8_t), &m56_m4C8); 

	for(;;) {
	   /* Now wait for a trigger. */
	   recv_type= clt_ipc_receive(pclt, &trig_info, sizeof(trig_info));
	   if( DB_TRIG_VAR(&trig_info) == DB_KOMODO_VAR ) {
	   count++;
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

		//New comm messages
		case 0x200:
		    get_m56_m200(db_kom.msg, &m56_m200);
		    check_msg_timeout(ts_ms, &m56_m200.ts_ms, &m56_m200.two_message_periods, &m56_m200.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG200_VAR, 
			sizeof(m56_m200), &m56_m200); 
		    break;
		case 0x201:
		    get_m56_m201(db_kom.msg, &m56_m201);
		    check_msg_timeout(ts_ms, &m56_m201.ts_ms, &m56_m201.two_message_periods, &m56_m201.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG201_VAR, 
			sizeof(m56_m201), &m56_m201); 
		    break;
		case 0x202:
		    get_m56_m202(db_kom.msg, &m56_m202);
		    check_msg_timeout(ts_ms, &m56_m202.ts_ms, &m56_m202.two_message_periods, &m56_m202.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG202_VAR, 
			sizeof(m56_m202), &m56_m202); 
		    break;
		case 0x203:
		    get_m56_m203(db_kom.msg, &m56_m203);
		    check_msg_timeout(ts_ms, &m56_m203.ts_ms, &m56_m203.two_message_periods, &m56_m203.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG203_VAR, 
			sizeof(m56_m203), &m56_m203); 
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

		//New comm messages
		case 0x430:
		    get_m56_m4n0(db_kom.msg, &m56_m430);
		    check_msg_timeout(ts_ms, &m56_m430.ts_ms, &m56_m430.two_message_periods, &m56_m430.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG430_VAR, 
			sizeof(m56_m430), &m56_m430); 
		    break;
		case 0x440:
		    get_m56_m4n0(db_kom.msg, &m56_m440);
		    check_msg_timeout(ts_ms, &m56_m440.ts_ms, &m56_m440.two_message_periods, &m56_m440.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG440_VAR, 
			sizeof(m56_m440), &m56_m440); 
		    break;
		case 0x450:
		    get_m56_m4n0(db_kom.msg, &m56_m450);
		    check_msg_timeout(ts_ms, &m56_m450.ts_ms, &m56_m450.two_message_periods, &m56_m450.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG450_VAR, 
			sizeof(m56_m450), &m56_m450); 
		    break;
		case 0x460:
		    get_m56_m4n0(db_kom.msg, &m56_m460);
		    check_msg_timeout(ts_ms, &m56_m460.ts_ms, &m56_m460.two_message_periods, &m56_m460.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG460_VAR, 
			sizeof(m56_m460), &m56_m460); 
		    break;
		case 0x470:
		    get_m56_m4n0(db_kom.msg, &m56_m470);
		    check_msg_timeout(ts_ms, &m56_m470.ts_ms, &m56_m470.two_message_periods, &m56_m470.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG470_VAR, 
			sizeof(m56_m470), &m56_m470); 
		    break;

		case 0x431:
		    get_m56_m4n1(db_kom.msg, &m56_m431);
		    check_msg_timeout(ts_ms, &m56_m431.ts_ms, &m56_m431.two_message_periods, &m56_m431.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG431_VAR, 
			sizeof(m56_m431), &m56_m431); 
		    break;
		case 0x441:
		    get_m56_m4n1(db_kom.msg, &m56_m441);
		    check_msg_timeout(ts_ms, &m56_m441.ts_ms, &m56_m441.two_message_periods, &m56_m441.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG441_VAR, 
			sizeof(m56_m441), &m56_m441); 
		    break;
		case 0x451:
		    get_m56_m4n1(db_kom.msg, &m56_m451);
		    check_msg_timeout(ts_ms, &m56_m451.ts_ms, &m56_m451.two_message_periods, &m56_m451.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG451_VAR, 
			sizeof(m56_m451), &m56_m451); 
		    break;
		case 0x461:
		    get_m56_m4n1(db_kom.msg, &m56_m461);
		    check_msg_timeout(ts_ms, &m56_m461.ts_ms, &m56_m461.two_message_periods, &m56_m461.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG461_VAR, 
			sizeof(m56_m461), &m56_m461); 
		    break;
		case 0x471:
		    get_m56_m4n1(db_kom.msg, &m56_m471);
		    check_msg_timeout(ts_ms, &m56_m471.ts_ms, &m56_m471.two_message_periods, &m56_m471.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG471_VAR, 
			sizeof(m56_m471), &m56_m471); 
		    break;

		case 0x432:
		    get_m56_m4n2(db_kom.msg, &m56_m432);
		    check_msg_timeout(ts_ms, &m56_m432.ts_ms, &m56_m432.two_message_periods, &m56_m432.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG432_VAR, 
			sizeof(m56_m432), &m56_m432); 
		    break;
		case 0x442:
		    get_m56_m4n2(db_kom.msg, &m56_m442);
		    check_msg_timeout(ts_ms, &m56_m442.ts_ms, &m56_m442.two_message_periods, &m56_m442.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG442_VAR, 
			sizeof(m56_m442), &m56_m442); 
		    break;
		case 0x452:
		    get_m56_m4n2(db_kom.msg, &m56_m452);
		    check_msg_timeout(ts_ms, &m56_m452.ts_ms, &m56_m452.two_message_periods, &m56_m452.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG452_VAR, 
			sizeof(m56_m452), &m56_m452); 
		    break;
		case 0x462:
		    get_m56_m4n2(db_kom.msg, &m56_m462);
		    check_msg_timeout(ts_ms, &m56_m462.ts_ms, &m56_m462.two_message_periods, &m56_m462.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG462_VAR, 
			sizeof(m56_m462), &m56_m462); 
		    break;
		case 0x472:
		    get_m56_m4n2(db_kom.msg, &m56_m472);
		    check_msg_timeout(ts_ms, &m56_m472.ts_ms, &m56_m472.two_message_periods, &m56_m472.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG472_VAR, 
			sizeof(m56_m472), &m56_m472); 
		    break;

		case 0x433:
		    get_m56_m4n3(db_kom.msg, &m56_m433);
		    check_msg_timeout(ts_ms, &m56_m433.ts_ms, &m56_m433.two_message_periods, &m56_m433.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG433_VAR, 
			sizeof(m56_m433), &m56_m433); 
		    break;
		case 0x443:
		    get_m56_m4n3(db_kom.msg, &m56_m443);
		    check_msg_timeout(ts_ms, &m56_m443.ts_ms, &m56_m443.two_message_periods, &m56_m443.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG443_VAR, 
			sizeof(m56_m443), &m56_m443); 
		    break;
		case 0x453:
		    get_m56_m4n3(db_kom.msg, &m56_m453);
		    check_msg_timeout(ts_ms, &m56_m453.ts_ms, &m56_m453.two_message_periods, &m56_m453.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG453_VAR, 
			sizeof(m56_m453), &m56_m453); 
		    break;
		case 0x463:
		    get_m56_m4n3(db_kom.msg, &m56_m463);
		    check_msg_timeout(ts_ms, &m56_m463.ts_ms, &m56_m463.two_message_periods, &m56_m463.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG463_VAR, 
			sizeof(m56_m463), &m56_m463); 
		    break;
		case 0x473:
		    get_m56_m4n3(db_kom.msg, &m56_m473);
		    check_msg_timeout(ts_ms, &m56_m473.ts_ms, &m56_m473.two_message_periods, &m56_m473.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG473_VAR, 
			sizeof(m56_m473), &m56_m473); 
		    break;

		case 0x434:
		    get_m56_m4n4(db_kom.msg, &m56_m434);
		    check_msg_timeout(ts_ms, &m56_m434.ts_ms, &m56_m434.two_message_periods, &m56_m434.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG434_VAR, 
			sizeof(m56_m434), &m56_m434); 
		    break;
		case 0x444:
		    get_m56_m4n4(db_kom.msg, &m56_m444);
		    check_msg_timeout(ts_ms, &m56_m444.ts_ms, &m56_m444.two_message_periods, &m56_m444.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG444_VAR, 
			sizeof(m56_m444), &m56_m444); 
		    break;
		case 0x454:
		    get_m56_m4n4(db_kom.msg, &m56_m454);
		    check_msg_timeout(ts_ms, &m56_m454.ts_ms, &m56_m454.two_message_periods, &m56_m454.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG454_VAR, 
			sizeof(m56_m454), &m56_m454); 
		    break;
		case 0x464:
		    get_m56_m4n4(db_kom.msg, &m56_m464);
		    check_msg_timeout(ts_ms, &m56_m464.ts_ms, &m56_m464.two_message_periods, &m56_m464.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG464_VAR, 
			sizeof(m56_m464), &m56_m464); 
		    break;
		case 0x474:
		    get_m56_m4n4(db_kom.msg, &m56_m474);
		    check_msg_timeout(ts_ms, &m56_m474.ts_ms, &m56_m474.two_message_periods, &m56_m474.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG474_VAR, 
			sizeof(m56_m474), &m56_m474); 
		    break;

		case 0x435:
		    get_m56_m4n5(db_kom.msg, &m56_m435);
		    check_msg_timeout(ts_ms, &m56_m435.ts_ms, &m56_m435.two_message_periods, &m56_m435.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG435_VAR, 
			sizeof(m56_m435), &m56_m435); 
		    break;
		case 0x445:
		    get_m56_m4n5(db_kom.msg, &m56_m445);
		    check_msg_timeout(ts_ms, &m56_m445.ts_ms, &m56_m445.two_message_periods, &m56_m445.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG445_VAR, 
			sizeof(m56_m445), &m56_m445); 
		    break;
		case 0x455:
		    get_m56_m4n5(db_kom.msg, &m56_m455);
		    check_msg_timeout(ts_ms, &m56_m455.ts_ms, &m56_m455.two_message_periods, &m56_m455.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG455_VAR, 
			sizeof(m56_m455), &m56_m455); 
		    break;
		case 0x465:
		    get_m56_m4n5(db_kom.msg, &m56_m465);
		    check_msg_timeout(ts_ms, &m56_m465.ts_ms, &m56_m465.two_message_periods, &m56_m465.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG465_VAR, 
			sizeof(m56_m465), &m56_m465); 
		    break;
		case 0x475:
		    get_m56_m4n5(db_kom.msg, &m56_m475);
		    check_msg_timeout(ts_ms, &m56_m475.ts_ms, &m56_m475.two_message_periods, &m56_m475.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG475_VAR, 
			sizeof(m56_m475), &m56_m475); 
		    break;

		case 0x436:
		    get_m56_m4n6(db_kom.msg, &m56_m436);
		    check_msg_timeout(ts_ms, &m56_m436.ts_ms, &m56_m436.two_message_periods, &m56_m436.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG436_VAR, 
			sizeof(m56_m436), &m56_m436); 
		    break;
		case 0x446:
		    get_m56_m4n6(db_kom.msg, &m56_m446);
		    check_msg_timeout(ts_ms, &m56_m446.ts_ms, &m56_m446.two_message_periods, &m56_m446.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG446_VAR, 
			sizeof(m56_m446), &m56_m446); 
		    break;
		case 0x456:
		    get_m56_m4n6(db_kom.msg, &m56_m456);
		    check_msg_timeout(ts_ms, &m56_m456.ts_ms, &m56_m456.two_message_periods, &m56_m456.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG456_VAR, 
			sizeof(m56_m456), &m56_m456); 
		    break;
		case 0x466:
		    get_m56_m4n6(db_kom.msg, &m56_m466);
		    check_msg_timeout(ts_ms, &m56_m466.ts_ms, &m56_m466.two_message_periods, &m56_m466.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG466_VAR, 
			sizeof(m56_m466), &m56_m466); 
		    break;
		case 0x476:
		    get_m56_m4n6(db_kom.msg, &m56_m476);
		    check_msg_timeout(ts_ms, &m56_m476.ts_ms, &m56_m476.two_message_periods, &m56_m476.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG476_VAR, 
			sizeof(m56_m476), &m56_m476); 
		    break;

		case 0x437:
		    get_m56_m4n7(db_kom.msg, &m56_m437);
		    check_msg_timeout(ts_ms, &m56_m437.ts_ms, &m56_m437.two_message_periods, &m56_m437.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG437_VAR, 
			sizeof(m56_m437), &m56_m437); 
		    break;
		case 0x447:
		    get_m56_m4n7(db_kom.msg, &m56_m447);
		    check_msg_timeout(ts_ms, &m56_m447.ts_ms, &m56_m447.two_message_periods, &m56_m447.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG447_VAR, 
			sizeof(m56_m447), &m56_m447); 
		    break;
		case 0x457:
		    get_m56_m4n7(db_kom.msg, &m56_m457);
		    check_msg_timeout(ts_ms, &m56_m457.ts_ms, &m56_m457.two_message_periods, &m56_m457.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG457_VAR, 
			sizeof(m56_m457), &m56_m457); 
		    break;
		case 0x467:
		    get_m56_m4n7(db_kom.msg, &m56_m467);
		    check_msg_timeout(ts_ms, &m56_m467.ts_ms, &m56_m467.two_message_periods, &m56_m467.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG467_VAR, 
			sizeof(m56_m467), &m56_m467); 
		    break;
		case 0x477:
		    get_m56_m4n7(db_kom.msg, &m56_m477);
		    check_msg_timeout(ts_ms, &m56_m477.ts_ms, &m56_m477.two_message_periods, &m56_m477.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG477_VAR, 
			sizeof(m56_m477), &m56_m477); 
		    break;

		case 0x438:
		    get_m56_m4n8(db_kom.msg, &m56_m438);
		    check_msg_timeout(ts_ms, &m56_m438.ts_ms, &m56_m438.two_message_periods, &m56_m438.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG438_VAR, 
			sizeof(m56_m438), &m56_m438); 
		    break;
		case 0x448:
		    get_m56_m4n8(db_kom.msg, &m56_m448);
		    check_msg_timeout(ts_ms, &m56_m448.ts_ms, &m56_m448.two_message_periods, &m56_m448.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG448_VAR, 
			sizeof(m56_m448), &m56_m448); 
		    break;
		case 0x458:
		    get_m56_m4n8(db_kom.msg, &m56_m458);
		    check_msg_timeout(ts_ms, &m56_m458.ts_ms, &m56_m458.two_message_periods, &m56_m458.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG458_VAR, 
			sizeof(m56_m458), &m56_m458); 
		    break;
		case 0x468:
		    get_m56_m4n8(db_kom.msg, &m56_m468);
		    check_msg_timeout(ts_ms, &m56_m468.ts_ms, &m56_m468.two_message_periods, &m56_m468.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG468_VAR, 
			sizeof(m56_m468), &m56_m468); 
		    break;
		case 0x478:
		    get_m56_m4n8(db_kom.msg, &m56_m478);
		    check_msg_timeout(ts_ms, &m56_m478.ts_ms, &m56_m478.two_message_periods, &m56_m478.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG478_VAR, 
			sizeof(m56_m478), &m56_m478); 
		    break;


		case 0x480:
		    get_m56_m4n0(db_kom.msg, &m56_m480);
		    check_msg_timeout(ts_ms, &m56_m480.ts_ms, &m56_m480.two_message_periods, &m56_m480.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG480_VAR, 
			sizeof(m56_m480), &m56_m480); 
		    break;
		case 0x490:
		    get_m56_m4n0(db_kom.msg, &m56_m490);
		    check_msg_timeout(ts_ms, &m56_m490.ts_ms, &m56_m490.two_message_periods, &m56_m490.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG490_VAR, 
			sizeof(m56_m490), &m56_m490); 
		    break;
		case 0x4A0:
		    get_m56_m4n0(db_kom.msg, &m56_m4A0);
		    check_msg_timeout(ts_ms, &m56_m4A0.ts_ms, &m56_m4A0.two_message_periods, &m56_m4A0.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4A0_VAR, 
			sizeof(m56_m4A0), &m56_m4A0); 
		    break;
		case 0x4B0:
		    get_m56_m4n0(db_kom.msg, &m56_m4B0);
		    check_msg_timeout(ts_ms, &m56_m4B0.ts_ms, &m56_m4B0.two_message_periods, &m56_m4B0.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4B0_VAR, 
			sizeof(m56_m4B0), &m56_m4B0); 
		    break;
		case 0x4C0:
		    get_m56_m4n0(db_kom.msg, &m56_m4C0);
		    check_msg_timeout(ts_ms, &m56_m4C0.ts_ms, &m56_m4C0.two_message_periods, &m56_m4C0.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4C0_VAR, 
			sizeof(m56_m4C0), &m56_m4C0); 
		    break;

		case 0x481:
		    get_m56_m4n1(db_kom.msg, &m56_m481);
		    check_msg_timeout(ts_ms, &m56_m481.ts_ms, &m56_m481.two_message_periods, &m56_m481.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG481_VAR, 
			sizeof(m56_m481), &m56_m481); 
		    break;
		case 0x491:
		    get_m56_m4n1(db_kom.msg, &m56_m491);
		    check_msg_timeout(ts_ms, &m56_m491.ts_ms, &m56_m491.two_message_periods, &m56_m491.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG491_VAR, 
			sizeof(m56_m491), &m56_m491); 
		    break;
		case 0x4A1:
		    get_m56_m4n1(db_kom.msg, &m56_m4A1);
		    check_msg_timeout(ts_ms, &m56_m4A1.ts_ms, &m56_m4A1.two_message_periods, &m56_m4A1.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4A1_VAR, 
			sizeof(m56_m4A1), &m56_m4A1); 
		    break;
		case 0x4B1:
		    get_m56_m4n1(db_kom.msg, &m56_m4B1);
		    check_msg_timeout(ts_ms, &m56_m4B1.ts_ms, &m56_m4B1.two_message_periods, &m56_m4B1.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4B1_VAR, 
			sizeof(m56_m4B1), &m56_m4B1); 
		    break;
		case 0x4C1:
		    get_m56_m4n1(db_kom.msg, &m56_m4C1);
		    check_msg_timeout(ts_ms, &m56_m4C1.ts_ms, &m56_m4C1.two_message_periods, &m56_m4C1.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4C1_VAR, 
			sizeof(m56_m4C1), &m56_m4C1); 
		    break;

		case 0x482:
		    get_m56_m4n2(db_kom.msg, &m56_m482);
		    check_msg_timeout(ts_ms, &m56_m482.ts_ms, &m56_m482.two_message_periods, &m56_m482.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG482_VAR, 
			sizeof(m56_m482), &m56_m482); 
		    break;
		case 0x492:
		    get_m56_m4n2(db_kom.msg, &m56_m492);
		    check_msg_timeout(ts_ms, &m56_m492.ts_ms, &m56_m492.two_message_periods, &m56_m492.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG492_VAR, 
			sizeof(m56_m492), &m56_m492); 
		    break;
		case 0x4A2:
		    get_m56_m4n2(db_kom.msg, &m56_m4A2);
		    check_msg_timeout(ts_ms, &m56_m4A2.ts_ms, &m56_m4A2.two_message_periods, &m56_m4A2.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4A2_VAR, 
			sizeof(m56_m4A2), &m56_m4A2); 
		    break;
		case 0x4B2:
		    get_m56_m4n2(db_kom.msg, &m56_m4B2);
		    check_msg_timeout(ts_ms, &m56_m4B2.ts_ms, &m56_m4B2.two_message_periods, &m56_m4B2.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4B2_VAR, 
			sizeof(m56_m4B2), &m56_m4B2); 
		    break;
		case 0x4C2:
		    get_m56_m4n2(db_kom.msg, &m56_m4C2);
		    check_msg_timeout(ts_ms, &m56_m4C2.ts_ms, &m56_m4C2.two_message_periods, &m56_m4C2.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4C2_VAR, 
			sizeof(m56_m4C2), &m56_m4C2); 
		    break;

		case 0x483:
		    get_m56_m4n3(db_kom.msg, &m56_m483);
		    check_msg_timeout(ts_ms, &m56_m483.ts_ms, &m56_m483.two_message_periods, &m56_m483.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG483_VAR, 
			sizeof(m56_m483), &m56_m483); 
		    break;
		case 0x493:
		    get_m56_m4n3(db_kom.msg, &m56_m493);
		    check_msg_timeout(ts_ms, &m56_m493.ts_ms, &m56_m493.two_message_periods, &m56_m493.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG493_VAR, 
			sizeof(m56_m493), &m56_m493); 
		    break;
		case 0x4A3:
		    get_m56_m4n3(db_kom.msg, &m56_m4A3);
		    check_msg_timeout(ts_ms, &m56_m4A3.ts_ms, &m56_m4A3.two_message_periods, &m56_m4A3.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4A3_VAR, 
			sizeof(m56_m4A3), &m56_m4A3); 
		    break;
		case 0x4B3:
		    get_m56_m4n3(db_kom.msg, &m56_m4B3);
		    check_msg_timeout(ts_ms, &m56_m4B3.ts_ms, &m56_m4B3.two_message_periods, &m56_m4B3.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4B3_VAR, 
			sizeof(m56_m4B3), &m56_m4B3); 
		    break;
		case 0x4C3:
		    get_m56_m4n3(db_kom.msg, &m56_m4C3);
		    check_msg_timeout(ts_ms, &m56_m4C3.ts_ms, &m56_m4C3.two_message_periods, &m56_m4C3.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4C3_VAR, 
			sizeof(m56_m4C3), &m56_m4C3); 
		    break;

		case 0x484:
		    get_m56_m4n4(db_kom.msg, &m56_m484);
		    check_msg_timeout(ts_ms, &m56_m484.ts_ms, &m56_m484.two_message_periods, &m56_m484.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG484_VAR, 
			sizeof(m56_m484), &m56_m484); 
		    break;
		case 0x494:
		    get_m56_m4n4(db_kom.msg, &m56_m494);
		    check_msg_timeout(ts_ms, &m56_m494.ts_ms, &m56_m494.two_message_periods, &m56_m494.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG494_VAR, 
			sizeof(m56_m494), &m56_m494); 
		    break;
		case 0x4A4:
		    get_m56_m4n4(db_kom.msg, &m56_m4A4);
		    check_msg_timeout(ts_ms, &m56_m4A4.ts_ms, &m56_m4A4.two_message_periods, &m56_m4A4.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4A4_VAR, 
			sizeof(m56_m4A4), &m56_m4A4); 
		    break;
		case 0x4B4:
		    get_m56_m4n4(db_kom.msg, &m56_m4B4);
		    check_msg_timeout(ts_ms, &m56_m4B4.ts_ms, &m56_m4B4.two_message_periods, &m56_m4B4.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4B4_VAR, 
			sizeof(m56_m4B4), &m56_m4B4); 
		    break;
		case 0x4C4:
		    get_m56_m4n4(db_kom.msg, &m56_m4C4);
		    check_msg_timeout(ts_ms, &m56_m4C4.ts_ms, &m56_m4C4.two_message_periods, &m56_m4C4.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4C4_VAR, 
			sizeof(m56_m4C4), &m56_m4C4); 
		    break;

		case 0x485:
		    get_m56_m4n5(db_kom.msg, &m56_m485);
		    check_msg_timeout(ts_ms, &m56_m485.ts_ms, &m56_m485.two_message_periods, &m56_m485.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG485_VAR, 
			sizeof(m56_m485), &m56_m485); 
		    break;
		case 0x495:
		    get_m56_m4n5(db_kom.msg, &m56_m495);
		    check_msg_timeout(ts_ms, &m56_m495.ts_ms, &m56_m495.two_message_periods, &m56_m495.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG495_VAR, 
			sizeof(m56_m495), &m56_m495); 
		    break;
		case 0x4A5:
		    get_m56_m4n5(db_kom.msg, &m56_m4A5);
		    check_msg_timeout(ts_ms, &m56_m4A5.ts_ms, &m56_m4A5.two_message_periods, &m56_m4A5.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4A5_VAR, 
			sizeof(m56_m4A5), &m56_m4A5); 
		    break;
		case 0x4B5:
		    get_m56_m4n5(db_kom.msg, &m56_m4B5);
		    check_msg_timeout(ts_ms, &m56_m4B5.ts_ms, &m56_m4B5.two_message_periods, &m56_m4B5.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4B5_VAR, 
			sizeof(m56_m4B5), &m56_m4B5); 
		    break;
		case 0x4C5:
		    get_m56_m4n5(db_kom.msg, &m56_m4C5);
		    check_msg_timeout(ts_ms, &m56_m4C5.ts_ms, &m56_m4C5.two_message_periods, &m56_m4C5.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4C5_VAR, 
			sizeof(m56_m4C5), &m56_m4C5); 
		    break;

		case 0x486:
		    get_m56_m4n6(db_kom.msg, &m56_m486);
		    check_msg_timeout(ts_ms, &m56_m486.ts_ms, &m56_m486.two_message_periods, &m56_m486.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG486_VAR, 
			sizeof(m56_m486), &m56_m486); 
		    break;
		case 0x496:
		    get_m56_m4n6(db_kom.msg, &m56_m496);
		    check_msg_timeout(ts_ms, &m56_m496.ts_ms, &m56_m496.two_message_periods, &m56_m496.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG496_VAR, 
			sizeof(m56_m496), &m56_m496); 
		    break;
		case 0x4A6:
		    get_m56_m4n6(db_kom.msg, &m56_m4A6);
		    check_msg_timeout(ts_ms, &m56_m4A6.ts_ms, &m56_m4A6.two_message_periods, &m56_m4A6.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4A6_VAR, 
			sizeof(m56_m4A6), &m56_m4A6); 
		    break;
		case 0x4B6:
		    get_m56_m4n6(db_kom.msg, &m56_m4B6);
		    check_msg_timeout(ts_ms, &m56_m4B6.ts_ms, &m56_m4B6.two_message_periods, &m56_m4B6.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4B6_VAR, 
			sizeof(m56_m4B6), &m56_m4B6); 
		    break;
		case 0x4C6:
		    get_m56_m4n6(db_kom.msg, &m56_m4C6);
		    check_msg_timeout(ts_ms, &m56_m4C6.ts_ms, &m56_m4C6.two_message_periods, &m56_m4C6.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4C6_VAR, 
			sizeof(m56_m4C6), &m56_m4C6); 
		    break;

		case 0x487:
		    get_m56_m4n7(db_kom.msg, &m56_m487);
		    check_msg_timeout(ts_ms, &m56_m487.ts_ms, &m56_m487.two_message_periods, &m56_m487.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG487_VAR, 
			sizeof(m56_m487), &m56_m487); 
		    break;
		case 0x497:
		    get_m56_m4n7(db_kom.msg, &m56_m497);
		    check_msg_timeout(ts_ms, &m56_m497.ts_ms, &m56_m497.two_message_periods, &m56_m497.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG497_VAR, 
			sizeof(m56_m497), &m56_m497); 
		    break;
		case 0x4A7:
		    get_m56_m4n7(db_kom.msg, &m56_m4A7);
		    check_msg_timeout(ts_ms, &m56_m4A7.ts_ms, &m56_m4A7.two_message_periods, &m56_m4A7.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4A7_VAR, 
			sizeof(m56_m4A7), &m56_m4A7); 
		    break;
		case 0x4B7:
		    get_m56_m4n7(db_kom.msg, &m56_m4B7);
		    check_msg_timeout(ts_ms, &m56_m4B7.ts_ms, &m56_m4B7.two_message_periods, &m56_m4B7.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4B7_VAR, 
			sizeof(m56_m4B7), &m56_m4B7); 
		    break;
		case 0x4C7:
		    get_m56_m4n7(db_kom.msg, &m56_m4C7);
		    check_msg_timeout(ts_ms, &m56_m4C7.ts_ms, &m56_m4C7.two_message_periods, &m56_m4C7.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4C7_VAR, 
			sizeof(m56_m4C7), &m56_m4C7); 
		    break;

		case 0x488:
		    get_m56_m4n8(db_kom.msg, &m56_m488);
		    check_msg_timeout(ts_ms, &m56_m488.ts_ms, &m56_m488.two_message_periods, &m56_m488.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG488_VAR, 
			sizeof(m56_m488), &m56_m488); 
		    break;
		case 0x498:
		    get_m56_m4n8(db_kom.msg, &m56_m498);
		    check_msg_timeout(ts_ms, &m56_m498.ts_ms, &m56_m498.two_message_periods, &m56_m498.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG498_VAR, 
			sizeof(m56_m498), &m56_m498); 
		    break;
		case 0x4A8:
		    get_m56_m4n8(db_kom.msg, &m56_m4A8);
		    check_msg_timeout(ts_ms, &m56_m4A8.ts_ms, &m56_m4A8.two_message_periods, &m56_m4A8.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4A8_VAR, 
			sizeof(m56_m4A8), &m56_m4A8); 
		    break;
		case 0x4B8:
		    get_m56_m4n8(db_kom.msg, &m56_m4B8);
		    check_msg_timeout(ts_ms, &m56_m4B8.ts_ms, &m56_m4B8.two_message_periods, &m56_m4B8.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4B8_VAR, 
			sizeof(m56_m4B8), &m56_m4B8); 
		    break;
		case 0x4C8:
		    get_m56_m4n8(db_kom.msg, &m56_m4C8);
		    check_msg_timeout(ts_ms, &m56_m4C8.ts_ms, &m56_m4C8.two_message_periods, &m56_m4C8.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG4C8_VAR, 
			sizeof(m56_m4C8), &m56_m4C8); 
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

		//New comm messages
		case 0x650:
		    get_m56_m650(db_kom.msg, &m56_m650);
		    check_msg_timeout(ts_ms, &m56_m650.ts_ms, &m56_m650.two_message_periods, &m56_m650.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG650_VAR, 
			sizeof(m56_m650), &m56_m650); 
		    break;
		case 0x651:
		    get_m56_m651(db_kom.msg, &m56_m651);
		    check_msg_timeout(ts_ms, &m56_m651.ts_ms, &m56_m651.two_message_periods, &m56_m651.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG651_VAR, 
			sizeof(m56_m651), &m56_m651); 
		    break;
		case 0x652:
		    get_m56_m652(db_kom.msg, &m56_m652);
		    check_msg_timeout(ts_ms, &m56_m652.ts_ms, &m56_m652.two_message_periods, &m56_m652.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG652_VAR, 
			sizeof(m56_m652), &m56_m652); 
		    break;
		case 0x653:
		    get_m56_m653(db_kom.msg, &m56_m653);
		    check_msg_timeout(ts_ms, &m56_m653.ts_ms, &m56_m653.two_message_periods, &m56_m653.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG653_VAR, 
			sizeof(m56_m653), &m56_m653); 
		    break;
		case 0x654:
		    get_m56_m654(db_kom.msg, &m56_m654);
		    check_msg_timeout(ts_ms, &m56_m654.ts_ms, &m56_m654.two_message_periods, &m56_m654.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG654_VAR, 
			sizeof(m56_m654), &m56_m654); 
		    break;
		case 0x655:
		    get_m56_m655(db_kom.msg, &m56_m655);
		    check_msg_timeout(ts_ms, &m56_m655.ts_ms, &m56_m655.two_message_periods, &m56_m655.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG655_VAR, 
			sizeof(m56_m655), &m56_m655); 
		    break;
		case 0x656:
		    get_m56_m656(db_kom.msg, &m56_m656);
		    check_msg_timeout(ts_ms, &m56_m656.ts_ms, &m56_m656.two_message_periods, &m56_m656.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG656_VAR, 
			sizeof(m56_m656), &m56_m656); 
		    break;
		case 0x657:
		    get_m56_m657(db_kom.msg, &m56_m657);
		    check_msg_timeout(ts_ms, &m56_m657.ts_ms, &m56_m657.two_message_periods, &m56_m657.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG657_VAR, 
			sizeof(m56_m657), &m56_m657); 
		    break;
		case 0x658:
		    get_m56_m658(db_kom.msg, &m56_m658);
		    check_msg_timeout(ts_ms, &m56_m658.ts_ms, &m56_m658.two_message_periods, &m56_m658.message_timeout_counter); 
	   	    db_clt_write(pclt,DB_M56_ITSCAN_MSG658_VAR, 
			sizeof(m56_m658), &m56_m658); 
		    break;

	}
	   if(print_msg)
		printmsg(&db_kom);
	   if(verbose)
		printcan(&db_kom);
	    }	
	    else {
		TIMER_WAIT (ptimer);
		ipc_message_error_ctr++;
	   }
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
