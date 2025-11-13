/*
 * Belle Biery
 * 11/13/25
 * Basic class for creating and calling commands
 */
#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include "Commands.h"

using namespace std;

typedef void (*fnPtr)(vector<char*>);

// Default costructor
Commands::Commands() {}

// Get the pointer to the command with the given key, private
fnPtr Commands::getCommand(char* key) {
	for (auto const& [cmdKey, cmd] : commands) {
		if (strcmp(cmdKey, key) == 0) {
			return cmd;
		}
	}
	return nullptr;
}


// Add a key, function pointer pair to the map
void Commands::addCommand(char* key, fnPtr cmd) {
	char* heapMem = new char[16];
	*heapMem = *key;
	commands.at(heapMem) = cmd;
}

// Run the command with the given key and the deallocate the memory for the key
void Commands::runCommand(char* key, vector<char*> args) {
	getCommand(key)(args);
	delete[] key;
}

// Deconstructor
Commands::~Commands() {
	for (auto const& [cmdKey, cmd] : commands) {
		delete[] cmdKey;
	}
}
