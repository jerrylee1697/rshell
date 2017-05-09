#include "Or.h"

Or::Or () {
    Lchild = NULL;
    Rchild = NULL;
}

Or::Or (Base*Lchild, Base* Rchild) {
    this->Lchild = Lchild;
    this->Rchild = Rchild;
}

Or::~Or () {
    delete Lchild;
    delete Rchild;
}

bool Or::execute() {
    if (!this->Lchild->execute()) {
        return this->Rchild->execute();
    }
    return this->Lchild;
}