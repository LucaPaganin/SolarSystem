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
	protected:
	Vector3D m_R, m_V, m_A;
	double m_M;
	std::string m_name;
public:
	PointMass(Vector3D r, Vector3D v, double m, std::string name):
	m_R(r),
	m_V(v),
	m_M(m),
	m_name(name)
	{
	}
	
	PointMass(Vector3D r, Vector3D v, Vector3D a, double m, std::string name):
	m_R(r),
	m_V(v),
	m_A(a),
	m_M(m),
	m_name(name)
	{
	}

	PointMass():
	m_R(0,0,0),
	m_V(0,0,0),
	m_A(0,0,0),
	m_M(0),
	m_name("")
	{
	}

	//Getters
	Vector3D R() const{return m_R;}
	Vector3D V() const{return m_V;}
	Vector3D A() const{return m_A;}
	std::string Name() const{return m_name;}
	double M() const{return m_M;}
	//Setters
	void R(const Vector3D& r){m_R = r;}
	void V(const Vector3D& v){m_V = v;}
	void A(const Vector3D& a){m_A = a;}
	//Computing physical quantities
	virtual Vector3D ComputeGravitationalField(const Vector3D&) const;
	virtual double ComputeGravitationalPotential(const Vector3D&) const;
	Vector3D AngularMomentum() const;
	double KineticEnergy() const;
	//Virtual destructor
	virtual ~PointMass() = default;
};

#endif /* PointMass_H */
