# SolarSystem

This is a repository hosting some C++/Python code which computes the time evolution of a Solar System, starting from some initial conditions provided into an input txt file with the following form:
```
Planet1  
Mass_1  
X1 Y1 Z1  
VX1 VY1 VZ1  
Planet2  
Mass_2  
X2 Y2 Z2  
VX2 VY2 VZ2  
...  
```

With Xi, Yi, Zi being the initial coordinates of the planet i, and VXi, VYi, VZi being the initial velocities. Clearly Mass_i is the mass of the planet i.
The units of measure with respect to which each quantity MUST be expressed are: 
* Astronomical Units for the Length;
* Solar Masses for the Mass;
* Terrestrial Days for the Time.

Exercise: in which units will be expressed the velocity with this choice? Which value will have the Gravitational constant G, which in the International System of units is

G = 6.67408 x 10^-11 m^3 kg^-1 s^-2

In order to start using the code download this folder clicking on the green button saying "Download as ZIP", extract the content and move it to your home directory; the extracted content should be a directory named like "SolarSystem-master". Then open a terminal and type the following command

```
cd <name-of-extracted-directory>
```

Great! Now you are into the directory previously extracted. Now you have to install the simulator program: in order to do this type the command:

```  
python3 installer.py
```

You should see something like:
  
```
  Creating object directory /Users/lucapaganin/SolarSystem/c++/obj  
  Creating output directory /Users/lucapaganin/SolarSystem/c++/output  
  Changing directory to /Users/lucapaganin/SolarSystem/c++  
  Compiling C++ code...  
  g++ -std=c++11 -Wall -g -I inc/ -c -o obj/main.o main.cpp  
  g++ -std=c++11 -Wall -g -I inc/ -c -o obj/PointMass.o src/PointMass.cpp  
  g++ -std=c++11 -Wall -g -I inc/ -c -o obj/SolarSystem.o src/SolarSystem.cpp  
  g++ -std=c++11 -Wall -g -I inc/ -c -o obj/Vector3D.o src/Vector3D.cpp  
  g++ -std=c++11 -Wall -g -I inc/ -o main obj/main.o obj/PointMass.o obj/SolarSystem.o obj/Vector3D.o  
  Returning to previous directory /Users/lucapaganin/SolarSystem  
  Done.  
```

  
Now the program is correctly installed. You are ready to do your first solar system simulation! In order to do this, in the terminal window change directory into the directory named "c++":

```
  cd c++
```
  
  Once here type the command:
  
```
  ls
```  
  you should see a list of the files and directories contained in the c++ directory, and in particular there should be a file named main. It is the executable which does the simulation; in order to launch it type:

```
  ./main 
```  
  The output on the terminal window should be
```
  Input file with initial conditions: effemeridi.txt
  Simulation timespan: 365 terrestrial days  
  Simulation timestep: 0.1 terrestrial days  
  Simulation sampling timestep: 1 terrestrial days  
  Nsamples = 365  
  Nsteps = 3650  
  M = Nsteps/Nsamples = 10  
  A photo of the system will be taken every 10 steps.  
  Starting simulation...  
  Done.
```

You have completed your first Solar System time evolution! To see an animation which shows the planets moving I suggest you to create another terminal window with the following keyboard shortcut

```
Ctrl + Shift + T
```

Check where you are typing 

```
pwd
```

The result should end with "c++". If it is so you should change your directory typing

```
cd ../python
```

Now you are in the directory python. Do an `ls` to check for a file named `3danimate.py`. If it is present type the command

```
python3 3danimate.py -p Sun Earth Mars
```

You should see a 3D animation with the Earth and Mars orbiting around the Sun (do not pay attention to the colors...).
