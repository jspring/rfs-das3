#!/bin/sh
MUTE_DURATION=$1
WAV_FILE=$2
DISTRIB_DIR=/home
ADVDAQ_DIR=$DISTRIB_DIR/path/sens/digio/advdaq-1.06.0001/examples/console/do_soft
# first parameter is port, second is time to mute other audio
$ADVDAQ_DIR/do_soft /dev/advdaq0 1 $MUTE_DURATION & 
sleep 1
/usr/local/bin/mplayer -af volume=10 $WAV_FILE.wav 
echo "Got alert! $MUTE_DURATION seconds duration, file $WAV_FILE"
