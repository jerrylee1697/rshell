#include "Cmd.h"
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

Cmd::Cmd (const string& input) {
    // string temp1 = input;
    
    // char* str = new char temp1.length();
    // strcpy(str, temp1.c_str());
    
    // char* pointer = strtok(str, " ");
    
    // while (point != NULL) {
    //     string temp2 = pointer;
    //     argumentList.push_back(temp2);
    //     pointer = strtok(NULL, " ");
    // }
}

Cmd::Cmd (const string& executable, const vector<string>& arguments) {
    this->executable = executable;
    for (unsigned i = 0; i < arguments.size(); ++i) {
        argumentList.push_back(arguments.at(i));
    }
}

//Cmd::~Cmd { }

bool Cmd::execute (bool done) {
    if (this->executable == "exit") {
        exit(0);
    }
    
    char* args[100];
    
    args[0] = (char*)executable.c_str();
    
    unsigned size = argumentList.size();
    for (unsigned i = 0; i < size; ++i) {
        args[i + 1] = (char*)(argumentList.at(i)).c_str();
    }
    
    args[size + 1] = NULL;
    
    pid_t pid = fork();
    
    if (pid == 0) {
        if (execvp(args[0],args) == -1) {
                perror ("The execution has failed.");
                return false;
             
        }
    }
    
    if (pid > 0) {
        if (waitpid(-1,0,0) == -1) {
            perror ("Waitpid has failed.");
            return false;
        }
    }
    return true;
}

string Cmd::getExecutable() {
    return executable;
}

