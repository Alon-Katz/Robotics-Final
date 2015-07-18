/*
 * Manager.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "Manager.h"

Manager::Manager(Robot* robot, Plan* pln, LocalizationManager* l_manager, ConfigurationManager* cm, WaypointsManager* wayPointsManager) {
	_robot = robot;
	_wayPointsManager = wayPointsManager;
	_curr = pln->getStartPoint();

	_localization_manager = new LocalizationManager();
	_cm = cm;
}
void Manager::run()
{
	wayPoint wpm;
	set<wayPoint>::iterator it;

	_robot->Read();


	// Gets the position of the robot
	double x_Coordinate = _robot->getXpos();
	double y_Coordinate = _robot->getYpos();
	double dTeta = _robot->getYaw();

	bool behavior_exsist = true;
	for (it = (_wayPointsManager->wayPoints).begin(); it != (_wayPointsManager->wayPoints).end(); ++it) {
		wpm = *it;
		_robot->Read();

		_wayPointsManager->setNextWayPoint(wpm);

		_curr->startCond();

		while (true){


			// If the current behavior can't run
			if(_curr->stopCond())
			{
				// Perform the next behavior according to the plan
			    _curr = _curr->selectNextBehavior();

			    _robot->Read();

				if (_wayPointsManager->isInWayPoint(_robot->getXpos(),_robot->getYpos()))
				{
					break;
				}

				if (!_curr)
					break;
			}

			_curr->action();

			_robot->Read();
			cout << "CHECK WAYPOINTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
			cout << wpm.x_Coordinate << " " << wpm.y_Coordinate << " " << wpm.yaw << endl;

			// Gets the position of the robot after read
			double current_x_coordinate = _robot->getXpos();
			double current_y_coordinate = _robot->getYpos();
			double current_teta = _robot->getYaw();

			cout << "CHECK ROBOT LOCATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
			cout << current_x_coordinate << " " << current_y_coordinate << " " << current_teta << endl;

			double deltaX = current_x_coordinate - x_Coordinate;
			double deltaY = current_y_coordinate - y_Coordinate;
			double deltaTeta = current_teta - dTeta;

			_localization_manager->update(x_Coordinate, y_Coordinate, dTeta, deltaX, deltaY, deltaTeta, _robot->getLaser());

			x_Coordinate = current_x_coordinate;
			y_Coordinate = current_y_coordinate;
			dTeta = current_teta;
		}
	}
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}
