#!/bin/bash

cd ..
make
cat tests/single_command.txt | ./bin/rshell > tests/output.txt
cd tests
