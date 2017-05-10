#include "Or.h"

Or::Or () {
    Lchild = NULL;
    Rchild = NULL;
}

Or::Or (Base*Lchild) {
    this->Lchild = Lchild;
}

Or::~Or () {
    // delete Lchild;
    // delete Rchild;
}

bool Or::execute() {
    if (!this->Lchild->execute()) {
        return this->Rchild->execute();
    }
    return this->Lchild;
}