#include "Semi.h"

Semi::Semi () {
    Lchild = NULL;
    Rchild = NULL;
}

Semi::Semi (Cmd* Lchild) {
    this->Lchild = Lchild;
}

Semi::~Semi () {
    // delete Lchild;
    // delete Rchild;
}

bool Semi::execute (bool done) {
    //this->Lchild->execute();
    return false;//this->Rchild->execute();
}