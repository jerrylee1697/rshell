#ifndef SEMI_H
#define SEMI_H

#include "Connector.h"
#include "Base.h"
#include <string>
using namespace std;

class Cmd;

class Semi : public Connector {
    public:
        Semi ();
        Semi (Cmd*);
        ~Semi ();
        bool execute (bool);
        string getExecutable () {
            return "";
        };
};

#endif