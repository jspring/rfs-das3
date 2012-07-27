#!/bin/bash

cp config.ssh $HOME/.ssh/config && \

if [[ ! -d $HOME/.subversion ]]
then
	mkdir $HOME/.subversion
	mkdir $HOME/tmp
	mkdir $HOME/tmp/.ssh
fi
cp config.subversion $HOME/.subversion/config && \

sudo apt-get install aptitude && \
sudo apt-get install subversion && \
sudo apt-get install g++ && \
sudo apt-get install cmake && \
sudo apt-get install cmake-curses-gui && \
sudo apt-get install openssh-server && \
sudo apt-get install libhighgui-dev && \
sudo apt-get install libcvaux-dev && \
sudo apt-get install libtorch3-dev && \
sudo apt-get install libxml2-dev && \
sudo apt-get install mplayer && \
sudo apt-get install ntpdate && \
sudo apt-get install liblapack-dev && \
sudo apt-get install liblapack-doc && \
sudo apt-get install vim-runtime && \
sudo apt-get install lm-sensors && \

cd /home
sudo chown jspring . && \
sudo chgrp users . && \

if [[ ! -d path ]]
then
	svn co $SVNURL/path/trunk path 
else
	svn up path 
fi

if [[ ! -d das3 ]]
then
	svn co $SVNURL/das3/trunk das3
else
	svn up das3
fi

if [[ ! -d video ]]
then
	svn co $SVNURL/video/trunk video
else
	svn up video
fi

if [[ ! -d vision ]]
then
	svn co $SVNURL/vision/trunk vision
else
	svn up vision
fi

mkdir /home/capath
cd /home/capath
ln -s ../path path
ln -s ../video video
ln -s ../vision vision

cd /home/path
make clean && \
make && \

cd /home/path/tilcon/setup && \
sudo ./550G-GM-TSP-RHLE4-X86-002.bin && \
sudo cp licensex.til /usr/Tilcon && \
cd /home/path/tilcon && \
make clean && \
make && \

cd /home/vision/zulibsrc && \
mkdir build
cd build
ccmake .. && \

cd /home/video && \
sudo ./setup-v4l2 && \

cd /home/das3/system_setup && \
sudo cp rc.local.das3 /etc/rc.local && \
sudo cp interfaces.das3 /etc/network/interfaces && \
sudo cp 10-usbdevs.rules /etc/udev/rules.d/10-usbdevs.rules && \
sudo cp resolv.conf.das3 /etc/resolv.conf && \
sudo cp das3.conf /etc/ld.so.conf.d && \
sudo ldconfig && \
cd /home/das3 && \
make clean && \
make && \

echo && \
echo && \
echo && \
echo "PUT THIS INTO /usr/include/libavutil/common.h:" && \
echo "#define UINT64_C(c)    c ## ULL" && \
echo && \
echo && \
echo && \
echo "Well, if you got this far, everything should work!"
echo && \
echo
