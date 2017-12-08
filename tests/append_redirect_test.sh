#!/bin/bash

cd ..
make
cat tests/append_redirect.txt | ./bin/rshell > tests/output.txt
cd tests
