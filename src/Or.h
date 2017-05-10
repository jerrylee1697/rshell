#ifndef OR_H
#define OR_H

#include <string>
using namespace std;
#include "Connector.h"
#include "Base.h"

class Or : public Connector {
    public:
        Or ();
        Or (Base*);
        ~Or ();
        bool execute();
        string getExecutable () {
            return "";
        };
};

#endif