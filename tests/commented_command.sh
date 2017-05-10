#!/bin/sh
cd ../bin/
#case 1: simple command with no parameters
echo "Case 1: Middle Hash"
cat ../tests/commented_command_test/test1.dat | ./rshell > ../tests/commented_command_test/test1o.dat