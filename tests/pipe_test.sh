#!/bin/sh
cd ../bin/

#case 1: '|' is valid command
cat ../tests/pipe_test/test1.dat | ./rshell.exe > ../tests/pipe_test/test1o.dat

#case 2: multiple '|'
cat ../tests/pipe_test/test2.dat | ./rshell.exe > ../tests/pipe_test/test2o.dat