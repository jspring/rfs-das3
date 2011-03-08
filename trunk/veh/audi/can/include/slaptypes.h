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

#ifndef SLAPTYPES_H_
#define SLAPTYPES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#if defined(WIN32) || defined(_WINDOWS)
#include <winsock2.h>
#else
#include <sys/time.h>
#endif

#include "slapdecl.h"


/**
 * @file slaptypes.h Definitions of cSlap datatypes
 *
 * @defgroup cslap cSlap C-API
 * @ingroup cSlap
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Enumeration of SLAP vapi types
 */
typedef enum _slap_vtype_t {
	SLAP_VTYPE_NONE = 0,
	SLAP_VTYPE_ACT  = 1,
	SLAP_VTYPE_ENM  = 2,
	SLAP_VTYPE_ABS  = 3,
	SLAP_VTYPE_IDT  = 4,
	SLAP_VTYPE_SPC  = 5,
	SLAP_VTYPE_REL  = 6,
	SLAP_VTYPE_TIM  = 7,
	SLAP_VTYPE_STM  = 8,
	SLAP_VTYPE_TXT  = 9,
} slap_vtype_t;

/**
 * String representations for <code>slap_DataElement</code>s
 * for <code>slap_vtype_t</code>
 */
static const char * SLAP_VTYPE_STR[] = {
	"None", "Act", "Enm", "Abs", "Idt", "Spc", "Rel", "Tim", "Stm", "Txt"
};

/**
 * String representations for info types for <code>slap_vtype_t</code>
 */
static const char * SLAP_VTYPE_INFO_STR[] = {
	"None",
	"Activity",
	"Enumeration",
	"Absolute",
	"Identity",
	"Specification",
	"Relative",
	"Time",
	"Stream",
	"Text"
};

/**
 * Enumeration for response msg states
 */
typedef enum _slap_rspStatus_t {
	SLAP_RSP_STATUS_OK                          =  0,
	SLAP_RSP_STATUS_ERROR                       =  1,
	SLAP_RSP_STATUS_VERSION_NOT_SUPPORTED       =  2,
	SLAP_RSP_STATUS_NOT_IMPLEMENTED             =  3,
	SLAP_RSP_STATUS_SUBSCRIPTION_LIMIT_REACHED  =  4,
	SLAP_RSP_STATUS_NO_WRITE_ACCESS             =  5,
	SLAP_RSP_STATUS_NO_SUBSCRIPTION             =  6,
	SLAP_RSP_STATUS_NO_MATCHING_URL             =  7,
	SLAP_RSP_STATUS_INTERNAL_ERROR              =  8,
	SLAP_RSP_STATUS_MAX                         =  8
} slap_rspStatus_t;



/**
 * Enumeration for status event states
 */
typedef enum _slap_status_t {
	SLAP_STATUS_NONE     = 0,
	SLAP_STATUS_INIT     = 1,
	SLAP_STATUS_BYE      = 2,
	SLAP_STATUS_ALIVE    = 3,
	SLAP_STATUS_DATALOSS = 4
} slap_status_t;

/**
 * String representations for {@link slap_status_t}
 */
static const char * SLAP_STATUS_STR[] = {
	"None", "Init", "Bye", "Alive", "Dataloss"
};

/**
 * Maximum length of an identifier
 */
#define SLAP_IDENTIFIER_TYPE_MAX_LEN 32

/**
 * Maxmimum length of a name
 */
#define SLAP_NAME_TYPE_MAX_LEN 32

/**
 * Maxmimum length of a unit specifier
 */
#define SLAP_UNIT_TYPE_MAX_LEN 32

/**
 * Identifier type for urls, names, ids, unit; limited to
 * <code>SLAP_IDENTIFIER_TYPE_MAX_LEN</code> chars
 */
typedef char slap_ident_t [SLAP_IDENTIFIER_TYPE_MAX_LEN + 1] ;

/**
 * Unknown sequence-nr.
 */
#define SLAP_SEQ_NONE -1

/**
 * Access type for a VAPIObject
 */
typedef enum _slap_access_t {
	SLAP_ACCESS_NONE = 0,
	SLAP_ACCESS_READ = 1,
	SLAP_ACCESS_WRITE = 2,
	SLAP_ACCESS_READWRITE = 3
} slap_access_t;

/**
 * String representations for <code>slap_access_t</code>
 */
static const char * SLAP_ACCESS_TYPE_STR[] = {
	"none", "read", "write", "readwrite"
};

