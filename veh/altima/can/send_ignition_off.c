/**\file
 * 	Receive Altima CAN data from Peak CAN to USB converter stream.	
 *	Write data  to the DB data server.
 */
#include <sys_os.h>
#include <local.h>
#include <sys_rt.h>
#include <db_clt.h>
#include <db_utils.h>
#include "nt_peak_can.h"
#include "timestamp.h"
#include "altima.h"

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

int main(int argc, char **argv)
{
	int count = 0;	/// number of PEAK CAN messages received, no error
	alt_turn_signal_ignition_t alt_tsi;

	/// variables for use with PATA data server
        char hostname[MAXHOSTNAMELEN];
        char *domain = DEFAULT_SERVICE; /// on Linux sets DB q-file directory
        db_clt_typ *pclt;       	/// data server client pointer
        int xport = COMM_OS_XPORT;      /// value set correctly in sys_os.h 

	/// when desk checking, may want to simulate delays
	/// simple method (when arrival assumed much slower than read from
	/// file and associated parsing) is to keep last timestamp
	/// and nanosleep time difference


        get_local_name(hostname, MAXHOSTNAMELEN);
        if ((pclt = db_list_init(argv[0], hostname, domain, xport,
			NULL, 0, NULL, 0)) == NULL) {
                printf("Database initialization error in %s\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        if (setjmp(exit_env) != 0) {
		db_list_done(pclt, NULL, 0, NULL, 0);
		printf("%s: received %d CAN messages\n", argv[0], count);
                exit(EXIT_SUCCESS);
        } else
               sig_ign(sig_list, sig_hand);

		alt_tsi.ignition = 0;
		db_clt_write(pclt, DB_ALT_TSI_VAR, 
			sizeof(alt_tsi), (void *) &alt_tsi);
	return 0;
}
