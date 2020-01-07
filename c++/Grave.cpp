//
//  Grave.cpp
//  
//
//  Created by Luca Paganin on 06/01/2020.
//

#include "Grave.h"

Vettore3D Grave::R(){return m_R;}

Vettore3D Grave::V(){return m_V;}

void Grave::R(const Vettore3D& r){m_R = r;}

void Grave::V(const Vettore3D& v){m_V = v;}

double Grave::M() const {return m_M;}

Vettore3D Grave::CampoGravitazionale(const Grave& g){
	
	Vettore3D rel_pos = m_R - g.m_R;
	Vettore3D field = rel_pos;
	
	if (rel_pos == Vettore3D(0,0,0)){
		//std::cout << "Error, can't evaluate gravitational field of point source into source position." << std::endl;
	}
	else{
		field = -(G*g.m_M/(std::pow(rel_pos.mod(), 3)))*(rel_pos);
	}
	return field;
}

Vettore3D Grave::CampoGravitazionale(const std::vector<Grave>& sources){
	
	Vettore3D field(0,0,0);
	
	for (auto src : sources) {
		field += this->CampoGravitazionale(src);
	}
	
	return field;
	
}
