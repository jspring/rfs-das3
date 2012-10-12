#!/bin/bash

if [[ $1 ]]
then
	PERIOD=$1
else
	PERIOD=60
fi

while [[ 1 ]]
do
	/usr/bin/top -n 1 -b | /usr/bin/head -n 15
	/usr/bin/sensors
	sleep $PERIOD
done
