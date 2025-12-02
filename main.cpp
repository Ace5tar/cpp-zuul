#include <iostream>
#include <vector>
#include "world/WorldInterface.h"


using namespace std;


int main() {
cout <<"\n\"That damn seabeast knocked up my ship pretty bad... I hope I can make it to that little trade spot off the coast of Intercy before she gives in. I got a hole in the hull, and I'm gonna need to fix this engine. Plus I'm getting low on supplies so I should stop there anyway.\"\n\nYou pull into the docks of the trade villiage, if you can even call it that, it's only three buildings. Yellow-orange gas lanterns pop up every dozen feet or so. It would be hard to make your way without them.\n\nTaking in the sights you see a shipwreck down the coast, might be a good place for spare parts.\n\nUse 'help' for a list of commands!\n\n";
	WorldInterface wi = WorldInterface();
	while(true) {
		int returnVal = wi.runTick();
		if (returnVal == 1) { 
			cout << endl << "The darkness of tarwater waits for your return..." << endl;
			return 0;
		}
		if (returnVal == 2) {
			cout << endl << "\"I have supplies, a new engine, and fixed up the ship. Thats everything I need before I take off.\"\n\nYou untie your boat from the docks, and take one more look at the small town. You'll have to visit again someday, if you live long enough to do so.\n\nWith that, you take off into the dark ocean waves, and continue your journey towards Starsect." << endl;
			return 0;
		}
	}
}

