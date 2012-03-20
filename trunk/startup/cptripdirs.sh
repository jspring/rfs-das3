#!/bin/sh

echo "CPTRIPDIRS: Starting cptripdirs.sh" `date`
if [ ! $1 ] ; then
	echo Usage: $0 '<altima_silver, altima_grey, audi_silver, or audi_red>'
	exit
fi

cd /big/data
if [[ -a lasttripcopied.dat ]] ; then
        lasttripcopied=$((10#`cat lasttripcopied.dat`))
else
	echo CPTRIPDIRS.SH: No readable file /big/data/lasttripcopied.dat
	lasttripcopied=0
	echo $lasttripcopied >lasttripcopied.dat
fi
echo lasttripcopied $lasttripcopied
lasttripnum=`echo $lasttripcopied`
nexttripnum=$lasttripnum
if [[ -a lasttripdir.dat ]] ; then
	# Subtract 1 from lasttripdir.dat because cptripdirs.sh is started 
	# after wrfiles_nt, which has already incremented lasttripdir.dat
	savetripnum=$((10#`cat lasttripdir.dat`-1))
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
		scp -rp *$nexttripdir viduser@$videohost:/home/viduser/$1/e$nexttripdir/
		ssh root@$videohost mv /big/data/v$nexttripdir /home/viduser/$1/e$nexttripdir
		echo $nexttripnum > lasttripcopied.dat
		lasttripcopied=$nexttripdir
		echo trip directory $lasttripcopied copied to $videohost
	fi
done
ssh root@$videohost chown -R viduser /big/data
ssh root@$videohost chgrp -R users /big/data
ssh root@$videohost chown -R viduser /home/viduser/$1
ssh root@$videohost chgrp -R users /home/viduser/$1

echo "CPTRIPDIRS: Finished with cptripdirs.sh" `date`
