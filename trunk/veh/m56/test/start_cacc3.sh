#!/bin/bash

if [[ $# != 1 ]]
then
	echo "Usage $0 <dnc304, dne491, pro4>"
	exit 1
fi
if [[ $1 == "dnc304" ]]
then
	VEH="m"
else
if [[ $1 == "pro4" ]]
then
	VEH="n"
else
if [[ $1 == "dne491" ]]
then
	VEH="o"
else
	echo "Usage $0 <dnc304, dne491, pro4>"
	exit 1
fi
fi
fi

tripdir=$(/home/cacc3/test/mknewtripdir.sh)
echo "VEH $VEH tripdir $tripdir"

/home/das3/veh/m56/test/setports.sh
/home/path/sens/gps/examples/lnx/gpssetdate < /dev/ttyS0 &
/home/das3/startup/killsoon.sh -x gpssetdate -t 120 >$tripdir/killsoon.log

/home/cacc3/test/stop_cacc3.sh
sleep 2
echo Starting db_slv...
/home/path/db/lnx/db_slv &
sleep 1
echo Starting cacc3_create...
/home/cacc3/veh/lnx/cacc3_create &
sleep 1 

cd /home/path/sens/can2usb/komodo/files/komodo-api-linux-i686-v1.00/c
echo Starting komodo_db_write...
lnx/komodo_db_write >$tripdir/komodo_db_write.log 2>$tripdir/komodo_db_write.err &
sleep 1
if [[ `ps -ef | grep -v grep | grep komodo_db_write` == '' ]]
then
        echo $0: komodo_db_write startup error. Exiting.
        exit 1
fi
sleep 1

echo Starting m56_can...
/home/das3/veh/m56/can/src/lnx/m56_can >$tripdir/m56_can.log &
sleep 1
echo Starting gpsdb...
/home/path/sens/gps/examples/lnx/gpsdb -d 1 < /dev/ttyS0 >$tripdir/gpsdb.log 2>&1 &
sleep 1
echo Starting wrfiles_cacc3 with tripdir $tripdir vehicle prefix $VEH...
/home/cacc3/veh/lnx/wrfiles_cacc3 -m 2 -t 50 -d $tripdir -c $VEH -i 1>$tripdir/wrfiles_cacc3.log 2>$tripdir/wrfiles_cacc3.err &
sleep 2
echo Starting video with tripdir $tripdir vehicle prefix $VEH...
/home/capath/video/videorecorder/video -0 $VEH -qt -f "/big/data" -p $tripdir -b 2000000 -c >$tripdir/video.log 2>$tripdir/video.err &
/home/cacc3/test/getstats.sh >$tripdir/stats.log &
/home/das3/veh/m56/lcd_hw/lcd_io.sh $1 &
