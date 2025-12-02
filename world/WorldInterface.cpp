#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>
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
	
	player->getInvPtr()->addItem(new Item("coin", "Defacto currency in these parts", 3));
	printZoneDetails(player->getCurrentZone());
}

// Checks state based actions then asks user for input and does that command
int WorldInterface::runTick() {
	for (StateBasedAction* sba : SBAVec){
			if(sba->checkState()) {
				SBAVec.erase(find(SBAVec.begin(), SBAVec.end(), sba));
		} 
	}	

	if (zoneVec.at(0)->checkStatusFlag("win-con")) {
		return 2;
	}

	cout << " > ";
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
	zoneVec.at(0)->setDescription("Your very own ship, she's seen worse but it's probably best to get her fixed up sooner rather than later.");
	zoneVec.at(0)->addExit("docks", zoneVec.at(1));
	zoneVec.at(0)->addStatusFlag("hole-fixed", false);
	zoneVec.at(0)->addStatusFlag("win-con", false);

	zoneVec.at(1)->setName("Docks");
	zoneVec.at(1)->setDescription("Just a bunch of planks jutting out into the sea, every coast town has to have one. ");
	zoneVec.at(1)->addExit("ship", zoneVec.at(0));
	zoneVec.at(1)->addExit("north", zoneVec.at(2));
	zoneVec.at(1)->addExit("south", zoneVec.at(5));
	zoneVec.at(1)->addExit("street", zoneVec.at(6));

	zoneVec.at(2)->setName("Coast");
	zoneVec.at(2)->setDescription("The white sand under your feet shines in constrast to the black tar that threatens to swallow you whole. You've enough experience to know to keep your distance from the shoreline.");
	zoneVec.at(2)->addExit("north", zoneVec.at(3));
	zoneVec.at(2)->addExit("south", zoneVec.at(1));

	zoneVec.at(3)->setName("Coast");
	zoneVec.at(3)->setDescription("Its hard to see the wreck without the light of the town, but your eyes adjust enough to make out a hole carved in the side of the boat. You expected not to be the first to explore a find like this, you just hope whoever it was left something for you too.\n\nA large cliffside blocks your way further north. In another situation you might try to climb it, but that doesnt seem like the most important thing right now.");
	zoneVec.at(3)->addExit("south", zoneVec.at(2));
	zoneVec.at(3)->addExit("wreck", zoneVec.at(4));

	zoneVec.at(4)->setName("Shipwreck");
	zoneVec.at(4)->setDescription("Its cramped, dark, and probably home to some kind of creeper. Nothing you find seems of use say for the broken engine sitting in the back. You manage to pull out a gearbox that seems to be in good enough condition, even though the rest of the engine is just junk.");
	zoneVec.at(4)->addExit("coast", zoneVec.at(3));
	zoneVec.at(4)->getInvPtr()->addItem(new Item("gearbox", "A gearbox for a ship's engine"));

	zoneVec.at(5)->setName("Coast");
	zoneVec.at(5)->setDescription("Its not far before the shore creeps in closer than you are comfortable with, but a glimmer of something catches your eye just barely resting on the black tar. You're probably fine to go to the shore for just a second, right?");
	zoneVec.at(5)->addExit("north", zoneVec.at(1));
	zoneVec.at(5)->getInvPtr()->addItem(new Item("coin", "Defacto currency in these parts"));

	zoneVec.at(6)->setName("Street");
	zoneVec.at(6)->setDescription("You walk down the thin dirt road. The ground seems unnaturally dry, and the air unnaturally dead. \n\nFar ahead you can see a large dense forest. From this distance the shadows that weave between the trees seem to be impenetrable. \n\nTo your left is the town's Star Effigy, because even small settlements like this need a place for worship. \n\nAcross from the statue sits what seems to be the shipwrights place of residence. Off to the side is a small wooden boat, either halfway built or halfway deconstructed, it's hard to tell.");
	zoneVec.at(6)->addExit("docks", zoneVec.at(1));
	zoneVec.at(6)->addExit("east", zoneVec.at(9));
	zoneVec.at(6)->addExit("statue", zoneVec.at(7));
	zoneVec.at(6)->addExit("shipwright", zoneVec.at(8));

	zoneVec.at(7)->setName("Statue");
	zoneVec.at(7)->setDescription("Its not the biggest you've seen, only about twice as high as you are, but it seems to do the job for this small settlement. Its made of wood far nicer than the rest of the town's buildings, almost as if it was built the day before, although it certainy has been around longer than anyone in this town can remember. \n\nAt the foot of the statue is a small coin. At some point someone must have made an offering, but Star seems to have rejeted it. Besides, you will get more use out of a measly coin than Star would.");
	zoneVec.at(7)->addExit("street", zoneVec.at(6));
	zoneVec.at(7)->getInvPtr()->addItem(new Item("coin", "Defacto currency in these parts"));

	zoneVec.at(8)->setName("Shipwright");
	zoneVec.at(8)->setDescription("A gruff looking woman swings around when you open the door, she sits in front of the hull of a ship, various tools strewn on the floor around her. \n\n\"Hmf, another traveller. Let me guess, boat need a bit o' fixing?\"\n\nYou explain your situation, bringing specific attention to the hole in the side of your boat.\n\n\"I can help ya, it is my job after all, but I'm sure you know it ain't gonna be free,\" she thinks for a second, and then says, \"Listen, the tavernkeep been cutting me off recently, I'll fix up your ship if you sneak over there and get me some of his good stuff he keeps in the basement.\"\n\n\"There's an entrance to his storage room around the back. Best way around is through the woods, I'm sure a smart one like you can find it no problem.\" She winks at you, then turns around and gets right back to her work.");
	zoneVec.at(8)->addExit("street", zoneVec.at(6));
	zoneVec.at(8)->addStatusFlag("helped-shipwright", false);

	zoneVec.at(9)->setName("Street");
	zoneVec.at(9)->setDescription("You stroll further down the dirt road and approach the edge of the forest, trees loom above you, crushing you under the weight of their shadows.\n\nTo your left seems to be the woodworkers hut, various axes and saws line the outside wall.\n\nTo your right is the nicest building in the town, likely the tavern. The warm glow inside pulls you towards it.");
	zoneVec.at(9)->addExit("west", zoneVec.at(6));
	zoneVec.at(9)->addExit("forest", zoneVec.at(12));
	zoneVec.at(9)->addExit("woodworker", zoneVec.at(10));
	zoneVec.at(9)->addExit("tavern", zoneVec.at(11));

	zoneVec.at(10)->setName("Woodworker");
	zoneVec.at(10)->setDescription("\"Hi, can I help you with anything?\" A lean girl sits on a chair in the corner whitting, you can't tell what from this distance.\n\nYou explain your situation to her.\n\n\"Well, I can't really help much, but if you need a little extra coin I am in need of some more lumber. If you bring me say, 4 pieces of lumber I'll give you some coin, how about 2 pieces?\"\n\nShe returns to whitting, leaving you alone.");
	zoneVec.at(10)->addExit("street", zoneVec.at(9));

	zoneVec.at(11)->setName("Tavern");
	zoneVec.at(11)->setDescription("A man behind a counter perks up when you step in. \n\n\"Hello traveller, welcome to our little settlements tavern. We sell only the finest goods and services around here. I can help you to some supplies for only 10 coin, or for 20 theres a room you can reside in for as long as you would like. What do you say?\"\n\nThose supplies seem useful, but you dont have enough coin at the moment.");
	zoneVec.at(11)->addExit("street", zoneVec.at(9));

	zoneVec.at(12)->setName("Forest");
	zoneVec.at(12)->setDescription("Dense trees surround you, it's hard to find your way in the dark.\n\nYou can see the light of the town shine through some of the trees.");
	zoneVec.at(12)->addExit("street", zoneVec.at(9));
	zoneVec.at(12)->addExit("north", zoneVec.at(13));
	zoneVec.at(12)->addExit("east", zoneVec.at(16));
	zoneVec.at(12)->addExit("south", zoneVec.at(19));

	zoneVec.at(13)->setName("Forest");
	zoneVec.at(13)->setDescription("Dense trees surround you, it's hard to find your way in the dark.");
	zoneVec.at(13)->addExit("south", zoneVec.at(12));
	zoneVec.at(13)->addExit("east", zoneVec.at(14));
	zoneVec.at(13)->getInvPtr()->addItem(new Item("wood", "Some wood, the woodworker will definitely want some"));

	zoneVec.at(14)->setName("Forest");
	zoneVec.at(14)->setDescription("Dense trees surround you, it's hard to find your way in the dark.\n\nBetween the trees is a run down shack, who knows how long it's been since it was used.");
	zoneVec.at(14)->addExit("shack", zoneVec.at(15));
	zoneVec.at(14)->addExit("east", zoneVec.at(17));
	zoneVec.at(14)->addExit("south", zoneVec.at(16));
	zoneVec.at(14)->addExit("west", zoneVec.at(13));

	zoneVec.at(15)->setName("Shack");
	zoneVec.at(15)->setDescription("The dust makes it hard to breath, and the flooring creaks with each step. Someone may have lived here at some point, but they havent for a long long time. \n\nThere is a propeller in the corner, it's rusty and old, but it's probably better than nothing.");
	zoneVec.at(15)->addExit("forest", zoneVec.at(14));
	zoneVec.at(15)->getInvPtr()->addItem(new Item("propeller", "It's not perfect but it'll do the trick"));

	zoneVec.at(16)->setName("Forest");
	zoneVec.at(16)->setDescription("Dense trees surround you, it's hard to find your way in the dark.");
	zoneVec.at(16)->addExit("north", zoneVec.at(14));
	zoneVec.at(16)->addExit("east", zoneVec.at(17));
	zoneVec.at(16)->addExit("south", zoneVec.at(18));
	zoneVec.at(16)->addExit("west", zoneVec.at(12));
	zoneVec.at(16)->getInvPtr()->addItem(new Item("wood", "Some wood, the woodworker will definitely want some"));

	zoneVec.at(17)->setName("Forest");
	zoneVec.at(17)->setDescription("The light of the town is a distant memory, out here it's just you and the forest. The forest begins to swirl, paths become familiar, yet every step feels new. Eventually you come across a patch of stones that you passed by not too long ago, probably best to stay close to town. ");
	zoneVec.at(17)->addExit("back", zoneVec.at(16));

	zoneVec.at(18)->setName("Forest");
	zoneVec.at(18)->setDescription("Dense trees surround you, it's hard to find your way in the dark.");
	zoneVec.at(18)->addExit("north", zoneVec.at(16));
	zoneVec.at(18)->addExit("east", zoneVec.at(17));
	zoneVec.at(18)->addExit("west", zoneVec.at(19));
	zoneVec.at(18)->getInvPtr()->addItem(new Item("wood", "Some wood, the woodworker will definitely want some", 2));

	zoneVec.at(19)->setName("Forest");
	zoneVec.at(19)->setDescription("Dense trees surround you, it's hard to find your way in the dark.\n\nSome light shines through a few of the trees, not a lot, but just enough to draw you closer.");
	zoneVec.at(19)->addExit("north", zoneVec.at(12));
	zoneVec.at(19)->addExit("east", zoneVec.at(18));
	zoneVec.at(19)->addExit("alley", zoneVec.at(20));

	zoneVec.at(20)->setName("Tavern Alley");
	zoneVec.at(20)->setDescription("You emerge from the forest to see the back of the tavern, a cellar door set into the ground, and a canister of fuel laying next to it.\n\nThere is a lock on the cellar door, preventing anyone from getting it. Better tell the shipwright.");
	zoneVec.at(20)->addExit("forest", zoneVec.at(19));
	zoneVec.at(20)->getInvPtr()->addItem(new Item("fuel", "A can half full of fuel for the boat"));
	zoneVec.at(20)->addStatusFlag("know-locked", false);

	zoneVec.at(21)->setName("Basement");
	zoneVec.at(21)->setDescription("It's dark, damp, and cold. Shelves of various items line the walls, but nothing stand out to you, say for a bottle of whiskey sitting on a barrel in the corner.");
	zoneVec.at(21)->getInvPtr()->addItem(new Item("coin", "Defacto currency in these parts"));
	zoneVec.at(21)->getInvPtr()->addItem(new Item("whiskey", "Aged whiskey, hard to come across nowadays"));
	zoneVec.at(21)->addExit("alley", zoneVec.at(20));
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
	cmds.insert({"get", &WorldInterface::pickupCommand});

	cmds.insert({"drop", &WorldInterface::dropCommand});

	cmds.insert({"inventory", &WorldInterface::invCommand});
	cmds.insert({"inv", &WorldInterface::invCommand});

	cmds.insert({"explore", &WorldInterface::exploreCommand});
	cmds.insert({"examine", &WorldInterface::exploreCommand});
	cmds.insert({"look", &WorldInterface::exploreCommand});
	
	cmds.insert({"help", &WorldInterface::helpCommand});
}

