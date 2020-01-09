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

	std::ofstream output_file("output/test_time_evolution.txt");

	//std::ofstream out_coords("output/coords.txt"), out_vels("output/vels.txt"), out_fields("output/fields.txt");

	/*

	Vector3D EarthPos(-2.892698924363897E-01,
					  9.483553307419959E-01,
					  -1.652548618901187E-05);

	Vector3D EarthSpeed(-1.674611909353826E-02,
	-5.062528512469250E-03,
	-1.030143695482691E-07);

	Vector3D SunPos(-3.857022300275326E-03,
	7.425738921434983E-03,
	2.464082047600554E-05);

	Vector3D SunSpeed(-8.334249208811721E-06,
	-2.062229084310973E-06,
	2.298339656433683E-07);


	double EarthMass = 3.0026093514328813e-06;
	double SunMass = 1.0;


	PointMass Earth(EarthPos, EarthSpeed, EarthMass);
	PointMass Sun(SunPos, SunSpeed, SunMass);


	std::vector<PointMass> test_planets{Sun,Earth};

	SolarSystem test_sys(test_planets, "");
	*/

	SolarSystem test_system;

	std::ifstream input_file("test_input.h");

	test_system.ReadInitialConditions(input_file);

	input_file.close();

	int Nsteps=1000;
	double dt=1;

	for (unsigned i=0; i<Nsteps; ++i){
		auto planets = test_system.Planets();
		test_system.PrintSystemCoords(output_file);
		test_system.EulerCromerStep(dt);

		/*

		out_coords << planets[0].R() << " " << planets[1].R() << std::endl;
		out_vels << planets[0].V() << " " << planets[1].V() << std::endl;
		out_fields << planets[0].GravitationalField(planets[1]) << " ";
		out_fields << planets[1].GravitationalField(planets[0]) << std::endl;
		*/

	}

	/*
	//Close various outputfiles
	out_coords.close();
	out_vels.close();
	out_fields.close();
	*/
	//Close output file
	output_file.close();
	return 0;
}
