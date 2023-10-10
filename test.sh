#!/usr/bin/env sh

hw=hw$1
shift

./build/tests/$hw/test_$hw "$@"