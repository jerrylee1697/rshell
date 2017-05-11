#ifndef BASE_H
#define BASE_H

#include <string>
using namespace std;

class Cmd;

class Base {
    protected:
        Cmd* Lchild;
        Base* Rchild;
    public:
        Base () { };
        ~Base () { };
        virtual bool execute (bool) = 0;
        virtual string getExecutable () = 0;
        void setRightChild(Base* tree) {
            Rchild = tree;
        }
};

#endif