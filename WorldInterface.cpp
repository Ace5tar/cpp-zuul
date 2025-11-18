#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include "Player.h"
#include "Zone.h"
#include "StateBasedAction.h"
#include "WorldInterface.h"
#include "CommandParser.h"

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

void WorldInterface::createZones() {
	zoneVec.push_back(new Zone(0));
	zoneVec.push_back(new Zone(1));

	zoneVec.at(0)->setName("Starting Zone");
	zoneVec.at(0)->setDescription("This is the starting zone!");
	zoneVec.at(0)->getInvPtr()->addItem(new Item("Test-Item", "This is a test item!"));
	zoneVec.at(0)->addExit("NORTH", zoneVec.at(1));

	zoneVec.at(1)->setName("Cool Zone");
	zoneVec.at(1)->setDescription("This is the coolest zone B)");
	zoneVec.at(1)->addExit("SOUTH", zoneVec.at(0));

}

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
	

}

void WorldInterface::createSBAs() {
	SBAVec.push_back(
		new StateBasedAction(
			[](){
				cout << "This is an example!" << endl;
			}, 
			[](){
				return false;
			}
		)
	);
}

fnPtr WorldInterface::getCmd(const char* key) {
	for (auto const [cmdKey, cmd] : cmds) {
		if (strcmp(cmdKey, key) == 0) {return cmd;}
	}
	return nullptr;
}

WorldInterface::~WorldInterface() {
	delete player;
	delete[] input;
	for (Zone* zone : zoneVec) {delete zone;}
	for (StateBasedAction* sba : SBAVec) {delete sba;}
}

void WorldInterface::printZoneDetails(Zone* zone) {
	cout << "You are in: " << zone->getName() << endl;
	cout << zone->getDescription() << endl;
	if (zone->getInvPtr()->getItemVect().size() == 0) {
		cout << "You don't spot any items here..." << endl;
	} else	{	
		cout << "There are items: " << endl; 
		for (Item* item : zone->getInvPtr()->getItemVect()) {
			cout << "\t" << item->getName() << " - " << item->getDescription() << endl;
		}
	}
	cout << "There are exits: " << endl;
	for (auto const [name, exit] : zone->getExitMap()) {
		cout << "\t" << name << endl;
	}
}


int WorldInterface::quitCommand(vector<const char*> args) {
	return 1;
}

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

int WorldInterface::invCommand(vector<const char*> args) {

	if (player->getInvPtr()->getItemVect().size() == 0) {
		cout << "There are no items in your inventory!" << endl;
	} else {
		for (Item* item : player->getInvPtr()->getItemVect()) {
			cout << "\t" << item->getName() << " - " << item->getDescription() << endl;
		}
	}

	return 0;
}

int WorldInterface::helpCommand(vector<const char*> args) {
	return 0;
}


