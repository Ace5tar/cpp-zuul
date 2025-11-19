#include <iostream>
#include <functional>

using namespace std;


#ifndef STATEBASEDACTION_H
#define STATEBASEDACTION_H

class StateBasedAction {
	private:
		function<void()> funcToDo;
		function<bool()> stateNeeded;
	public:
		StateBasedAction();
		StateBasedAction(function<void()> func, function<bool()> state);
		void checkState();
		~StateBasedAction();
};

#endif
