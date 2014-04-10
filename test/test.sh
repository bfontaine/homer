#! /bin/bash

TESTS=`find . -name 'test_*.sh' -type f -perm +111`
EXIT_CODE=0

echo "Testing with $HOMER"

if [ ! -x $HOMER ]; then
    echo "Can't find or execute $HOMER."
    exit 1
fi

for t in $TESTS; do
    ./$t >/dev/null
    if [ $? -eq 0 ]; then
        echo "[ ok ] $t"
    else
        echo "[fail] $t"
        EXIT_CODE=1
    fi
done

exit $EXIT_CODE
