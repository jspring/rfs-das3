#!/bin/bash
#
# $1 argument is vehicle type, passed to wrfiles_nt
#	possible values are: altima_silver, altima_grey, audi_silver,audi_red
#

CARTYPE=audi_red

# Run this as root, or from rc.local
/home/nt-onboard/test/setports.sh

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

# Synchronize engineering computer to NTP server
while [[ ! `sudo ntpdate 128.32.234.183` ]]
do 
	sleep 1
done &

/home/nt-onboard/test/startup.sh $CARTYPE
