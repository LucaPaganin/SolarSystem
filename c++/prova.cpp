#include<iostream>
#include<fstream>
#include<string>
#include "Vettore3D.h"
#include "Grave.h"
#include "SistemaSolare.h"

int main(){
    
    std::ifstream ifile("input_file.h");
    
    std::vector<Grave> planets;

    double mass,x,y,z,vx,vy,vz;
    
    std::string name;
     
    while(ifile >> name >> mass >> vx >> x >> vy >> y >> vz >> z)
    {
        Vettore3D r(x,y,z), v(vx,vy,vz);
        std::cout << "name = " << name << std::endl;
        std::cout << "r = " << r << std::endl;
        std::cout << "v = " << v << std::endl;
        std::cout << "mass = " << mass << std::endl;
    }
    

    SistemaSolare sys(planets,"");

    return 0;
}
