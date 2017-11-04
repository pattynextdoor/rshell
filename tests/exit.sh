#!/bin/bash

cd ..
make
cat tests/exit.txt | ./bin/rshell > tests/output.txt
cd tests
