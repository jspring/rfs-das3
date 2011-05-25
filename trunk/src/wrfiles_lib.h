#include <db_include.h>
#include <sys_buff.h>
#include <evt300.h>
#include "sms_lib.h"
#include "data_log.h"

/// These variables require processing other than DB reads done by wrfiles_nt.c
extern double seconds_since_midnight;    // from hh:mm.ss.sss in column 1
extern double seconds_since_start;       // local time since start of run
extern double gps_utc_seconds;           // local UTC seconds since midnight
extern double clock_gps_read_seconds;    // gps read time, seconds since midnight
extern double local_clock_seconds;       // local time seconds since midnight
extern float gps_formatted_utc_time ;    // hhmmss.ss
extern char * not_implemented;

void save_evt300(FILE *f_radar, evt300_radar_typ *pradar, timestamp_t ts,
	int use_memory, buff_typ *pbuff);
void save_to_spec (FILE *fout, timestamp_t timestamp,
	int use_memory, buff_typ *pbuff,
	int num_columns, data_log_column_spec_t *spec);
void save_sms(db_clt_typ *pclt, FILE *f_sms,
	timestamp_t ts, int use_memory, buff_typ *pbuff);
