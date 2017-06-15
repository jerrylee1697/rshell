#include "Or.h"

Or::Or () {
    Lchild = NULL;
    Rchild = NULL;
}

Or::Or (Cmd* Lchild) {
    this->Lchild = Lchild;
}

Or::~Or () {
    // delete Lchild;
    // delete Rchild;
}

bool Or::execute(bool skip) {
    //  if (skip == false) {
    //      return true;
    //  }
    //  return false;
    return skip;
}