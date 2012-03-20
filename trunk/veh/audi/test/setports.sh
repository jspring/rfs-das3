#!/bin/sh

#GPS
#stty -F /dev/ttyUSB1 raw 4800

#EVT300 radar (from the intersection radar)
stty -F /dev/ttyS0 19200
stty -F /dev/ttyS0 -parenb -parodd cs8 -hupcl -cstopb cread clocal \
	-crtscts ignbrk -brkint ignpar -parmrk -inpck -istrip -inlcr igncr \
	-icrnl -ixon -ixoff -iuclc ixany -imaxbel -iutf8 -opost -olcuc \
	-ocrnl -onlcr onocr -onlret -ofill -ofdel nl0 cr0 tab0 bs0 vt0 ff0 \
	-isig -icanon -iexten -echo -echoe -echok -echonl -noflsh -xcase \
	-tostop -echoprt -echoctl -echoke


#Serial 5 Hz GPS
stty -F /dev/ttyS1 raw 19200

#Memsense Gyro
stty -F /dev/ttyUSB0 raw 115200
