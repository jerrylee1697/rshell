#!/bin/sh
cd ../bin/

#case 1: exit
echo "Case 1: Exit Alone" 
cat ../tests/exit_test/test1.dat | ./rshell > ../tests/exit_test/test1o.dat

#case 4: beginning with exit
echo "Case 1: Exit at Beginning" 
cat ../tests/exit_test/test2.dat | ./rshell > ../tests/exit_test/test2o.dat

#case 3: exit in middle
echo "Case 1: Exit at Middle" 
cat ../tests/exit_test/test3.dat | ./rshell > ../tests/exit_test/test3o.dat

#case 1: exit at end
echo "Case 1: Exit at End" 
cat ../tests/exit_test/test4.dat | ./rshell > ../tests/exit_test/test4o.dat