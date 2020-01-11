from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
from pathlib import Path
import matplotlib
import argparse
import re

"""
Set up dictionary with temporal evolution matrix for each planet:
    - The key will be the planet name
    - The value will be a numpy array with Nphotos rows and 3 columns, where:
        * Nphotos is the number of photographs of the system taken during the time evolution
        * the 3 columns contain the 3 coordinates X,Y,Z of the given planet

The form of the input data file is assumed to be as follows:
#Planet_1 Planet_2 ... Planet_nplanets
x_1(t0) y_1(t0) z_1(t0) x_2(t0) y_2(t0) z_2(t0) ... x_nplanets(t0) y_nplanets(t0) z_nplanets(t0)
x_1(t1) y_1(t1) z_1(t1) x_2(t1) y_2(t1) z_2(t1) ... x_nplanets(t1) y_nplanets(t1) z_nplanets(t1)
.
.
.
x_1(tN) y_1(tN) z_1(tN) x_2(tN) y_2(tN) z_2(tN) ... x_nplanets(tN) y_nplanets(tN) z_nplanets(tN)
"""

def load_from_file(filepath=None):

    #Read names from first line, assuming it is a comment starting with #
    names = None
    with open(filepath, "r") as datafile:
        line = datafile.readline().strip()
        line = re.sub("#", "", line)
        names = line.split()

    #Load data into numpy array, skipping the first row
    data = np.loadtxt(filepath)

    if not(len(names)==int(data.shape[1]/3)):
        print(f"Provided file {Path(filepath).name} has got invalid format; first line must contain exactly one third of the numeric columns.")
        quit()

    #Create solar system dictionary
    solar_system = dict(zip(names, [data[:,3*i:3*i+3] for i in range(len(names))]))

    return solar_system


#Parameters parsing
parser = argparse.ArgumentParser()
parser.add_argument("-f", "--filename", required=False, default="temporal_evolution.txt" , help="The name of the file containing time evolution data.")
parser.add_argument("-p", "--planets", nargs="+", default=None, help="The list of the planets to be plotted.")
args = parser.parse_args()

filename = args.filename
planets = args.planets

#Setting up paths
cwd = Path().resolve()
filepath = cwd.parent.joinpath("c++", "output", filename)

solar_system = load_from_file(filepath=filepath)

if planets is None:
    planets = list(solar_system.keys())

#Check if the chosen planets are in the list loaded from the file:
if not all([p in solar_system.keys() for p in planets]):
    print("Some of the planets you have chosen are not in the full list of available planets. The available planets are:")
    print(*list(solar_system.keys()), sep="\n")
    quit()

#Set up plot machinery
colors = matplotlib.cm.rainbow(np.linspace(0, 1, len(planets)))
fig = plt.figure(figsize = (10,6))
ax = fig.add_subplot(111, projection='3d')

#For each planet set up
for pname, c in zip(planets, colors):
    ax.plot(solar_system[pname][:,0], solar_system[pname][:,1], solar_system[pname][:,2] , c=c, marker='o', label=pname)

ax.set_xlabel('X [A.U.]')
ax.set_ylabel('Y [A.U.]')
ax.set_zlabel('Z [A.U.]')

ax.legend(loc="upper right")

plt.show()
