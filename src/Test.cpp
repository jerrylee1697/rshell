#include "Test.h"

Test::Test() {
}

Test::Test(std::vector<string>& argumentList) {
    this->arguments = argumentList;
}

// IF arguments > 2, return false because not possible to have > 2
// If arguments < 2, default to -e
// If arguments == 2, check for:
//      -f: file/directory exists and is regular file
//      -d: file/directiry exists and is directory
// if strut(~,~) == 0: success
bool Test::execute(bool done) {
    
    // Checks if there are more than 2 arguments (invalid)
    if (arguments.size() > 2) {
        cout << "(False)\n";
        // return false;
        return false;
    }
    
    struct stat buf;
    
    // Checks single argument (defaults to -e)
    if (arguments.size() == 1) {
        if (stat(arguments.at(0).c_str(), &buf) == 0) {
            cout << "(True)\n";
            return true;
            // return false;
        }    
    }
    // cout << arguments.at(0)
    // Checks for arguments (-e, -f, -d)
    if (arguments.size() == 2) {
        if (stat(arguments.at(1).c_str(), &buf) == 0) {
            if (arguments.at(0) == "-f") {
                if (S_ISREG(buf.st_mode) == 0) {
                    cout << "(True)\n";
                    return true;
                    // return false;
                }
            }   
            if (arguments.at(0) == "-d") {
                if (S_ISDIR(buf.st_mode) != 0) {
                    cout << "(True)\n";
                    return true;
                    // return false;
                }
            }
            if (arguments.at(0) == "-e") {
                cout << "(True)\n";
                return true;
                // return false;
            }
        }
    }
    
    cout << "(False)\n";
    return false;
    // return true;
}