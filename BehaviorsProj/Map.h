/*
 * Map.h
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <set>
#include "ConfigurationManager.h"
#include "PathPlanner.h"
#include "Global.h"

using namespace std;

using std::vector;
using std::set;

class Map {
public:
	int m_wayPointsSize;
	std::vector<unsigned char> m_vec; //the raw pixels
	int** m_original_grid;
	int** m_inflated_grid;
	int** matrix;
	unsigned m_width, m_height;
	double m_grid_resulotion;
	int cellSize;
	Map(double grid_resulotion);
	Map();

	int dy[dir]={1, 1, 0, -1, -1, -1, 0, 1};
	int dx[dir]={0, 1, 1, 1, 0, -1, -1, -1};


	vector<Location> getRoute(Location sourceLocation, Location destLocation);
	int getWaypointsSize();
	vector<Location> InitMap(ConfigurationManager p_configData);
	void convertMapToGrid(double grid_resolution, double map_resolution, const char* originalMap);
	void InflatingMap(const char* filename, int intRobotSize, double mapResolution);
	void createGrids(double map_resolution, double grid_resolution, const char* originalMap);
	int checkIfOccupy(int gridRow, int gridCol, int cellSize);
	unsigned getWidth();
	int** getGrid();
	unsigned getHeight();
	int getCellValue(int col, int row);
	int getGridRow(double row);
	int getGridCol(double col);
	vector<unsigned char> colorizeWaypoints(vector<Location> p_wayPoints);
	virtual ~Map();
};

#endif /* MAP_H_ */
