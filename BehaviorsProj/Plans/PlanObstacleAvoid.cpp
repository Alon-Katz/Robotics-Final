/*
 * PlnObstacleAvoid.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "PlanObstacleAvoid.h"
#include "../behaviors/GoToWayPoint.h"

PlanObstacleAvoid::PlanObstacleAvoid(Robot* robot, WaypointsManager* wpm) : Plan(robot){

	//Creating Behaviors
	_behaviors = new Behavior*[BEHAVIORS_COUNT];
	_behaviors[0] = new GoToWayPoint(robot, wpm);
	_behaviors[1] = new GoForward(robot, wpm);

	//Connecting behaviors
	_behaviors[0]->addNextBehavior(_behaviors[1]);
	_behaviors[1]->addNextBehavior(_behaviors[0]);

	_start = _behaviors[0];
}

Behavior* PlanObstacleAvoid::getStartPoint(){
	return _start;
}

PlanObstacleAvoid::~PlanObstacleAvoid() {

	for(int i = 0; i < BEHAVIORS_COUNT; i++)
		delete _behaviors[i];
}