/**
 * URL-match or a single object directory entry
 */
typedef struct _slap_UrlMatch {
	/**
	 * URL
	 */
	char url[SLAP_IDENTIFIER_TYPE_MAX_LEN + 1];

	/**
	 * Access type
	 */
	slap_access_t access;

	/**
	 * Flag if object is subscribed by
	 * the calling client
	 */
	char isSubscribed;
} slap_UrlMatch;

/**
 * VAPI object (sub-)directory
 */
typedef struct _slap_UrlList {
	/**
	 * References to URL matches
	 */
	slap_UrlMatch ** match;

	/**
	 * Number of URL matches
	 */
	int numMatches;
} slap_UrlList;

/**
 * Function to clear the contents of the specified {@link slap_UrlList}.
 *
 * @param urlList The url-list to be cleared
 * @return The cleared {@link slap_UrlList} that can be freed
 */
CSLAP_DECLARE slap_UrlList * slap_clearUrlList(slap_UrlList * urlList);


/**
 * Protocol info type
 */
typedef struct _slap_ProtocolInfo {
	/**
	 * Protocol version
	 */
	float protocol;

	/**
	 * Maximum number of subscriptions supported
	 * by the server
	 */
	int subscriptionLimit;

	/**
	 * Flag if server supports the 'ObjectInfo' command
	 */
	char objInfoCmd;

	/**
	 * Flag if server supports the 'Set' command
	 */
	char setCmd;

	/**
	 * Flag if server supports authentification
	 */
	char authCmd;

	/**
	 * Flag if server supports the 'Heartbeat' command
	 */
	char heartbeatCmd;

	/**
	 * Flag if server supports timestamping data elements
	 */
	char timeStampingDat;

} slap_ProtocolInfo;

/**
 * Server information type
 */
typedef struct _slap_ServerData {
	/**
	 * Description
	 */
	char * description;

	/**
	 * Reference to a list of {@link slap_ProtocolInfo}s
	 */
	slap_ProtocolInfo ** info;

	/**
	 * Size of the list containing protocol infos
	 */
	int numInfos;
} slap_ServerData;

/**
 * Function to clear the contents of the specified {@link slap_ServerData}.
 *
 * @param serverData Server data to be cleared
 * @return The cleared {@link slap_ServerData} that can be freed
 */
CSLAP_DECLARE slap_ServerData * slap_clearServerData(slap_ServerData * serverData);

/**
 * Type for cSlap status, that can be received by
 * using the status callback.
 * TODO: Eggers - Make this more simple
 */
#if 0
typedef struct _slap_Status {
	/**
	 * Status type
	 */
	slap_status_t type;
} slap_Status;
#endif

/**
 * Value state type
 */
typedef enum _slap_valueState_t {
	SLAP_VALUE_STATE_OK = 0,
	SLAP_VALUE_STATE_NODATA = 1,
	SLAP_VALUE_STATE_ERROR = 2,
	SLAP_VALUE_STATE_DEFAULT = 3
} slap_valueState_t;

/**
 * String representations of {@link slap_valueState_t}.
 */
static const char * SLAP_VALUE_STATE_STR[] = {
	"ok", "nodata", "error", "default"
};


/**
 * Type for data elements like <code>&lt;Abs|Rel|etc/&gt;</code> contained
 * in a &lt;Dat/&gt; element; this specifies a members of
 * {@link slap_DataObject}; ; <code>&lt;Rel|Abs|Spc/&gt;</code> are
 * represented as '<code>double</code>', <code>&lt;Act/&gt;</code> is
 * represented as '<code>bool</code>' and <code>&lt;Txt|Idt|Tim/&gt;</code>
 *  are represented as c-string. <code>&lt;Stm/&gt;</code> is not supported, yet!
 */
typedef struct _slap_DataElement {
	/**
	 * VAPI type of the value
	 */
	slap_vtype_t vtype;

	/**
	 * Name of the value or members
	 */
	char name[SLAP_NAME_TYPE_MAX_LEN + 1];

	union {
		/**
		 * Possible double value
		 */
		double dblValue;

		/**
		 * Possible string value
		 */
		char * strValue;

		/**
		 * Possible boolean value
		 */
		int boolValue;
	} val;

	/**
	 * The value state
	 */
	slap_valueState_t state;

	/**
	 * A message that may come with the value, e.g. if
	 * its state is 'error'
	 */
	char * msg;

} slap_DataElement;


