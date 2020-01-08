//
//  PointMass.cpp
//
//
//  Created by Luca Paganin on 06/01/2020.
//

#include "PointMass.h"

Vector3D PointMass::R() const {return m_R;}

Vector3D PointMass::V() const {return m_V;}

void PointMass::R(const Vector3D& r){m_R = r;}

void PointMass::V(const Vector3D& v){m_V = v;}

double PointMass::M() const {return m_M;}

Vector3D PointMass::GravitationalField(const PointMass& g){

	Vector3D rel_pos = m_R - g.m_R;
	Vector3D field = rel_pos;

	if (rel_pos == Vector3D(0,0,0)){
		//std::cout << "Error, can't evaluate gravitational field of point source into source position." << std::endl;
	}
	else{
		field = -(G*g.m_M/(std::pow(rel_pos.mod(), 3)))*(rel_pos);
	}
	return field;
}

Vector3D PointMass::GravitationalField(const std::vector<PointMass>& sources){

	Vector3D field(0,0,0);

	for (auto src : sources) {
		field += this->GravitationalField(src);
	}
	
	//std::cout << field << std::endl;

	return field;

}
