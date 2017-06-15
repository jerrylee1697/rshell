#ifndef REDIRECTINPUT_H
#define REDIRECTINPUT_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#include "Base.h"
#include "Connector.h"
#include "Cmd.h"

// class Cmd;

class RedirectInput : public Connector {
    public:
        RedirectInput ();
        ~RedirectInput ();
        RedirectInput (Cmd*);
        bool execute (bool);
        string getExecutable () {return "";}; 
};

#endif