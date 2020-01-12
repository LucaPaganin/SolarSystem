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
	
	m_forces.resize(m_planets.size());
}

std::vector<PointMass> SolarSystem::Planets() const {return m_planets;}

void SolarSystem::Method(std::string method){m_odemethod = method;}

void SolarSystem::PrintSystemCoords(std::ostream& os){
	
	for (const auto &p : m_planets) {
		os << p.R() << " ";
	}
	os << std::endl;
}

void SolarSystem::TimeStep(double dt){
	
	if (m_odemethod=="EulerCromer") {
		
		//Update coordinates
		for(int i=0; i<m_planets.size(); ++i){
			m_planets[i].R((m_planets[i].R() + dt*m_planets[i].V()));
		}
		
		//Update forces
		this->ComputeGravitationalForces();
		
		//Update velocities
		for(int i=0; i<m_planets.size(); ++i){
			m_planets[i].V((m_planets[i].V()
							+ (dt/m_planets[i].M()) * m_forces[i]));
		}
	}
	
	else if (m_odemethod=="VerletVelocity"){
		auto old_forces = m_forces;
		
		//Update coordinates
		for (unsigned i=0; i<m_planets.size(); ++i) {
			auto dR = dt * m_planets[i].V()
			+ 0.5 * ((dt * dt)/m_planets[i].M()) * m_forces[i];
			
			m_planets[i].R(m_planets[i].R() + dR);
		}
		
		//Compute new forces
		this->ComputeGravitationalForces();
		
		//Update velocities
		for (unsigned i=0; i<m_planets.size(); ++i) {
			auto dV = (0.5 * dt / m_planets[i].M()) * (old_forces[i] + m_forces[i]);
			m_planets[i].V(m_planets[i].V() + dV);
		}
	}
	
}

void SolarSystem::ComputeGravitationalForces(){
	
	//Initialize forces to zero
	for (auto &f : m_forces) {
		f = Vector3D(0,0,0);
	}
	
	//Compute new forces
	for (unsigned i=0; i<m_planets.size(); i++) {
		for (unsigned j=i+1; j<m_planets.size(); j++){
			auto fij = m_planets[i].M()*m_planets[j].ComputeGravitationalField(m_planets[i].R());
			
			//Add fij to fi, where fij is the force of j on i
			m_forces[i] += fij;
			//Add -fij to fj, for Newton third principle
			m_forces[j] -= fij;
		}
	}
}

Vector3D SolarSystem::TotalAngularMomentum() const{
	Vector3D Ltot(0,0,0);
	
	for (const auto &p : m_planets) {
		Ltot += p.AngularMomentum();
	}
	
	return Ltot;
}

double SolarSystem::TotalEnergy() const{
	double E = 0;
	for (unsigned i=0; i<m_planets.size(); ++i) {
		E += m_planets[i].KineticEnergy();
		for (unsigned j=i+1; j<m_planets.size(); ++j) {
			E += -Constants::G *
			(m_planets[i].M() * m_planets[j].M())/
			((m_planets[i].R() - m_planets[j].R()).mod());
		}
	}
	return E;
}
