#!/bin/bash

# DAS3 audi_startup.sh
#
# STARTUP COMMANDS COMMON TO AUDI A3s
#
# This script is generally called by	/home/das3/startup/vehicle_startup.sh
# This script always ends by calling	/home/das3/startup/experiment_startup.sh
# CARTYPE & EXPERIMENT set in		/etc/rc.d/rc.local

if [[ $# != 2 ]]
then
	echo "$0: Usage $0 <vehicle> <experiment>"
	exit 1
fi

CARTYPE=$1
EXPERIMENT=$2

# Run this as root, or from rc.local
/home/das3/veh/audi/test/setports.sh
sleep 2

# Load digio driver and bind it to device
cd /home/path/sens/digio/advdaq-1.06.0001
./adv_load_template
sleep 1

if [[ `lsmod | grep usb4761` && `ls /dev/advdaq0` ]]
then
	/usr/bin/advdevice_bind usb4761 0 /dev/advdaq0
else 
	echo Could not find module usb4761 or device /dev/advdaq0
fi

# Kill Anything Running
/home/das3/veh/audi/test/stop.sh

# Run Script to Set Clock Time to GPS Time Here
echo Synchronizing System Clock to GPS Time...
/home/path/sens/gps/examples/lnx/gpssetdate < /dev/ttyS1 &
/home/das3/startup/killsoon.sh -x gpssetdate -t 60 >/big/data/gpssetdate_killsoon.log

# Create Next Trip Directory in Big Data & Copy gpssetdate log
echo Creating Current Trip Directory...
TRIPDIR=`/home/das3/startup/mknewtripdir.sh`
mv /big/data/gpssetdate_killsoon.log $TRIPDIR/gpssetdate_killsoon.log

# Start DB Clients
echo Starting db_slv...	
/home/path/db/lnx/db_slv &
sleep 1

echo Starting audi_cr...
/home/das3/veh/audi/src/lnx/audi_cr >$TRIPDIR/audi_cr.log 2>&1 &
sleep 2

echo Starting uimu...
/home/path/sens/gyro/memsense/src/lnx/uimu -d </dev/ttyUSB0 >$TRIPDIR/uimu.log 2>&1 &
sleep 2

echo Starting evt300a...
/home/path/sens/radar/lnx/evt300 -s "/dev/ttyS0" -r a -o 2 >$TRIPDIR/evt300a.log 2>&1 &
sleep 2

echo Starting gpsdb...
/home/path/sens/gps/examples/lnx/gpsdb -d 1 < /dev/ttyS1 >$TRIPDIR/gpsdb.log 2>&1 &
sleep 2

# Start Audi Ignition Monitor
echo Starting di_soft...
/home/path/sens/digio/advdaq-1.06.0001/examples/console/di_soft/lnx/di_soft -d /dev/advdaq0 >$TRIPDIR/di_soft.log 2>$TRIPDIR/di_soft.err &
sleep 2

# Start Audi CAN
echo Starting audi_can...
/home/das3/veh/audi/src/lnx/audi_can -h 10.0.0.30 >$TRIPDIR/audi_can.log 2>$TRIPDIR/audi_can.err &
sleep 2

echo Starting canmemcheck.sh...
/home/das3/veh/audi/test/canmemcheck.sh >>$TRIPDIR/audi_can.log 2>>$TRIPDIR/audi_can.err &
sleep 2

# On DAS3 Dual Computers -> Copy Engineering Data to Video Computer
echo Starting cptripdirs.sh...
/home/das3/startup/cptripdirs.sh $CARTYPE >$TRIPDIR/cptripdirs.log 2>&1 &

# Start Experiment Script
/home/das3/exp/experiment_startup.sh $CARTYPE $EXPERIMENT $TRIPDIR
