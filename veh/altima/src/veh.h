// veh.h - Common variables for Audis and Altimas

#ifndef VEH_H
#define VEH_H
/// These variables require processing other than DB reads done by wrfiles_nt.c
static double seconds_since_midnight = 0.0;    // from hh:mm.ss.sss in column 1
static double seconds_since_start = 0.0;       // local time since start of run
static double gps_utc_seconds = 0.0;           // local UTC seconds since midnight
static double clock_gps_read_seconds = 0.0;    // gps read time, seconds since midnight
static double local_clock_seconds = 0.0;       // local time seconds since midnight
static float gps_formatted_utc_time = 0.0;    // hhmmss.ss
static char * not_implemented = "9999";
#endif
