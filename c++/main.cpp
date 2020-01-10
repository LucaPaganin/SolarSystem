//
//  main.cpp
//
//
//  Created by Luca Paganin on 06/01/2020.
//

#include "Vector3D.h"
#include "PointMass.h"
#include "SolarSystem.h"
#include <cstdlib>

int main(int argc, const char* argv[]){
	
	std::ofstream output_file("output/temporal_evolution.txt");
	std::ofstream names_file("output/planets_names.txt");
	
	if (argc < 2) {
		std::cout << "Usage: ./" << argv[0] << " initialconditions_file n_days dt" << std::endl;
		return 1;
	}
	
	auto input_filename = argv[1];
	auto n_days = atof(argv[2]);
	auto dt = atof(argv[3]);
	
	int Nsteps = n_days/dt;
	
	std::ifstream input_file(input_filename);
	
	SolarSystem system;
	
	system.ReadInitialConditions(input_file);
	input_file.close();
	
	auto planets = system.Planets();
	
	for (const auto &p: planets){
		auto index = &p - &planets[0];
		std::cout << p.Name() << " : " << std::endl;
		std::cout <<  "Coordinates: (" << p.R() << "); Velocity: (" << p.V() << "); Mass = " << p.M() << std::endl;
		names_file << p.Name() << " ";
	}
	names_file.close();
	
	int Nphotos = 500;
	int M = (Nsteps%Nphotos==0) ? Nsteps/Nphotos : 100;
	
	for (unsigned i=0; i<Nsteps; ++i){
		if (i%M==0)
			system.PrintSystemCoords(output_file);
		
		system.EulerCromerStep(dt);
	}
	
	/*
	out_coords.close();
	out_vels.close();
	out_fields.close();
	 */
	output_file.close();
	
	return 0;
}
