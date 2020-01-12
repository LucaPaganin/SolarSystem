from matplotlib import pyplot as plt
import numpy as np
import mpl_toolkits.mplot3d.axes3d as p3
from matplotlib import animation
from pathlib import Path
import re
import json
import functions as fnc
import argparse

#Parameters parsing
parser = argparse.ArgumentParser()
parser.add_argument("-f", "--filename", required=False, default="temporal_evolution.txt" , help="The name of the file containing time evolution data.")
parser.add_argument("-p", "--planets", nargs="+", default=None, help="The list of the planets to be plotted.")
args = parser.parse_args()

filename = args.filename
planets = args.planets

#Setting up paths and load data into dictionary of numpy arrays
cwd = Path().resolve()
filepath = cwd.parent.joinpath("c++", "output", filename)
solar_system = fnc.load_from_file(filepath=filepath)

if planets is None:
    planets = list(solar_system.keys())

"""
Choose the planets to animate and put data into right form for animation
The data matrix for the given planet must have the following shape:
3 x Ntimesteps
"""

#Check if the chosen planets are in the list loaded from the file:
if not all([p in solar_system.keys() for p in planets]):
    print("Some of the planets you have chosen are not in the full list of available planets. The available planets are:")
    print(*list(solar_system.keys()), sep="\n")
    quit()

planets_data = [solar_system[k] for k in planets]

fig = plt.figure()
ax = p3.Axes3D(fig)

lines = []
for p in planets:
    line, = ax.plot(solar_system[p][0, 0:1],
                    solar_system[p][1, 0:1],
                    solar_system[p][2, 0:1],
                    label=p, markersize=5, marker='o', color=fnc.solar_system_colormap(p))
    lines.append(line)


limits = fnc.get_plot_limits(planets_data)

# Setting the axes properties
ax.set_xlabel('X [A.U.]')
ax.set_ylabel('Y [A.U.]')
ax.set_zlabel('Z [A.U.]')
ax.set_xlim3d([limits[0,0], limits[0,1]])
ax.set_ylim3d([limits[1,0], limits[1,1]])
ax.set_zlim3d([limits[2,0], limits[2,1]])

ax.legend(loc="lower left")

ani = animation.FuncAnimation(fig,
                              fnc.update_solar_system,
                              planets_data[0].shape[1],
                              fargs=(planets_data, lines),
                              interval=fnc.get_animation_interval(planets_data[0], 5),
                              blit=False)
#ani.save('matplot003.gif', writer='imagemagick')
plt.show()
