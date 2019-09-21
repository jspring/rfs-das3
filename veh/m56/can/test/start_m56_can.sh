#!/bin/bash

/bin/ps -ef | grep db_slv | grep -v grep

if [ $? != 0 ]
then
	killall db_slv
fi

/home/path/db/lnx/db_slv &

killall m56_can
killall komodo_db_write
sleep 1
cd /home/path/sens/can2usb/komodo/files/komodo-api-linux-i686-v1.00/c
echo Starting komodo_db_write...
lnx/komodo_db_write  &
sleep 1
if [[ `ps -ef | grep -v grep | grep komodo_db_write` == '' ]]
then
	echo $0: komodo_db_write startup error. Exiting.
	exit 1
fi
sleep 1
/home/das3/veh/m56/can/src/lnx/m56_can -c -v &
