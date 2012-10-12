#!/bin/bash

# DAS3 vehicle_startup.sh 
#
# STARTUP COMMANDS COMMON TO ALL DAS3 SYSTEMS
#
# This script called from	/etc/rc.d/rc.local
# CARTYPE & EXPERIMENT set in	/etc/rc.d/rc.local

if [[ $# != 2 ]]
then
	echo "$0: Usage $0 <vehicle> <experiment>"
	exit 1
fi

CARTYPE=$1
EXPERIMENT=$2

# Create /big/data if it does not already exist
if [[ ! -d /big/data ]]
then
	mkdir /big
	mkdir /big/data
	chgrp users /big/data
	chmod ug+w /big/data
fi

# SELECT VEHICLE-SPECIFIC STARTUP SCRIPT TO RUN
if [[ $CARTYPE =~ "altima" ]]
then
	if [[ -x /home/das3/veh/altima/test/altima_startup.sh ]]
	then
		echo "Starting Nissan Altima Drivers..."
		/home/das3/veh/altima/test/altima_startup.sh $CARTYPE $EXPERIMENT
		exit 0
	else
		echo "$0: Unable to execute /home/das3/veh/altima/test/altima_startup.sh"
		sleep 5
		exit 1
	fi
fi

if [[ $CARTYPE =~ "audi" ]]
then
	if [[ -x /home/das3/veh/audi/test/audi_startup.sh ]]
	then
		echo "Starting Audi A3 Drivers..."
		/home/das3/veh/audi/test/audi_startup.sh $CARTYPE $EXPERIMENT
		exit 0
	else
		echo "$0: Unable to execute /home/das3/veh/audi/test/audi_startup.sh"
		sleep 5
		exit 1
	fi
fi

if [[ $CARTYPE =~ "m56" ]]
then
	if [[ -x /home/das3/veh/m56/test/m56_startup.sh ]]
	then
		echo "Starting Infiniti M56 Drivers..."
		/home/das3/veh/m56/test/m56_startup.sh $CARTYPE $EXPERIMENT
		exit 0
	else
		echo "$0: Unable to execute /home/das3/veh/m56/test/m56_startup.sh"
		sleep 5
		exit 1
	fi
	
fi

# UNKNOWN VEHICLE STRING RECEIVED AS INPUT
echo "$0: Detected Unknown CARTYPE=$CARTYPE"
sleep 5
exit 1
