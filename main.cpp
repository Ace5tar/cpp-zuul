#include <iostream>
#include <vector>
#include "world/WorldInterface.h"


using namespace std;


int main() {

	WorldInterface wi = WorldInterface();
	while(true) {
		if (wi.runTick() == 1) { return 0;}
	}
}

