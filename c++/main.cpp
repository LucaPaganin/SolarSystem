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
	
	auto input_path = "effemeridi.txt";
	auto ndays = 365;
	auto dt = 0.1;
	auto Nphotos = 500;
	
	//Error message if argc > 5
	if (argc > 4) {
		std::cout << "Too many parameters. Usage is: " << argv[0];
		std::cout << " input_filename (default " << input_path << ")";
		std::cout << " n_days (default " << ndays << ")";
		std::cout << " dt (default " << dt << ")";
		std::cout << " Nphotos (default " << Nphotos << ")";
		//std::cout << std::endl;
		return 1;
	}
	
	//Assign the given values to the parameters
	
	switch (argc) {
		case 1:
			break;
		case 2:
			input_path = argv[1];
			break;
		case 3:
			input_path = argv[1];
			ndays = atoi(argv[2]);
			break;
		case 4:
			input_path = argv[1];
			ndays = atoi(argv[2]);
			dt = atof(argv[3]);
			break;
			
		default:
			break;
	}
	
	//Read initial conditions
	std::ifstream input_file(input_path);
	SolarSystem system;
	system.ReadInitialConditions(input_file);
	input_file.close();
	
	//Set ODE solution method
	system.Method("VerletVelocity");
	
	//get planets
	auto planets = system.Planets();
	
	//Open output file
	std::ofstream output_file("output/temporal_evolution.txt");
	std::ofstream output_E("output/energy.txt");
	std::ofstream output_L("output/L.txt");
	
	//Print first line as a comment
	output_file << "#";
	
	//Print planets names
	for (const auto &p: planets){
		output_file << p.Name() << " ";
	}
	output_file << std::endl;
	
	//Do time evolution
	int Nsteps = ndays/dt;
	int M = (Nsteps>Nphotos)? Nsteps/Nphotos : 100;
	
	for (unsigned i=0; i<Nsteps; ++i){
		if (i%M==0){
			system.PrintSystemCoords(output_file);
			output_E << system.TotalEnergy() << std::endl;
			output_L << system.TotalAngularMomentum() << std::endl;
		}
		
		system.TimeStep(dt);
	}
	
	output_file.close();
	output_E.close();
	output_L.close();
	
	return 0;
}
