#!/bin/bash

cd ..
make
cat tests/output_redirect.txt | ./bin/rshell > tests/output.txt
cd tests
