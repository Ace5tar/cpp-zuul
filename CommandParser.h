#include <iostream>
#include <vector>

using namespace std;

class CommandParser{
	private:
		char* txtLoc;
		const char* command;
		vector<const char*> arguments;	
	public:
		CommandParser(char* inputText);
		const char* getCommand();
		const char* getArg();
		const char* getArg(int index);
		vector<const char*> getArgs();
		~CommandParser();
};
