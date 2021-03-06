/*
 * Particle.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: Natanel Biber
 */

#include "Particle.h"

Particle::Particle(Location cell, double dYaw){
    this->_cell.setX(cell.getX());
    this->_cell.setY(cell.getY());
    this->_Teta = dYaw;
    this->_Belief = 1;
}

// This function update the particle according to the delats and the laser
double Particle::update(double deltaX, double deltaY, double deltaTeta , LaserProxy* laser)
{
    // Variable Definition
    double predBel;
    //double normalizeFactor = 1.2;

    // Update the particle position
    _cell.setX(_cell.getX() + deltaX);
    _cell.setY(_cell.getY() + deltaY);
    _Teta += deltaTeta;

    // Guess the probability
    predBel = _Belief * probMov(deltaX, deltaY, deltaTeta);
    _Belief = NORMALIZE_FACTOR * predBel;
    return _Belief;
}

double Particle::probMov(double deltaX, double deltaY, double deltaTeta)
{
    double dist = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
    double pro = 0;

	if(deltaTeta < 0)
		deltaTeta *= -1;
	if(dist > TRH_DIS && deltaTeta > TRH_YAW)
		pro = 0.2;
	if((dist < TRH_DIS && deltaTeta > TRH_YAW)||(dist > TRH_DIS && deltaTeta < TRH_YAW))
		pro = 0.4;
	if(dist < TRH_DIS && deltaTeta < TRH_YAW)
		pro = 0.8;
	if(dist < TRH_DIS && deltaTeta == 0)
		pro = 1;
	return pro;

//	if ((dist < TOP_DISTANCE) && (abs(deltaTeta) < TOP_DELTA_TETA))
//    {
//        return 1;
//    }
//
//    return 0;
}

// This function is the belief property
double Particle::getBelief()
{
    return (this->_Belief);
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

