#include "And.h"

And::And () {
    Lchild = NULL;
    Rchild = NULL;
}

And::And (Cmd* Lchild) {
    this->Lchild = Lchild;
}

And::~And () {
    //delete Lchild;
    //delete Rchild;
}

bool And::execute (bool done) {
    if (done == true) {
        return false;
    }
    return true;
}