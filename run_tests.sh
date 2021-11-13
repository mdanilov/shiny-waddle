#!/bin/bash

# clear test output files
rm -r examples/test/out
mkdir examples/test/out

./build.sh

if [ $? -eq 0 ]
then
    cd build && ctest -C Debug -T test --output-on-failure
fi
