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

if [[ $CARTYPE =~ "altima" ]]
then
	# Set vehicle character for Altimas
	if [[ $CARTYPE =~ "grey" ]]
	then
		VEH=g
	else if [[ $CARTYPE =~ "silver" ]]
	then
                        VEH=h
	else 
		echo CARTYPE $CARTYPE not found
		exit 1
	fi
	fi

	# Create library links for altima
	ls -l /home/das3/src/libveh_tables.so.1 | grep libaltima_tables.so.1.0
	x=$?
	ls -L /home/das3/src/libveh_tables.so
	y=$?
	if [[ $x != 0 || $y != 0 ]]
	then
		echo No Altima vehicle library links - creating them now
		rm /home/das3/src/libveh*
		ln -sf /home/das3/veh/altima/src/lnx/libaltima_tables.so.1.0 /home/das3/src/libveh_tables.so.1
		ln -sf /home/das3/src/libveh_tables.so.1 /home/das3/src/libveh_tables.so
		sudo ldconfig -n /home/das3/src
	fi
fi

if [[ $CARTYPE =~ "audi" ]]
then
	if [[ $CARTYPE =~ "silver" ]]
	then
		VEH=j
	else
		VEH=k
	fi

	echo "$0: No Standalone Data Logging Script Specified for CARTYPE=$CARTYPE"
	exit 1
fi

if [[ $CARTYPE =~ "m56" ]]
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
	# Create library links for standalone m56
	ls -l /home/das3/src/libveh_tables.so.1 | grep libm56_tables.so.1.0
	x=$?
	ls -L /home/das3/src/libveh_tables.so
	y=$?
	if [[ $x != 0 || $y != 0 ]]
	then
		rm /home/das3/src/libveh*
		ln -sf /home/das3/veh/m56/src/lnx/libm56_tables.so.1.0 /home/das3/src/libveh_tables.so.1
		ln -sf /home/das3/src/libveh_tables.so.1 /home/das3/src/libveh_tables.so
		sudo ldconfig -n /home/das3/src
	fi

echo VEH $VEH
fi

# STANDALONE starts the wrtfiles for the vehicle type contained in /home/das3
if [[ $EXPERIMENT =~ "standalone" ]]
then
	echo "Starting $CARTYPE Standalone Data Logging..."

	if [[ $CARTYPE =~ "altima" ]]
	then
		ls -l /home/das3/src/libexpt_tables.so.1 | grep libexpt_tables.so.1.0
		x=$?
		ls -L /home/das3/src/libexpt_tables.so
		y=$?
		if [[ $x != 0 || $y != 0 ]]
		then
			echo No Altima standalone library links - creating them now
			rm /home/das3/src/libexpt*
			ln -sf /home/das3/src/lib_templates/lnx/libexpt_tables.so.1.0 /home/das3/src/libexpt_tables.so.1
			ln -sf /home/das3/src/libexpt_tables.so.1 /home/das3/src/libexpt_tables.so
			sudo ldconfig -n /home/das3/src
		fi
		
		# Start standalone altima data logging
#		/home/das3/src/lnx/wrfiles_das3 -m 2 -t 50 -d $TRIPDIR -c $VEH -i -D -r 1>$TRIPDIR/wrfiles_altima.log 2>$TRIPDIR/wrfiles_altima.err &
		/home/das3/src/lnx/wrfiles_das3 -m 2 -t 50 -d $TRIPDIR -c $VEH -D 1>$TRIPDIR/wrfiles_altima.log 2>$TRIPDIR/wrfiles_altima.err &
		exit 0
	fi
	
	if [[ $CARTYPE =~ "audi" ]]
	then
		if [[ $CARTYPE =~ "silver" ]]
		then
			VEH=j
		else
			VEH=k
		fi

		echo "$0: No Standalone Data Logging Script Specified for CARTYPE=$CARTYPE"
		exit 1
	fi

	if [[ $CARTYPE =~ "m56" ]]
	then
		ls -l /home/das3/src/libexpt_tables.so.1 | grep libexpt_tables.so.1.0
		x=$?
		ls -L /home/das3/src/libexpt_tables.so
		y=$?
		if [[ $x != 0 || $y != 0 ]]
		then
			echo No M56 standalone library links - creating them now
			rm /home/das3/src/libexpt*
			ln -sf /home/das3/src/lib_templates/lnx/libexpt_tables.so.1.0 /home/das3/src/libexpt_tables.so.1
			ln -sf /home/das3/src/libexpt_tables.so.1 /home/das3/src/libexpt_tables.so
			sudo ldconfig -n /home/das3/src
		fi
		
