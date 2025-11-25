#include <iostream>
#include <vector>
#include "world/WorldInterface.h"


using namespace std;


int main() {
cout <<"\n\"That damn seabeast knocked up my ship pretty bad... I hope I can make it to that little trade spot off the coast of Intercy before she gives in. I got a hole in the hull, and I'm gonna need to fix this engine. Plus I'm getting low on supplies so I should stop there anyway.\"\n\nYou pull into the docks of the trade villiage, if you can even call it that, it's only three buildings. Yellow-orange gas lanterns pop up every dozen feet or so. It would be hard to make your way without them.\n\nTaking in the sights you see a shipwreck down the coast, might be a good place for spare parts.\n\nUse 'help' for a list of commands!\n\n";
	WorldInterface wi = WorldInterface();
	while(true) {
		if (wi.runTick() == 1) { return 0;}
	}
}

