//
//  PointMass.h
//
//
//  Created by Luca Paganin on 06/01/2020.
//

#ifndef PointMass_H
#define PointMass_H

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "Vector3D.h"
#include "Constants.h"

class PointMass{
public:

	//using Vector3D::Vector3D;

	PointMass(Vector3D r, Vector3D v, double m, std::string name):
	m_R(r),
	m_V(v),
	m_M(m),
	m_name(name)
	{
	}

	PointMass():
	m_R(0,0,0),
	m_V(0,0,0),
	m_M(0),
	m_name("")
	{
	}

	Vector3D R() const;
	Vector3D V() const;
	std::string Name() const;
	void R(const Vector3D&);
	void V(const Vector3D&);
	double M() const;

	virtual Vector3D ComputeGravitationalField(const Vector3D&) const;
	Vector3D AngularMomentum() const;
	double KineticEnergy() const;
	
	virtual ~PointMass() = default;


protected:
	Vector3D m_R, m_V;
	double m_M;
	std::string m_name;
};

#endif /* PointMass_H */
