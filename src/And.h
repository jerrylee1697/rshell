#ifndef AND_H
#define AND_H

#include <string>
using namespace std;
#include "Connector.h"
#include "Base.h"

class And : public Connector {
    public:
        And ();
        And (Base*);
        ~And ();
        bool execute ();
        string getExecutable () {
            return "";
            
        };
};

#endif