#ifndef CONNECTOR_H
#define CONNECTOR_H

class Or : protected Connector {
    public:
        Or ();
        Or (Base*, Base*);
        ~Or ();
        bool execute();
        string getExecutable () {
            return "";
        };
};

#endif