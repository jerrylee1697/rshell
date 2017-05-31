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

bool Or::execute(bool done) {
    //  if (done == false) {
    //      return false;
    //  }
    //  return true;
    return done;
}