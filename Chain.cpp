#ifndef __CHAIN_CLASS__
#define __CHAIN_CLASS__

#include <iostream>
#include "Cmd.h"

using namespace std;

class Chain {
	private:
		int history_index;
		vector<Command*> history;

	public:
		Menu() {
			history_index = 0;
		};
		void execute() {
			//Prints the current commands value (based on history_index), if no commands exist
			//print 0 by default
			cout << history_index << ", " << history.size() << endl;
			if (history.size() == 0) {
				cout << "0" << endl;
			}
			else {
				cout << history.at(history_index)->execute() << endl;
			}
		};
		bool initialized() {
			//Return true if the history has been primed with a single op instruciton
			//This is necessary because that is the base of a calculation
			if(history.size() != 0) {return true;}
			return false;
		};
		void add_command(Command* cmd) {
			//Adds a command to history in the appropriate position (based on history_index)
			if(history_index < history.size() - 1 && history.size() != 0) {
				++history_index;
				history.at(history_index) = cmd;
			}
			else{
				history.push_back(cmd);
				if(history.size() > 1) {++history_index;}
			}
		};
		Command* get_command() {
			//Returns the command in history we are currently referring to (based on history_index)
			return history.at(history_index);
		};
		void undo() {
			//Moves to the last command in history (if possible)
			if(history.size() > 1 && history_index > 0) {
				--history_index;
			}
			else {
				cout << "Nothing to undo." << endl;
			}
		};
		void redo() {
			//Moves to the next command in history (if possible)
			if(history.size() > 1 && (history_index < history.size() - 1)) {
				++history_index;
			}
			else {
				cout << "Nothing to redo." << endl;
			}
		};
};

#endif //__MENU_CLASS__