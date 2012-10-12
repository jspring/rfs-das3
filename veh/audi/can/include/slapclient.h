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

#ifndef SLAPCLIENT_H
#define SLAPCLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#ifdef _WIN32
#include <io.h>
#include <winsock2.h>
#else
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#endif

#include "slapdecl.h"
#include "slaptypes.h"


#define SLAP_DEBUG if(0)

/**
 * @file slapclient.h Definitions of the cSlap Client API
 *
 * @defgroup cslap cSlap C-API
 * See the <code>exampleclient.c</code> below for a simple
 * example how to use the cSlap C-API: \include exampleclient.c
 * @ingroup cSlap
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif


/**
 * Defintion for callback function that can be registered to receive
 * {@link slap_DataObject}s from subscriptions; the callback function
 * is always called when a new data element arrives an must return as soon as
 * possible!
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @param data Reference to the {@link slap_DataObject} received; this reference
 * is invalid and will be deleted after this function
 */
typedef int (*slap_onDataFunction) (void * ctxt, slap_DataObject * data);

/**
 * Defintion for callback function that can be registered to receive
 * {@link slap_Status} events from the VAPI server; the callback function
 * is always called when a status message arrives an must return as soon as
 * possible!
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @param status The status received from the server
 *
 */
typedef int (*slap_onStatusFunction) (void * ctxt, slap_status_t status);

#if 0
/*
 * This callback function not used, because error handling is solved
 * by using return types.
 */
/**
 * Defintion for callback function that can be registered to receive
 * cSlap internal errors; the callback function not used, because error
 * handling is solved by using return types.
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @param ctxt A reference to the client context associated to the VAPI server
 * @param errorMsg Reference to a string containing the error message
 * @param errorCode The error code
 */
typedef int (*slap_onErrorFunction) (void * ctxt, const char * errorMsg, int errorCode);
#endif

/**
 * The default request timeout in milliseconds
 */
#define SLAP_DEFAULT_REQUEST_TIMEOUT 10000

/**
 * cSlap Client context - defines the association to the VAPI server
 */
typedef struct _slap_ClientCtxt {

	/**
	 * The last error occured within the client-context
	 */
	slap_status_t lastError;

	/**
	 * Last status- or error-message
	 */
	char * lastMsg;

	/**
	 * Request-response-sequence counter
	 */
	long seq;

	/**
	 * Request timeout (Defaults to 10000 msec.)
	 */
	unsigned long reqTimeout;

	/**
	 * Alive flag for client-context thread
	 */
	char alive;

	/**
	 * Debug flag
	 */
	char debug;

	/**
	 * Reference to data callback function
	 */
	slap_onDataFunction onData;

	/**
	 * Reference to status callback function
	 */
	slap_onStatusFunction onStatus;

	/**
	 * Can be initialzed with custom user data
	 */
	void * userData;

	/**
	 * Reference to private internal data
	 */
	void * internalData;

} slap_ClientCtxt;


/**
 * Enumeration type for notification patterns
 */
typedef enum _slap_notification_t {
	/**
	 * This notification pattern just sets the object
	 * to subscribed without requesting single or continuous
	 * updates from the server
	 */
	SLAP_NOTIFICATION_NEVER = 0,

	/**
	 * This notification pattern tells the server
	 * to send data every time a new value is available
	 * from the vehicle
	 */
	SLAP_NOTIFICATION_ON_CHANGE = 1,

	/**
	 * This notification pattern tells the server to
	 * send data once when it's available, but to avoid
	 * continous updates
	 */
	SLAP_NOTIFICATION_ONCE_AVAILABLE = 2
} slap_notification_t;


/**
 * Initialize the slap-library; this MUST be done
 * once in a client application to initialize resources
 * used by the library.
 *
 * @return 0 on success; -1 on failure
 */
CSLAP_DECLARE int slap_init();

/**
 * Check the initialization status of the slap-library.
 *
 * @return 0 if library is initialized; -1 otherwise
 */
CSLAP_DECLARE int slap_initStatus();

/**
 * Used to Shutdown the slap-library; this
 * should be done once just before exiting.
 */
CSLAP_DECLARE void slap_shutdown();


/**
 * Initialized a {@link slap_ClientCtxt} and opens a connection to the
 * VAPI server specified by host and port. The {@link slap_ClientCtxt}
 * is the handle for submitting commands and requests to the VAPI server.
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server to be initialized
 * @param host Hostname or IP
 * @param port Server port
 * @return 0 on success; -1 on failure
 */
CSLAP_DECLARE int slap_openConnection(slap_ClientCtxt * ctxt, const char * host, int port);


/**
 * Close and shutdown a SLAP client connection and discard
 * the {@link slap_ClientCtxt}.
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @return 0 on success; -1 on failure
 */
CSLAP_DECLARE int slap_closeConnection(slap_ClientCtxt * ctxt);


/**
 * Set the data callback function for a client context; the callback function
 * is always called when a new data element arrives an must return as soon as
 * possible!
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @param onData Reference to {@link slap_onDataFunction} callback; <code>NULL</code>
 * can be used to delete/disable the callback
 *
 * @return 0 on success; -1 on failure
 */
CSLAP_DECLARE int slap_setDataListener(slap_ClientCtxt * ctxt, slap_onDataFunction onData);

/**
 * Set the status callback function for a client context; the callback function
 * is always called when a status message arrives an must return as soon as
 * possible!
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @param onStatus Reference to {@link slap_onStatusFunction} callback; <code>NULL</code>
 * can be used to delete/disable the callback
 *
 * @return 0 on success; -1 on failure
 */
