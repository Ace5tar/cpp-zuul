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
void Zone::setName(const char* name) {
	char* heapMem = new char[64];
	strcpy(heapMem, name);
	zoneName = heapMem;	
}

// Returns the name of this zone
char* Zone::getName() {
	return zoneName;
}

// Allocated memory on the heao and sets the description of this zone
void Zone::setDescription(const char* description) {
	char* heapMem = new char[512];
	strcpy(heapMem, description);
	zoneDescription = heapMem;
}

// Returns the description of this zone
char* Zone::getDescription() {
	return zoneDescription;
}

void Zone::addExit(const char* exitName, Zone* exitLocation) {
	char* heapMem = new char[64];
	strcpy(heapMem, exitName);
	exits.insert({heapMem, exitLocation});
}

Zone* Zone::getExitByName(const char* exitName) {
	for (const auto& [name, ptr] : exits) {
		if (strcmp(name, exitName) == 0) return ptr;
	}
	return nullptr;
}

map<char*, Zone*> Zone::getExitMap() {
	return exits;
}

// Deconstructor
Zone::~Zone() {
	for (auto const& [key, val] : exits) {delete[] key;}
	delete invPtr;
	delete[] zoneDescription;
	delete[] zoneName;
}
