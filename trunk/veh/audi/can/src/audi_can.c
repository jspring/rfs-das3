/*
 * Vehicle API - cSlap
 * Copyright (c) 2003-2008 Volkswagen Group Research.
 * All rights reserved.
 *
 * Correspondence should be directed to Volkswagen at:
 *
 * Volkswagen AG
 * Jens Krueger
 * Letter box 1777/0
 * D-38436 Wolfsburg
 * GERMANY
 *
 * email: jens2.krueger@volkswagen.de
 *
 * Neither Volkswagen Group nor the authors admit liability
 * nor provide any warranty for any of this software.
 * This material is provided "AS-IS"
 *
 * Until the distribution is granted by the Volkswagen rights
 * department this sourcecode is under non disclosure and must
 * only be used within projects with the Volkswagen group.
 */


/**
 * @file exampleclient.c cSlap Example Client for C-API
 * \include exampleclient.c
 *
 * @defgroup exampleclient cSlap Example Client for C-API
 * @ingroup cSlap
 *
 * @{
 */

#include <db_include.h>
#include <db_utils.h>
#include <slapclient.h>
#include <slaputils.h>
#include "audi_can.h"
static int sig_list[] =
{
        SIGINT,
        SIGQUIT,
        SIGTERM,
        SIGALRM,
        ERROR,
};

static jmp_buf exit_env;

static void sig_hand(int code)
{
        if (code == SIGALRM)
                return;
        else
                longjmp(exit_env, code);
}

int running;
typedef struct {
	char objtype[30];
} objlist_t;

objlist_t objlist[] = {
	{"BrakeActuation"},		//1 boolean
	{"BrakingPressure"},		//2 double
	{"LateralAcceleration"},		//3 double
	{"LongitudinalAcceleration"}, 	//4 double
	{"PedalForce"},			//5 double
	{"SteeringWheelAngle"},		//6 double
	{"VehicleSpeed"},			//7 double
	{"YawVelocity"},			//8 double
	{"TurnSignalLights"},		//9 boolean
	{"CruiseControlSystemState"},	//10 ???
	{"CurrentGear"},			//11 ???
	{"TurnSignalLever"},		//12 ???
	{"WiperControl"}			//13 ???
};

/**
 * onData function is called, when a Dat arrives
 */
int onData(void *cli, slap_DataObject *tmpobj)
{
/*
	fprintf(stdout, "XX");
	switch(tmpobj->elem[0]->vtype) {
		case SLAP_VTYPE_REL:
		case SLAP_VTYPE_ABS:
		case SLAP_VTYPE_SPC:
			fprintf(stdout, "%s %.2f vtype dbl %d", 
			tmpobj->elem[0]->name,
			tmpobj->elem[0]->val.dblValue,
			(int)tmpobj->elem[0]->vtype);
			break;
		case SLAP_VTYPE_ACT:
		fprintf(stdout, "%s %d vtype bool %d", 
			tmpobj->elem[0]->name,
			tmpobj->elem[0]->val.boolValue,
			(int)tmpobj->elem[0]->vtype);
			break;
		case SLAP_VTYPE_TXT:
		case SLAP_VTYPE_IDT:
		case SLAP_VTYPE_TIM:
		fprintf(stdout, "%s %s vtype str %d", 
			tmpobj->elem[0]->name,
			tmpobj->elem[0]->val.strValue,
			(int)tmpobj->elem[0]->vtype);
			break;
		default:
 			fprintf(stdout,"%s -222.22222 vtype %d",
				tmpobj->elem[0]->name,
				(int)tmpobj->elem[0]->vtype);
			break;
	}
	fprintf(stdout, "\n");
*/
	return 0;
}

/**
 * onStatus function is called when a Status arrives
 */
int onStatus(void *cli, slap_status_t status)
{
	return 0;
}

void doDir(slap_ClientCtxt *cli)
{
	int i;
	slap_UrlList *dir = NULL; 

	/* here we get a dir and walk through it to make sure, the two objects we want, are in fact available */
	/* this is quite an optional step, because the return value of the subscribes contains the same info */

	if (slap_getObjectDir(cli, NULL, 0, 0, &dir) == 0) {
		printf("numMatches %d\n", dir->numMatches);
		for (i = 0; i < dir->numMatches; i++) {
			if (strcmp(dir->match[i]->url, objlist[i].objtype) == 0) 
				printf("%s is available\n", objlist[i].objtype);
			else
				printf("%s is not available\n", objlist[i].objtype);
			
		}
		slap_clearUrlList(dir);
		free(dir);
	}
}

