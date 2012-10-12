#!/bin/sh
# Starts data server, read process in simulation mode (-s)
# and altima_db_read process 
# Copy file to test into local data.txt
DB_DIR=/home/capath/path/db/lnx
CAN_DIR=/home/capath/nt-onboard/can/lnx
$DB_DIR/db_slv &
sleep 1
$CAN_DIR/altima_db_write -s < data.txt & 
sleep 1
$CAN_DIR/altima_db_read  -v 
