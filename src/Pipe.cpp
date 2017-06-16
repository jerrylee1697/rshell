#include "Pipe.h"

Pipe::Pipe() {
    Lchild = NULL;
    Rchild = NULL;
}

Pipe::~Pipe() {
    // delete Lchild;
    // delete Rchild;
}

Pipe::Pipe(Cmd* left, Cmd* right) {
    this->Lchild = left;
    this->Rchild = right;
}

bool Pipe::execute (bool done) {
    int fds[2];
    int stdinSaved = dup(0);    // Saves file descriptor 0 (read in) to 3
    int stdoutSaved = dup(1);   // Saves file descriptor 1 (write out) to 4
    int pipeResult;             // Result of Pipe()
    
    // If result == 0, Success
    // If result == -1, Error occured
    pipeResult = pipe(fds);
    
    if (pipeResult == -1) {
        perror("Pipe Failure");
        return false;
    }
    
    bool result = false;
    
    close(1);
    dup2(fds[1], STDOUT_FILENO);  // Puts one end of pipe stdout
    Lchild->execute(done);
    
    close(fds[1]);
    dup2(stdoutSaved,STDOUT_FILENO);    // Puts saved file descriptor to stdout
    close(0);
    
    dup2(fds[0],STDIN_FILENO);
    close(fds[0]);
    
    if (Rchild->execute(done)) {
        result = true;
    }
    
    dup2(stdinSaved, STDIN_FILENO); // Restores file descriptor
    close(stdinSaved);
    close(stdoutSaved);
    
    return result;
}