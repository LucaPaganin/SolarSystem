//
//  Vettore3D.cpp
//  
//
//  Created by Luca Paganin on 06/01/2020.
//

#include "Vettore3D.h"
#include <cmath>

double Vettore3D::X(){
	return m_v[0];
}

double Vettore3D::Y(){
	return m_v[1];
}

double Vettore3D::Z(){
	return m_v[2];
}

void Vettore3D::X(double x){
	m_v[0] = x;
}

void Vettore3D::Y(double y){
	m_v[1] = y;
}

void Vettore3D::Z(double z){
	m_v[2] = z;
}

double Vettore3D::mod(){
	return std::sqrt((*this)*(*this));
}

//Overloaded operators

Vettore3D Vettore3D::operator+(const Vettore3D& v){
	return Vettore3D(this->m_v[0]+v.m_v[0], this->m_v[1]+v.m_v[1], this->m_v[2]+v.m_v[2]);
}

Vettore3D Vettore3D::operator+=(const Vettore3D& v){
	m_v[0] += v.m_v[0];
	m_v[1] += v.m_v[1];
	m_v[2] += v.m_v[2];
	return *this;
}

Vettore3D Vettore3D::operator-(const Vettore3D& v){
	return Vettore3D(this->m_v[0]-v.m_v[0], this->m_v[1]-v.m_v[1], this->m_v[2]-v.m_v[2]);
}

Vettore3D Vettore3D::operator-=(const Vettore3D& v){
	m_v[0] -= v.m_v[0];
	m_v[1] -= v.m_v[1];
	m_v[2] -= v.m_v[2];
	return *this;
}

Vettore3D Vettore3D::operator=(const Vettore3D& v){
	m_v[0] = v.m_v[0];
	m_v[1] = v.m_v[1];
	m_v[2] = v.m_v[2];
	return *this;
}

bool Vettore3D::operator==(const Vettore3D& v){
	bool eq = (this->m_v[0] == v.m_v[0]) && (this->m_v[1] == v.m_v[1]) && (this->m_v[2] == v.m_v[2]);
	return eq;
}

bool Vettore3D::operator!=(const Vettore3D& v){
	return !(*(this) == v);
}

Vettore3D Vettore3D::cross(const Vettore3D& v){
	return Vettore3D(this->m_v[1] * v.m_v[2] - this->m_v[2] * v.m_v[1],
					 this->m_v[2] * v.m_v[0] - this->m_v[0] * v.m_v[2],
					 this->m_v[0] * v.m_v[1] - this->m_v[1] * v.m_v[0]);
}

double Vettore3D::operator*(const Vettore3D& v){
	return (this->m_v[0]*v.m_v[0] + this->m_v[1]*v.m_v[1] + this->m_v[2]*v.m_v[2]);
}

//Friends

std::ostream& operator<<(std::ostream& os, const Vettore3D& v){
	os << v.m_v[0] << ", " << v.m_v[1] << ", " << v.m_v[2];
	return os;
}

std::istream& operator>>(std::istream& is, Vettore3D& v){
	is >> v.m_v[0] >> v.m_v[1] >> v.m_v[2];
	return is;
}

Vettore3D operator*(double a, const Vettore3D& v){
	return Vettore3D(a*v.m_v[0], a*v.m_v[1], a*v.m_v[2]);
}
