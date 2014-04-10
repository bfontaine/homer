#! /bin/bash

STDERR_LOG=xyzabc${RANDOM}.tmp

$HOMER -e $STDERR_LOG ls doesntexist${RANDOM}
sleep 1
if [ ! -f $STDERR_LOG ] || [ $(wc -l < $STDERR_LOG) -ne 1 ]; then
    exit 1
fi
rm -f $STDERR_LOG
