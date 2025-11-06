/*
 * Belle Biery
 * 11/6/2025
 * Class for zones
 * https://stackoverflow.com/questions/26281979/how-do-you-loop-through-a-stdmap
 */

#include <iostream>
#include <vector>
#include <map>
#include "Item.h"
#include "Zone.h"

using namespace std;

// Default constructor, should never be called
Zone::Zone() {
	vector<Item*> items;
	map<char*, Zone*> exits;
	map<char*, bool> statusFlags;
	char* zoneDescription;
	char* zoneName;
	int zoneIndex = 0;
}

// Parameterized constructor, only takes an integer, set other data with it's method
Zone::Zone(int index) {
	vector<Item*> items;
	map<char*, Zone*> exits;
	map<char*, bool> statusFlags;
	char* zoneDescription;
	char* zoneName;
	int zoneIndex = index;
}

// add an item to the item vector TODO
void Zone::addItem(Item* item) {

} 

// remove an item from the item vector TODO
void Zone::delItem(Item* item) {

}
	
// Returns the vector of items in this room
vector<Item*> Zone::getItems() {
	return items;
}

// Returns an item pointer to the item specified, returns a null pointer if item doesnt exist TODO
Item* Zone::getItemByName(char* item) {

}


// Returns the index of this zone
void Zone::getIndex() {
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
	return zoneDescription();
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
	for (Item* item : items) {delete item}
	delete[] zoneDescription;
	delete[] zoneName;
}
