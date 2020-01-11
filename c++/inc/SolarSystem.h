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
	std::vector<Vector3D> m_forces;
	std::string m_odemethod;
public:
	
	SolarSystem(const std::vector<PointMass>& pns, const std::string& method):
	m_planets(pns),
	m_forces(std::vector<Vector3D>(pns.size())),
	m_odemethod(method)
	{
	}
	
	SolarSystem():
	m_planets(std::vector<PointMass>(0)),
	m_forces(std::vector<Vector3D>(0)),
	m_odemethod("")
	{
	}
	
	std::vector<PointMass> Planets() const;
	void Method(std::string);
	void ReadInitialConditions(std::istream&);
	void PrintSystemCoords(std::ostream&);
	
	void ComputeGravitationalForces();
	void TimeStep(double);
	void EulerCromerStep(double);
	void VerletVelocity(double);
	
	Vector3D TotalAngularMomentum() const;
	double TotalEnergy() const;
	
	
};



#endif /* SolarSystem_H */
