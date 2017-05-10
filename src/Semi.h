#ifndef SEMI_H
#define SEMI_H

#include "Connector.h"
#include "Base.h"
#include <string>
using namespace std;

class Semi : public Connector {
    public:
        Semi ();
        Semi (Base*);
        ~Semi ();
        bool execute ();
        string getExecutable () {
            return "";
        };
};

#endif