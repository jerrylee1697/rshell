#ifndef REDIRECTOUTPUT_H
#define REDIRECTOUTPUT_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#include "Base.h"
#include "Connector.h"
#include "Cmd.h"

using namespace std;
#include <iostream>
// class Cmd;

class RedirectOutput : public Connector {
        string filename;
    public:
        RedirectOutput();
        ~RedirectOutput();
        RedirectOutput(Cmd*, string);
        bool execute(bool);
        string getExecutable () {return "";};
};

#endif