/*
 * Global.h
 *
 *  Created on: 10 July 2015
 *      Author: Liron Bilya, Yaron Elhadad, Ran Amar
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <math.h>
#include <libplayerc++/playerc++.h>
#include <string>
#include <sstream>

#define LASER_SAMPLES 666
#define PI 3.14159265
#define SCALE_OF_OBSTACLE 100
//#define ROBOT_LIVE_RESOLUTION_X_LONG 14.25
//#define ROBOT_LIVE_RESOLUTION_X 60.77
//#define ROBOT_LIVE_RESOLUTION_Y 45.34

// Configuration Manager
#define NUM_OF_PROPERTIES 10
#define MAX_LINE_LENGTH 100
#define CONFIGURATION_PATH "Configuration"


#define INFLATED_MAP_NAME "InflatedMap.png"

#define ROBOT_LIVE_RESOLUTION_X_LONG 14.25
#define ROBOT_LIVE_RESOLUTION_X 16.25
#define ROBOT_LIVE_RESOLUTION_Y 18.25

// movement
#define ROTATION_SPEED 0.02
#define FORWARD_SPEED_SLOW 0.2
#define FORWARD_SPEED 0.4
#define TOLERANCE_DISTANCE 1.7

// robot movement directions
#define MOVE_FORWARD 0
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define UP_LEFT 5
#define UP_RIGHT 6
#define DOWN_LEFT 7
#define DOWN_RIGHT 8
#define STOP 9

// robot angle directions
#define ANGLE_UP 1.57
#define ANGLE_DOWN -1.57
#define ANGLE_RIGHT 0
#define ANGLE_LEFT -3.14
#define ANGLE_UP_LEFT 2.425
//#define ANGLE_UP_LEFT 2.356
#define ANGLE_UP_RIGHT 0.785
#define ANGLE_DOWN_LEFT -2.356
#define ANGLE_DOWN_RIGHT -0.785

// Find Path Map Enum
#define FREE 0
#define OCCUPIED 1
#define PATH_CELL 2
#define START_CELL 3
#define GOAL_CELL 4

// Files name
#define MAP_BLOWED "blowedMap.png"
#define MAP_WAYPOINTS "waypointsMap.png"

//
// Laser Proxy
#define FORWARD_LASER_PROXY_VALUE 332
#define RIGHT_LASER_PROXY_VALUE 50
#define LEFT_LASER_PROXY_VALUE 614
#define DISTANCE_TOLERANCE 0.3

// Movement
#define TURN_RIGHT_SPEED -0.3
#define TURN_LEFT_SPEED 0.3
#define MOVE_SPEED 0.1

#define TOLLERANCE 10

// Behaviors
#define BEHAVIORS_COUNT 2
#define ONE_DEGREE_INDEXES 2.4667
#define LASER_SPEC 111
#define MAX_YAW_DIFF 2

using namespace std;

class Global
{
public:
	static double mapResolution;
	Global();
	virtual ~Global();
	static double index_to_angle(int index);
	static int angle_to_index(double angle);
	static string trim(const std::string& str,const std::string& whitespace);
	static int str2int(string num);
	static double str2double(string num);
	static int* getValuesArray(string value);
};

#define X_LONG_RESOLUTION_POINT -10
#endif /* GLOBAL_H_ */
