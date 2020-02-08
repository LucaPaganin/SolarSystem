//
//  Vector3D.h
//  
//
//  Created by Luca Paganin on 06/01/2020.
//

#ifndef Vector3D_H
#define Vector3D_H

#include <iostream>

class Vector3D{
private:
	double m_v[3];
public:
	Vector3D (double x, double y, double z){
		m_v[0] = x;
		m_v[1] = y;
		m_v[2] = z;
	}
	Vector3D(){m_v[0] = 0; m_v[1] = 0; m_v[2] = 0;}
	
	//Getters and Setters
	double X() const{return m_v[0];}
	double Y() const{return m_v[1];}
	double Z() const{return m_v[2];}
	void X(double x){m_v[0] = x;}
	void Y(double y){m_v[1] = y;}
	void Z(double z){m_v[2] = z;}
	
	//Module
	double mod() const;
	
	//operators
	Vector3D operator+(const Vector3D&);
	Vector3D operator+=(const Vector3D&);
	Vector3D operator-(const Vector3D&) const;
	Vector3D operator-=(const Vector3D&);
	Vector3D operator=(const Vector3D&);
	bool operator==(const Vector3D&);
	bool operator!=(const Vector3D&);
	Vector3D cross(const Vector3D&) const;
	double operator*(const Vector3D&) const;
	
	//friends
	friend std::ostream& operator<<(std::ostream&, const Vector3D&);
	friend std::istream& operator>>(std::istream&, Vector3D&);
	friend Vector3D operator*(double, const Vector3D&);
};



#endif /* Vector3D_H */
