//
//  PointMass.cpp
//
//
//  Created by Luca Paganin on 06/01/2020.
//

#include "PointMass.h"

Vector3D PointMass::R() const {return m_R;}

Vector3D PointMass::V() const {return m_V;}

std::string PointMass::Name() const {return m_name;}

void PointMass::R(const Vector3D& r){m_R = r;}

void PointMass::V(const Vector3D& v){m_V = v;}

double PointMass::M() const {return m_M;}

double PointMass::ComputeGravitationalPotential(const Vector3D& r) const{
	Vector3D rel_pos = r - m_R;
	double potential = 0;
	
	if (rel_pos == Vector3D(0,0,0)){
		std::cout << "Error, can't evaluate gravitational potential of point source into source position." << std::endl;
	}
	else{
		potential = - Constants::G * m_M / (rel_pos.mod());
	}
	
	return potential;
}

Vector3D PointMass::ComputeGravitationalField(const Vector3D& r) const{

	Vector3D rel_pos = r - m_R;
	Vector3D field(0,0,0);
	
	if (rel_pos == Vector3D(0,0,0)){
		std::cout << "Error, can't evaluate gravitational field of point source into source position." << std::endl;
	}
	else{
		field = -((Constants::G * m_M)/(std::pow(rel_pos.mod(), 3)))*(rel_pos);
	}
	return field;
}

Vector3D PointMass::AngularMomentum() const{return m_R.cross(m_M * m_V);}

double PointMass::KineticEnergy() const{return (0.5 * m_M * (m_V * m_V));}
