/*
 * Belle Biery
 * 11/12/25
 * Class for inventory, just stores an item vector with methods to manipulate it
 */
#include <iostream>
#include <cstring>
#include <vector>
#include "Inventory.h"
#include "Item.h"

using namespace std;

// Default constructor
Inventory::Inventory() {}

// add an item to the item vector or increase the count if an item of the same name exists
void Inventory::addItem(Item* item) {
	Item* itemPointer = this->getItemByName(item->getName());
	if (itemPointer != nullptr) {
		itemPointer->changeCount(item->getCount());
	} else {
		itemVect.push_back(item);
	}
} 

// remove an item from the item vector 
void Inventory::delItem(Item* item) {
	int i = 0;
	for (Item* itemIt : itemVect) {
		if (itemIt == item) itemVect.erase(itemVect.begin() + i);	
		++i;
	}
}

// Returns an item pointer to the item specified, returns a null pointer if item doesnt exist
Item* Inventory::getItemByName(const char* itemName) {
	for (Item* itemIt : itemVect) {
		if (strcmp(itemIt->getName(), itemName) == 0) {
			return itemIt;
				}
			}
	return nullptr;
}

//Returns the item vector
vector<Item*> Inventory::getItemVect() {
	return itemVect;
}

// Deconstructor
Inventory::~Inventory() {
	for (Item* item : itemVect) {delete item;}
}
