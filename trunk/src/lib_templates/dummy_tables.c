/**\file
 *
 *	Tables for DB variables and column specification for logging
 *	CACC3 vehicles
 */	
#include <db_include.h>
#include <db_utils.h>
#include <path_gps_lib.h>
#include "data_log.h"

/**  DB VARs read, declared global so that the variable addresses will
 *   be available to initialize the DB variable and column specification arrays.
 */

path_gps_point_t cabinet_gps; 		// GPS in cabinet
path_gps_point_t my_gps; 
path_gps_point_t veh1_gps; 		// sent from SV Taurus
path_gps_point_t veh2_gps;
path_gps_point_t veh3_gps;


/**
 *	Additional variables derived from DB VAR fields that
 *	are part of the output column specification
 */
timestamp_t timestamp;
double utc_seconds_since_midnight = 0.0;// UTC seconds since midnight 
double seconds_since_start = 0.0;	// seconds since start of run

double veh1_utc_seconds = 0.0;
double veh2_utc_seconds = 0.0;
double veh3_utc_seconds = 0.0;

/**
 *	This array is used to specify how to read in the DB vars.
 */
db_var_spec_t db_vars[] =
{

};
int num_db_vars = (sizeof(db_vars)/sizeof(db_var_spec_t));

/** This array is used to specify the output format of the "[mnop]a" file.
 */
data_log_column_spec_t file_speca[] = 
{
};

#define NUM_AFILE_COLUMNS sizeof(file_speca)/sizeof(data_log_column_spec_t)
int num_afile_columns = sizeof(file_speca)/sizeof(data_log_column_spec_t);


/** This array is used to specify the output format of the "[mnop]b" file.
 */
data_log_column_spec_t file_specb[] = 
{
};

#define NUM_BFILE_COLUMNS sizeof(file_specb)/sizeof(data_log_column_spec_t)
int num_bfile_columns = sizeof(file_specb)/sizeof(data_log_column_spec_t);

/** This array is used to specify the output format of the "[mnop]c" file.
 */
data_log_column_spec_t file_specc[] = 
{
};

#define NUM_CFILE_COLUMNS sizeof(file_specc)/sizeof(data_log_column_spec_t)
int num_cfile_columns = sizeof(file_specc)/sizeof(data_log_column_spec_t);


/** This array is used to specify the output format of the "[mnop]d" file.
 */
data_log_column_spec_t file_specd[] = 
{
};

#define NUM_DFILE_COLUMNS sizeof(file_specd)/sizeof(data_log_column_spec_t)
int num_dfile_columns = sizeof(file_specd)/sizeof(data_log_column_spec_t);

/** This array is used to specify the output format of the "[mnop]e" file.
 */
data_log_column_spec_t file_spece[] = 
{
};

#define NUM_EFILE_COLUMNS sizeof(file_spece)/sizeof(data_log_column_spec_t)
int num_efile_columns = sizeof(file_spece)/sizeof(data_log_column_spec_t);


/** This array is used to specify the output format of the "[mnop]f" file.
 */
data_log_column_spec_t file_specf[] = 
{
};

#define NUM_FFILE_COLUMNS sizeof(file_specf)/sizeof(data_log_column_spec_t)
int num_ffile_columns = sizeof(file_specf)/sizeof(data_log_column_spec_t);

/** This array is used to specify the output format of the "[mnop]g" file.
 */
data_log_column_spec_t file_specg[] = 
{
};

#define NUM_GFILE_COLUMNS sizeof(file_specg)/sizeof(data_log_column_spec_t)
int num_gfile_columns = sizeof(file_specg)/sizeof(data_log_column_spec_t);
