#!/bin/sh
# Run this as root, or from rc.local
#
# $1 argument is vehicle type; its corresponding video file prefix is passed to
# video as argument '0'
#       possible values are: altima_silver, altima_grey, audi_silver,audi_red
#


CARTYPE=audi_red

# Synchronize video computer to NTP server
while [[ ! `sudo ntpdate 128.32.234.183` ]]
do
        sleep 1
done &

if [[ ! -d /big/data ]]
then
	mkdir /big
	mkdir /big/data
	chgrp users /big/data
	chmod ug+w /big/data
fi

/home/nt-onboard/test/startup_video.sh $CARTYPE
