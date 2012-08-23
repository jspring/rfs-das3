#!/bin/bash

# DAS3 altima_startup.sh
#
# STARTUP COMMANDS COMMON TO NISSAN ALTIMAS
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
/home/das3/veh/altima/test/setports.sh
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
/home/das3/veh/altima/test/stop.sh

# Run Script to Set Clock Time to GPS Time Here
echo Synchronizing System Clock to GPS Time...
/home/path/sens/gps/examples/lnx/gpssetdate < /dev/ttyS1 &
/home/das3/startup/killsoon.sh -x gpssetdate -t 60 >/big/data/gpssetdate_killsoon.log

# Create Next Trip Directory in Big Data
echo Creating Current Trip Directory...
TRIPDIR=`/home/das3/startup/mknewtripdir.sh`
mv /big/data/gpssetdate_killsoon.log $TRIPDIR/gpssetdate_killsoon.log

# Start DB Clients
echo Starting db_slv...	
/home/path/db/lnx/db_slv &
sleep 1

echo Starting altima_cr...
/home/das3/veh/altima/src/lnx/altima_cr >$TRIPDIR/altima_cr.log 2>&1 &
sleep 2

echo Starting uimu...
/home/path/sens/gyro/memsense/src/lnx/uimu -d </dev/ttyUSB0 >$TRIPDIR/uimu.log 2>&1 &
sleep 2

echo Starting video ethernet server...
/home/capath/video/videorecorder/vid_enet_srv -a 10.0.0.140 -v >$TRIPDIR/vid_enet_srv.log 2>&1 &
sleep 2

echo Starting evt300a...
/home/path/sens/radar/lnx/evt300 -s "/dev/ttyS0" -r a -o 2 >$TRIPDIR/evt300a.log 2>&1 &
sleep 2

echo Starting gpsdb...
/home/path/sens/gps/examples/lnx/gpsdb -d 1 < /dev/ttyS1 >$TRIPDIR/gpsdb.log 2>&1 &
sleep 2

# Start Altima CAN
start_ctr=0
	echo Starting altima_db_write...
while [[ $start_ctr < 5 ]]
do
	/home/das3/veh/altima/can/lnx/altima_db_write </dev/pcan32 >$TRIPDIR/altima_db_write.log 2>&1 &
	sleep 2
	if [[ `ps -aef | grep altima_db_write | grep -v grep` == '' ]]
	then
		if [[ `/sbin/lsmod | grep pcan` == '' ]]
		then
			echo Loading pcan.ko module
			/sbin/insmod /lib/modules/`uname -r`/misc/pcan.ko
		fi
		start_ctr=$(($start_ctr + 1))
		echo Trying to start CAN client $start_ctr times
	else
		start_ctr=5
	fi
done

# On DAS3 Dual Computers -> Copy Engineering Data to Video Computer
#echo Starting cptripdirs.sh...
#/home/das3/startup/cptripdirs.sh $CARTYPE >$TRIPDIR/cptripdirs.log 2>&1 &

if [[ ! -h /home/das3/src/home/das3/veh/altima/src/lnx/libaltima_tables.so.1.0 || \
        ! -h /home/das3/src/home/ntmm/src/lnx/libalert_tables.so.1.0 ]]
then
	rm /home/das3/src/lib*
        ln -sf /home/das3/veh/altima/src/lnx/libaltima_tables.so.1.0 /home/das3/src/libveh_tables.so
        ln -sf /home/das3/veh/altima/src/lnx/libaltima_tables.so.1.0 /home/das3/src/libveh_tables.so.1
        ln -sf /home/ntmm/src/lnx/libalert_tables.so.1.0 /home/das3/src/libexpt_tables.so
        ln -sf /home/ntmm/src/lnx/libalert_tables.so.1.0 /home/das3/src/libexpt_tables.so.1
        ldconfig -n /home/das3/src
fi

# Start Experiment Script
/home/das3/startup/experiment_startup.sh $CARTYPE $EXPERIMENT $TRIPDIR
