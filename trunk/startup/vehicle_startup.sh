#!/bin/sh

# DAS3 startup.sh 
#
# Script called from		/etc/rc.d/rc.local
# CARTYPE & EXPERIMENT set by	/etc/rc.d/rc.local
#

if [[ $# != 2 ]]
then
	echo "$0: Usage $0 <vehicle> <experiment>"
	exit 1
fi

CARTYPE=$1
EXPERIMENT=$2

# STARTUP COMMANDS COMMON TO ALL VEHICLES

# Create /big/data if it does not already exist
if [[ ! -d /big/data ]]
then
	mkdir /big
	mkdir /big/data
	chgrp users /big/data
	chmod ug+w /big/data
fi

# SELECT VEHICLE-SPECIFIC STARTUP SCRIPT TO RUN
if [[ `grep altima $CARTYPE` != '' ]]
then
	if [[ -x /home/das3/veh/altima/test/altima_startup.sh ]]
	then
		/home/das3/veh/altima/test/altima_startup.sh $CARTYPE $EXPERIMENT
		exit 0
	else
		echo "$0: Unable to execute /home/das3/veh/altima/test/altima_startup.sh"
		exit 1
	fi
fi

if [[ `grep audi $CARTYPE` != '' ]]
then
	if [[ -x /home/das3/veh/audi/test/audi_startup.sh ]]
	then
		/home/das3/veh/audi/test/audi_startup.sh $CARTYPE $EXPERIMENT
		exit 0
	else
		echo "$0: Unable to execute /home/das3/veh/audi/test/audi_startup.sh"
		exit 1
	fi
fi

if [[ `grep m56 $CARTYPE` != '' ]]
then
	if [[ -x /home/das3/veh/m56/test/.sh ]]
	then
		/home/das3/veh/audi/test/audi_startup.sh $CARTYPE $EXPERIMENT
		exit 0
	else
		echo "$0: Unable to execute /home/das3/veh/audi/test/audi_startup.sh"
		exit 1
	fi
	
fi

echo "$0: Unknown CARTYPE=$CARTYPE"
exit 1
