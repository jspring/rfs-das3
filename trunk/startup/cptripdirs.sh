#!/bin/sh

if [ ! $1 ] ; then
	echo Usage: $0 '<altima_silver, altima_grey, audi_silver, or audi_red>'
	exit
fi

CARTYPE=$1
echo "CPTRIPDIRS: Starting cptripdirs.sh for $CARTYPE" `date`

cd /big/data
if [[ -a lasttripcopied.txt ]] ; then
        lasttripcopied=$((10#`cat lasttripcopied.txt`))
else
	echo CPTRIPDIRS.SH: No readable file /big/data/lasttripcopied.txt
	lasttripcopied=0
	echo $lasttripcopied >lasttripcopied.txt
fi
echo lasttripcopied $lasttripcopied
lasttripnum=`echo $lasttripcopied`
nexttripnum=$lasttripnum
if [[ -a lasttripdir.txt ]] ; then
	# Do not copy current trip so subtract 1 from lasttripdir.txt
	savetripnum=$((10#`cat lasttripdir.txt`-1))
else
	savetripnum=$(($lasttripnum+100))
fi
echo lasttripnum $lasttripnum
echo nexttripnum $nexttripnum finaltripnum $savetripnum

if [ $1 = "test" ] ; then
	videohost="localhost"
else
	videohost=10.0.0.140
fi

ssh viduser@$videohost mkdir $1

while [[ nexttripnum -lt $savetripnum ]] ; do 
	
	nexttripnum=$(($nexttripnum+1))
	nexttripdir=`echo $nexttripnum |awk '{printf("%04d", $nexttripnum)}'` 
#	nexttripdir=`echo $nexttripnum |awk '{printf("%04d", $nexttripnum)}' 2>/dev/null`
#	nexttripdir=`ls -d *$nexttripnum 2>/dev/null`
	nexttripdir=`ls -d *$nexttripnum`
	if [[ -d $nexttripdir ]] ; then
		echo nexttripdir $nexttripdir
		echo nexttripnum $nexttripnum
		scp -rp *$nexttripdir viduser@$videohost:/home/viduser/$CARTYPE/nexttripdir/
		ssh root@$videohost mv /big/data/v${TRIPDIR:1:${#TRIPDIR}-1}/home/viduser/$CARTYPE/$nexttripdir
		echo $nexttripnum > lasttripcopied.txt
		lasttripcopied=$nexttripdir
		echo trip directory $lasttripcopied copied to $videohost
	fi
done
ssh root@$videohost chown -R viduser /big/data
ssh root@$videohost chgrp -R users /big/data
ssh root@$videohost chown -R viduser /home/viduser/$CARTYPE
ssh root@$videohost chgrp -R users /home/viduser/$CARTYPE

echo "CPTRIPDIRS: Finished with cptripdirs.sh" `date`
