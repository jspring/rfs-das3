#!/bin/bash

if [[ $# != 2 ]]
then
	echo "Usage $0 <m56_dnc304, m56_dne491, m56_pro4> <cacc3, standalone>"
	exit 1
fi
if [[ $1 == "m56_dnc304" ]]
then
	VEH="m"
	VID="mq"
else
if [[ $1 == "m56_pro4" ]]
then
	VEH="n"
	VID="oq"
else
if [[ $1 == "m56_dne491" ]]
then
	VEH="o"
	VID="oq"
else
if [[ $1 == "m56_dne596" ]]
then
	VEH="p"
	VID="pq"
else
	echo "Usage $0 <dnc304, dne491, pro4, dne596> <cacc3, standalone>"
	exit 1
fi
fi
fi
fi

if [[ $2 != "cacc3" && $2 != "standalone" ]]
then
	echo "Usage $0 <dnc304, dne491, pro4, dne596> <cacc3, standalone>"
	exit 1
else
	EXP=$2
fi

tripdir=$(/home/das3/veh/m56/test/mknewtripdir.sh $VEH)
echo "VEH $VEH tripdir $tripdir"

/home/das3/veh/m56/test/setports.sh
/home/path/sens/gps/examples/lnx/gpssetdate < /dev/ttyS0 &
/home/das3/startup/killsoon.sh -x gpssetdate -t 120 >$tripdir/killsoon.log

/home/das3/veh/m56/test/m56_stop.sh
sleep 2
echo Starting db_slv...
/home/path/db/lnx/db_slv &
sleep 1
echo Starting m56_create...
/home/das3/veh/m56/src/lnx/m56_create >$tripdir/m56_create.log &
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

echo Starting video with tripdir $tripdir vehicle prefix $VID...
/home/capath/video/videorecorder/video -0 $VID -qt -f "/big/data" -p $tripdir -b 2000000 -c >$tripdir/video.log 2>$tripdir/video.err &
/home/das3/veh/m56/test/getstats.sh >$tripdir/stats.log &
#/home/das3/veh/m56/lcd_hw/lcd_io.sh $1 &
/home/path/sens/lcd/crystalfontz/src/lnx/crystalfontz_CFA635 -c -V $1 &

# Start Experiment Script
/home/das3/startup/experiment_startup.sh $1 $EXP $tripdir
