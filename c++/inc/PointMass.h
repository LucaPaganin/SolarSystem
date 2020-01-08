//
//  PointMass.h
//
//
//  Created by Luca Paganin on 06/01/2020.
//

#ifndef PointMass_H
#define PointMass_H

#define G 2.95905e-4


/*
 Units:

 Length: A.U. --> 1 A.U. = 1.5e11 m
 Mass: Solar Masses --> 1 M_Sun = 1.989e30 kg
 Time: Days --> 1 d = 86400 s

 G = 2.936e-4 A.U.^3 M_Sun^-1 d^-2

 */

#include <iostream>
#include <cmath>
#include <vector>
#include "Vector3D.h"

class PointMass{
public:

	//using Vector3D::Vector3D;

	PointMass(Vector3D r, Vector3D v, double m):
	m_R(r),
	m_V(v),
	m_M(m)
	{
	}

	PointMass():
	m_R(0,0,0),
	m_V(0,0,0),
	m_M(0)
	{
	}

	Vector3D R() const;
	Vector3D V() const;
	void R(const Vector3D&);
	void V(const Vector3D&);
	double M() const;

	Vector3D GravitationalField(const PointMass&);
	Vector3D GravitationalField(const std::vector<PointMass> &);


private:
	Vector3D m_R, m_V;
	double m_M;
};

#endif /* PointMass_H */
