#!/bin/bash
#
# Makes a trip directory in /big/data that is one trip
# larger than the greatest trip. This is determined by
# either reading the last trip directory number in 
# /big/data/lasttripdir.txt, or if it doesn't exist, by
# looking at the characters after the eighth character
# in all valid directory names, and incrementing the
# highest number by 1.

if [[ $# != 1 || $1 != [mnop] ]]
then
        echo "Usage $0 <m, n, o, or p>"
        exit 1
fi

VEH=$1

if [[ ! -e /big/data/lasttripdir.txt ]]
then
	y=0
	z=-1
	for x in /big/data/*
	do 
		if [[ $x == /big/data/$VEH?????????? ]]
		then
			y=`echo $x | cut -c 18-`
			q=$((10#$y))
			if [[ $? == 0 ]]
			then
				if [[ $q -gt $z ]]
				then
					z=$q
				fi
			fi
		fi
	done
else
	z=$((10#`cat /big/data/lasttripdir.txt`))
fi
s=$( printf "%04d" $((10#$z+1)) )
tripdir=/big/data/$VEH$(date +%y%m%d)$s
mkdir $tripdir
echo $tripdir
echo $s >/big/data/lasttripdir.txt
