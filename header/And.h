#ifndef AND_H
#define AND_H

class And : protected Connector {
    public:
        And ();
        And (Base*, Base*);
        ~And ();
        bool execute ();
        string getExecutable () {
            return "";
            
        };
};

#endif