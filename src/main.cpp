#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#include <sys/types.h>
#include <sys/stat.h>
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
    typedef tokenizer<char_separator<char> > tokenizer;
    char_separator<char> sep(";&|#()", ";&|#()", boost::keep_empty_tokens);
    tokenizer tok(str, sep);
    
    for(tokenizer::iterator tok_iter = tok.begin(); tok_iter != tok.end(); ++tok_iter) {
        vec.push_back(*tok_iter);
        if(*tok_iter == "&" || *tok_iter == "|") {tok_iter++; tok_iter++;}
    }

}
void _Tokenize (const string& str, vector<string>& vec) { //splits string into tokens
    typedef tokenizer<char_separator<char> > tokenizer;
    char_separator<char> sep(" ");
    tokenizer tok(str, sep);
    
    for(tokenizer::iterator tok_iter = tok.begin(); tok_iter != tok.end(); ++tok_iter) {
        vec.push_back(*tok_iter);
        //if(*tok_iter == "&" || *tok_iter == "|") {tok_iter++;}
    }

}

void commentCheck(vector<string>& tok) { //if a # is detected, remove all following tokens
    if(tok.size() >= 2) {
        if (tok.at(1) == "#") {tok.clear();}
    }
    //else {
        for(unsigned int i = 0; i < tok.size(); ++i) {
            if(tok.at(i) == "#") {
                tok.erase(tok.begin() + i, tok.end());
            }
        }
    //}
    
}

bool Execute(vector<string> input) {
    vector<string> arguments;
    string executable;
    Cmd* command;
    Connector* connect;
    bool done = false;
    bool skip = false;
    int i = 0;
    
    while(input.size() != 0) {
        
        if(input.size() == 1) { //base case: no connectors
            arguments.clear();
            _Tokenize(input.at(i), arguments);
            //commentCheck(arguments);
            //if(arguments.size() == 0) {return true;}
            executable = arguments.front();
            arguments.erase(arguments.begin());
            //cout << executable << ", " << arguments.at(0) << endl;
            command = new Cmd(executable, arguments);
            return command->execute(done);
        }
        arguments.clear();
        _Tokenize(input.at(i), arguments);
        executable = arguments.front();
        arguments.erase(arguments.begin());
        command = new Cmd(executable, arguments);
        
        input.erase(input.begin());
        
        if(input.at(i) == ";") {
            connect = new Semi(command);
        }
        else if(input.at(i) == "&") {
            connect = new And(command);
        }
        else if(input.at(i) == "|") {
            connect = new Or(command);
        }
        input.erase(input.begin());
        
        done = command->execute(done);
        skip = connect->execute(done);
        
        if(skip == true) { //check if the first OR condition executed
            input.erase(input.begin());
            while(input.size() != 0) {
                if(input.at(0) == "|") {
                    input.erase(input.begin());
                    input.erase(input.begin());
                }
                if(input.size() == 0) {break;}
                if(input.at(0) == "&") {
                    input.erase(input.begin());
                    break;
                }
            }
        }
    }
    return 0;
}

int main() {
    string executable = "";
        vector<string> tok;
   while(1) {
        tok.clear();
        
        cout << "$ ";
        getline(cin, executable);
        
        Tokenize(executable, tok);
        commentCheck(tok);
        Execute(tok);
   }
}

