#!/bin/sh

# DAS3 experiment_startup.sh
#
# This script is generally called from one of the vehicle scripts in the
# following location /home/das3/veh/<vehicle>/test/<vehicle>_startup.sh
# 
# CARTYPE & EXPERIMENT set by /etc/rc.d/rc.local
# TRIPDIR set by /home/das3/veh/<vehicle>/test/<vehicle>_startup.sh
#

if [[ $# != 3 ]]
then
	echo "$0: Usage $0 <vehicle> <experiment> <tripdir>"
	exit 1
fi

CARTYPE=$1
EXPERIMENT=$2
TRIPDIR=$3

# NOEXPERIMENT starts no experiment script and no data logging
if [[ `grep noexperiment $EXPERIMENT` != '' ]]
then
	echo Starting no experiment script or data logging...
	exit 0
fi
