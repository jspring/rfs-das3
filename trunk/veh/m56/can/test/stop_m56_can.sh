#!/bin/sh

killall m56_can
killall -s KILL komodo_db_write
killall db_slv
/home/path/db/db_clean.sh
