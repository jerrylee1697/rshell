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
#include "Pipe.h"
#include "RedirectInput.h"
#include "RedirectOutput.h"
#include "RedirectOutputAppend.h"

using namespace boost;

void Tokenize (const string& str, vector<string>& vec) { //splits string into tokens
    typedef tokenizer<char_separator<char> > tokenizer;
    char_separator<char> sep(";&|#()<>", ";&|#()<>", boost::keep_empty_tokens);
    tokenizer tok(str, sep);
    
    for(tokenizer::iterator tok_iter = tok.begin(); tok_iter != tok.end(); ++tok_iter) {
        vec.push_back(*tok_iter);
        if(*tok_iter == "&" || *tok_iter == "|" ) {tok_iter++; tok_iter++;}
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
        // if(*tok_iter == "&" || *tok_iter == "|") {tok_iter++;}
    }

}

void commentCheck(vector<string>& tok) { //if a # is detected, remove all following tokens
    if(tok.size() >= 2) {
        if (tok.at(1) == "#") {tok.clear();}
    }
    for(unsigned int i = 0; i < tok.size(); ++i) {
        if(tok.at(i) == "#") {
            tok.erase(tok.begin() + i, tok.end());
        }
    }
}

bool Execute(vector<string> input) {
    vector<string> arguments;
    string executable;
    Cmd* command;
    Connector* connect;
    bool done = false;
    bool skip = false;
   // bool redirect = false;
    int i = 0;
    
    while(input.size() != 0) {
        for(unsigned int j = 0; j < input.size(); ++j) {cout << input.at(j) << ", ";} cout << endl;
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
        for(unsigned int j = 0; j < input.size(); ++j) {cout << input.at(j) << ", ";} cout << endl;
        
        input.erase(input.begin());
        
        if(input.at(i) == ";") {
            connect = new Semi(command);
        }
        else if(input.at(i) == "&") {
            connect = new And(command);
        }
        else if(input.at(i) == "|") {
            if (input.at(i + 1) != "|") {   // Pipe if one "|"
                connect = new Pipe(command);
                input.erase(input.begin());
            }
            else {                              // Or if two "|"
                connect = new Or(command);
            }
        }
        else if(input.at(i) == "<") {   // Input Redirect
            connect = new RedirectInput(command);
            RedirectOutput();
        }
        else if(input.at(i) == ">") {
            if (input.at(i + 1) != ">") {
                connect = new RedirectOutput(command, input.at(i + 1));
                input.erase(input.begin());
                //redirect = true;
            }
            else {
                connect = new RedirectOutputAppend(command);
            }
        }
        
        input.erase(input.begin());
        for(unsigned int j = 0; j < input.size(); ++j) {cout << input.at(j) << ", ";} cout << endl;
        
        cout << "1" << endl;
        /*if(redirect == true) {
            skip = connect->execute(done);
            done = command->execute(done);
        } */
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
    bool recursion = false; //used to track whether commands in parentheses succeeded
    bool rightClosed = false; //check if the parentheses have closed
    //bool andVal = false;
    int i = 0;
    
    while(input.size() != 0) {
        //for(unsigned int j = 0; j < input.size(); ++j) {cout << input.at(j) << ", ";} cout << endl;
        if(input.size() == 1) { //BASE CASE: no connectors left
            arguments.clear();
            _Tokenize(input.at(i), arguments);
            executable = arguments.front();
            arguments.erase(arguments.begin());
            command = new Cmd(executable, arguments);
            return command->execute(done);
        }
        
        if(input.at(i) == "(") { //check for beginning parentheses, if found ENTER RECURSION
            input.erase(input.begin());
            //for(unsigned int j = 0; j < input.size(); ++j) {cout << input.at(j) << ", ";} cout << endl;
            recursion = ParenthExecute(input, recursion);
            rightClosed = true;
            if(input.size() == 0) {break;}
        }
        
        if(input.at(i) == ")") { //checks for empty parentheses
            input.erase(input.begin()); 
            //for(unsigned int j = 0; j < input.size(); ++j) {cout << input.at(j) << ", ";} cout << endl;
            return recursion;
        }
        
        if(input.at(i) != ";" && input.at(i) != "&" && input.at(i) != "|") { //check if a new command must be parsed
            arguments.clear();                    //parse first command
            _Tokenize(input.at(i), arguments);
            executable = arguments.front();
            arguments.erase(arguments.begin());
            command = new Cmd(executable, arguments);
            input.erase(input.begin());
            //for(unsigned int j = 0; j < input.size(); ++j) {cout << input.at(j) << ", ";} cout << endl;
        }
        
        if(input.at(i) == ")") { //check if there is a single command left within parentheses
            input.erase(input.begin()); 
            //for(unsigned int j = 0; j < input.size(); ++j) {cout << input.at(j) << ", ";} cout << endl;
            return command->execute(done);
        } 
        
        if(input.at(i) == ";") { //check for appropriate connector
            connect = new Semi(command);
            input.erase(input.begin());
            //andVal = true;
        }
        else if(input.at(i) == "&") {
            connect = new And(command);
            input.erase(input.begin());
            //andVal = true;
        }
        else if(input.at(i) == "|") {
            connect = new Or(command);
            input.erase(input.begin());
        } //for(unsigned int j = 0; j < input.size(); ++j) {cout << input.at(j) << ", ";} cout << endl;
        //if l-value is parentheses, set new command (r-value)
        if(rightClosed == true && input.at(i) != "(") {
            arguments.clear();                   
            _Tokenize(input.at(i), arguments);
            executable = arguments.front();
            arguments.erase(arguments.begin());
            command = new Cmd(executable, arguments);
            input.erase(input.begin());
        }
        
        if(recursion != true /*&& andVal == true*/) {
            //andVal = false;
            done = command->execute(done); //execute command and return success
            recursion = done;
            rightClosed = false;
            skip = connect->execute(done);
        }
        else { //if l-value succeeded, no need to re-execute command, simply figure out if skipping commands is necessary
            skip = connect->execute(recursion);
        } //execute connector to determine if rightCmd needs to be executed
        
        if(skip == true && input.size() >= 1) { //verify that first OR condition succeeded
            input.erase(input.begin());
            while(input.size() != 0) {
                if(input.at(0) == ")") {input.erase(input.begin()); return recursion;}
                //for(unsigned int j = 0; j < input.size(); ++j) {cout << input.at(j) << ", ";} cout << endl; return recursion;
                if(input.at(0) == "(") {
                    input.erase(input.begin());
                    input.erase(input.begin());
                    //for(unsigned int j = 0; j < input.size(); ++j) {cout << input.at(j) << ", ";} cout << endl;
                }
                if(input.at(0) == "|") {
                    input.erase(input.begin());
                    input.erase(input.begin());
                    //for(unsigned int j = 0; j < input.size(); ++j) {cout << input.at(j) << ", ";} cout << endl;
                }
                if(input.size() == 0) {break;}
                if(input.at(0) == "&" && rightClosed == false) {
                    input.erase(input.begin());
                    //for(unsigned int j = 0; j < input.size(); ++j) {cout << input.at(j) << ", ";} cout << endl;
                    break;
                }
                else if(input.at(0) == "&") {
                    input.erase(input.begin());
                    input.erase(input.begin());
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
   }
}

