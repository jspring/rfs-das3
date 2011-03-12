#!/bin/bash

sleep 5
ctr=0
while [[ ! `ps -aef | grep wrfiles_nt |grep -v grep` ]]
do
	echo Waiting for wrfiles_nt for $ctr seconds >> /home/das3/test/tilcon_autostart.log
	ctr=$(($ctr+1))
	sleep 1
done

# Start Tilcon Screen For Altima
xterm -e "/home/das3/test/vehicle_status -c altima" &

# Start Tilcon Screen For Audi
# xterm -e "/home/das3/test/vehicle_status -c audi" &

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
echo $bad_pid >> /home/das3/test/tilcon_autostart.log
kill -15 $bad_pid

