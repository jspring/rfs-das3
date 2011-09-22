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

const char *usage = "-A <Chan A baud rate (500 kHz)>\n\t\t-B <Chan B baud rate (500 kHz)> \n\t\t-w <power, 0=all off, 1=Chan A on only, 2=Chan B on only, \n\t\t\t3=both channels on, default=3)> \n\t\t-t <timeout (1000 ms)> \n\t\t-v verbose";

db_id_t db_vars_list[] =  {
        {DB_M56_VCAN2_MSG002_VAR, sizeof(m56_steering_t)},
        {DB_M56_VCAN2_MSG180_VAR, sizeof(m56_engine_rpm_t)},
        {DB_M56_VCAN2_MSG239_VAR, sizeof(m56_pedal_position_t)},
};

int num_db_variables = sizeof(db_vars_list)/sizeof(db_id_t);

int main(int argc, char *argv[]) {
	Komodo km;
	int power[2] = {1,1};
	int bitrate[2] = {500000, 500000};
	unsigned short timeout = 1000;
	int port = 0;
	int verbose = 0;
	int print_msg = 0;
	int ret;
	km_can_info_t info;
	km_can_packet_t pkt;
	int data_len;
	unsigned char msg[8];
	int option;
	int tmp;
	int count = 0;

        char hostname[MAXHOSTNAMELEN];
        char *domain = DEFAULT_SERVICE; /// on Linux sets DB q-file directory
        db_clt_typ *pclt;               /// data server client pointer
        int xport = COMM_OS_XPORT;      /// value set correctly in sys_os.h

	m56_engine_rpm_t m56_engine_rpm;

        while ((option = getopt(argc, argv, "A:B:w:t:vp:")) != EOF) {
                switch(option) {
                case 'A':
                        bitrate[0] = atoi(optarg) * 1000;
                        break;
                case 'B':
                        bitrate[1] = atoi(optarg) * 1000;
                        break;
                case 'w':
			tmp = atoi(optarg);
			power[0] = tmp & 0x1;
			power[1] = tmp & 0x2;
                        break;
                case 't':
                        timeout = atoi(optarg);
                        break;
                case 'p':
			print_msg = atoi(optarg);
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
                        db_vars_list, num_db_variables, NULL, 0)) == NULL) {
                printf("Database initialization error in %s\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        if (setjmp(exit_env) != 0) {
                db_list_done(pclt, db_vars_list, num_db_variables, NULL, 0);
                printf("%s: received %d CAN messages\n", argv[0], count);
                exit(EXIT_SUCCESS);
        } else
               sig_ign(sig_list, sig_hand);



	init_kom(km, &power, port, timeout, &bitrate);

	for(;;) {

        ret = km_can_read(km, &info, &pkt, data_len, msg);
	   switch(pkt.id) {
		case 0x002:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG002_VAR, sizeof(msg), &msg); 
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
		    get_m56_engine_rpm(msg, &m56_engine_rpm);
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG180_VAR, sizeof(m56_engine_rpm_t), &m56_engine_rpm); 
		    printf("engine rpm %f\n", m56_engine_rpm.engine_rpm);
		    break;
		case 0x1c3:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG1c3_VAR, sizeof(msg), &msg); 
		    break;
		case 0x239:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG239_VAR, sizeof(msg), &msg); 
		    break;
		case 0x245:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG245_VAR, sizeof(msg), &msg); 
		    break;
		case 0x284:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG284_VAR, sizeof(msg), &msg); 
		    break;
		case 0x285:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG285_VAR, sizeof(msg), &msg); 
		    break;
		case 0x292:
	   	    //db_clt_write(pclt,DB_M56_VCAN2_MSG292_VAR, sizeof(msg), &msg); 
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
	   if(print_msg)
		printmsg(pkt.id, msg);
	   if(verbose)
		printcan(pkt.id, msg);
	}
	}
	return 0;
}
