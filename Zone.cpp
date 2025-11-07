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
#include "Item.h"
#include "Zone.h"

using namespace std;

// Default constructor, should never be called
Zone::Zone() {
	items = new vector<Item*>;
	exits = new map<char* Zone*>;
	statusFlags = new map<char*, bool>;
	zoneDescription = "DESCRIPTION";
	zoneName = "ZONE";
	zoneIndex = 0;
}

// Parameterized constructor, only takes an integer, set other data with their methods
Zone::Zone(int index) {
	items = new vector<Item*>;
	exits = new map<char* Zone>;
	statusFlags = new map<char*, bool>;
	zoneDescription = "DESCRIPTION";
	zoneName = "ZONE"; 
	zoneIndex = index;
}

// add an item to the item vector or increase the count if an item of the same name exists
void Zone::addItem(Item* item) {
	Item* itemPointer = this->getItemByName(item->getName());
	if (itemPointer != nullptr) {
		itemPointer->changeCount(item->getCount());
	} else {
		items.push_back(item);
	}
} 

// remove an item from the item vector 
void Zone::delItem(Item* item) {
	int i = 0;
	for (Item* itemIt : items) {
		if (itemIt == item) {items.erase(items.begin() + i);	
		++i;
	}
}
	
// Returns the vector of items in this room
vector<Item*> Zone::getItems() {
	return items;
}

// Returns an item pointer to the item specified, returns a null pointer if item doesnt exist
Item* Zone::getItemByName(char* item) {
	for (Item* itemIt : items) {
		if (strcmp(itemIt->getName(), item) == 0) {
			return itemIt;
				}
			}
	return nullptr;
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
