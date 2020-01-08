//
//  SistemaSolare.hpp
//  
//
//  Created by Luca Paganin on 06/01/2020.
//

#ifndef SISTEMASOLARE_H
#define SISTEMASOLARE_H

#include "Grave.h"
#include "Vettore3D.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class SistemaSolare{
private:
	std::vector<Grave> m_planets;
	std::string m_odemethod;
public:
	
	SistemaSolare(const std::vector<Grave>& pns, const std::string& method):
	m_planets(pns),
	m_odemethod(method)
	{
	}
	
	SistemaSolare():
	m_planets(std::vector<Grave>(0)),
	m_odemethod("")
	{
	}
	
	std::vector<Grave> Planets() const;
	
	void ReadInitialConditions(std::istream&);
	void PrintSystemCoords(std::ostream&);
	void print_planets_coords(std::ostream&);
	void print_system();
	
	void EulerCromerStep(double);
	
	
	
};



#endif /* SISTEMASOLARE_H */
