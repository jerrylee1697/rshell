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
    for(unsigned int a = 0; a < vec.size(); ++a) { //check for a delete empty spaces
        if(vec.at(a) == " " || vec.at(a) == "") {vec.erase(vec.begin() + a);}
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

bool ParenthExecute(vector<string>& input, bool in) {
    vector<string> arguments;
    string executable;
    Cmd* command;
    Connector* connect;
    bool done = false;
    bool skip = false;
    bool recursion = false;
    bool rightClosed = false;
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
       // for(unsigned int a = 0; a < input.size(); ++a) {cout << input.at(a) << ", "; } cout << endl;
        
        if(input.at(i) == "(") { //check for beginning parentheses, if found ENTER RECURSION
            input.erase(input.begin());
            recursion = ParenthExecute(input, recursion);
            rightClosed = true;
            //for(unsigned int a = 0; a < input.size(); ++a) {cout << input.at(a) << ", "; } cout << endl;
            if(input.size() == 0) {break;}
        }
        
        if(input.at(i) == ")") {/*return false;*/ return recursion;}
        
        if(input.at(i) != ";" && input.at(i) != "&" && input.at(i) != "|") {
        arguments.clear();                    //parse first command
        _Tokenize(input.at(i), arguments);
        executable = arguments.front();
        arguments.erase(arguments.begin());
        command = new Cmd(executable, arguments);
        input.erase(input.begin());
        }
        
        if(input.at(i) == ")") {return command->execute(done);} //check if there is a single command contained within parentheses
        
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
        
        if(rightClosed != true) {done = command->execute(done); rightClosed = false;} //execute command and return success 
        skip = connect->execute(done); //execute connector to determine if rightCmd needs to be executed
        recursion = done;
        
        if(skip == true) { //verify that first OR condition succeeded
            input.erase(input.begin());
            while(input.size() != 0) {
                if(input.at(0) == ")") {/*return done;*/ return recursion;}
                if(input.at(0) == "(") {
                    input.erase(input.begin());
                    input.erase(input.begin());
                }
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

void ParenthCheck(vector<string> input) {
    int leftParenth = 0;
    int rightParenth = 0;
    
    for(unsigned int i = 0; i < input.size(); ++i) {
        if(input.at(i) == "(") {leftParenth++;}
        if(input.at(i) == ")") {rightParenth++;}
    }
    if(leftParenth != rightParenth) {
        cout << "Error: Uneven number of parentheses." << endl;
    }
    if(leftParenth == rightParenth && leftParenth != 0 && rightParenth != 0) {
        ParenthExecute(input, 0);
    }
    if (leftParenth == 0 && rightParenth == 0) {
        Execute(input);
    }
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
        ParenthCheck(tok);
        //Execute(tok);
   }
}

