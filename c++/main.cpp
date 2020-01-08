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
	
	std::ofstream output_file("output/temporal_evolution.txt");
    
    Vettore3D r(1,2,3);
    Vettore3D v(1,2,3);
    double m=1;

    Grave g(r,v,m);

    std::vector<Grave> planets{g};

    for (auto p: planets){
        std::cout << p.R() << " " << p.V() << " " << p.M() << std::endl;
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
	output_file.close();
	*/
	
	return 0;
}
