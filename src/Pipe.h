#ifndef PIPE_H
#define PIPE_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#include "Connector.h"
#include "Cmd.h"
#include "Base.h"

class Cmd;

class Pipe : public Connector {
    public:
        Pipe();
        ~Pipe();
        Pipe(Cmd*); 
        bool execute(bool);
        string getExecutable() {return "";}; 
};

#endif