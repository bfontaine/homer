#! /bin/bash

STDOUT_LOG=abcxyz${RANDOM}.tmp
DIR=dir${RANDOM}.tmp
EXPECTED=expected${RANDOM}.tmp

mkdir -p $DIR
touch $DIR/a
touch $DIR/b

\ls $DIR > $EXPECTED
$HOMER -o $STDOUT_LOG ls ${DIR}
sleep 1
diff -q $EXPECTED $STDOUT_LOG >/dev/null 2>&1
if [ $? -ne 0 ]; then
    exit 1
fi
rm -f $STDERR_LOG
rm -f $EXPECTED
rm -rf $DIR
