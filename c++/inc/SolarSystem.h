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
	double m_t, m_dt;
public:
	SolarSystem(const std::vector<PointMass>& pns, const std::string& method, double dt):
	m_planets(pns),
	m_forces(std::vector<Vector3D>(pns.size())),
	m_odemethod(method),
	m_t(0.),
	m_dt(dt)
	{
	}
	
	SolarSystem():
	m_planets(std::vector<PointMass>(0)),
	m_forces(std::vector<Vector3D>(0)),
	m_odemethod(""),
	m_t(0.),
	m_dt(0.01)
	{
	}
	
	//Getters
	double TimeStep() const{return m_dt;}
	std::string Method() const{return m_odemethod;}
	std::vector<PointMass> Planets() const{return m_planets;}
	//Setters
	void Method(const std::string& method){m_odemethod = method;}
	void TimeStep(double dt){m_dt = dt;}
	//Auxiliary methods
	void ReadInitialConditions(std::istream&);
	void PrintData(std::ostream&, const std::string&) const;
	//Updating methods
	void UpdateGravitationalForces();
	void DoTimeStep();
	//Physical quantities evaluation
	Vector3D ComputeTotalAngularMomentum() const;
	double ComputeTotalEnergy() const;
	std::vector<double> ComputeEnergies() const;
};



#endif /* SolarSystem_H */