void setRunning(int signum)
{
	running = 0;
}

int main(int argc, char **argv)
{
	slap_ClientCtxt *client;
	slap_DataObject *tmpobj;
	char *host = "localhost";
	short port = 28500;
	int i;
	int numobj = 13;
	int retval;
	audi_t audi;
	int counter = 0;
        db_clt_typ *pclt;              /* Database client pointer */
        char hostname[MAXHOSTNAMELEN+1];
        char *domain=DEFAULT_SERVICE;
        int xport = COMM_OS_XPORT;
        int option;
        int verbose = 0;
        int interval = 50;
        int no_db = 0;
        posix_timer_typ *ptimer;

        while ((option = getopt(argc, argv, "h:i:p:vn")) != EOF) {
                switch(option) {
                case 'h':
                        host = strdup(optarg);
                        break;
                case 'i':
                        interval = atoi(optarg);
                        break;
                case 'p':
                        port = atoi(optarg);
                        break;
                case 'v':
                        verbose = 1;
                        break;
                case 'n':
                        no_db = 1;
                        break;
                default:
                        fprintf(stderr, "Usage %s -d <device> -i <interval> -n (no DB) -v (verbose)\n",
                                argv[0]);
                        exit(1);
                        break;
                }
        }
	if(!no_db) {
        	get_local_name(hostname, MAXHOSTNAMELEN);
        	pclt = db_list_init(argv[0], hostname, domain, xport, NULL,
        	        0, NULL, 0);
	}

        /* Catch the signals SIGINT, SIGQUIT, and SIGTERM.  If signal occurs,
        * log out from database and exit. */
        if (setjmp(exit_env) != 0) {
                if (pclt != NULL)
	                db_list_done(pclt, NULL, 0, NULL, 0);
                exit(EXIT_SUCCESS);
        } else
                sig_ign(sig_list, sig_hand);

        if ((ptimer = timer_init( interval, ChannelCreate(0) )) == NULL) {
                fprintf(stderr, "Unable to initialize delay timer\n");
                exit(EXIT_FAILURE);
        }


	fprintf(stdout, "connecting to host %s\n", host);
	fprintf(stdout, "via port %d\n", port);


	client = malloc(sizeof(slap_ClientCtxt));
	memset(client, 0, sizeof(slap_ClientCtxt));

	/*
	 * Initialize library
	 */
	if(slap_init() < 0) {
		fprintf(stderr, "Cannot initialize cSlap library !\n");
		exit(-1);
	}

	slap_setDataListener(client, onData);

	slap_setStatusListener(client, onStatus);

	/* open a connection to a server on "localhost" on port 28500 */
	retval = slap_openConnection(client, host, 28500);

	if (retval != 0) {
		fprintf(stderr, "cannot connect to server, exiting!\n");
		exit(-1);
	}

	/* to see what objects the server has, a Dir is needed */
	doDir(client);

	/* subscription to an object means, that we will be informed about 
	** updates on this object */
	for(i = 0; i < numobj; i++) {
		retval = slap_subscribeObject(client,
		    objlist[i].objtype, /* the object EngineSpeed */
		    50, /* interval of 100 milliseconds */
		    SLAP_NOTIFICATION_ON_CHANGE,
		    0,/*no resolution filter (won't be in future SLAP version)*/
		    1,
		    0 /* no timestamp */
		);
//		retval = slap_subscribeObject(client,
//		    objlist[i].objtype, /* the object EngineSpeed */
//		    0,
//		    SLAP_NOTIFICATION_NEVER,
//		    0,
//		    0,
//		    0
//		);

		if (retval != 0)
		    fprintf(stderr, "Subscription of %s failed\n", objlist[i].objtype);

	}

	/*
	 * At this point we should get updates for "EngineSpeed" and the server
	** should be prepared to deliver data on "VehicleSpeed"
	 */

	running = 1;

	signal(SIGINT, setRunning);

	while(running) {
		
		slap_getObject(client, "BrakeActuation", &tmpobj);
		if ( tmpobj && 
		    (tmpobj->elem[0]->state == SLAP_VALUE_STATE_OK)) 
			audi.brake = tmpobj->elem[0]->val.boolValue;
		else
			audi.brake = -1;

		slap_getObject(client, "BrakingPressure", &tmpobj);
		if ( tmpobj && 
		    (tmpobj->elem[0]->state == SLAP_VALUE_STATE_OK)) 
			audi.brake_pressure = tmpobj->elem[0]->val.dblValue;
		else
			audi.brake_pressure = -222.22222;

		slap_getObject(client, "LateralAcceleration", &tmpobj);
		if ( tmpobj && 
		    (tmpobj->elem[0]->state == SLAP_VALUE_STATE_OK)) 
			audi.lat_acc = tmpobj->elem[0]->val.dblValue;
		else
			audi.lat_acc = -222.22222;

		slap_getObject(client, "LongitudinalAcceleration", &tmpobj);
		if ( tmpobj && 
		    (tmpobj->elem[0]->state == SLAP_VALUE_STATE_OK)) 
			audi.long_acc = tmpobj->elem[0]->val.dblValue;
		else
			audi.long_acc = -222.22222;

		slap_getObject(client, "PedalForce", &tmpobj);
		if ( tmpobj && 
		    (tmpobj->elem[0]->state == SLAP_VALUE_STATE_OK)) 
			audi.throttle = tmpobj->elem[0]->val.dblValue;
		else
			audi.throttle = -222.22222;

		slap_getObject(client, "SteeringWheelAngle", &tmpobj);
		if ( tmpobj && 
		    (tmpobj->elem[0]->state == SLAP_VALUE_STATE_OK)) 
			audi.steering_angle = tmpobj->elem[0]->val.dblValue;
		else
			audi.steering_angle = -222.22222;

		slap_getObject(client, "VehicleSpeed", &tmpobj);
		if ( tmpobj && 
		    (tmpobj->elem[0]->state == SLAP_VALUE_STATE_OK)) 
			audi.veh_speed = tmpobj->elem[0]->val.dblValue;
		else
			audi.veh_speed = -222.22222;

		slap_getObject(client, "YawVelocity", &tmpobj);
		if ( tmpobj && 
		    (tmpobj->elem[0]->state == SLAP_VALUE_STATE_OK)) 
			audi.yaw = tmpobj->elem[0]->val.dblValue;
		else
			audi.yaw = -222.22222;

		slap_getObject(client, "TurnSignalLights", &tmpobj);
		if ( tmpobj && 
		    (tmpobj->elem[0]->state == SLAP_VALUE_STATE_OK)) 
			audi.turn_lights= tmpobj->elem[0]->val.boolValue;
		else
			audi.turn_lights= -222.22222;

		slap_getObject(client, "CruiseControlSystemState", &tmpobj);
		if ( tmpobj && 
		    (tmpobj->elem[0]->state == SLAP_VALUE_STATE_OK)) 
			audi.cc = tmpobj->elem[0]->val.dblValue;
		else
			audi.cc = -222.22222;

		slap_getObject(client, "CurrentGear", &tmpobj);
		if ( tmpobj && 
		    (tmpobj->elem[0]->state == SLAP_VALUE_STATE_OK)) 
			audi.gear = tmpobj->elem[0]->val.dblValue;
		else
			audi.gear = -222.22222;

		slap_getObject(client, "TurnSignalLever", &tmpobj);
		if ( tmpobj && 
		    (tmpobj->elem[0]->state == SLAP_VALUE_STATE_OK)) 
			audi.turn_signal = tmpobj->elem[0]->val.boolValue;
		else
			audi.turn_signal = -222.22222;

		slap_getObject(client, "WiperControl", &tmpobj);
		if ( tmpobj && 
		    (tmpobj->elem[0]->state == SLAP_VALUE_STATE_OK)) 
			audi.wiper = tmpobj->elem[0]->val.dblValue;
		else
			audi.wiper = -222.22222;
	      if(!no_db) {
			db_clt_read(pclt, DB_USB4761_DIGIN_VAR, sizeof(usb4761_digin_typ), &audi.ignition);
			db_clt_write(pclt, DB_AUDI_VAR, sizeof(audi_t), &audi);
			}
                TIMER_WAIT (ptimer);
	}

	/* remove the subscriptions. This is not necessary, but a nice thing 
	** to do */
	for(i = 0; i < numobj; i++)
		slap_unsubscribeObject(client, objlist[i].objtype);

	/* deinitialization of the connection and the library */
	slap_closeConnection(client);
	slap_shutdown();

	return 0;

}

/**
 * @}
 */
