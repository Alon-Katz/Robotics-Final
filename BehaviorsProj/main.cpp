/*
 * main.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#include <iostream>
#include "Robot.h"
#include "Manager.h"
#include "Map.h"
#include "ConfigurationManager.h"
#include <vector>
//#include "WaypointsManager.h"

using namespace std;

int main()
{

	ConfigurationManager configData(CONFIGURATION_PATH);

	Map map(configData.grid_resolution);
	vector<Location> wayPoints = map.InitMap(configData);
	Robot robot("localhost",6665,&configData, map.m_width);

	WaypointsManager wp(wayPoints, configData.grid_resolution, configData.map_resolution);
		wp.build_way_point_vector(3);

		wayPoint wpm;
		set<wayPoint>::iterator it;

		for (it = (wp.wayPoints).begin(); it != (wp.wayPoints).end(); ++it) {
			wpm = *it;
			cout << wpm.x_Coordinate << " " << wpm.y_Coordinate << " " << wpm.yaw << endl;
		}

		PlnObstacleAvoid plnOA(&robot, &wp);
		LocalizationManager lm;


		Manager manager(&robot, &plnOA, &lm, &configData, &wp);
		manager.run();

 	return 0;
}
