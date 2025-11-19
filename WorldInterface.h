#include <iostream>
#include <vector>
#include <map>
#include "Player.h"
#include "Zone.h"
#include "StateBasedAction.h"

#ifndef WORLDINTERFACE_H
#define WORLDINTERFACE_H

using namespace std;

class WorldInterface{
	private:
		typedef int (WorldInterface::*fnPtr)(vector<const char*>);
		Player* player;
		vector<Zone*> zoneVec;
		map<const char*, fnPtr> cmds;
		vector<StateBasedAction*> SBAVec;
		void createZones();
		void initZone(int index, const char* name, const char* desc, map<const char*, Zone*> exits);
		void createCommands();
		void createSBAs();
		fnPtr getCmd(const char* key);
		char* input;
		void printZoneDetails(Zone* zone);

		int quitCommand(vector<const char*> args);
		int moveCommand(vector<const char*> args);
		int pickupCommand(vector<const char*> args);
		int dropCommand(vector<const char*> args);
		int invCommand(vector<const char*> args);
		int exploreCommand(vector<const char*> args);
		int helpCommand(vector<const char*> args);

	public:
		WorldInterface();
		int runTick();
		~WorldInterface();

};

#endif
