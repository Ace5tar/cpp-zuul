/*
 * Belle Biery
 * 11/6/2025
 * Class for zones
 * https://stackoverflow.com/questions/26281979/how-do-you-loop-through-a-stdmap
 */

#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include "Inventory.h"
#include "Zone.h"

using namespace std;

// Default constructor, should never be called
Zone::Zone() {
	invPtr = new Inventory();
	zoneIndex = 0;
}

// Parameterized constructor, only takes an integer, set other data with their methods
Zone::Zone(int index) {
	invPtr = new Inventory();
	zoneIndex = index;
}

// Returns a pointer to the inventory in this room
Inventory* Zone::getInvPtr() {
	return invPtr;
}

// Returns the index of this zone
int Zone::getIndex() {
	return zoneIndex;
}

// Sets the name of this zone
void Zone::setName(char* name) {
	zoneName = name;	
}

// Returns the name of this zone
char* Zone::getName() {
	return zoneName;
}

// Sets the description of this zone
void Zone::setDescription(char* description) {
	zoneDescription = description;
}

// Returns the description of this zone
char* Zone::getDescription() {
	return zoneDescription;
}

// Returns the value of the status flag with the given name
bool Zone::checkStatusFlag(char* flagName){
	return statusFlags[flagName];
}

// Changes the status flag of the given name to the given value
void Zone::setStatusFlag(char* flagName, bool value) {
	statusFlags[flagName] = value;
}

// Deconstructor
Zone::~Zone() {
	for (auto const& [key, val] : statusFlags) {delete[] key;}
	for (auto const& [key, val] : exits) {delete[] key;}
	delete[] zoneDescription;
	delete[] zoneName;
}
