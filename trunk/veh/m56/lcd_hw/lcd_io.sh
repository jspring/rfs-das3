#!/bin/bash

(echo hello
echo 'screen_add 0'
echo 'screen_set 0 -priority foreground'
echo 'widget_add 0 0 string'
echo 'widget_add 0 2 string'
echo 'widget_add 0 1 scroller'
echo 'client_add_key -exclusively {F5}+'
loopctr=0
mystr="widget_set 0 0 1 1 \"Starting lcd_io.sh\""
echo $mystr
while [ 1 ]
do 
	curstr=`tail -1 /tmp/lcdtemp`
	if [[ `echo $curstr | grep success` == '' ]]
	then
		if [[ `echo $curstr | grep "key F5"` != '' ]]
		then
			mount /dev/LaCie_USB_drive /mnt
			if [[ `mount | grep LaCie_USB_drive | grep /mnt` == '' ]]
			then
				mystr="widget_set 0 0 1 1 \"USB drive unmounted\""
				mystr1="widget_set 0 2 1 2 \"Is it plugged in?\""
				echo $mystr
				echo $mystr1
			else	
				numdirs=`ls -d /big/data/e* | wc -l`
				counter=1
				for x in /big/data/e*
				do
					mystr="widget_set 0 0 1 1 \"Copying $counter/$numdirs\""
					echo $mystr
					cp -rfp $x /mnt/cacc/M56-3_DNE491
					if [[ $? != 0 ]]
					then
						echo $mystr
						mystr="widget_set 0 1 1 1 20 1 h -1 \" \""
						echo $mystr
						mystr="widget_set 0 1 1 1 20 1 h -1 \"Error copying $x  \""
						echo $mystr
					else
						mv $x /big/data/olddata
					fi	
				done	
			fi
		fi
		touch /tmp/lcdlasttouch
	else
		mystr="widget_set 0 0 1 1 \"$curstr\""
#		mystr="widget_set 0 1 1 1 15 1 h -1 \"$curstr\""
	fi
#	echo $mystr
sleep 5
done) \
| nc localhost 13666 >/tmp/lcdtemp
