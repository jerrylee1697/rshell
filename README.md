Project: rshell

Names: Jerry Lee, Natasha Orie

In this project, we have created a command shell called rshell in C++.
The shell is able to read in command lines, consisting of executables followed 
by arguements and connectors. Connectors consist of || or && or ;.
The shell is required to use C++ syscalls such as fork, execvp, and waitpid.
Anything that appears after a "#" character is considered a comment.
The shell is exited through typing "exit". 

In order to parse our inputs, we implemented a tokenizer function from the 
boost library. We also used the library unistd.h to use the fork() function.

