//
//  Grave.hpp
//
//
//  Created by Luca Paganin on 06/01/2020.
//

#ifndef GRAVE_H
#define GRAVE_H

#define G 38.94

/*
 Units:

 Length: A.U. --> 1 A.U. = 1.5e11 m
 Mass: Solar Masses --> 1 M_Sun = 1.98e30 kg
 Time: Years --> 1 y = 3.1536e7 s

 G = 38.94 A.U.^3 M_Sun^-1 y^-2

 */

#include <iostream>
#include <cmath>
#include <vector>
#include "Vettore3D.h"

class Grave{
public:

	//using Vettore3D::Vettore3D;

	Grave(Vettore3D r, Vettore3D v, double m):
	m_R(r),
	m_V(v),
	m_M(m)
	{
	}

	Grave():
	m_R(0,0,0),
	m_V(0,0,0),
	m_M(0)
	{
	}

	Vettore3D R() const;
	Vettore3D V() const;
	void R(const Vettore3D&);
	void V(const Vettore3D&);
	double M() const;

	Vettore3D CampoGravitazionale(const Grave&);
	Vettore3D CampoGravitazionale(const std::vector<Grave> &);


private:
	Vettore3D m_R, m_V;
	double m_M;
};

#endif /* GRAVE_H */
