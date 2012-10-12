#!/bin/sh
#
killall -s TERM evt300
killall -s TERM uimu
killall -s TERM gpsdb
killall -s TERM di_soft
killall -s TERM canmemcheck.sh
killall -s TERM audi_can
killall -s TERM audi_cr
killall -s TERM db_slv

echo Cleaning up Posix queues
/home/path/db/db_clean.sh