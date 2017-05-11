#ifndef AND_H
#define AND_H

#include <string>
using namespace std;
#include "Connector.h"
#include "Base.h"

class Cmd;

class And : public Connector {
    public:
        And ();
        And (Cmd*);
        ~And ();
        bool execute (bool);
        string getExecutable () {
            return "";
            
        };
};

#endif