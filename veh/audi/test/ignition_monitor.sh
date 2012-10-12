#!/bin/sh
#
# ignition_monitor.sh - monitors input 0 on the Advantech USB-4761 digio. This
# input should be connected to the vehicle's ignition switch. When this input
# goes to zero, we issue a shutdown command via ssh to the video computer,
# wait 1 second, then issue a shutdown command to this computer 

cd /home/path/sens/digio/advdaq-1.06.0001/examples/console/di_soft
out=0

# Let's make sure the driver is up and running before we start monitoring
# the ignition input.
while [[ `echo $out | grep "System Error"` != '' || $(($out & 1)) -eq 0 ]]
do
	echo Waiting for digio.... 
	out=`/usr/bin/sudo ./di_soft /dev/advdaq0`
	sleep 1
done

while [[ 1 ]]
do 
	out=`/usr/bin/sudo ./di_soft /dev/advdaq0`
	if [[ `echo $out | grep "System Error"` != '' || $(($out)) -lt 0 ]]
	then 
		echo Error: out = $out
	else 
		if [[ $(($out & 1)) -eq 0 ]] 
		then
			echo `date` executing shutdown
			/usr/bin/sudo /usr/bin/ssh ntvid /sbin/shutdown -hf now
			sleep 1
			/usr/bin/sudo /sbin/shutdown -hf now
		fi
	fi
	sleep 1
done
