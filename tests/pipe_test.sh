#!/bin/bash

cd ..
make
cat tests/pipe.txt | ./bin/rshell > tests/output.txt
cd tests
