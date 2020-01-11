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
	
	while (is >> name >> m >> x >> y >> z >> vx >> vy >> vz) {
		
		m_planets.push_back(PointMass(Vector3D(x,y,z), Vector3D(vx,vy,vz), m, name));
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

void SolarSystem::EulerCromerStep(double dt){
	
	for(int i=0; i<m_planets.size(); ++i){
		m_planets[i].R((m_planets[i].R() + dt*m_planets[i].V()));
	}
	
	auto forces = ComputeGravitationalForces();
	
	for(int i=0; i<m_planets.size(); ++i){
		m_planets[i].V((m_planets[i].V() + (dt/m_planets[i].M()) * forces[i]));
	}
	
}

std::vector<Vector3D> SolarSystem::ComputeGravitationalForces(){
	
	std::vector<Vector3D> forces(m_planets.size(), Vector3D(0,0,0));
	
	for (int i=0; i<m_planets.size(); i++) {
		for (int j=i+1; j<m_planets.size(); j++){
			
			auto fij = m_planets[i].M()*m_planets[j].ComputeGravitationalField(m_planets[i].R());
			
			//Add fij to fi, where fij is the force of j on i
			forces[i] += fij;
			//Add -fij to fj, for Newton third principle
			forces[j] -= fij;
		}
	}
	
	return forces;
	
}

