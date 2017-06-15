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

bool And::execute (bool skip) {
    if (skip == true) {
        return false;
    }
    return true;
    
    // if (done == false) {
    //     return true;
    // }
    // return fa;
}