#include <iostream>
#include <vector>

using namespace std;

class CommandParser{
	private:
		char* rawText;
		char* command;
		vector<char*> arguments;	
	public:
		CommandParser(char* inputText);
		char* getCommand();
		char* getArg();
		char* getArg(int index);
		~CommandParser();
};
