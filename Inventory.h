#include <iostream>
#include "Item.h"

using namespace std;

#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory {
	private:
		vector<Item*> itemVect;
	public:
		Inventory();
		void addItem(Item* item);
		void delItem(Item* item); 	
		Item* getItemByName(char* itemName);
		~Inventory();
};

#endif
