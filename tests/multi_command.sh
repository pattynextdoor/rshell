#!/bin/bash

cd ..
make
cat tests/multi_command.txt | ./bin/rshell > tests/output.txt
cd tests
