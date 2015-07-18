// ----------------------------------------------------------------------------------------
// main.cpp
// Professional Developers:
// Natanel Beber - 308480284 , Alon Katz - 204368450 , Itay Eylon - 307872515
// Date: 15.7.15
//
// ----------------------------------------------------------------------------------------

#include <iostream>
#include "Robot.h"
#include "Manager.h"
#include "Map.h"
#include "ConfigurationManager.h"
#include <vector>

#define SELECTED_WAY_POINTS 3

using namespace std;

int main()
{
	// Read Configuration File
	ConfigurationManager ConfigData(CONFIGURATION_PATH);

	// Inflate Map, Change to Grid and Resize
	Map Map(ConfigData.grid_resolution);

	// Get Location from ASTAR Algo
	vector<Location> PathLocations = Map.InitMap(ConfigData);

	// Play The Robot
	Robot Robot("localhost",6665,&ConfigData, Map.m_width);

	// Manage Way Points
	WaypointsManager WayPointMangaer(PathLocations, ConfigData.grid_resolution, ConfigData.map_resolution);

	// Set every third location to be a waypoint
	WayPointMangaer.build_way_point_vector(SELECTED_WAY_POINTS);

	// How to avoid obstacles
	PlanObstacleAvoid PlanObstacleAvoid(&Robot, &WayPointMangaer);

	// Where the robot is realy is
	LocalizationManager LocalizationManager;

	// Start the Logic
	Manager manager(&Robot, &PlanObstacleAvoid, &LocalizationManager, &ConfigData, &WayPointMangaer);

	// Run until we get to destination
	manager.run();

 	return 0;
}
