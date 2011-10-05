#!/bin/sh

/bin/ps -ef | grep db_slv | grep -v grep

if [ $? != 0 ]
then
	/home/path/db/lnx/db_slv &
fi

killall m56_can
killall komodo_db_write
killall run_komodo.sh
sleep 1

/home/path/sens/can2usb/komodo/files/komodo-api-linux-i686-v1.00/test/run_komodo.sh &
/home/das3/veh/m56/can/src/lnx/m56_can &
