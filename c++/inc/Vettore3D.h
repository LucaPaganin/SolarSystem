//
//  Vettore3D.hpp
//  
//
//  Created by Luca Paganin on 06/01/2020.
//

#ifndef VETTORE3D_H
#define VETTORE3D_H

#include <iostream>

class Vettore3D{
public:
	
	Vettore3D (double x, double y, double z){
		m_v[0] = x;
		m_v[1] = y;
		m_v[2] = z;
	}
	Vettore3D(){m_v[0] = 0; m_v[1] = 0; m_v[2] = 0;}
	
	//Getters and Setters
	
	double X();
	double Y();
	double Z();
	void X(double);
	void Y(double);
	void Z(double);
	
	//Modulus
	double mod();
	
	//operators
	Vettore3D operator+(const Vettore3D&);
	Vettore3D operator+=(const Vettore3D&);
	Vettore3D operator-(const Vettore3D&);
	Vettore3D operator-=(const Vettore3D&);
	Vettore3D operator=(const Vettore3D&);
	bool operator==(const Vettore3D&);
	bool operator!=(const Vettore3D&);
	Vettore3D cross(const Vettore3D&);
	double operator*(const Vettore3D&);
	
	//friends
	friend std::ostream& operator<<(std::ostream&, const Vettore3D&);
	friend std::istream& operator>>(std::istream&, Vettore3D&);
	friend Vettore3D operator*(double, const Vettore3D&);
	
private:
	double m_v[3];
	
};



#endif /* VETTORE3D_H */
