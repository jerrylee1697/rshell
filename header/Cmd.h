#ifndef CMD_H
#define CMD_H

class CMD : public Base {
    private:
        vector<string> executable;
        Base* Lchild;
        Base* Rchild;
    public:
        CMD () {};
        CMD (const string) {};
        CMD (const string) {};
        ~CMD () {};
        bool execute ();
        string getExecutable ();
};

#endif