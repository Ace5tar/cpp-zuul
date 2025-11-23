#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include "world-util/Player.h"
#include "world-util/Zone.h"
#include "../util/StateBasedAction.h"
#include "WorldInterface.h"
#include "../util/CommandParser.h"

using namespace std;

typedef int (WorldInterface::*fnPtr)(vector<const char*>);

//Defalt Constructor
WorldInterface::WorldInterface() {

	this->createZones();
	this->createCommands();
	this->createSBAs();

	player = new Player(zoneVec.at(0));

	input = new char[128];

	printZoneDetails(player->getCurrentZone());
}

// Checks state based actions then asks user for input and does that command
int WorldInterface::runTick() {
	for (StateBasedAction* sba : SBAVec){ sba->checkState(); }	

	cin.getline(input, 128);
	while(strlen(input) == 0) {cin.getline(input, 128);}
	CommandParser cp = CommandParser(input);
	fnPtr cmdPtr = getCmd(cp.getCommand());
	if (cmdPtr == nullptr) {
		cout << "Invalid command!" << endl;
		return 0;
	} else {
		return (this->*(cmdPtr))(cp.getArgs());
	}
}

// Create the zone vector and adds zone information
void WorldInterface::createZones() {
	zoneVec.push_back(new Zone(0));
	zoneVec.push_back(new Zone(1));
	zoneVec.push_back(new Zone(2));
	zoneVec.push_back(new Zone(3));
	zoneVec.push_back(new Zone(4));
	zoneVec.push_back(new Zone(5));
	zoneVec.push_back(new Zone(6));
	zoneVec.push_back(new Zone(7));
	zoneVec.push_back(new Zone(8));
	zoneVec.push_back(new Zone(9));
	zoneVec.push_back(new Zone(10));
	zoneVec.push_back(new Zone(11));
	zoneVec.push_back(new Zone(12));
	zoneVec.push_back(new Zone(13));
	zoneVec.push_back(new Zone(14));
	zoneVec.push_back(new Zone(15));
	zoneVec.push_back(new Zone(16));
	zoneVec.push_back(new Zone(17));
	zoneVec.push_back(new Zone(18));
	zoneVec.push_back(new Zone(19));
	zoneVec.push_back(new Zone(20));
	zoneVec.push_back(new Zone(21));
	
	zoneVec.at(0)->setName("Ship");
	zoneVec.at(0)->setDescription("Your ship!");
	zoneVec.at(0)->addExit("docks", zoneVec.at(1));

	zoneVec.at(1)->setName("Docks");
	zoneVec.at(1)->setDescription("The docks");
	zoneVec.at(1)->addExit("ship", zoneVec.at(0));
	zoneVec.at(1)->addExit("north", zoneVec.at(2));
	zoneVec.at(1)->addExit("south", zoneVec.at(5));
	zoneVec.at(1)->addExit("street", zoneVec.at(6));

	zoneVec.at(2)->setName("Coast");
	zoneVec.at(2)->setDescription("Just north of the docks");
	zoneVec.at(2)->addExit("north", zoneVec.at(3));
	zoneVec.at(2)->addExit("south", zoneVec.at(1));

	zoneVec.at(3)->setName("Coast");
	zoneVec.at(3)->setDescription("Far north from the docks");
	zoneVec.at(3)->addExit("south", zoneVec.at(2));
	zoneVec.at(3)->addExit("wreck", zoneVec.at(4));

	zoneVec.at(4)->setName("Shipwreck");
	zoneVec.at(4)->setDescription("Someones ship who wasnt as lucky as me");
	zoneVec.at(4)->addExit("coast", zoneVec.at(3));
	zoneVec.at(4)->getInvPtr()->addItem(new Item("gearbox", "A gearbox for a ship's engine"));

	zoneVec.at(5)->setName("Coast");
	zoneVec.at(5)->setDescription("Just south of the docks");
	zoneVec.at(5)->addExit("north", zoneVec.at(1));
	zoneVec.at(5)->getInvPtr()->addItem(new Item("coin", "Defacto currency in these parts"));

	zoneVec.at(6)->setName("Street");
	zoneVec.at(6)->setDescription("West side of the main street");
	zoneVec.at(6)->addExit("docks", zoneVec.at(1));
	zoneVec.at(6)->addExit("street", zoneVec.at(9));
	zoneVec.at(6)->addExit("statue", zoneVec.at(7));
	zoneVec.at(6)->addExit("shipwright", zoneVec.at(8));

	zoneVec.at(7)->setName("Statue");
	zoneVec.at(7)->setDescription("Statue of Star");
	zoneVec.at(7)->addExit("street", zoneVec.at(6));
	zoneVec.at(7)->getInvPtr()->addItem(new Item("coin", "Defacto currency in these parts"));

	zoneVec.at(8)->setName("Shipwright");
	zoneVec.at(8)->setDescription("Residence of the town shipwright");
	zoneVec.at(8)->addExit("street", zoneVec.at(6));

	zoneVec.at(9)->setName("Street");
	zoneVec.at(9)->setDescription("East side of the main street");
	zoneVec.at(9)->addExit("street", zoneVec.at(6));
	zoneVec.at(9)->addExit("forest", zoneVec.at(12));
	zoneVec.at(9)->addExit("woodworker", zoneVec.at(10));
	zoneVec.at(9)->addExit("tavern", zoneVec.at(11));

	zoneVec.at(10)->setName("Woodworker");
	zoneVec.at(10)->setDescription("Residence of the town woodworker");
	zoneVec.at(10)->addExit("street", zoneVec.at(9));

	zoneVec.at(11)->setName("Tavern");
	zoneVec.at(11)->setDescription("Hub for travellers");
	zoneVec.at(11)->addExit("street", zoneVec.at(9));

	zoneVec.at(12)->setName("Forest");
	zoneVec.at(12)->setDescription("Westmost part of the forest");
	zoneVec.at(12)->addExit("street", zoneVec.at(9));
	zoneVec.at(12)->addExit("north", zoneVec.at(13));
	zoneVec.at(12)->addExit("east", zoneVec.at(16));
	zoneVec.at(12)->addExit("south", zoneVec.at(19));

	zoneVec.at(13)->setName("Forest");
	zoneVec.at(13)->setDescription("Northwest part of the forest");
	zoneVec.at(13)->addExit("south", zoneVec.at(12));
	zoneVec.at(13)->addExit("east", zoneVec.at(14));
	zoneVec.at(13)->getInvPtr()->addItem(new Item("wood", "Some wood, the woodworker will definitely want some"));


	zoneVec.at(14)->setName("Forest");
	zoneVec.at(14)->setDescription("Northeast part of the forest, there is an abandoned shack here");
	zoneVec.at(14)->addExit("shack", zoneVec.at(15));
	zoneVec.at(14)->addExit("east", zoneVec.at(17));
	zoneVec.at(14)->addExit("south", zoneVec.at(16));
	zoneVec.at(14)->addExit("west", zoneVec.at(13));

	zoneVec.at(15)->setName("Shack");
	zoneVec.at(15)->setDescription("An abandoned shack");
	zoneVec.at(15)->addExit("forest", zoneVec.at(14));
	zoneVec.at(15)->getInvPtr()->addItem(new Item("propeller", "It's not perfect but it'll do the trick"));

	zoneVec.at(16)->setName("Forest");
	zoneVec.at(16)->setDescription("Eastmost part of the forest");
	zoneVec.at(16)->addExit("north", zoneVec.at(14));
	zoneVec.at(16)->addExit("east", zoneVec.at(17));
	zoneVec.at(16)->addExit("south", zoneVec.at(18));
	zoneVec.at(16)->addExit("west", zoneVec.at(12));
	zoneVec.at(16)->getInvPtr()->addItem(new Item("wood", "Some wood, the woodworker will definitely want some"));

	zoneVec.at(17)->setName("Forest");
	zoneVec.at(17)->setDescription("Farthest out part of the forest, its hard to find your way out here");
	zoneVec.at(17)->addExit("back", zoneVec.at(16));

	zoneVec.at(18)->setName("Forest");
	zoneVec.at(18)->setDescription("Southeast part of the forest");
	zoneVec.at(18)->addExit("north", zoneVec.at(16));
	zoneVec.at(18)->addExit("east", zoneVec.at(17));
	zoneVec.at(18)->addExit("west", zoneVec.at(19));
	zoneVec.at(18)->getInvPtr()->addItem(new Item("wood", "Some wood, the woodworker will definitely want some", 2));

	zoneVec.at(19)->setName("Forest");
	zoneVec.at(19)->setDescription("Southwest part of the forest");
	zoneVec.at(19)->addExit("north", zoneVec.at(12));
	zoneVec.at(19)->addExit("east", zoneVec.at(18));
	zoneVec.at(19)->addExit("alley", zoneVec.at(20));

	zoneVec.at(20)->setName("Tavern Alley");
	zoneVec.at(20)->setDescription("Alley behind the tavern, theres a locked door to the basement");
	zoneVec.at(20)->addExit("forest", zoneVec.at(19));
	zoneVec.at(20)->getInvPtr()->addItem(new Item("fuel", "A can half full of fuel for the boat"));


	zoneVec.at(21)->setName("Basement");
	zoneVec.at(21)->setDescription("Beneath the tavern, this is where the good stuff is kept");
	zoneVec.at(21)->getInvPtr()->addItem(new Item("coin", "Defacto currency in these parts"));
	zoneVec.at(21)->getInvPtr()->addItem(new Item("whiskey", "Aged whiskey, hard to come across nowadays"));


}

