#ifndef BASE_H
#define BASE_H

#include <string>
using namespace std;

class Base {
    protected:
        Base* Lchild;
        Base* Rchild;
    public:
        Base () { };
        ~Base () { };
        virtual bool execute () = 0;
        virtual string getExecutable () = 0;
        void setRightChild(Base* tree) {
            Rchild = tree;
        }
};

#endif