/**
 * Create a clone the specified {@link slap_DataElement}.
 *
 * @param dataElement Reference to original
 * @return A clone of the data element; NULL on failure
 */
CSLAP_DECLARE slap_DataElement * slap_cloneDataElement(const slap_DataElement * dataElement);

/**
 * Cleanup the contents of the specified {@link slap_DataElement}.
 *
 * @param dataElement The data element
 * @return The cleared data element that can be freed
 */
CSLAP_DECLARE slap_DataElement * slap_clearDataElement(slap_DataElement * dataElement);

/**
 * Create an <code>Activity</code> value.
 *
 * @param name Member name of the value
 * @param value The value
 * @return A new allocated {@link slap_DataElement} containing the type, name and value
 */
CSLAP_DECLARE slap_DataElement * slap_createActValue(const char * name, int value);

/**
 * Create an <code>Enumeration</code> value.
 *
 * @param name Member name of the value
 * @param value The value
 * @return A new allocated {@link slap_DataElement} containing the type, name and value
 */
CSLAP_DECLARE slap_DataElement * slap_createEnmValue(const char * name, const char * value);

/**
 * Create an <code>Absolute</code> value.
 *
 * @param name Member name of the value
 * @param value The value
 * @return A new allocated {@link slap_DataElement} containing the type, name and value
 */
CSLAP_DECLARE slap_DataElement * slap_createAbsValue(const char * name, double value);

/**
 * Create an <code>Text</code> value.
 *
 * @param name Member name of the value
 * @param value The value
 * @return A new allocated {@link slap_DataElement} containing the type, name and value
 */
CSLAP_DECLARE slap_DataElement * slap_createTxtValue(const char * name, const char * value);

/**
 * Create an <code>Relative</code> value.
 *
 * @param name Member name of the value
 * @param value The value
 * @return A new allocated {@link slap_DataElement} containing the type, name and value
 */
CSLAP_DECLARE slap_DataElement * slap_createRelValue(const char * name, double value);

/**
 * Create an <code>Identity</code> value.
 *
 * @deprecated Identity is deprecated - {@link Text} should be used instead!!!
 * @param name Member name of the value
 * @param value The value
 * @return A new allocated {@link slap_DataElement} containing the type, name and value
 */
CSLAP_DECLARE slap_DataElement * slap_createIdtValue(const char * name, const char * value);

/**
 * Create an <code>Activity</code> value.
 *
 * @deprecated Specification is deprecated - {@link Absolute} should be used instead!!!
 * @param name Member name of the value
 * @param value The value
 * @return A new allocated {@link slap_DataElement} containing the type, name and value
 */
CSLAP_DECLARE slap_DataElement * slap_createSpcValue(const char * name, double value);

/**
 * Create an <code>Time</code> value.
 *
 * @param name Member name of the value
 * @param value The value
 * @return A new allocated {@link slap_DataElement} containing the type, name and value
 */
CSLAP_DECLARE slap_DataElement * slap_createTimValue(const char * name, const char * value);

/**
 * Create an <code>Stream</code> value.
 *
 * @param name Member name of the value
 * @param value The value
 * @return A new allocated {@link slap_DataElement} containing the type, name and value
 */
CSLAP_DECLARE slap_DataElement * slap_createStmValue(const char * name);


/**
 * Type for vapi-object data, that is send by
 * the vapi-server when a vapi-object is subscribed;
 * this type is passed to the data-callback.
 *
 */
typedef struct _slap_DataObject {
	/**
	 * Url of the vapi-object
	 */
	char url[SLAP_NAME_TYPE_MAX_LEN + 1];

	/**
	 * List of {@link slap_DataElement}s containing
	 * the vapi-object members
	 */
	slap_DataElement ** elem;

	/**
	 * Size of the list of members
	 */
	unsigned int size;

	/**
	 * Timestamp of the data-element
	 */
	long timestamp;

	/**
	 * High resolution timestamp containing seconds and useconds
	 * since epoch
	 */
	struct timeval timestamp_highres;

} slap_DataObject;

/**
 * Only usable on a root object, that is, an object,
 * which was returned by onData or as a result to a function call.
 * 
 * \param object the data object
 * \param name the name of the member, which should be returned
 *
 * \return the member. Be careful here, This can be ANY member, so lists and objects are possible, too.<br/>
 *   NULL if member was not found
 */
