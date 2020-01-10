from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
from pathlib import Path
import matplotlib
import argparse

#Setting up paths
cwd = Path().resolve()
data_file = cwd.parent.joinpath("c++", "output", "temporal_evolution.txt")
names_file = cwd.parent.joinpath("c++", "output", "planets_names.txt")

#Load data into numpy arrays
data = np.loadtxt(data_file)
names = np.loadtxt(names_file, dtype="str")
all_planets = list(names)

if (int(data.shape[1]/3) != int(len(names))):
    print(f"""Inconsistency between number of planets in the name file
    {names_file.name} and number of coordinates list in the data file {data_file.name}""")
    quit()

"""
Set up dictionary with temporal evolution matrix for each planet:
    - The key will be the planet name
    - The value will be a numpy array with Nphotos rows and 3 columns, where:
        * Nphotos is the number of photographs of the system taken during the time evolution
        * the 3 columns contain the 3 coordinates X,Y,Z of the given planet

The form of the input data file is assumed to be as follows:

x1(t0) y1(t0) z1(t0) x2(t0) y2(t0) z2(t0) ... xn_planets(t0) yn_planets(t0) zn_planets(t0)
x1(t1) y1(t1) z1(t1) x2(t1) y2(t1) z2(t1) ... xn_planets(t1) yn_planets(t1) zn_planets(t1)
.
.
.
x1(tN) y1(tN) z1(tN) x2(tN) y2(tN) z2(tN) ... xn_planets(tN) yn_planets(tN) zn_planets(tN)
"""
solar_system = dict(zip(all_planets, [data[:,3*i:3*i+3] for i in range(len(all_planets))]))

#Parameters parsing
parser = argparse.ArgumentParser()
parser.add_argument("-p", "--planets", nargs="+", default=all_planets, help="The list of the planets to be plotted.")
args = parser.parse_args()


#Set up data
planets_names = args.planets

#Check if the chosen planets are in the list loaded from the file:
if not all([p in all_planets for p in planets_names]):
    print("Some of the planets you have chosen are not in the full list of available planets. The available planets are:")
    print(*all_planets, sep="\n")
    quit()

#Set up plot machinery
colors = matplotlib.cm.rainbow(np.linspace(0, 1, len(planets_names)))
fig = plt.figure(figsize = (10,6))
ax = fig.add_subplot(111, projection='3d')

#For each planet set up
for pname, c in zip(planets_names, colors):
    ax.plot(solar_system[pname][:,0], solar_system[pname][:,1], solar_system[pname][:,2] , c=c, marker='o', label=pname)

ax.set_xlabel('X [A.U.]')
ax.set_ylabel('Y [A.U.]')
ax.set_zlabel('Z [A.U.]')

ax.legend(loc="upper right")

plt.show()
