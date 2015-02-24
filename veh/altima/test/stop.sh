#!/bin/sh
#
killall -s TERM vehicle_status
killall -s TERM trtkrnlx
killall -s TERM wrfiles_das3
killall -s TERM vid_enet_srv
killall -s TERM evt300
killall -s TERM uimu
killall -s TERM gpsdb
killall -s TERM altima_db_write
killall -s TERM altima_cr
killall -s TERM db_slv

echo Cleaning up Posix queues
/home/path/db/db_clean.sh
