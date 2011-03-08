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

#ifndef SLAPUTILS_H_
#define SLAPUTILS_H_

#include <stdlib.h>
#include <errno.h>
#include <time.h>

#if defined(WIN32) || defined(_WINDOWS)
#include <winsock2.h>
#else
#include <sys/time.h>
#endif

#include "slapdecl.h"

/**
 * @file slaputils.h cSlap Utility Functions
 *
 * @defgroup cslap_utils cSlap Utilities
 * @ingroup cSlap
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Sleep the specified time in seconds.
 *
 * @param sec Sleep time in seconds
 */
CSLAP_DECLARE void slap_sleep(unsigned int sec);

/**
 * Sleep the specified time in milliseconds.
 *
 * @param msec Sleep time in milliseconds
 */
CSLAP_DECLARE void slap_msleep(unsigned long msec);

/**
 * Sleep the specified time in microseconds.
 *
 * @param usec Sleep time in microseconds
 */
CSLAP_DECLARE void slap_usleep(unsigned long usec);


/**
 * Convert a string to a long value.
 *
 * @param str The string to be converted
 * @param value Reference to a long to store the result in
 * @return 0 on success; -1 on failure; -2 if value is out of range
 */
CSLAP_DECLARE int slap_strtol(const char * str, long * value);

/**
 * Convert a string to a float value.
 *
 * @param str The string to be converted
 * @param value Reference to a float to store the result in
 * @return 0 on success; -1 on failure; -2 if value is out of range
 */
CSLAP_DECLARE int slap_strtof(const char * str, float * value);

/**
 * Convert a string to a double value.
 *
 * @param str The string to be converted
 * @param value Reference to a double to store the result in
 * @return 0 on success; -1 on failure; -2 if value is out of range
 */
CSLAP_DECLARE int slap_strtod(const char * str, double * value);

/**
 * Testcase for time parser.
 */
CSLAP_DECLARE void slap_test_iso8601_time();

/**
 * Parses a string containing an iso8601 time string and generates a
 * <code>struct timeval</code> containing the seconds and useconds since
 * epoch.
 *
 * @param timeStr The string containing the timestamp
 * @param result The resulting <code>struct timeval</code>
 * @return Ptr to the remaining string; <code>NULL</code> parsing failed
 */
CSLAP_DECLARE const char * slap_iso8601_time_to_timeval(const char * timeStr, struct timeval * result);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */

#endif /*CSLAPUTILS_H_*/
