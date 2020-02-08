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
	double m_t;
public:
	
	SolarSystem(const std::vector<PointMass>& pns, const std::string& method):
	m_planets(pns),
	m_forces(std::vector<Vector3D>(pns.size())),
	m_odemethod(method),
	m_t(0.)
	{
	}
	
	SolarSystem():
	m_planets(std::vector<PointMass>(0)),
	m_forces(std::vector<Vector3D>(0)),
	m_odemethod(""),
	m_t(0.)
	{
	}
	
	std::vector<PointMass> Planets() const;
	void Method(std::string);
	void ReadInitialConditions(std::istream&);
	void PrintData(std::ostream&, const std::string&) const;
	
	void ComputeGravitationalForces();
	void TimeStep(double);
	
	Vector3D TotalAngularMomentum() const;
	double TotalEnergy() const;
	std::vector<double> ComputeEnergies() const;
	
};



#endif /* SolarSystem_H */
