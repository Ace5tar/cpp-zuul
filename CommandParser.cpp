/*
 * Belle Biery
 * 11/6/2025
 * Parser to convert raw text input into commands and arguments
 * https://www.w3schools.com/cpp/ref_cstring_strtok.asp
 */

#include <iostream>
#include <cstring>
#include <vector>
#include "CommandParser.h"

using namespace std;

// Parameterized constructor
CommandParser::CommandParser(char* inputText) {
	rawText = inputText;
	char* delimPointer = strtok(rawText, " ");
	command = delimPointer;
	while (delimPointer != NULL) {
		arguments.push_back(strtok(NULL, " "));
	}	
}

// Returns first part of the input text
char* CommandParser::getCommand() {
	return command;
}

// Returns the first argument given 
char* CommandParser::getArg() {
	return arguments.at(0);
}

// Returns the argument at the given index
char* CommandParser::getArg(int index) {
	return arguments.at(index);
}

// Deconstructor
CommandParser::~CommandParser() {
	delete[] rawText;
}