// Create the state based action vector
void WorldInterface::createSBAs() {
	SBAVec.push_back(
		new StateBasedAction(
			[this](){
				cout << endl << "\"Ready to get this baby fixed up?\" The shipwright stands on the deck of your boat with some metal scrap and a makeshift toolbox. \"Show me where the problem is!\"\n\nYou take her down into your storage and she immediately sees the issue. \n\n\"Oh man that's nasty, ill get her fixed for you no problem.\"\n\nShe only works for ten of fifteen minutes before walking back towards you.\n\n\"All patched up, looks good as new if I do say so myself!\" she heads up out of the ship, presumably back to her shop to get back to work." << endl;
				zoneVec.at(8)->setDescription("You walk in to see her taking a drink of whiskey from the bottle you got her while putting together her boat. She's either too busy working or too drunk to notice that you arrived, likely the latter.");
				zoneVec.at(0)->changeStatusFlag("hole-fixed", true);
			},
			[this](){
				return (zoneVec.at(8)->checkStatusFlag("helped-shipwright") && player->getCurrentZone() == zoneVec.at(0));
			}
		)
	);

	SBAVec.push_back(
		new StateBasedAction(
			[this](){
				zoneVec.at(3)->setDescription("Its hard to see the wreck without the light of the town, but your eyes adjust enough to make out a hole carved in the side of the boat. \n\nA large cliffside blocks your way further north. In another situation you might try to climb it, but that doesnt seem like the most important thing right now.");
				zoneVec.at(4)->setDescription("Its cramped, dark, and probably home to some kind of creeper. Nothing here seems to be of any use to you. ");
			},
			[this](){
				return (zoneVec.at(4)->getInvPtr()->getItemByName("gearbox") == nullptr);
			}
		)
	);

	SBAVec.push_back(
		new StateBasedAction(
			[this](){
				zoneVec.at(5)->setDescription("Its not far before the shore creeps in closer than you are comfortable with, no reason the get that close again.");
			},
			[this](){
				return (zoneVec.at(5)->getInvPtr()->getItemByName("coin") == nullptr);
			}
		)
	);

	SBAVec.push_back(
		new StateBasedAction(
			[this](){
				zoneVec.at(7)->setDescription("Its not the biggest you've seen, only about twice as high as you are, but it seems to do the job for this small settlement. Its made of wood far nicer than the rest of the town's buildings, almost as if it was built the day before, although it certainy has been around longer than anyone in this town can remember. ");
			},
			[this](){
				return (zoneVec.at(7)->getInvPtr()->getItemByName("coin") == nullptr);
			}
		)
	);

	SBAVec.push_back(
		new StateBasedAction(
			[this](){
				zoneVec.at(8)->setDescription("The shipwright beams eagerly when she hears you approach, but her face turns sour noticing that you dont have what she asked for. You explain the lock on the door, and how you wont be able to get in without a key.\n\n\"Well damn, he's upping his security! Lucky for us I've got a special key that can get into any lock, don't you worry...\" \n\nAfter rummaging around her pile of tools she eventually pulls out a crowbar.\n\n\"Just use this puppy, I can worry about the consequences later. And hey, for your troubles I'll throw in a little extra coin too,\" with that, she turns around and goes back to work.");
				zoneVec.at(8)->getInvPtr()->addItem(new Item("crowbar", "The shipwright told me to use this to get into the cellar"));
			},
			[this](){
				return (player->getCurrentZone() == zoneVec.at(20));
			}
		)
	);	

	SBAVec.push_back(
		new StateBasedAction(
			[this](){
				zoneVec.at(8)->setDescription("\"Well I'll be damned, you got the good stuff! I knew you'd get it done,\" she grabs the drink from your hand and sets in down on the floor by her tools, \"Meet me o'er by the boat n I can get it all fixed up for you.\"\n\n\"Don't think I forgot your little extra payment too, its over there by the dresser, I'm sure you'll find it.\" She heads out the door, leaving you, and your payment, alone in the building.");
				player->getInvPtr()->delItem(player->getInvPtr()->getItemByName("whiskey"));
				zoneVec.at(8)->getInvPtr()->addItem(new Item("coin", "Defacto currency in these parts", 2));
				zoneVec.at(8)->changeStatusFlag("helped-shipwright", true);
			},
			[this](){
				return (player->getInvPtr()->getItemByName("whiskey") != nullptr);
			}
		)
	);
SBAVec.push_back(
		new StateBasedAction(
			[this](){
				zoneVec.at(10)->setDescription("She looks up from her whitting projects with curious eyes.\n\n\"Oh, you brought the wood! Go ahead and throw them over there and I'll grab the coin.\"");
			},
			[this](){
				Item* woodPtr = player->getInvPtr()->getItemByName("wood");
				if (woodPtr != nullptr) {
					return (woodPtr->getCount() == 4);
				}
				else {
					return false;
				}
			}
		)
	);

	SBAVec.push_back(
		new StateBasedAction(
			[this](){
				cout << endl << "\"Thanks for grabbing that for me, your reward is over there on the table by the door, feel free to grab it on your way out!\"" << endl;
				zoneVec.at(10)->getInvPtr()->addItem(new Item("coin", "Defacto currency in these parts", 2));
				zoneVec.at(10)->getInvPtr()->delItem(zoneVec.at(10)->getInvPtr()->getItemByName("wood"));
				zoneVec.at(10)->setDescription("She's still whitting, you still can't tell what she's making.\n\n\"Thanks again for grabbing that lumber! You've been a huge help.\"");
			},
			[this](){
				Item* woodPtr = zoneVec.at(10)->getInvPtr()->getItemByName("wood");
				if (woodPtr != nullptr) {
				return (woodPtr->getCount() == 4);
				}
				else {
					return false;
				}
			}
		)
	);

	SBAVec.push_back(
		new StateBasedAction(
			[this](){
				zoneVec.at(11)->setDescription("\"Hello traveller, welcome to our little settlements tavern. We sell only the finest goods and services around here. I can help you to some supplies for only 10 coin, or for 20 theres a room you can reside in for as long as you would like. What do you say?\"\n\nYou ask for some supplies.\n\n\"Ahh, some supplies huh? Well if you have the coin then I have the goods for you. Go ahead and set down what you have.\"");
			},
			[this](){
				Item* coinPtr = player->getInvPtr()->getItemByName("coin");
				if (coinPtr != nullptr) {
					return (coinPtr->getCount() == 10);
				} else {
					return false;
				}
			}
		)
	);

	SBAVec.push_back(
		new StateBasedAction(
			[this](){
				cout << endl << "\"Good.. a deals a deal good friend. Here are your supplies.\"" << endl;
				zoneVec.at(11)->getInvPtr()->addItem(new Item("supplies", "Extra food and other supplies for you journey"));
				zoneVec.at(11)->getInvPtr()->delItem(zoneVec.at(11)->getInvPtr()->getItemByName("coin"));
				zoneVec.at(11)->setDescription("\"Don't forget, only 20 coin for a room!\"");
			},
			[this](){
				Item* coinPtr = zoneVec.at(11)->getInvPtr()->getItemByName("coin");
				if (coinPtr != nullptr) {
					return (coinPtr->getCount() == 10);
				} else {
					return false;
				}
			}
		)
	);

	SBAVec.push_back(
		new StateBasedAction(
			[this](){
				zoneVec.at(15)->setDescription("The dust makes it hard to breath, and the flooring creaks with each step. Someone may have lived here at some point, but they havent for a long long time. ");
			},
			[this](){
				return (zoneVec.at(15)->getInvPtr()->getItemByName("propeller") == nullptr);
			}
		)
	);

	SBAVec.push_back(
		new StateBasedAction(
			[this](){
				zoneVec.at(20)->setDescription("You emerge from the forest to see the back of the tavern, a cellar door set into the ground.\n\nThere is a lock on the cellar door, preventing anyone from getting it. Better tell the shipwright.");
			},
			[this](){
				return (zoneVec.at(20)->getInvPtr()->getItemByName("fuel") == nullptr);
			}
		)
	);
	
	SBAVec.push_back(
		new StateBasedAction(
			[this](){
				zoneVec.at(20)->setDescription("You emerge from the forest to see the back of the tavern, a cellar door set into the ground.\n\nYou take the crobar to the lock, careful not to make too much noise, and it snaps in half under your might.");
				zoneVec.at(20)->addExit("cellar", zoneVec.at(21));
			},
			[this](){
				return (player->getInvPtr()->getItemByName("crowbar") != nullptr);
			}
		)
	);

	SBAVec.push_back(
		new StateBasedAction(
			[this](){
				zoneVec.at(20)->setDescription("You emerge from the forest to see the back of the tavern, a cellar door set into the ground.\n\nThe tavern cellar door has been opened.");
			},
			[this](){
				return (player->getInvPtr()->getItemByName("corwbar") != nullptr && player->getCurrentZone() == zoneVec.at(20));
			}
		)
	);

	SBAVec.push_back(
		new StateBasedAction(
			[this](){
				zoneVec.at(21)->setDescription("It's dark, damp, and cold. Shelves of various items line the walls, but nothing stand out to you. ");
			},
			[this](){
				return (zoneVec.at(21)->getInvPtr()->getItemByName("whiskey") == nullptr);
			}
		)
	);

	SBAVec.push_back(
		new StateBasedAction(
			[this](){
				cout << endl << "\"Seems like I have everything I need to make a new engine\"\n\n After a short while you put together a new engine fo your ship. It's not perfect, but it'll last you long enought to get somewhere selling a new one." << endl;
				player->getInvPtr()->delItem(player->getInvPtr()->getItemByName("gearbox"));
				player->getInvPtr()->delItem(player->getInvPtr()->getItemByName("propeller"));
				player->getInvPtr()->delItem(player->getInvPtr()->getItemByName("fuel"));
				player->getInvPtr()->addItem(new Item("engine", "Replacement engine for your ship"));
			},
			[this](){
				return player->getInvPtr()->getItemByName("gearbox") != nullptr 
						&& player->getInvPtr()->getItemByName("propeller") != nullptr 
						&& player->getInvPtr()->getItemByName("fuel") != nullptr;
			}
		)
	);

	SBAVec.push_back(
		new StateBasedAction(
			[this](){
				zoneVec.at(0)->changeStatusFlag("win-con", true);
			},
			[this](){
				return player->getInvPtr()->getItemByName("engine") != nullptr
						&& player->getInvPtr()->getItemByName("supplies") != nullptr
						&& zoneVec.at(0)->checkStatusFlag("hole-fixed")
						&& player->getCurrentZone() == zoneVec.at(0);
			}
		)
	);
}	


