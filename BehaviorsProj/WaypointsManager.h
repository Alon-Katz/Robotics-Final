/*
 * WaypointsManager.h
 *
 *  Created on: Jun 14, 2015
 *      Author: colman
 */

#ifndef WAYPOINTSMANAGER_H_
#define WAYPOINTSMANAGER_H_

#include <iostream>
#include <vector>
#include "wayPoint.h"
#include "Location.h"
#include<set>
#include "Global.h"
#include <math.h>
using std::vector;
using std::set;

class WaypointsManager {
public:

	set<wayPoint> wayPoints;
	wayPoint currWayPoint;

	WaypointsManager(vector<Location> path, double gridResolution, double mapResolution);
	void build_way_point_vector(int num_of_cells);
	void setNextWayPoint(wayPoint Next);
	bool isInWayPoint(double x,double y);
	virtual ~WaypointsManager();

private:
	vector<Location> astar_path;
	bool is_verticle = 0;
	wayPoint nextWayPoint;
	double _gridResolution;
	double _mapResolution;

	double calc_yaw(double m, Location cell_from, Location cell_to);
	double calc_incline(Location cell_from, Location cell_to);

};

#endif /* WAYPOINTSMANAGER_H_ */
