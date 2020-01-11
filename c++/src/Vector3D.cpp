//
//  Vector3D.cpp
//  
//
//  Created by Luca Paganin on 06/01/2020.
//

#include "Vector3D.h"
#include <cmath>

double Vector3D::X(){
	return m_v[0];
}

double Vector3D::Y(){
	return m_v[1];
}

double Vector3D::Z(){
	return m_v[2];
}

void Vector3D::X(double x){
	m_v[0] = x;
}

void Vector3D::Y(double y){
	m_v[1] = y;
}

void Vector3D::Z(double z){
	m_v[2] = z;
}

double Vector3D::mod(){
	return std::sqrt((*this)*(*this));
}

//Overloaded operators

Vector3D Vector3D::operator+(const Vector3D& v){
	return Vector3D(this->m_v[0]+v.m_v[0], this->m_v[1]+v.m_v[1], this->m_v[2]+v.m_v[2]);
}

Vector3D Vector3D::operator+=(const Vector3D& v){
	m_v[0] += v.m_v[0];
	m_v[1] += v.m_v[1];
	m_v[2] += v.m_v[2];
	return *this;
}

Vector3D Vector3D::operator-(const Vector3D& v) const{
	return Vector3D(this->m_v[0]-v.m_v[0], this->m_v[1]-v.m_v[1], this->m_v[2]-v.m_v[2]);
}

Vector3D Vector3D::operator-=(const Vector3D& v){
	m_v[0] -= v.m_v[0];
	m_v[1] -= v.m_v[1];
	m_v[2] -= v.m_v[2];
	return *this;
}

Vector3D Vector3D::operator=(const Vector3D& v){
	m_v[0] = v.m_v[0];
	m_v[1] = v.m_v[1];
	m_v[2] = v.m_v[2];
	return *this;
}

bool Vector3D::operator==(const Vector3D& v){
	bool eq = (this->m_v[0] == v.m_v[0]) && (this->m_v[1] == v.m_v[1]) && (this->m_v[2] == v.m_v[2]);
	return eq;
}

bool Vector3D::operator!=(const Vector3D& v){
	return !(*(this) == v);
}

Vector3D Vector3D::cross(const Vector3D& v) const{
	return Vector3D(this->m_v[1] * v.m_v[2] - this->m_v[2] * v.m_v[1],
					 this->m_v[2] * v.m_v[0] - this->m_v[0] * v.m_v[2],
					 this->m_v[0] * v.m_v[1] - this->m_v[1] * v.m_v[0]);
}

double Vector3D::operator*(const Vector3D& v) const{
	return (this->m_v[0]*v.m_v[0] + this->m_v[1]*v.m_v[1] + this->m_v[2]*v.m_v[2]);
}

//Friends

std::ostream& operator<<(std::ostream& os, const Vector3D& v){
	os << v.m_v[0] << " " << v.m_v[1] << " " << v.m_v[2];
	return os;
}

std::istream& operator>>(std::istream& is, Vector3D& v){
	is >> v.m_v[0] >> v.m_v[1] >> v.m_v[2];
	return is;
}

Vector3D operator*(double a, const Vector3D& v){
	return Vector3D(a*v.m_v[0], a*v.m_v[1], a*v.m_v[2]);
}