// Iterate over commands and return ptr to command that matches, if it doesnt exits return nullptr
fnPtr WorldInterface::getCmd(const char* key){
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
	cout << "You are in: " << zone->getName() << endl << endl;
	cout << zone->getDescription() << endl << endl;
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
	cout << "'help'" << endl
	     << " alias - none" << endl
	     << " arguments - none" << endl << endl
	     << "Displays this help text" << "\n\n\n";

	cout << "'move'" << endl
	     << " alias - 'mv', 'go'" << endl
	     << " arguments - none" << endl << endl
	     << "Allows you to travel through zone exits" << "\n\n\n";

	cout << "'inventory'" << endl
	     << " alias - 'inv'" << endl
	     << " arguments - none" << endl << endl
	     << "Display items in your inventory" << "\n";

	cout << "'pickup'" << endl
	     << " alias - 'get'" << endl
	     << " arguments - none" << endl << endl
	     << "Pickup an item in your current zone" << "\n\n\n";

	cout << "'drop'" << endl
	     << " alias - none" << endl
	     << " arguments - none" << endl << endl
	     << "Drop an item from your inventory to your current zone" << "\n\n\n";

	cout << "'explore'" << endl
	     << " alias - 'examine', 'look'" << endl
	     << " arguments - none" << endl << endl
	     << "Display details about your current zone" << "\n\n\n";

	cout << "'quit'" << endl
	     << " alias - 'exit', 'stop'" << endl
	     << " arguments - none" << endl << endl
	     << "End the program" << "\n";
	return 0;
}

// Prints details about the players current zone
int WorldInterface::exploreCommand(vector<const char*> args) {
	printZoneDetails(player->getCurrentZone());
	return 0;
}

