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
		Inventory* getInvPtr();
		int getIndex();
		void setName(const char* name);
		char* getName();
		void setDescription(const char* description);
		char* getDescription();
		void addExit(const char* exitName, Zone* exitLocation);
		Zone* getExitByName(const char* exitName);
		~Zone();
};

#endif
