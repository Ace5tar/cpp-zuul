#include <iostream>
#include <vector>

#include "Zone.h"
#include "Inventory.h"

using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player {
	private:
		Inventory* invPtr;
		Zone* currentZone;
	public:
		Player();
		Player(Zone* startingZone);
		Inventory* getInvPtr();
		Zone* getCurrentZone();
		void changeZone(Zone* newZone);
		~Player();
};

#endif
		
	
