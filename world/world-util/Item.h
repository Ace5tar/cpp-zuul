#include <iostream>

using namespace std;

#ifndef ITEM_H
#define ITEM_H


class Item {
	private:
		char* itemName;
		char* itemDescription;
		int itemNum;
	public:
		Item();
		Item(const char* name, const char* description);
		Item(const char* name, const char* description, int count);
		char* getName();
		char* getDescription();
		int getCount();
		void changeCount(int deltaCount);
		~Item();
};

#endif
