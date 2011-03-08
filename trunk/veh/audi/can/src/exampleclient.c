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

#include <slapclient.h>
#include <slaputils.h>
#include <signal.h>
#include <stdlib.h>

int enginespeedavailable = 0;
int vehiclespeedavailable = 0;

int running;


/**
 * onData function is called, when a Dat arrives
 */
int onData(void *cli, slap_DataObject *obj)
{
	fprintf(stdout, "the current value of EngineSpeed is %f\n", obj->elem[0]->val.dblValue);
}

/**
 * onStatus function is called when a Status arrives
 */
int onStatus(void *cli, slap_status_t status)
{
}

void doDir(slap_ClientCtxt *cli)
{
	int i;
	slap_UrlList *dir = NULL; 

	/* here we get a dir and walk through it to make sure, the two objects we want, are in fact available */
	/* this is quite an optional step, because the retturn value ofthe subscribes contains the same info */

	if (slap_getObjectDir(cli, NULL, 0, 0, &dir) == 0) {
		for (i = 0; i < dir->numMatches; i++) {
			if (strcmp(dir->match[i]->url, "EngineSpeed") == 0) {
				enginespeedavailable = 1;
			} else if (strcmp(dir->match[i]->url, "VehicleSpeed") == 0) {
				vehiclespeedavailable = 1;
			}
			if (vehiclespeedavailable && enginespeedavailable) {
				break;
			}
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
	char host[128] = {0};
	short port = 28500;

	int retval;

	if (argc > 1) {
		strcpy(host, argv[1]);
	}

	if (argc > 2) {
		port = strtol(argv[2], NULL, 10);
	}
	fprintf(stdout, "connecting to host %s\n", host?host:"localhost");
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
	retval = slap_openConnection(client, host[0]?host:"localhost", 28500);

	if (retval != 0) {
		fprintf(stderr, "cannot connect to server, exiting!\n");
		exit(-1);
	}

	/* to see what objects the server has, a Dir is needed */
	doDir(client);

	if (enginespeedavailable) {
		/* subscription to an object means, that we will be informed about updates on this object */
		retval = slap_subscribeObject(client,
				"EngineSpeed", /* the object EngineSpeed */
				100, /* interval of 100 milliseconds */
				SLAP_NOTIFICATION_ON_CHANGE,
				0, /* no resolution filter, this will be removed in future SLAP version anyway */
				1,
				0 /* no timestamp */
				);

		if (retval != 0) {
			fprintf(stderr, "Subscription of EngineSpeed failed\n");
		}
	}

	if (vehiclespeedavailable) {
		/* if just the occasional data is needed from an object and not every update, a subscription has to be done anyway but with a difference */
		retval = slap_subscribeObject(client,
				"VehicleSpeed",
				0,
				SLAP_NOTIFICATION_NEVER, /* we don't want to get updates */
				0,
				0,
				0);

		if (retval != 0) {
			fprintf(stderr, "Subscription of VehicleSpeed failed\n");
		}
	}

	if (!enginespeedavailable && !vehiclespeedavailable) {
		fprintf(stderr, "neither VehicleSpeed nor EngineSpeed is available. quitting\n");
	}

	/*
	 * At this point we should get updates for "EngineSpeed" and the server should be prepared to deliver data on "VehicleSpeed"
	 */

	running = 1;

	signal(SIGINT, setRunning);

	while(running) {
		
		slap_sleep(1);
		
		/* this should be the occasional interest in the data of VehicleSpeed */
		slap_getObject(client, "VehicleSpeed", &tmpobj);
		if (tmpobj) {
			if (tmpobj->elem[0]->state == SLAP_VALUE_STATE_OK) {
				fprintf(stdout, "VehicleSpeed is currently: %f\n", tmpobj->elem[0]->val.dblValue);
			} else {
				fprintf(stdout, "VehicleSpeed is currently not available\n");
			}
		}
	}

	/* remove the subscriptions. This is not necessry per se, but a nice thing to do */
	slap_unsubscribeObject(client, "VehicleSpeed");
	slap_unsubscribeObject(client, "EngineSpeed");

	/* deinitialization of the connection and the library */
	slap_closeConnection(client);
	slap_shutdown();

	return 0;

}

/**
 * @}
 */
