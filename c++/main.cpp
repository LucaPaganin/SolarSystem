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
#include <map>

void set_pars(const int argc, const char* argv[], std::string& input_path, double& ndays, double& dt, double& sampling_step){

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
	
}

void print_info(const std::string& input_path, double ndays, double dt, double sampling_step, int Nsteps, int Nsamples, int M){
	
	std::cout << "Input file with initial conditions: " << input_path << std::endl;
	std::cout << "Simulation timespan: " << ndays << " terrestrial days" << std::endl;
	std::cout << "Simulation timestep: " << dt << " terrestrial days" << std::endl;
	std::cout << "Simulation sampling timestep: " << sampling_step << " terrestrial days" << std::endl;
	std::cout << "Nsamples = " << Nsamples << std::endl;
	std::cout << "Nsteps = " << Nsteps << std::endl;
	std::cout << "M = Nsteps/Nsamples = " << M << std::endl;
	std::cout << "A photo of the system will be taken every " << M << " steps." << std::endl;
	std::cout << "Starting simulation..." << std::endl;
	
}

int main(const int argc, const char* argv[]){

	std::string input_path = "effemeridi.txt";
	double ndays = 365, dt = 0.1, sampling_step = 1.0;
	
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
	
	set_pars(argc, argv, input_path, ndays, dt, sampling_step);
	
	int Nsteps = ndays/dt, Nsamples = ndays/sampling_step, M = Nsteps/Nsamples;
	
	if( Nsamples > 10000 || Nsamples > Nsteps ){
		std::cout << "Error: maximum sampling exceeded. Reduce simulation time or increase sampling step" << std::endl;
		return 1;
	}
	
	//Print info messages with the simulation parameters:
	print_info(input_path, ndays, dt, sampling_step, Nsteps, Nsamples, M);

	//Read initial conditions
	SolarSystem system;
	std::ifstream input_file(input_path);
	system.ReadInitialConditions(input_file);
	input_file.close();
	//Set ODE solution method and time step
	system.Method("VerletVelocity");
	system.TimeStep(dt);
	
	//Manage output files
	std::map<std::string, std::ofstream*> Output_Files;
	
	std::vector<std::string>
	OutputFileTypes{
		"Coordinates",
		"TotalEnergy",
		"TotalAngularMomentum",
		"SingleEnergies",
		"SingleAngularMomenta"
	};
	
	for (const auto& type: OutputFileTypes){
		Output_Files[type] = new std::ofstream(("output/" + type + ".txt").c_str());
	}

	//Print header with planets' names
	for (auto it = Output_Files.begin(); it != Output_Files.end(); ++it) {
		system.PrintData(*(it->second), "Names");
	}

	//Do time evolution
	for (int i=0; i<Nsteps; ++i){
		if (i%M==0){
			for (auto it = Output_Files.begin(); it != Output_Files.end(); ++it) {
				system.PrintData(*(it->second), it->first);
			}
		}
		system.DoTimeStep();
	}

	std::cout << "Done." << std::endl;

	for (auto it = Output_Files.begin(); it != Output_Files.end(); ++it) {
		(it->second)->close();
		delete it->second;
	}

	return 0;
}
