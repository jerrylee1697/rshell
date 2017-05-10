#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "Base.h"

class Connector : public Base {
    public:
        Connector () {};
        //Connector (Base*, Base*);
        ~Connector () {};
        virtual bool execute () = 0;
        virtual string getExecutable () = 0;
};

#endif