// Create the command map
void WorldInterface::createCommands() {
	cmds.insert({"quit", &WorldInterface::quitCommand});
	cmds.insert({"exit", &WorldInterface::quitCommand});
	cmds.insert({"stop", &WorldInterface::quitCommand});

	cmds.insert({"move", &WorldInterface::moveCommand});
	cmds.insert({"mv", &WorldInterface::moveCommand});
	cmds.insert({"go", &WorldInterface::moveCommand});

	cmds.insert({"pickup", &WorldInterface::pickupCommand});

	cmds.insert({"drop", &WorldInterface::dropCommand});

	cmds.insert({"inv", &WorldInterface::invCommand});

	cmds.insert({"explore", &WorldInterface::exploreCommand});
	cmds.insert({"examine", &WorldInterface::exploreCommand});
	cmds.insert({"look", &WorldInterface::exploreCommand});
	

}

// Create the state based action vector
void WorldInterface::createSBAs() {
	SBAVec.push_back(
		new StateBasedAction(
			[this](){
				zoneVec.at(10)->getInvPtr()->addItem(new Item("coin", "Defacto currency in these parts", 2));
				zoneVec.at(10)->getInvPtr()->delItem(zoneVec.at(10)->getInvPtr()->getItemByName("wood"));
			},
			[this]() {
				Item* woodPtr = zoneVec.at(10)->getInvPtr()->getItemByName("wood");
				if (woodPtr != nullptr) { return woodPtr->getCount() == 4; }
				return false;
			}
		)
	);

}

