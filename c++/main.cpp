//
//  main.cpp
//  
//
//  Created by Luca Paganin on 06/01/2020.
//

#include "Vettore3D.h"
#include "Grave.h"
#include "SistemaSolare.h"

int main(){
	
	std::ifstream input_file("input_file.h");
	std::ofstream output_file("output.txt");
	
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
	output_file.close();
	
	
	return 0;
}
