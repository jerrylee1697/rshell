#include "RedirectOutputAppend.h"

RedirectOutputAppend::RedirectOutputAppend() {
    Lchild = NULL;
    Rchild = NULL;
}

RedirectOutputAppend::~RedirectOutputAppend() {
    // delete Lchild;
    // delete Rchild;
}

RedirectOutputAppend::RedirectOutputAppend(Cmd* Lchild) {
    this->Lchild = Lchild;
}

bool RedirectOutputAppend::execute(bool done) {
     string exec = Rchild->getExecutable();
     
     // 'w' = empty file & recreate
     // 'a' = append
     FILE *test = fopen(exec.c_str(), "a");
     
     int fd = fileno(test); 
     
     bool successful = false;
     
     int pid = fork();
     
     if (pid == 0) {
         dup2(fd,STDOUT_FILENO);
         if (Lchild->execute(done)) {
             successful = true;
         }
         fclose(test);
         exit(0);
     }
     
     return successful;
}