slap_DataElement * slap_getElement(slap_DataObject *object, const char *name);

/**
 * Clone a <code>slap_DataObject</code>.
 *
 * @param dataObject Reference to original
 * @return A clone of the data object; NULL on failure
 */
CSLAP_DECLARE slap_DataObject * slap_cloneDataObject(const slap_DataObject * dataObject);

/**
 * Cleanup the contents of the specified data object.
 *
 * @param dataObject The data object
 * @return The cleared data-object that can be freed
 */
CSLAP_DECLARE slap_DataObject * slap_clearDataObject(slap_DataObject * dataObject);



/**
 * Status type for {@link slap_SetElement}
 */
typedef enum _slap_setResult {
	SLAP_SET_RESULT_OK = 0,
	SLAP_SET_RESULT_ERROR = 1,
	SLAP_SET_RESULT_NO_MATCHING_MEMBER = 2,
	SLAP_SET_RESULT_TYPE_MISMATCH = 3
} slap_setResult_t;

/**
 * Status type string {@link slap_setResult_t}
 */
static const char * SLAP_SET_RESULT_STR[] = {
	"ok", "error", "no matching member", "type mismatch"
};

/**
 * Set element
 */
typedef struct _slap_SetElement {

	/**
	 * Name of the value or members
	 */
	char name[SLAP_NAME_TYPE_MAX_LEN + 1];

	/**
	 * The result
	 */
	slap_setResult_t result;

	/**
	 * A message that may come with the value, e.g. if
	 * its state is 'error'
	 */
	char * msg;

} slap_SetElement;


/**
 * Clone a <code>slap_SetElement</code>.
 *
 * @param setElement Reference to original
 * @return A clone of the set element; NULL on failure
 */
CSLAP_DECLARE slap_SetElement * slap_cloneSetElement(const slap_SetElement * setElement);

/**
 * Cleanup the contents of the specified set element
 *
 * @param setElement The set element
 * @return The cleared set element that can be freed
 */
CSLAP_DECLARE slap_SetElement * slap_clearSetElement(slap_SetElement * setElement);

/**
 * Type for set report
 */
typedef struct _slap_SetReport {
	/**
	 * Url of the vapi-object
	 */
	char url[SLAP_NAME_TYPE_MAX_LEN + 1];

	/**
	 * List of {@link slap_SetElement}s
	 */
	slap_SetElement ** elem;

	/**
	 * Size of the list of members
	 */
	unsigned int size;
} slap_SetReport;

/**
 * Clone a <code>slap_SetReport</code>.
 *
 * @param setReport Reference to original
 * @return A clone of the set report; NULL on failure
 */
CSLAP_DECLARE slap_SetReport* slap_cloneSetReport(const slap_SetReport * setReport);

/**
 * Cleanup the contents of the specified set element
 *
 * @param setReport The set report
 * @return The cleared set report that can be freed
 */
CSLAP_DECLARE slap_SetReport * slap_clearSetReport(slap_SetReport * setReport);


/**
 * General VAPIType
 */
typedef struct _slap_VapiType {
	/**
	 * Value type
	 */
	slap_vtype_t vtype;

	/**
	 * Name of the value
	 */
	char name[SLAP_NAME_TYPE_MAX_LEN + 1];
} slap_VapiType;


/**
 * Description of a {@link slap_DataObject}
 */
typedef struct _slap_Description {
	/**
	 * Language code
	 */
	char language[5];

	/**
	 * Description
	 */
	char * description;
} slap_Description;

/**
 * Cleanup the contents of the specified {@link slap_Description}.
 *
 * @param description The description
 * @return The cleared description that can be freed
 */
CSLAP_DECLARE slap_Description * slap_clearDescription(slap_Description * description);

/**
 * Characteristic type for {@link slap_DataObject}
 */
typedef enum _slap_characteristic_t {
	SLAP_CHARACTERISTIC_NONE = 0,
	SLAP_CHARACTERISTIC_STATIC = 1,
	SLAP_CHARACTERISTIC_DYNAMIC = 2,
	SLAP_CHARACTERISTIC_EVENT = 3
} slap_characteristic_t;

/**
 * String representations of {@link slap_characteristic_t}
 */
static const char * SLAP_CHARACTERISTIC_STR[] = {
	"none", "static", "dynamic", "event"
};

/**
 * This type defines VAPI object info
 * and provides a complete structure for
 * an object
 */
