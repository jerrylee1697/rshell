#include "RedirectInput.h"

RedirectInput::RedirectInput () {
    Lchild = NULL;
    Rchild = NULL;
}

RedirectInput::~RedirectInput () {
    // delete Lchild;
    // delete Rchild;
}

RedirectInput::RedirectInput (Cmd* left) {
    this->Lchild = left;
}

bool RedirectInput::execute (bool done) {
    string exec = Rchild->getExecutable();
    // Establish connection between file and file descriptor
    int fd = open(exec.c_str(), O_RDONLY, 0);
    // O_RDONLY = Open for reading only
    int stdin_copy = dup(0);
    // copying file descriptor
    
    close(0);
    // 0 - input redirect
    // 1 = output redirect
    dup2(fd, STDIN_FILENO);
    close(fd);
    
    bool successful = false;
    if (Lchild->execute(done)) {
        successful = true;
    }
    
    close(fd);
    dup2(stdin_copy, STDIN_FILENO);
    close(stdin_copy);
    
    return successful;
    
}