// Iterate over commands and return ptr to command that matches, if it doesnt exits return nullptr
fnPtr WorldInterface::getCmd(const char* key) {
	for (auto const [cmdKey, cmd] : cmds) {
		if (strcmp(cmdKey, key) == 0) {return cmd;}
	}
	return nullptr;
}

// Deconstructor
WorldInterface::~WorldInterface() {
	delete player;
	delete[] input;
	for (Zone* zone : zoneVec) {delete zone;}
	for (StateBasedAction* sba : SBAVec) {delete sba;}
}

// Print all of the details of the provided zone
void WorldInterface::printZoneDetails(Zone* zone) {
	cout << "You are in: " << zone->getName() << endl;
	cout << zone->getDescription() << endl;
	if (zone->getInvPtr()->getItemVect().size() == 0) {
		cout << "You don't spot any items here..." << endl;
	} else	{	
		cout << "There are items: " << endl; 
		for (Item* item : zone->getInvPtr()->getItemVect()) {
			cout << "\t" << item->getName() << " x" << item->getCount() << " - " << item->getDescription() << endl;
		}
	}
	cout << "There are exits: " << endl;
	for (auto const [name, exit] : zone->getExitMap()) {
		cout << "\t" << name << endl;
	}
}


// Command that retuns 1, used to return in main function
int WorldInterface::quitCommand(vector<const char*> args) {
	return 1;
}

// Checks for exit provided and sets players current zone to that exits zone
int WorldInterface::moveCommand(vector<const char*> args) {
	if (args.size() == 0) {
		cout << "Error: Please provide an exit!" << endl;
		return 0;
	}	
	Zone* exitPtr = player->getCurrentZone()->getExitByName(args.at(0));
	if (exitPtr == nullptr) {
		cout << "Error: That exit doesnt exitst!" << endl;
		return 0;
	}


	player->changeZone(exitPtr);	
	printZoneDetails(exitPtr);
	return 0;

}

// Checks if item exists and removes it from zone inv and adds it to player inv
int WorldInterface::pickupCommand(vector<const char*> args) {
	if (args.size() == 0) {
		cout << "Error: Please provide an item!" << endl;
		return 0;
	}	
	Item* itemPtr = player->getCurrentZone()->getInvPtr()->getItemByName(args.at(0));
	if (itemPtr == nullptr) {
		cout << "Error: Cannot find that item!" << endl;
		return 0;
	} 

	player->getCurrentZone()->getInvPtr()->delItem(itemPtr);
	player->getInvPtr()->addItem(itemPtr);
	cout << "Picked up the " << itemPtr->getName() << endl;
	return 0;


}

// Checks if item exists and removes it from player inv and adds it to zone inv
int WorldInterface::dropCommand(vector<const char*> args) {
	if (args.size() == 0) {
		cout << "Error: Please provide an item!" << endl;
		return 0;
	}	
	Item* itemPtr = player->getInvPtr()->getItemByName(args.at(0));
	if (itemPtr == nullptr) {
		cout << "Error: Cannot find that item!" << endl;
		return 0;
	} 

	player->getInvPtr()->delItem(itemPtr);
	player->getCurrentZone()->getInvPtr()->addItem(itemPtr);
	cout << "Dropped the " << itemPtr->getName() << endl;
	return 0;
}

// Displays contents of players inventory
int WorldInterface::invCommand(vector<const char*> args) {

	if (player->getInvPtr()->getItemVect().size() == 0) {
		cout << "There are no items in your inventory!" << endl;
	} else {
		for (Item* item : player->getInvPtr()->getItemVect()) {
			cout << "\t" << item->getName() << " x" << item->getCount() << " - " << item->getDescription() << endl;
		}
	}

	return 0;
}

// TODO: prints details about all of the commands
int WorldInterface::helpCommand(vector<const char*> args) {
	return 0;
}

// Prints details about the players current zone
int WorldInterface::exploreCommand(vector<const char*> args) {
	printZoneDetails(player->getCurrentZone());
	return 0;
}

