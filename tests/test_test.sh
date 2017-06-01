#!/bin/sh
cd ../bin/
#case 1: simple command with no parameters
echo "Case 1: No Parameter"
cat ../tests/test_test/test1.dat | ./rshell > ../tests/test_test/test1o.dat

#case 2: single parameter
echo "Case 2: Single Parameter"
cat ../tests/test_test/test2.dat | ./rshell > ../tests/test_test/test2o.dat

#case 3: multiple parameters
echo "Case 3: More than 1 Parameters"
cat ../tests/test_test/test3.dat | ./rshell > ../tests/test_test/test3o.dat

#case 4: invalid parameter
echo "Case 4: Invalid Parameter"
cat ../tests/test_test/test4.dat | ./rshell > ../tests/test_test/test4o.dat

