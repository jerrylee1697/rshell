#!/bin/sh
cd ../bin/

#case 1: test '>' on existing file
cat ../tests/input_redirect_test/test1.dat | ./rshell.exe > ../tests/input_redirect_test/test1o.dat

#case 2: test '>' on non-existing file
cat ../tests/input_redirect_test/test2.dat | ./rshell.exe > ../tests/input_redirect_test/test2o.dat