#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#include <unistd.h>
#include <boost/tokenizer.hpp>

#include "Base.h"
#include "Cmd.h"
#include "Or.h"
#include "And.h"
#include "Semi.h"
using namespace std;
using namespace boost;

void Tokenize (const string& str, vector<string>& vec) { //splits string into tokens
    typedef tokenizer<char_separator<char> > Tok;
    char_separator<char> sep; // default constructed
    Tok tok(str, sep);
    
    for(Tok::iterator tok_iter = tok.begin(); tok_iter != tok.end(); ++tok_iter) {
        vec.push_back(*tok_iter);
        if(*tok_iter == "&" || *tok_iter == "|") {tok_iter++;}
    }

}

void commentCheck(vector<string>& tok) { //if a # is detected, remove all following tokens
    for(unsigned int i = 0; i < tok.size(); ++i) {
        if(tok.at(i) == "#") {
            tok.erase(tok.begin() + i, tok.end());
        }
    }
}

Base* createTree(vector<string> tok) {
    unsigned int i;
    string executable;
    vector<string> arguments;
    Base* rt = NULL;
    
    bool found = false; 
    for(i = 0; i < tok.size(); ++i) { //checking to see if there are any connectors
        if(tok.at(i) == ";" || tok.at(i) == "|" || tok.at(i) == "&") {
            found = true;
        }
    }
    if(found == false) { //Base case: no connectors
        i = 0;
        executable = tok.at(i);
        ++i;
        for(;i < tok.size(); ++i) {
            arguments.push_back(tok.at(i));
        }
        Base* rt = new Cmd(executable, arguments);
        return rt;
    }
    
    return rt;
}
/*
Base* createTree(vector<string> tok) {
    unsigned int i = 0;
    string executable;
    vector<string> arguments;
    Base* tree = NULL;
    Base* prev;
    // Base* rt;
    
    //while(i < tok.size()) {
        executable = tok.at(i);
        ++i;
        while(i <= tok.size() && (tok.at(i) != ";" || tok.at(i) != "|" || tok.at(i) != "&")) {
            arguments.push_back(tok.at(i));
            ++i;
        } 
        tree = new Cmd(executable, arguments); 
        // rt = tree;
        prev = tree;
    while(i < tok.size()) {
        if(i != tok.size()) {
            if(tok.at(i) == ";") {
                tree = new Semi(tree);
                //prev->setRightChild(tree);
                prev = tree;
                ++i;
            } 
            else if (tok.at(i) == "|") {
                tree = new Or(prev);
                //prev->setRightChild(tree);
                prev = tree;
                ++i;
            }
            else if (tok.at(i) == "&") {
                tree = new And(prev);
                //prev->setRightChild(tree);
                prev = tree;
                ++i;
            }
        } 
        executable = tok.at(i);
        ++i;
        while(i <= tok.size() && (tok.at(i) != ";" || tok.at(i) != "|" || tok.at(i) != "&")) {
            arguments.push_back(tok.at(i));
            ++i;
        } 
        tree = new Cmd(executable, arguments); 
        prev->setRightChild(tree);
    }
    return tree;
}*/

int main() {
   while(1) {
        string executable = "";
        vector<string> tok;
        
        cout << "$ ";
        getline(cin, executable);
        
        Tokenize(executable, tok);
        commentCheck(tok);
        Base* tree;
        tree = createTree(tok);
        tree->execute();
   }
}

