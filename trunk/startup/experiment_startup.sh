#!/bin/bash

# DAS3 altima_startup.sh
#
# EXPERIMENT STARTUP SCRIPT LIST
#
# This script is generally called by	/home/das3/veh/<vehicle>/test/<vehicle>_startup.sh
# CARTYPE & EXPERIMENT set in		/etc/rc.d/rc.local
# TRIPDIR set in			/home/das3/veh/<vehicle>/test/<vehicle>_startup.sh

if [[ $# != 3 ]]
then
	echo "$0: Usage $0 <vehicle> <experiment> <tripdir>"
	exit 1
fi

CARTYPE=$1
EXPERIMENT=$2
TRIPDIR=$3

# DRIVERSONLY starts no experiment script and no data logging
if [[ $EXPERIMENT =~ "driversonly" ]]
then
	echo "Finished starting $CARTYPE drivers..."
	echo "No experiment script or data logging requested..."
	sleep 20
	exit 0
fi

# STANDALONE starts the wrtfiles for the vehicle type contained in /home/das3
if [[ $EXPERIMENT =~ "standalone" ]]
then
	echo "Starting $CARTYPE Standalone Data Logging..."
	
	if [[ $CARTYPE =~ "altima" ]]
	then
	
		exit 0
	
	else if [[ $CARTYPE =~ "audi" ]]
	then
	
		exit 0
	
	else if [[ $CARTYPE =~ "m56" ]]
	then
	
		exit 0
	
	else
		# UNKNOWN CARTYPE
		echo "Finished starting $CARTYPE drivers..."
		echo "$0: No Standalone Data Logging Script Specified for CARTYPE=$CARTYPE"
		sleep 20
		exit 1
	fi

fi

# NTMM starts Networked Traveler-Mobile Millennium Experiment
if [[ $EXPERIMENT =~ "ntmm" ]]
then

	echo "Starting NTMM Experiment & Data Logging..."
	exit 0

fi

# UNKNOWN EXPERIMENT
echo "$0: Detected Unknown EXPERIMENT=$EXPERIMENT"
echo "No Experiment Script or Data Logging Started..."
sleep 20
exit 1
