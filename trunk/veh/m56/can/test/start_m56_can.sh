#!/bin/sh

/bin/ps -ef | grep db_slv | grep -v grep

if [ $? != 0 ]
then
	/home/path/db/lnx/db_slv &
fi

killall m56_can
killall komodo_db_write
sleep 1
pushd /home/path/sens/can2usb/komodo/files/komodo-api-linux-i686-v1.00/c
echo Starting komodo_db_write...
lnx/komodo_db_write -v &
popd
sleep 1
/home/das3/veh/m56/can/src/lnx/m56_can -c &
