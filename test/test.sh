#! /bin/bash

TESTS=`find . -name 'test_*.sh' -type f`
EXIT_CODE=0

for t in $TESTS; do
    ./$t
    if [ $? -eq 0 ]; then
        echo "[ ok ] $t"
    else
        echo "[fail] $t"
        EXIT_CODE=1
    fi
done

exit $EXIT_CODE
