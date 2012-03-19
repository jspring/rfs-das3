#!/bin/sh
#
killall -s TERM trtkrnlx
killall -s TERM vehicle_status
killall -s TERM di_soft
killall -s TERM canmemcheck.sh
killall -s TERM evt300
killall -s TERM uimu
killall -s TERM gpsdb
killall -s TERM altima_db_write
killall -s TERM altima_cr
killall -s TERM db_slv
sleep 1
