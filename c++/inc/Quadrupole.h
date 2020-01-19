//
//  Quadrupole.h
//  
//
//  Created by Luca Paganin on 19/01/2020.
//

#ifndef Quadrupole_h
#define Quadrupole_h

#include "PointMass.h"

class Quadrupole: public PointMass{
	
protected:
	double m_Iperp, m_Izz;

public:
	
	Vector3D ComputeGravitationalField(const Vector3D&) const;
	
};


#endif /* Quadrupole_h */