CSLAP_DECLARE int slap_setStatusListener(slap_ClientCtxt * ctxt, slap_onStatusFunction onStatus);

/**
 * Set user specific data for a client context; can be used to pass arguments
 * or references to callback functions.
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @param userData Reference to the user data
 * @return 0 on success; -1 on failure
 */
CSLAP_DECLARE int slap_setUserData(slap_ClientCtxt * ctxt, void * userData);

/**
 * Get the current request timeout of a lient-context; defaults to 10000 msec.
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @return Current request timeout
 * milliseconds
 */
CSLAP_DECLARE unsigned long slap_getRequestTimeout(const slap_ClientCtxt * ctxt);

/**
 * Set request timeout for all future request for a client-context.
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @param msec new request timeout in msec.
 * @return 0 on success; -1 on failure
 */
CSLAP_DECLARE int slap_setRequestTimeout(slap_ClientCtxt * ctxt, unsigned long msec);

/**
 * Get the last status code of a client-context.
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @return The last response status code
 */
CSLAP_DECLARE slap_rspStatus_t slap_getCtxtStatus(const slap_ClientCtxt * ctxt);

/**
 * Get the last status message of a client-context.
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @return The last status message; <code>NULL</code> if no message is
 * available
 */
CSLAP_DECLARE const char * slap_getCtxtStatusMsg(const slap_ClientCtxt * ctxt);

/**
 * Reset the context status to ok with no message for a client-context.
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @return The context status after the reset
 */
CSLAP_DECLARE slap_rspStatus_t slap_resetCtxtStatus(slap_ClientCtxt * ctxt);

/**
 * Subscribe to a VAPIObject.
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @param url URL of the object
 * @param ival Subscription interval in msec (must be supported and may be ignored by server)
 * @param notification Notification pattern to be used
 * @param resolution Set signal resolution for notification (default is 0.0)
 * @param content Set sending content on notification
 * @param timestamp Enable/disable server-timestamping
 * (must be supported and may be ignored by server)
 *
 * @return 0 on success; -1 on failure
 */
CSLAP_DECLARE int slap_subscribeObject(slap_ClientCtxt * ctxt,
		const char * url,
		int ival,
		slap_notification_t notification,
		double resolution,
		int content,
		int timestamp);

/**
 * Unsubscribe from an object.
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @param url URL of object to unsubscribe
 *
 * @return 0 on success; -1 on failure
 */
CSLAP_DECLARE int slap_unsubscribeObject(slap_ClientCtxt * ctxt, const char * url);

/**
 * Get the data values of an object (object must be subscribed before).
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @param url URL of object to get data
 * @param dataObject Reference to a ptr where the resulting {@link slap_DataObject} will
 * be stored; the user is responsible for freeing resources of the data object
 *
 * @return 0 on success; -1 on failure
 */
CSLAP_DECLARE int slap_getObject(slap_ClientCtxt * ctxt, const char * url, slap_DataObject ** dataObject);

/**
 * Set an object value; not implemented, yet!
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 */
CSLAP_DECLARE int slap_setDataElements(slap_ClientCtxt * ctxt, const char * url,
		const slap_DataElement * dataElements[], size_t numDataElements,
		slap_SetReport ** setReport);

/**
 * Get the VAPI server information
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @param serverData Reference to ptr that will be initialized with the server information
 * @return 0 on success; -1 on failure
 */
CSLAP_DECLARE int slap_getServerInfo(slap_ClientCtxt * ctxt, slap_ServerData ** serverData);

/**
 * Get VAPI server object directory
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @param urlPattern Regular expression for object urls that should match; <code>NULL</code>
 * can be used to match all entries
 * @param fromEntry The first entry of the matching set
 * @param numOfEntries Maximum number of entries the server should give back
 * @param urlList Reference to a ptr to {@link slap_UrlList} that will be initialized with
 * the server (sub-)directory
 * @return 0 on success; -1 on failure
 */
CSLAP_DECLARE int slap_getObjectDir(slap_ClientCtxt * ctxt,
		const char * urlPattern, int fromEntry, int numOfEntries,
		slap_UrlList ** urlList);

/**
 * Get the object info of a VAPIObject.
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @param url Url of the vapi-object
 * @param objInfo Reference to a ptr that will be initialized with object info
 * of a VAPIObject
 * @return 0 on success; -1 on failure
 */
CSLAP_DECLARE int slap_getObjectInfo(slap_ClientCtxt * ctxt, const char * url,
		slap_InfoObject ** objInfo);

/**
 * Enable/disable and set VAPI server heartbeat; if the
 * heartbeat is enabled the VAPI server will send alive status-messages
 * to the client each ival seconds; the client can implement the
 * {@link slap_onStatusFunction} callback to receive the alive messages
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @param ival Heartbeat interval; 0 for heartbeat off
 * @return 0 on success; -1 on failure
 */
CSLAP_DECLARE int slap_setHeartbeat(slap_ClientCtxt * ctxt, int ival);

/**
 * Send an alive command to the VAPI server.
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 * @return 0 on success; -1 on failure
 */
CSLAP_DECLARE int slap_sendAlive(slap_ClientCtxt * ctxt);

/**
 * Do authentification with server; this feature not implemented, yet!
 *
 * @param ctxt Reference to the {@link slap_ClientCtxt} associated with the VAPI server
 */
CSLAP_DECLARE int slap_doAuthenicate(slap_ClientCtxt * ctxt, const char * user, const char * passwd);


#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /*SLAPCLIENT_H*/
