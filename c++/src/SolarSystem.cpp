//
//  SolarSystem.cpp
//  
//
//  Created by Luca Paganin on 06/01/2020.
//

#include "SolarSystem.h"

void SolarSystem::ReadInitialConditions(std::istream& is){
	
	//std::cout << "Hello" << std::endl;
	
	std::string name;
	double m,x,y,z,vx,vy,vz;
	
	while (is >> name >> m >> vx >> x >> vy >> y >> vz >> z) {
		
		m_planets.push_back(PointMass(Vector3D(x,y,z), Vector3D(vx,vy,vz), m));
	}
}

std::vector<PointMass> SolarSystem::Planets() const {return m_planets;}

void SolarSystem::print_planets_coords(std::ostream& os){
	for (auto &p : m_planets) {
		os << p.R() << " ";
	}
	os << std::endl;
}

void SolarSystem::PrintSystemCoords(std::ostream& os){
	for (const auto &p : m_planets) {
		os << p.R() << " ";
	}
	os << std::endl;
}

void SolarSystem::print_system(){
	for (const auto &p : m_planets) {
		std::cout << "r = " << p.R() << std::endl;
		std::cout << "v = " << p.V() << std::endl;
		std::cout << "m = " << p.M() << std::endl << std::endl;
	}
}

void SolarSystem::EulerCromerStep(double dt){
	
	for(int i=0; i<m_planets.size(); ++i){
		m_planets[i].R((m_planets[i].R() + dt*m_planets[i].V()));
		
		Vector3D field = m_planets[i].GravitationalField(m_planets);
		
		m_planets[i].V((m_planets[i].V() + dt * field));
	}
	
}

