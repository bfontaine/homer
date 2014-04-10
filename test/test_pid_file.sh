#! /bin/bash

PIDFILE=xyzabc${RANDOM}.tmp

$HOMER -p $PIDFILE sleep 2
sleep 1
if [ ! -f $PIDFILE ]; then
    exit 1
fi
rm -f $PIDFILE
