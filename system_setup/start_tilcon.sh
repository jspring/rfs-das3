#!/bin/bash

sleep 5
ctr=0
while [[ ! `ps -aef | grep m56_create |grep -v grep` ]]
do
	echo Waiting for m56_create for $ctr seconds >> /home/cacc3/test/tilcon_autostart.log
	ctr=$(($ctr+1))
	sleep 1
done

# Start Tilcon Screen For CACC3
#xterm -e "/home/cacc3/ui/src/lnx/cacc_vehicle_status -p /home/cacc3/ui/twd/kde -c altima -e ntsafety" &
xterm -e "/home/cacc3/ui/src/lnx/cacc_vehicle_status -p /home/cacc3/ui/twd" &

# The next part of this script is for killing the "bad" Tilcon process that 
# kdeinit (in /etc/X11/xinit/xinitrc) starts up; that one took up 85+% CPU time.

# Wait until the parent process starts up
while [[ ! `echo $parent_id` ]] ; do
sleep 1
parent_id=`ps -ef |grep vehicle_status |grep -v grep |grep xtsessionID | awk '{print $2}'`
done

# Wait until the daughter process starts up
while [[ ! `echo $bad_pid` ]] ; do
sleep 1
bad_pid=`ps -ef |grep vehicle_status |grep -v grep |grep $parent_id |grep -v xte
rm | awk '{print $2}'`
done

# Terminate daughter process (parent also dies; it's a mass murder)
sleep 1
echo $bad_pid >> /home/cacc3/test/tilcon_autostart.log
kill -15 $bad_pid
