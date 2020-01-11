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
	
	if (argc < 2) {
		std::cout << "Usage: ./" << argv[0] << " input_filename n_days dt" << std::endl;
		return 1;
	}
	
	auto input_path = std::string(argv[1]);
	auto n_days = atof(argv[2]);
	auto dt = atof(argv[3]);
	
	//Read initial conditions
	std::ifstream input_file(input_path);
	SolarSystem system;
	system.ReadInitialConditions(input_file);
	input_file.close();
	
	//get planets
	auto planets = system.Planets();
	
	//Open output file
	std::ofstream output_file("output/temporal_evolution.txt");
	
	//Print first line as a comment
	output_file << "#";
	
	//Print planets names
	for (const auto &p: planets){
		output_file << p.Name() << " ";
	}
	output_file << std::endl;
	
	//Do time evolution
	int Nsteps = n_days/dt;
	int Nphotos = 500;
	int M = (Nsteps%Nphotos==0) ? Nsteps/Nphotos : 100;
	
	for (unsigned i=0; i<Nsteps; ++i){
		if (i%M==0)
			system.PrintSystemCoords(output_file);
		
		system.EulerCromerStep(dt);
	}
	
	output_file.close();
	
	return 0;
}
