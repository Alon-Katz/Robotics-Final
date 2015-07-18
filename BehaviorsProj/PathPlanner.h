/*
 * AStar.h
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#ifndef ASTAR_H_
#define ASTAR_H_

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include "Location.h"
#include "WaypointsManager.h"

using namespace std;

const int dir=8; // number of possible directions to go at any position
//const int n=95; // horizontal size of the map
//const int m=137; // vertical size size of the map


class PathPlanner
{
public:

	int n,m, m_counter;
	int** closed_nodes_map; // map of closed (tried-out) nodes
	int** open_nodes_map; // map of open (not-yet-tried) nodes
	int** dir_map; // map of directions
	vector<Location> _path;

	int dy[dir]={1, 1, 0, -1, -1, -1, 0, 1};
	int dx[dir]={0, 1, 1, 1, 0, -1, -1, -1};


	PathPlanner(int width, int height);
	~PathPlanner();
	//WaypointsManager m_wayPoints;
	string pathFind( int  xStart, int  yStart, int  xFinish, int  yFinish, int** map);
	vector<Location> getPathLocations( string  direction, int  sourceX, int  sourceY);
	vector<Location> getWayPoints();
	int getWaypointsSize();
};

#endif /* ASTAR_H_ */