typedef struct _slap_InfoObject {

	/**
	 * Url of the data object
	 */
	char url[SLAP_NAME_TYPE_MAX_LEN + 1];

	/**
	 * Access type
	 */
	slap_access_t access;

	/**
	 * Characterristic type (static, dynamic, event)
	 */
	slap_characteristic_t characteristic;

	/**
	 * List of descriptions
	 */
	slap_Description ** description;

	/**
	 * Number of descriptions
	 */
	unsigned int numDescriptions;

	/**
	 * List of data object members
	 */
	slap_VapiType ** info;

	/**
	 * Number of members
	 */
	unsigned int numInfos;
} slap_InfoObject;

/**
 * Cleanup the contents of the specified {@link slap_InfoObject}.
 *
 * @param infoObject Reference to the {@link slap_InfoObject}
 * @return Reference to the cleared {@link slap_InfoObject}
 */
CSLAP_DECLARE slap_InfoObject * slap_clearInfoObject(slap_InfoObject * infoObject);



/**
 * Info-type for Absolute
 */
typedef struct _slap_Absolute {
	/**
	 * Head with type and name
	 */
	slap_VapiType head;

	/**
	 * Unit of the value, e.g. m, km/h
	 */
	char unit[SLAP_UNIT_TYPE_MAX_LEN + 1];

	/**
	 * Minimum of the value
	 */
	double min;

	/**
	 * Maximum of the value
	 */
	double max;

	/**
	 * Native interval of the value if available
	 */
	unsigned int ival;

	/**
	 * Resolution of the value
	 */
	double resolution;
} slap_Absolute;

/**
 * Info-type for Activity
 */
typedef struct _slap_Activity {
	/**
	 * Head with type and name
	 */
	slap_VapiType head;
} slap_Activity;

/**
 * Info-type for Enumeration
 */
typedef struct _slap_Enumeration {
	/**
	 * Head with type and name
	 */
	slap_VapiType head;

	/**
	 * Number of members in the enumeration
	 */
	unsigned int size;

	/**
	 * Array with references to the ids
	 */
	slap_ident_t * member;
} slap_Enumeration;

/**
 * Info-type for Text (replaces Identity)
 */
typedef struct _slap_Text {
	/**
	 * Head with type and name
	 */
	slap_VapiType head;

	/**
	 * Regular expression for Identity; can be empty
	 */
	char regExp[128];
} slap_Text;

/**
 * Info-type for Identity
 *
 * @deprecated The Identity type is deprecated
 * since VAPI1 and is replaced by the Absolute type
 */
typedef struct _slap_Identity {
	/**
	 * Head with type and name
	 */
	slap_VapiType head;

	/**
	 * Regular expression for Identity; can be empty
	 */
	char regExp[128];
} slap_Identity;

/**
 * Info-type for Relative
 */
typedef struct _slap_Relative {
	/**
	 * Head with type and name
	 */
	slap_VapiType head;

	/**
	 * Minimum of the value
	 */
	double min;

	/**
	 * Maximum of the value
	 */
	double max;

	/**
	 * Minimum label of the value, e.g. 'min', 'empty', 'low'
	 */
	char minLabel[SLAP_IDENTIFIER_TYPE_MAX_LEN + 1];

	/**
	 * Maximum label of the value, e.g. 'max', 'fulle', 'high'
	 */
	char maxLabel[SLAP_IDENTIFIER_TYPE_MAX_LEN + 1];

	/**
	 * Native interval of the value if available
	 */
	unsigned int ival;

	/**
	 * Resolution of the value
	 */
	double resolution;
} slap_Relative;

/**
 * Info-type for Specification
 *
 * @deprecated The Specification type is deprecated
 * since VAPI1 and is replaced by the Absolute type
 */
typedef struct _slap_Specification {
	/**
	 * Head with type and name
	 */
	slap_VapiType head;

	/**
	 * Unit of the value
	 */
	char unit[SLAP_UNIT_TYPE_MAX_LEN + 1];
} slap_Specification;

/**
 * Info-type for Stream; currently empty and not used
 */
typedef struct _slap_Stream {
	/**
	 * Head with type and name
	 */
	slap_VapiType head;
} slap_Stream;

/**
 * Info-type for Time
 */
typedef struct _slap_Time {
	/**
	 * Head with type and name
	 */
	slap_VapiType head;

	/**
	 * Flag if time is localtime or not
	 */
	int isLocalTime;
} slap_Time;


#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /*SLAPTYPES_H_*/
