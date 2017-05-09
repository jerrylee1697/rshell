#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#include "Base.h"
#include "Cmd.h"
#include "Connector.h"
#include "And.h"
#include "Or.h"
#include "Semi.h"

int main() {
    // while(1) {
        string executable = "";
        CMD command;
        
        cout << "$ ";
        cin >> executable;
        
        char* strptr;
        while(ret) {
            ret = strtok(ret, " ");
            cout << *ret << " ";
        }
    // }
}