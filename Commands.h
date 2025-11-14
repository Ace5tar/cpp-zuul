#include <iostream>
#include <map>
#include <vector>

using namespace std;

#ifndef COMMANDS_H
#define COMMANDS_H

class Commands{
	private:
		typedef int (*fnPtr)(vector<char*>);
		map<char*, fnPtr> commands;
		fnPtr getCommand(char* key);
		
	public:
		Commands();
		void addCommand(char* key, fnPtr cmd);
		void runCommand(char* key, vector<char*> args);
		~Commands();
};

#endif
