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
	auto sampling_step = 1.0;

	//Error message if argc > 5
	if (argc > 5) {
		std::cout << "Too many parameters. Usage is: " << argv[0];
		std::cout << " input_filename (default " << input_path << ")";
		std::cout << " simulation_timespan (default " << ndays << ")";
		std::cout << " timestep (default " << dt << ")";
		std::cout << " sampling_step (default " << sampling_step << ")";
		std::cout << std::endl;
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
		case 5:
			input_path = argv[1];
			ndays = atoi(argv[2]);
			dt = atof(argv[3]);
			sampling_step = atof(argv[4]);
			break;

		default:
			break;
	}

	//Print info messages with the simulation parameters:

	std::cout << "Input file with initial conditions: " << input_path << std::endl;
	std::cout << "Simulation timespan: " << ndays << " terrestrial days" << std::endl;
	std::cout << "Simulation timestep: " << dt << " terrestrial days" << std::endl;
	std::cout << "Simulation sampling timestep: " << sampling_step << " terrestrial days" << std::endl;

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
	std::ofstream output_E("output/Total_Energy.txt");
	std::ofstream output_L("output/Total_L.txt");
	std::ofstream output_energies("output/Single_Energies.txt");
	std::ofstream output_Ls("output/Single_AngularMomenta.txt");

	//Print first line as a comment
	output_file << "#";
	output_energies << "#";
	output_Ls << "#";

	//Print planets names
	for (const auto &p: planets){
		output_file << p.Name() << " ";
		output_energies << p.Name() << " ";
		output_Ls << p.Name() << " ";
	}
	output_file << std::endl;
	output_energies << std::endl;

	//Do time evolution
	int Nsteps = ndays/dt;
	int Nsamples = ndays/sampling_step;

	if( Nsamples > 5000 || Nsamples > Nsteps ){
		std::cout << "Error: maximum sampling exceeded. Reduce simulation time or increase sampling step" << std::endl;
		return 1;
	}

	int M = Nsteps/Nsamples;

	std::cout << "Nsamples = " << Nsamples << std::endl;
	std::cout << "Nsteps = " << Nsteps << std::endl;
	std::cout << "M = Nsteps/Nsamples = " << M << std::endl;
	std::cout << "A photo of the system will be taken every " << M << " steps." << std::endl;
	std::cout << "Starting simulation..." << std::endl;

	for (int i=0; i<Nsteps; ++i){
		if (i%M==0){
			auto my_planets = system.Planets();
			auto energies = system.ComputeEnergies();
			system.PrintSystemCoords(output_file);
			output_E << i*dt << " " << system.TotalEnergy() << std::endl;
			output_L << i*dt << " " << system.TotalAngularMomentum().mod() << std::endl;
			output_energies << i*dt << " ";
			output_Ls << i*dt << " ";
			for (const auto &e: energies){
				output_energies << e << " ";
			}
			output_energies << std::endl;
			for (const auto &p: my_planets){
				output_Ls << p.AngularMomentum() << " ";
			}
			output_Ls << std::endl;
		}

		system.TimeStep(dt);
	}

	std::cout << "Done." << std::endl;

	output_file.close();
	output_E.close();
	output_L.close();
	output_energies.close();
	output_Ls.close();

	return 0;
}
