#!/bin/sh
cd ../bin/
#case 1: simple command with no parameters
echo "Case 1: No Parameter"
cat ../tests/single_command_test/test1.dat | ./rshell > ../tests/single_command_test/test1o.dat

#case 2: single parameter
echo "Case 2: Single Parameter"
cat ../tests/single_command_test/test2.dat | ./rshell > ../tests/single_command_test/test2o.dat

#case 3: multiple parameters
echo "Case 3: More than 1 Parameters"
cat ../tests/single_command_test/test3.dat | ./rshell > ../tests/single_command_test/test3o.dat

#case 4: invalid parameter
echo "Case 4: Invalid Parameter"
cat ../tests/single_command_test/test4.dat | ./rshell > ../tests/single_command_test/test4o.dat

#case 5: invalid and valid parameter
echo "Case 5: Invalid and Valid Parameter"
cat ../tests/single_command_test/test5.dat | ./rshell > ../tests/single_command_test/test5o.dat

#case 6: simple command and invalid command
echo "Case 6: Invalid Command"
cat ../tests/single_command_test/test6.dat | ./rshell > ../tests/single_command_test/test6o.dat
