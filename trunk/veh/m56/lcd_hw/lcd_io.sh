#!/bin/bash

if [[ $# != 1 ]]
then
        echo "Usage $0 <m56_dnc304, m56_dne491, m56_pro4, m56_dne596>"
        exit 1
fi

if [[ $1 == "m56_dnc304" ]]
then
        VEH="M56-1_DNC304"
        FP="m"
else
if [[ $1 == "m56_pro4" ]]
then
        VEH="M56-2_PRO4"
        FP="n"
else
if [[ $1 == "m56_dne491" ]]
then
        VEH="M56-3_DNE491"
        FP="o"
else
if [[ $1 == "m56_dne596" ]]
then
        VEH="M56-4_DNE596"
        FP="p"
else
        echo "Usage $0 <m56_dnc304, m56_dne491, m56_pro4, m56_dne596>"
        exit 1
fi
fi
fi
fi

rm /tmp/lcdtemp

(echo hello
echo 'screen_add 0'
echo 'screen_set 0 -priority foreground'
echo 'widget_add 0 0 string'
echo 'widget_add 0 2 string'
echo 'widget_add 0 1 scroller'
echo 'client_add_key -exclusively {F5}+'
mystr='widget_set 0 0 1 1 "Starting lcd_io.sh"'
echo $mystr

while [ 1 ]
do 
	curstr=`tail -1 /tmp/lcdtemp`
	if [[ `echo $curstr | grep success` == '' && \
	   `echo $curstr | grep listen` == '' ]]
	then
		if [[ `echo $curstr | grep "key F5"` != '' ]]
		then
			umount /mnt
			mount /dev/LaCie_USB_drive /mnt
			if [[ `grep /mnt /etc/mtab` == '' ]]
			then
				mystr="widget_set 0 0 1 1 \"USB drive unmounted\""
				mystr1="widget_set 0 2 1 2 \"Is it plugged in?\""
				echo $mystr
				echo $mystr1
			else	
				numdirs=`ls -d /big/data/$FP'1'* | wc -l`
				numdirs=$(($numdirs-1))
				counter=0
				mystr="widget_set 0 0 1 1 \"\""
				echo $mystr
				mystr1="widget_set 0 0 1 2 \"\""
				echo $mystr1
				lastdir=`cat /big/data/lasttripdir.txt`
				for x in `ls -d /big/data/$FP'1'* | grep -v $lastdir$`
				do
					counter=$(($counter+1))
					mystr="widget_set 0 0 1 1 \"Copying $counter/$numdirs\""
					y=`echo $x | cut -c 11-`
					mystr1="widget_set 0 2 1 2 \"$y\""
					echo $mystr
					echo $mystr1
					cp -rfp $x /mnt/cacc/$VEH
					if [[ $? != 0 ]]
					then
						echo $mystr
						mystr="widget_set 0 1 1 1 20 1 h -1 \" \""
						echo $mystr
						mystr="widget_set 0 1 1 1 20 1 h -1 \"Error copying $x  \""
						echo $mystr
						counter=$(($counter-1))
					else
						mv $x /big/data/olddata
					fi	
				done	
				if [[ $counter -lt $numdirs ]]
				then
					numerrs=$((numdirs-$counter))
					mystr="widget_set 0 1 1 1 20 1 h -1 \"Copy error $numerrs dirs \""
					mystr1="widget_set 0 2 1 2 \"\""
					echo $mystr
					echo $mystr1
				else
					mystr="widget_set 0 1 1 1 20 1 h -1 \"Copy successful!\""
					mystr1="widget_set 0 2 1 2 \"\""
					echo $mystr
					echo $mystr1
				fi
			umount /mnt
			fi
		else
			mystr="widget_set 0 1 1 1 \"\""
			mystr1="widget_set 0 2 1 1 \"\""
			echo $mystr
			echo $mystr1
			mystr="widget_set 0 1 1 1 20 1 h -1 \"$curstr\""
			mystr1="widget_set 0 2 1 2 \"\""
			echo $mystr
			echo $mystr1
		fi
		touch /tmp/lcdlasttouch
	fi
sleep 5
done) \
| nc localhost 13666 >/tmp/lcdtemp
