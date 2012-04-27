#!/bin/bash

killall video
if [[ $1 != "ignorewrfiles" ]]
then
	killall wrfiles_m56
fi
killall lcd_io.sh 
killall getstats.sh 
killall gpsdb
killall m56_can
killall komodo_db_write
killall -s KILL komodo_db_write
killall m56_create
killall db_slv
/home/path/db/db_clean.sh
