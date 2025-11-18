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
	txtLoc = new char[64];
	strcpy(txtLoc, inputText);

	const char* delimPointer = strtok(txtLoc, " ");
	command = delimPointer;
	delimPointer = strtok(NULL, " ");
	while (delimPointer != NULL) {
		arguments.push_back(delimPointer);
		delimPointer = strtok(NULL, " ");
	}	
}

// Returns first part of the input text
const char* CommandParser::getCommand() {
	return command;
}

// Returns the first argument given 
const char* CommandParser::getArg() {
	return arguments.at(0);
}

// Returns the argument at the given index
const char* CommandParser::getArg(int index) {
	return arguments.at(index);
}

vector <const char*> CommandParser::getArgs() {
	return arguments;
}

// Deconstructor
CommandParser::~CommandParser() {
	delete[] txtLoc;
}
