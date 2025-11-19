/*
 * Belle Biery
 * 11/12/25
 * Class for state based actions that are checked regularly
 */

#include <iostream>
#include <functional>
#include "StateBasedAction.h"

using namespace std;

// Default constructor, should not be called
StateBasedAction::StateBasedAction() {
	funcToDo = [](){return;};
	stateNeeded = [](){return false;};
}

// Parameterized constructor
StateBasedAction::StateBasedAction(function<void()> func, function<bool()> state) {
	funcToDo = func;
	stateNeeded = state;
}

// If the state needed is true, then do function
void StateBasedAction::checkState() {
	if (stateNeeded()) {funcToDo();}
}

// Deconstructor
StateBasedAction::~StateBasedAction() {

}
