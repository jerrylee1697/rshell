#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#include "rshell.h"

bool CMD::execute() {
    return 0;
}

void CMD::push(string a) {
    executable.push_back(a);
}

bool Semi::execute() {
    return 0;
}

bool And::execute() {
    return 0;
}

bool Or::execute() {
    return 0;
}