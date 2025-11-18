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
}

int WorldInterface::runTick() {
	cout << "You are in: " << player->getCurrentZone()->getName() << endl;
	cout << player->getCurrentZone()->getDescription() << endl;
	cout << "There are: " << endl; 
	for (Item* item : player->getCurrentZone()->getInvPtr()->getItemVect()) {
		cout << item->getName() << " - " << item->getDescription() << endl;
	}
	cin.getline(input, 128);
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

	zoneVec.at(0)->setName("Starting Zone");
	zoneVec.at(0)->setDescription("This is the starting zone!");
	zoneVec.at(0)->getInvPtr()->addItem(new Item("Test Item", "This is a test item!"));

}

void WorldInterface::createCommands() {
	cmds.insert({"quit", &WorldInterface::quitCommand});
}

void WorldInterface::createSBAs() {
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

int WorldInterface::quitCommand(vector<const char*>) {
	return 1;
}
