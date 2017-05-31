#ifndef TEST_H
#define TEST_H

#include "Base.h"

#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
using namespace std;


class Test : public Base {
    protected:
        vector<string> arguments;
    public:
        Test();
        Test(vector<string> &argumentList);
        bool execute(bool);
        string getExecutable() {return "";};
};

#endif