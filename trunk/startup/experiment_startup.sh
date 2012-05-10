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
	sleep 5
	exit 0
fi

# STANDALONE starts the wrtfiles for the vehicle type contained in /home/das3
if [[ $EXPERIMENT =~ "standalone" ]]
then
	echo "Starting $CARTYPE Standalone Data Logging..."
	
	if [[ $CARTYPE =~ "altima" ]]
	then
		if [[ $CARTYPE =~ "silver" ]]
		then
			VEH=g
		else if [[ $CARTYPE =~ "grey" ]]
		then
                        VEH=g
#		/home/das3/src/lnx/wrfiles_das3 -m 2 -t 50 -d $TRIPDIR -c $VEH -i -ABCEFG -r 1>$TRIPDIR/wrfiles_altima.log 2>$TRIPDIR/wrfiles_altima.err &
		/home/das3/src/lnx/wrfiles_das3 -m 2 -t 50 -d $TRIPDIR -c $VEH -i -ABCEFG 1>$TRIPDIR/wrfiles_altima.log 2>$TRIPDIR/wrfiles_altima.err &
		fi
		fi
		exit 0
	
	else if [[ $CARTYPE =~ "audi" ]]
	then
	
		exit 0
	
	else if [[ $CARTYPE =~ "m56" ]]
	then
		if [[ $CARTYPE =~ "dnc304" ]]
		then
			VEH=m
		else if [[ $CARTYPE =~ "pro4" ]]
		then
                        VEH=n
		else if [[ $CARTYPE =~ "dne491" ]]
		then
                        VEH=o
		else if [[ $CARTYPE =~ "dne596" ]]
		then
                        VEH=p
		else 
			echo CARTYPE $CARTYPE not found
			exit 1
		fi
		fi
		fi
		fi
echo VEH $VEH
		/home/das3/src/lnx/wrfiles_das3 -m 2 -t 50 -d $TRIPDIR -c $VEH -i -BCEFG 1>$TRIPDIR/wrfiles_m56.log 2>$TRIPDIR/wrfiles_m56.err &
		exit 0
	else
		# UNKNOWN CARTYPE
		echo "Finished starting $CARTYPE drivers..."
		echo "$0: No Standalone Data Logging Script Specified for CARTYPE=$CARTYPE"
		sleep 5
		exit 1
	fi
	fi
	fi

fi
# NTMM starts Networked Traveler-Mobile Millennium Experiment
if [[ $EXPERIMENT =~ "ntmm" ]]
then

	echo "Starting NTMM Experiment & Data Logging..."
	exit 0

fi

# CACC3 starts Nissan CACC3 Experiment
if [[ $EXPERIMENT =~ "cacc3" ]]
then

	echo "Starting CACC3 Experiment & Data Logging..."
	/home/das3/src/lnx/wrfiles_das3 -m 2 -t 50 -d $tripdir -c $VEH -i 1>$tripdir/wrfiles_m56.log 2>$tripdir/wrfiles_m56.err &
	exit 0
fi

# UNKNOWN EXPERIMENT
echo "$0: Detected Unknown EXPERIMENT=$EXPERIMENT"
echo "No Experiment Script or Data Logging Started..."
sleep 5
exit 1
