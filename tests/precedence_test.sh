#!/bin/sh
cd ../bin/
#case 1: simple command with no parameters
echo "Case 1: No Parameter"
cat ../tests/precedence_test/test1.dat | ./rshell > ../tests/precedence_test/test1o.dat

#case 2: single parameter
echo "Case 2: Single Parameter"
cat ../tests/precedence_test/test2.dat | ./rshell > ../tests/precedence_test/test2o.dat
