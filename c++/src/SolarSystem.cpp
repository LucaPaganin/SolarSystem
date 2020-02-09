//
//  SolarSystem.cpp
//  
//
//  Created by Luca Paganin on 06/01/2020.
//

#include "SolarSystem.h"

void SolarSystem::ReadInitialConditions(std::istream& is){
	std::string name;
	double m,x,y,z,vx,vy,vz;
	
	while (is >> name >> m >> x >> y >> z >> vx >> vy >> vz) {
		m_planets.push_back(PointMass(Vector3D(x,y,z), Vector3D(vx,vy,vz), m, name));
	}
}

void SolarSystem::DoTimeStep(){
	if (m_odemethod=="EulerCromer") {
		//Update coordinates
		for(unsigned i=0; i<m_planets.size(); ++i){
			m_planets[i].R((m_planets[i].R() + m_dt*m_planets[i].V()));
		}
		//Update forces
		this->UpdateAccelerations();
		//Update velocities
		for(unsigned i=0; i<m_planets.size(); ++i){
			m_planets[i].V((m_planets[i].V()
							+ (m_dt) * m_planets[i].A()));
		}
	}
	else if (m_odemethod=="VerletVelocity"){
		std::vector<Vector3D> old_accelerations(m_planets.size(),Vector3D(0,0,0));
		for (unsigned i=0; i<m_planets.size(); ++i) {
			old_accelerations[i] = m_planets[i].A();
		}
		
		//Update coordinates
		for (unsigned i=0; i<m_planets.size(); ++i) {
			auto dR = m_dt * m_planets[i].V()
			+ 0.5 * (m_dt * m_dt) * m_planets[i].A();
			
			m_planets[i].R(m_planets[i].R() + dR);
		}
		
		//Compute new forces
		this->UpdateAccelerations();
		
		//Update velocities
		for (unsigned i=0; i<m_planets.size(); ++i) {
			auto dV = 0.5 * m_dt * (old_accelerations[i] + m_planets[i].A());
			m_planets[i].V(m_planets[i].V() + dV);
		}
	}
	
	m_t += m_dt;
	
}

void SolarSystem::UpdateAccelerations(){
	
	std::vector<Vector3D> forces(m_planets.size(),Vector3D(0,0,0));
	
	//Compute forces
	for (unsigned i=0; i<m_planets.size(); i++) {
		for (unsigned j=i+1; j<m_planets.size(); j++){
			auto fij = m_planets[i].M()*m_planets[j].ComputeGravitationalField(m_planets[i].R());
			
			//Add fij to fi, where fij is the force of j on i
			forces[i] += fij;
			//Add -fij to fj, for Newton third principle
			forces[j] -= fij;
		}
	}
	
	for (unsigned i=0; i<m_planets.size(); ++i) {
		m_planets[i].A((1./m_planets[i].M())*forces[i]);
	}
	
}

std::vector<double> SolarSystem::ComputeEnergies() const{
	
	std::vector<double> energies(m_planets.size(), 0.0);
	
	for (unsigned i=0; i<m_planets.size(); ++i){
		energies[i] += m_planets[i].KineticEnergy();
		
		for (unsigned j=i+1; j<m_planets.size(); ++j) {
			double Uij = m_planets[i].M() * m_planets[j].ComputeGravitationalPotential(m_planets[i].R());
			energies[i] += Uij;
			energies[j] += Uij;
		}
	}
	
	return energies;
	
}

Vector3D SolarSystem::ComputeTotalAngularMomentum() const{
	Vector3D Ltot(0,0,0);
	
	for (const auto &p : m_planets) {
		Ltot += p.AngularMomentum();
	}
	
	return Ltot;
}

double SolarSystem::ComputeTotalEnergy() const{
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

void SolarSystem::PrintData(std::ostream& os, const std::string& type) const{
	
	//Print planets names
	if (type == "Names") {
		
		os << "#";
		for (const auto &p : m_planets) {
			os << p.Name() << " ";
		}
	}
	
	else if (type == "Coordinates") {
		for (const auto &p : m_planets) {
			os << p.R() << " ";
		}
	}
	
	else if (type == "TotalEnergy") {
		os << m_t << " " << this->ComputeTotalEnergy();
	}
	
	else if (type == "TotalAngularMomentum"){
		os << m_t << " " << this->ComputeTotalAngularMomentum();
	}
	
	
	else if (type == "SingleEnergies"){
		
		os << m_t << " ";
		
		auto single_energies = this->ComputeEnergies();
		
		for (const auto &e : single_energies) {
			os << e << " ";
		}
	}
	
	else if (type == "SingleAngularMomenta"){
		
		os << m_t << " ";
		
		for (const auto &p : m_planets) {
			os << p.AngularMomentum() << " ";
		}
	}
	
	os << std::endl;
	
}
