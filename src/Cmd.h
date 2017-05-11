#ifndef CMD_H
#define CMD_H

#include <string>
#include <vector>
#include "Base.h"
using namespace std;

class Cmd : public Base {
    private:
        string executable;
        vector<string> argumentList;
    public:
        Cmd ();
        Cmd (const string&);
        Cmd (const string&, const vector<string>&);
        ~Cmd ();
        bool execute (bool);
        string getExecutable ();
};

#endif