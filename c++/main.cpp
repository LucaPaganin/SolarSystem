//
//  main.cpp
//
//
//  Created by Luca Paganin on 06/01/2020.
//

#include "Vector3D.h"
#include "PointMass.h"
#include "SolarSystem.h"

int main(int argc, const char* argv[]){
	
	std::ofstream output_file("output/temporal_evolution.txt");
	std::ifstream input_file("input_file.h");
	
	SolarSystem system;
	
	system.ReadInitialConditions(input_file);
	
	auto planets = system.Planets();
	
	for (const auto &p: planets){
		auto index = &p - &planets[0];
		std::cout << "Planet " << index+1 << ": " << std::endl;
		std::cout <<  "Coordinates: (" << p.R() << "); Velocity: (" << p.V() << "); Mass = " << p.M() << std::endl;
	}
	
	/*
	 
	 int N = 1e5;
	 double dt=1e-5;
	 
	 for (int i=0; i<N; ++i){
	 if (i%100 == 0)
	 system.print_planets_coords(output_file);
	 
	 system.EulerCromerStep(dt);
	 }
	 
	 
	 input_file.close();
	 */
	output_file.close();
	return 0;
}
