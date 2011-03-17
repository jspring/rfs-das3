#!/bin/sh
#
# Script for checking Audi CAN process
#

# Maximum percentage of memory (*10) allowed
# Set to 200000 ~ 50% of 1 GB of memory ~ 8 minutes
maxmem=200000
while [[ 1 ]]
do
	# Check whether CAN process has crashed
	if [[ ! `/usr/bin/ps -aef | /usr/bin/grep -v grep | /usr/bin/grep audi_can` ]]
	then
		cd /home/nt-onboard/test
		/home/nt-onboard/test/audi_can -h 10.0.0.30 >>audi_can.log 2>>audi_can.err &
	fi

	# Check whether CAN process is using more than maxmem
	canmem=`/usr/bin/ps -elf | grep -v grep | grep audi_can | /usr/bin/awk '{print $10}'`
	#echo canmem = $canmem maxmem = $maxmem
	if [[ $canmem -gt $maxmem ]]
	then
		/bin/killall audi_can
		sleep 2
		cd /home/nt-onboard/test
		/usr/bin/echo "`date`: Killed audi_can. Memory at $canmem" >>audi_can.err
		/home/nt-onboard/test/audi_can -h 10.0.0.30 >>audi_can.log 2>>audi_can.err &
	fi
/usr/bin/sleep  10
done
