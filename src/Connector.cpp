#include "Connector.h"

Connector::Connector () {
    Lchild = NULL;
    Rchild = NULL;
}

Connector::Connector (Base*Lchild, Base*Rchild) {
    this->Lchild = Lchild;
    this->Rchild = Rchild;
}

Connector::~Connector () {
    delete Lchild;
    delete Rchild;
}

