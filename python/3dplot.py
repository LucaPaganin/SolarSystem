from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
from pathlib import Path
import matplotlib
import argparse
import re
import functions as fnc

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

solar_system = fnc.load_from_file(filepath=filepath)

if planets is None:
    planets = list(solar_system.keys())

#Check if the chosen planets are in the list loaded from the file:
if not all([p in solar_system.keys() for p in planets]):
    print("Some of the planets you have chosen are not in the full list of available planets. The available planets are:")
    print(*list(solar_system.keys()), sep="\n")
    quit()

#Set up plot machinery
fig = plt.figure(figsize = (10,6))
ax = fig.add_subplot(111, projection='3d')

colors = matplotlib.cm.rainbow(np.linspace(0, 1, len(planets)))

#For each planet set up
for pname, c in zip(planets, colors):
    ax.plot(solar_system[pname][0,:],
            solar_system[pname][1,:],
            solar_system[pname][2,:],
            color=c,
            marker='o',
            label=pname)

ax.set_xlabel('X [A.U.]')
ax.set_ylabel('Y [A.U.]')
ax.set_zlabel('Z [A.U.]')

ax.legend(loc="upper right")

plt.show()
