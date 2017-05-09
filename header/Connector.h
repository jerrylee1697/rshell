#ifndef CONNECTOR_H
#define CONNECTOR_H

class Connector : public Base {
    
    protected:
        Base* Lchild;
        Base* Rchild;
        
    public:
        Connector ();
        Connector (Base*, Base*);
        ~Connector ();
        virtual bool execute () = 0;
        virtual string getExecutable () = 0;
};

#endif