This directory contains scripts and other files necessary for setting
up a DAS system in a vehicle for the first time.

Several system files have to be modified (e.g. /etc/rc.local, 
/etc/network/interfaces) which are standard to the Linux operating system and
not part of our DAS.  Also, certain utilities and libraries that are used by
our DAS must be installed in OS directories in order to be visible to the OS.

This README will probably be edited a lot in the future, but for now, look at
the installation script INSTALL.sh to see what is supposed to happen. Then run
it.  Deal with the errors until there aren't any.  Good luck.
