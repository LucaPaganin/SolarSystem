# SolarSystem

This is a repository hosting some C++/Python code which computes the time evolution of a Solar System, starting from some initial conditions provided into an input txt file with the following form:

Planet1
Mass_1
X1 Y1 Z1
VX1 VY1 VZ1
Planet2
Mass_2
X2 Y2 Z2
VX2 VY2 VZ2
...

With Xi, Yi, Zi being the initial coordinates of the planet i, and VXi, VYi, VZi being the initial velocities. Clearly Mass_i is the mass of the planet i.
The units of measure with respect to which each quantity MUST be expressed are: 
* Astronomical Units for the Length;
* Solar Masses for the Mass;
* Terrestrial Days for the Time.
