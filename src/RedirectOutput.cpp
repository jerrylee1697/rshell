#include "RedirectOutput.h"

RedirectOutput::RedirectOutput() {
    Lchild = NULL;
    Rchild = NULL;
}

RedirectOutput::~RedirectOutput() {
    // delete Lchild;
    // delete Rchild;
}

RedirectOutput::RedirectOutput(Cmd* Lchild, string filename) {
    this->Lchild = Lchild;
    this->filename = filename;
}

bool RedirectOutput::execute(bool done) {
     string exec = filename;
     
     //cout << filename << " inside\n";
     // 'w' = empty file & recreate
     // 'a' = append
     FILE *test = fopen(exec.c_str(), "w");
     
     if (test == NULL) {
         cout << "failed to open file\n";
     }
     
     int fd = fileno(test); 
     
     bool successful = false;
     
     int pid;
     pid = fork();
     
     if (pid == 0) {
         dup2(fd,STDOUT_FILENO);
         if (Lchild->execute(done)) {
             successful = true;
            //  cout <<"success";
         }
         fclose(test);
         exit(0);
     }
     
     return successful;
}

