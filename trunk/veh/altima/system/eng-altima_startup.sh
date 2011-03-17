#!/bin/bash

# Run this as root, or from rc.local
/home/das3/veh/altima/system/setports.sh

sleep 5

if [[ ! `ntpdate 128.32.234.183` ]]
then 
	echo NTP server 128.32.234.183 not found
fi

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

if [[ ! -d /big/data ]]
then
	mkdir /big
	mkdir /big/data
	chgrp users /big/data
	chmod ug+w /big/data
fi
#!/bin/bash
#

CARTYPE=altima_grey

/home/path/db/db_clean.sh
killall -s TERM trtkrnlx
killall -s TERM vehicle_status
killall -s TERM evt300
killall -s TERM altima_db_write
killall -s TERM di_soft
killall -s TERM canmemcheck.sh
killall -s TERM uimu
killall -s TERM gpsdb
killall -s TERM altima_cr
killall -s TERM db_slv

sleep 1

echo Cleaning up Posix queues
/home/path/db/db_clean.sh
sleep 3

echo Starting db_slv...	
/home/path/db/lnx/db_slv &
sleep 1

echo Starting altima_cr...
/home/das3/veh/altima/src/lnx/altima_cr >altima_cr.log 2>&1 &
sleep 2

echo Starting gpsdb...
/home/path/sens/gps/examples/lnx/gpsdb -d 1 < /dev/ttyS1 >gpsdb.log 2>&1 &
sleep 2

echo Starting uimu...
/home/path/sens/gyro/memsense/src/lnx/uimu -d </dev/ttyUSB0 >uimu.log 2>&1 &
sleep 2

echo Starting evt300a...
/home/path/sens/radar/lnx/evt300 -s "/dev/ttyS0" -r a -o 2 >evt300a.log 2>&1 &
sleep 2

start_ctr=0
	echo Starting altima_db_write...
while [[ $start_ctr < 5 ]]
do
	/home/das3/veh/altima/can/lnx/altima_db_write </dev/pcan32 >altima_db_write.log 2>&1 &
	sleep 2
	if [[ ! `ps -aef | grep altima_db_write | grep -v grep` ]]
	then
		if [[ ! `/sbin/lsmod | grep pcan` ]]
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
