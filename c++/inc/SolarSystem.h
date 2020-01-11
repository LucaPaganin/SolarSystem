//
//  SolarSystem.h
//  
//
//  Created by Luca Paganin on 06/01/2020.
//

#ifndef SolarSystem_H
#define SolarSystem_H

#include "PointMass.h"
#include "Vector3D.h"
#include <iostream>
#include <fstream>
#include <vector>

class SolarSystem{
private:
	std::vector<PointMass> m_planets;
	std::string m_odemethod;
public:
	
	SolarSystem(const std::vector<PointMass>& pns, const std::string& method):
	m_planets(pns),
	m_odemethod(method)
	{
	}
	
	SolarSystem():
	m_planets(std::vector<PointMass>(0)),
	m_odemethod("")
	{
	}
	
	std::vector<PointMass> Planets() const;
	
	void ReadInitialConditions(std::istream&);
	void PrintSystemCoords(std::ostream&);
	void print_planets_coords(std::ostream&);
	
	std::vector<Vector3D> ComputeGravitationalForces();
	
	void EulerCromerStep(double);
	
	
	
};



#endif /* SolarSystem_H */