#		/home/das3/src/lnx/wrfiles_das3 -m 2 -t 50 -d $TRIPDIR -c $VEH -i -AD 1>$TRIPDIR/wrfiles_m56.log 2>$TRIPDIR/wrfiles_m56.err &
		/home/das3/src/lnx/wrfiles_das3 -m 2 -t 50 -d $TRIPDIR -c $VEH -AD 1>$TRIPDIR/wrfiles_m56.log 2>$TRIPDIR/wrfiles_m56.err &
echo VEH $VEH
		exit 0
	fi
fi

# NTMM starts Networked Traveler-Mobile Millennium Experiment
if [[ $EXPERIMENT =~ "ntmm" ]]
then
	if [[ $CARTYPE =~ "altima" ]]
	then
		ls -l /home/das3/src/libexpt_tables.so.1 | grep libalert_tables.so.1.0
		x=$?
		ls -L /home/das3/src/libexpt_tables.so
		y=$?
		if [[ $x != 0 || $y != 0 ]]
		then
			echo No CACC3 library links - creating them now
			rm /home/das3/src/libexpt*
			ln -sf /home/ntmm/src/lnx/libalert_tables.so.1.0 /home/das3/src/libexpt_tables.so.1
			ln -sf /home/das3/src/libexpt_tables.so.1 /home/das3/src/libexpt_tables.so
			sudo ldconfig -n /home/das3/src
		fi
		echo "Starting NTMM Experiment & Data Logging..."
		/home/ntmm/test/start.sh $CARTYPE $EXPERIMENT $TRIPDIR
		exit 0
	else
		echo "$CARTYPE CARTYPE not correct for $EXPERIMENT EXPERIMENT
		exit 1
	fi
fi

# CACC3 starts Nissan CACC3 Experiment
if [[ $EXPERIMENT =~ "cacc3" ]]
then
	if [[ $CARTYPE =~ "m56" ]]
	then
		ls -l /home/das3/src/libexpt_tables.so.1 | grep libcacc3_tables.so.1.0
		x=$?
		ls -L /home/das3/src/libexpt_tables.so
		y=$?
		if [[ $x != 0 || $y != 0 ]]
		then
			echo No CACC3 library links - creating them now
			rm /home/das3/src/libexpt*
			ln -sf /home/cacc3/src/lnx/libcacc3_tables.so.1.0 /home/das3/src/libexpt_tables.so.1
			ln -sf /home/das3/src/libexpt_tables.so.1 /home/das3/src/libexpt_tables.so
			sudo ldconfig -n /home/das3/src
		fi

		echo "Starting CACC3 Experiment & Data Logging..."
		/home/das3/src/lnx/wrfiles_das3 -m 2 -t 50 -d $TRIPDIR -c $VEH -i 1>$TRIPDIR/wrfiles_m56.log 2>$TRIPDIR/wrfiles_m56.err &
		exit 0
	else
		echo "$CARTYPE CARTYPE not correct for $EXPERIMENT EXPERIMENT
		exit 1
	fi
fi

# UNKNOWN EXPERIMENT
echo "$0: Detected Unknown EXPERIMENT=$EXPERIMENT"
echo "No Experiment Script or Data Logging Started..."
sleep 5
exit 1
