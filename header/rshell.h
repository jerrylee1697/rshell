#ifndef RSHELL_H
#define RSHELL_H

#include <vector>
#include <cstring>





class Connector : public Base {
    private:
        Base* Lchild;
        Base* Rchild;
    public:
};

class Semi : protected Connector {
    public:
        bool execute();
};

class And : protected Connector {
    public:
        bool execute();
};

class Or : protected Connector {
    public:
        bool execute();
};

#endif
