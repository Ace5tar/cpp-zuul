/*
 * Belle Biery
 * 11/6/2025
 * Header file for zone class
 */

#include <iostream>
#include <vector>
#include <map>
#include "Item.h"
#include "Inventory.h"

using namespace std;

#ifndef ZONE_H
#define ZONE_H

class Zone {
	public:
		Inventory* invPtr;
		int zoneIndex;
		map<char*, Zone*> exits;
		map<char*, bool> statusFlags;
		char* zoneDescription;
		char* zoneName;
	public:
		Zone();
		Zone(int index);
		//void addItem(Item* item);
		//void delItem(Item* item);
		Inventory* getInvPtr();
		//Item* getItemByName(char* item);
		int getIndex();
		void setName(char* name);
		char* getName();
		void setDescription(char* description);
		char* getDescription();
		bool checkStatusFlag(char* flagName);
		void setStatusFlag(char* flagName, bool value);
		~Zone();
};

#endif
