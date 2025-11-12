/*
 * Belle Biery
 * 11/12/25
 * Player class for storing current inventory and current zone
 */

#include <iostream>
#include <vector>

#include "Zone.h"
#include "Inventory.h"
#include "Player.h"

using namespace std;

// Default constructor, should never be called
Player::Player() {
	invPtr = new Inventory();	
	currentZone = nullptr;
}

// Parameterized constructor
Player::Player(Zone* startingZone) {
	invPtr = new Inventory();
	currentZone = startingZone;
}

// Returns pointer to inventory
Inventory* Player::getInvPtr() {
	return invPtr;
}

// Returns pointer to the players current zone
Zone* Player::getCurrentZone() {
	return currentZone;
}

// Changes the current zone to the supplied one
void Player::changeZone(Zone* newZone) {
	currentZone = newZone;
}

// Deconstructor
Player::~Player() {
	delete invPtr;
}
