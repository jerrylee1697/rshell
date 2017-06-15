#ifndef REDIRECTOUTPUTAPPEND_H
#define REDIRECTOUTPUTAPPEND_H

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

// class Cmd;

class RedirectOutputAppend : public Connector {
    public:
        RedirectOutputAppend();
        ~RedirectOutputAppend();
        RedirectOutputAppend(Cmd*);
        bool execute(bool);
        string getExecutable () {return "";};
};

#endif