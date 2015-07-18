// ----------------------------------------------------------------------------------------
// Behavior.h
// Professional Developers:
// Natanel Beber - 308480284 , Alon Katz - 204368450 , Itay Eylon - 307872515
// Date: 15.7.15
//
// ----------------------------------------------------------------------------------------

// The Behavior class is the decision-making system of the robot's movement in the space

#include "Behavior.h"

Behavior::Behavior(Robot* robot) {

	// Get the robot's instance
	_robot = robot;

	// Init Other variables
	_nextBehavior = NULL;
	_behaviorsCount = 0;
}

Behavior* Behavior::addNextBehavior(Behavior* behavior){

	// Initiate 2d array behaviors
	Behavior** tempBeh = new Behavior*[_behaviorsCount + 1];

	if (!tempBeh) {
		return NULL;
	}

	int i;
	for (i = 0; i < _behaviorsCount; ++i) {
		tempBeh[i] = _nextBehavior[i];
	}

	tempBeh[i] = behavior;
	delete [] _nextBehavior;
	_behaviorsCount++;

	_nextBehavior = tempBeh;
	return this;
}

Behavior* Behavior::selectNextBehavior(){

	int i;
	for(i=0; i<_behaviorsCount; i++)
		if(_nextBehavior[i]->startCond())
			return _nextBehavior[i];

	return NULL;
}

Behavior::~Behavior() {

	delete [] _nextBehavior;
	delete _robot;
}
