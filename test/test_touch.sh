#! /bin/bash

FILE=x2_ceRc-a12.tmp

$HOMER touch $FILE
sleep 1
if [ ! -f $FILE ]; then
    exit 1
fi
rm -f $FILE
