/*
 * Location.h
 *
 *  Created on: 10 July 2015
 *      Author: Liron Bilya, Yaron Elhadad, Ran Amar
 */

#ifndef LOCATION_H_
#define LOCATION_H_

class Location {
private:
	double _x;
	double _y;
	double _yaw;
public:
	Location();
	Location(double x, double y, double yaw);
	Location(double x, double y);
	virtual ~Location();

	double getX();
	double getY();
	double getYaw();

	void setX(double x);
	void setY(double y);
	void setYaw(double yaw);
};

#endif /* LOCATION_H_ */
