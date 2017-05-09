#ifndef BASE_H
#define BASE_H

class Base {
    public:
        Base () { };
        ~Base () { };
        virtual bool execute () = 0;
        virtual string getExecutable () = 0;
};

#endif