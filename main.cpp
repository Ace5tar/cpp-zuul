#include <iostream>
#include <vector>
#include "WorldInterface.h"


using namespace std;


int main() {

	WorldInterface wi = WorldInterface();
	while(true) {
		if (wi.runTick() == 1) { return 0;}
	}
}

