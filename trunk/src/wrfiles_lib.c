/**\file
** wrfiles_lib.c - library for printing function definitions for wrfiles.c
*/

#include "wrfiles_lib.h"

/**
 *      Since EVT300  radar data has complicated structure 
 *      and is used for multiple devices, easier to write
 *      device-specific print routines than to use column specification format.
 */
void save_evt300(FILE *f_radar, evt300_radar_typ *pradar, timestamp_t ts,
                int use_memory, buff_typ *pbuff)
{
        char char_buf[MAX_LOG_LINE_LEN];
        int cnt = 0;
        if (use_memory) {
                cnt += evt300_sprint_radar(char_buf, pradar, ts, NULL);
                cnt += (sprintf(char_buf+cnt, "\n"));
                buff_add(pbuff, char_buf, cnt);
        } else {
                evt300_print_radar(f_radar, pradar, ts, NULL);
                fprintf(f_radar,"\n");
                return;
        }
}

// Let's keep the files smaller for now
// Will we ever get more objects than this in our tests?
#define SMS_MAX_PRINT 16

/**
 *      SMS radar also has compilcated DB access, use library functiosn
 *      to read the DB.
 */
void save_sms(db_clt_typ *pclt, FILE *f_sms,
                timestamp_t ts, int use_memory, buff_typ *pbuff)
{
        char char_buf[MAX_LOG_LINE_LEN];
        int cnt = 0;
        sms_object_list_t sms_list;

        sms_get_object_list(pclt, &sms_list);

        if (use_memory) {
                cnt += sms_sprint_list(char_buf, &sms_list, ts, SMS_MAX_PRINT);
                cnt += (sprintf(char_buf+cnt, "\n"));
                buff_add(pbuff, char_buf, cnt);
        } else {
                cnt += sms_sprint_list(char_buf, &sms_list, ts, SMS_MAX_PRINT);
                fprintf(f_sms, "%s\n", char_buf);
        }
        if (cnt > MAX_LOG_LINE_LEN)
                fprintf(stderr, "Line too long for logging SMS radar!");
}

/**
 *      This routine is used for saving any log file defined by
 *      specification in sv_tables.c
 */
void save_to_spec (FILE *fout, timestamp_t timestamp,
                        int use_memory, buff_typ *pbuff,
                        int num_columns, data_log_column_spec_t *spec)
{
        int i;
        int cnt = 0;
        char char_buf[MAX_LOG_LINE_LEN];
        for (i = 0; i < num_columns; i++)
                cnt += (sprint_data_log_column_entry(
                                char_buf + cnt, &spec[i]));
        cnt += (sprintf(char_buf + cnt, "\n"));
        if (use_memory)
                buff_add(pbuff, char_buf, cnt);
        else
                fprintf(fout, "%s", char_buf);
}
