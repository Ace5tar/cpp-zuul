/*
 * Belle Biery
 * 11/6/2025
 * Class for items
 */
#include <iostream>
#include <cstring>
#include "Item.h"

using namespace std;

// Default constrcutor
Item::Item() {
	itemNum = 1;
}

// Parameterized constructor without count - defaults to one
Item::Item(const char* name, const char* description) {
	char* nameHeapMem = new char[64];
	char* descHeapMem = new char[512];

	strcpy(nameHeapMem, name);
	strcpy(descHeapMem, description);

	itemName = nameHeapMem;
	itemDescription = descHeapMem;

	itemNum = 1;
}

// Parameterized constructor with count
Item::Item(const char* name, const char* description, int count) {
	char* nameHeapMem = new char[64];
	char* descHeapMem = new char[512];

	strcpy(nameHeapMem, name);
	strcpy(descHeapMem, description);

	itemName = nameHeapMem;
	itemDescription = descHeapMem;

	itemNum = count;
}

// Returns name of the item
char* Item::getName() {
	return itemName;
}

// Returns description of the item
char* Item::getDescription() {
	return itemDescription;
}

// Returns the count of the item
int Item::getCount() {
	return itemNum;
}

// Changes itemNum by deltacount
void Item::changeCount(int deltaCount) {
	itemNum += deltaCount;
} 

// Deconstructor
Item::~Item() {
	delete[] itemName;
	delete[] itemDescription;
}
