#include<iostream>
#include<fstream>
#include<string>

int main(){
    
    std::string name;
    double mass,x,y,z,vx,vy,vz;

    std::ifstream ifile("input_file.h");

    while(ifile >> name >> mass >> vx >> x >> vy >> y >> vz >> z){
        std::cout << name << std::endl;
        Vettore3D r(x,y,z), v(vx,vx,vz);
        std::cout << "Mass: " << mass << std::endl;
        std::cout << "Coordinates: " << r << std::endl;
        std::cout << "Velocity: " << v << std::endl;
    }

    return 0;

}
