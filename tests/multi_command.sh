#!/bin/sh
cd ../bin/

#case 1: simple command with no parameter
echo "Case 1: AND"
cat ../tests/multi_command_test/test1.dat | ./rshell > ../tests/multi_command_test/test1o.dat

#case 2: simple command with 1 parameter
echo "Case 2: OR"
cat ../tests/multi_command_test/test2.dat | ./rshell > ../tests/multi_command_test/test2o.dat

#case 3: simple command with multiple parameters
echo "Case 3: SEMI"
cat ../tests/multi_command_test/test3.dat | ./rshell > ../tests/multi_command_test/test3o.dat

#case 4: simple command with multiple parameters
echo "Case 4: COMBINED"
cat ../tests/multi_command_test/test4.dat | ./rshell > ../tests/multi_command_test/test4o.dat