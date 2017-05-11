#ifndef OR_H
#define OR_H

#include <string>
using namespace std;
#include "Connector.h"
#include "Base.h"

class Cmd;

class Or : public Connector {
    public:
        Or ();
        Or (Cmd*);
        ~Or ();
        bool execute(bool);
        string getExecutable () {
            return "";
        };
};

#endif