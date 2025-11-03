#!/usr/bin/env sh

expected_sha1=$(sha1sum tests/test_file.txt | cut -d' ' -f1)

actual_sha1=$(echo 'SHA1 tests/test_file.txt' | ./rhasher | tr -d '\n' | sed 's/rhasher> //')

if [ "$expected_sha1" = "$actual_sha1" ]; then
    echo "SHA1 test PASSED"
    exit 0
else
    echo "SHA1 test FAILED"
    echo "Expected: $expected_sha1"
    echo "Got: $actual_sha1"
    exit 1
fi
