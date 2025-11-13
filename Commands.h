#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Commands{
	private:
		typedef void (*fnPtr)(vector<char*>);
		map<char*, fnPtr> commands;
		fnPtr getCommand(char* key);
		
	public:
		Commands();
		void addCommand(char* key, fnPtr cmd);
		void runCommand(char* key, vector<char*> args);
		~Commands();
};
