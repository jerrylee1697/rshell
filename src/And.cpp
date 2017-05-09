#include "And.h"

And::And () {
    Lchild = NULL;
    Rchild = NULL;
}

And::And (Base* Lchild, Base* Rchild) {
    this->Lchild = Lchild;
    this->Rchild = Rchild;
}

And::~And () {
    delete Lchild;
    delete Rchild;
}

bool And::execute () {
    if (this->Lchild->execute()) {
        return this->Rchild->execute();
    }
    return false;
}