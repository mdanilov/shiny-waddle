#!/bin/bash

./build.sh

cd examples/basic
cp initial/Items.txt Items.txt
find . -type f -name '*.out' -delete
../../build/executor 4 Reader.txt Writer.txt Items.txt
cd -
