#!/bin/bash

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

cd /home
sudo chown jspring . && \
sudo chgrp users . && \
svn co $SVNURL/path/trunk path && \
svn co $SVNURL/das3/trunk das3 && \
svn co $SVNURL/video/trunk video && \
svn co $SVNURL/vision/trunk vision && \
mkdir /home/capath && \
cd capath && \
ln -s ../path path && \
ln -s ../video video && \
ln -s ../vision vision && \

cd /home/path && \
make && \
cd /home/path/tilcon/setup && \
sudo ./550G-GM-TSP-RHLE4-X86-002.bin && \
sudo cp licensex.til /usr/Tilcon && \

echo
echo
echo
echo "PUT THIS INTO /usr/include/libavutil/common.h:" && \
echo "#define UINT64_C(c)    c ## ULL" && \
echo
echo
echo

cd /home/vision/zulibsrc && \
mkdir build && \
cd build && \
ccmake .. && \

cd /home/video && \
sudo ./setup-v4l2
