#include <iostream>

using namespace std;

class Item {
	private:
		char* itemName;
		char* itemDescription;
		int itemNum;
	public:
		Item();
		Item(char* name, char* description);
		Item(char* name, char* description, int count);
		char* getName();
		char* getDescription();
		int getCount();
		void changeCount();
		~Item();
}
