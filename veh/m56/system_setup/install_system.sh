#!/bin/bash
#
# Do various things when the OS is first installed
#

ps -aef |grep LCDd | grep -v grep
if [[ $? -ne 0 ]]
then
	sudo dpkg -i /home/das3/veh/m56/lcd_hw/lcdproc_0.5.3-1_i386.deb
	sudo cp /home/das3/veh/m56/system_setup/10-usbdevs.rules /etc/udev/rules.d
	sudo service udev restart
fi

sudo apt-get install lm-sensors

# Create data directories
sudo mkdir /big
sudo mkdir /big/data
sudo chown jspring /big/data
sudo chgrp users /big/data
mkdir /big/data/olddata
