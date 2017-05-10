#include "Semi.h"

Semi::Semi () {
    Lchild = NULL;
    Rchild = NULL;
}

Semi::Semi (Base* Lchild) {
    this->Lchild = Lchild;
}

Semi::~Semi () {
    // delete Lchild;
    // delete Rchild;
}

bool Semi::execute () {
     this->Lchild->execute();
    return this->Rchild->execute();
}