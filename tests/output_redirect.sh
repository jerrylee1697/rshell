#!/bin/sh
cd ../bin/

#case 1: '<' on file that does not exist
cat ../tests/output_redirect_test/test1.dat | ./rshell.exe > ../tests/output_redirect_test/test1o.dat

#case 2: '<<' on existing file
cat ../tests/output_redirect_test/test2.dat | ./rshell.exe > ../tests/output_redirect_test/test2o.dat

#case 3: '<<' on non existing file
cat ../tests/output_redirect_test/test3.dat | ./rshell > ../tests/output_redirect_test/test3o.dat

#case 4: '<' on existing file
cat ../tests/output_redirect_test/test4.dat | ./rshell > ../tests/output_redirect_test/test4o.dat