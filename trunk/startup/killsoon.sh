#!/bin/bash
#
# killsoon.sh - waits for a time "time" for process "exe" to die.  
# If this doesn't happen, kill x myself.

usage="Usage: $0 -x \<executable\> -t \<time til kill\>"

while getopts "x:t:" opts ; do
	case $opts in
	x) exe=$OPTARG ;;
	t) time=$OPTARG;;
	[?]) echo $usage
		exit
	esac
done

if [[ $OPTIND -lt 5 ]] ; then
	echo $usage
	exit
fi

counter=0
while [[ counter -lt $time && `ps -aef |grep $exe |grep -v grep| \
	grep -v $0` != "" ]] ; do
	sleep 1
	counter=$(($counter+1))
	echo KILLSOON: Waiting $counter seconds....
done
if [[ `ps -aef |grep $exe |grep -v grep| grep -v $0` != "" ]] 
then
	echo "KILLSOON: $exe still running after $time seconds. Must kill...."
	/bin/kill `ps -aef |grep $exe |grep -v grep| grep -v $0 | awk '{print $2}'`
else
	echo "KILLSOON: $exe exited normally; did not have to kill it."
fi
