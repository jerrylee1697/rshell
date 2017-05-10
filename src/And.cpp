#include "And.h"

And::And () {
    Lchild = NULL;
    Rchild = NULL;
}

And::And (Base* Lchild) {
    this->Lchild = Lchild;
}

And::~And () {
    //delete Lchild;
    //delete Rchild;
}

bool And::execute () {
    if (this->Lchild->execute()) {
        return this->Rchild->execute();
    }
    return false;
}