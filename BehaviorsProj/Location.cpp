/*
 * Location.cpp
 *
 *  Created on: 10 July 2015
 *      Author: Liron Bilya, Yaron Elhadad, Ran Amar
 */

#include "Location.h"

Location::Location()
{
	this->_x = 0;
	this->_y = 0;
	this->_yaw = 0;
}

Location::Location(double x, double y, double yaw)
{
	this->_x = x;
	this->_y = y;
	this->_yaw = yaw;
}

Location::Location(double x, double y)
{
	this->_x = x;
	this->_y = y;
}

Location::~Location()
{
}

double Location::getX()
{
	return this->_x;
}

double Location::getY()
{
	return this->_y;
}

double Location::getYaw()
{
	return this->_yaw;
}

void Location::setX(double x)
{
	this->_x = x;
}

void Location::setY(double y)
{
	this->_y = y;
}
void Location::setYaw(double yaw)
{
	this->_yaw = yaw;
}
