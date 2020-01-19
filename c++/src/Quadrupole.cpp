//
//  Quadrupole.cpp
//  
//
//  Created by Luca Paganin on 19/01/2020.
//

#include "Quadrupole.h"
#include "Constants.h"

Vector3D Quadrupole::ComputeGravitationalField(const Vector3D& r) const{
	
	Vector3D rel_pos = m_R - r;
	
	double A = 3*Constants::G*(m_Iperp - m_Izz)/2;
	
	double B = (rel_pos.X() * rel_pos.X() + rel_pos.Y() * rel_pos.Y() + rel_pos.Z() * rel_pos.Z()) - 5 * rel_pos.Z() * rel_pos.Z();
	
	return A/(std::pow(rel_pos.mod(),7)) * Vector3D(0,0,0);
	
}
