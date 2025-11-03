#!/usr/bin/env sh

expected_md5=$(md5sum tests/test_file.txt | cut -d' ' -f1)

actual_md5=$(echo 'MD5 tests/test_file.txt' | ./rhasher | tr -d '\n' | sed 's/rhasher> //')

if [ "$expected_md5" = "$actual_md5" ]; then
    echo "MD5 test PASSED"
    exit 0
else
    echo "MD5 test FAILED"
    echo "Expected: $expected_md5"
    echo "Got: $actual_md5"
    exit 1
fi
