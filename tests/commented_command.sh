#!/bin/bash

cd ..
make
cat tests/commented_command.txt | ./bin/rshell > tests/output.txt
cd tests
