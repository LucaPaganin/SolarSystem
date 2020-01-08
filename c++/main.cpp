//
//  main.cpp
//
//
//  Created by Luca Paganin on 06/01/2020.
//

#include "Vettore3D.h"
#include "Grave.h"
#include "SistemaSolare.h"

int main(int argc, const char* argv[]){

	std::ofstream output_file("output/temporal_evolution.txt");

  Vettore3D r(1,2,3);
  Vettore3D v(1,2,3);
  double m=1;

  Grave g(r,v,m), g2(Vettore3D(0,0,0), Vettore3D(0,0,0), 2*m);

  std::vector<Grave> planets{g,g2};

  for (const auto &p: planets){
		auto index = &p - &planets[0];
		std::cout << "Planet " << index+1 << ": " << std::endl;
    std::cout <<  "Coordinates: (" << p.R() << "); Velocity: (" << p.V() << "); Mass = " << p.M() << std::endl;
  }

  /*
	std::ifstream input_file("input_file.h");


	SistemaSolare system;

	system.ReadInitialConditions(input_file);

	//system.print_system();

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
