#include <db_include.h>
#include <sys_buff.h>
#include <evt300.h>
#include "sms_lib.h"
#include "data_log.h"

void save_evt300(FILE *f_radar, evt300_radar_typ *pradar, timestamp_t ts,
	int use_memory, buff_typ *pbuff);
void save_to_spec (FILE *fout, timestamp_t timestamp,
	int use_memory, buff_typ *pbuff,
	int num_columns, data_log_column_spec_t *spec);
void save_sms(db_clt_typ *pclt, FILE *f_sms,
	timestamp_t ts, int use_memory, buff_typ *pbuff);
