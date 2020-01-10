import os
from pathlib import Path
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import json

data_filename = "temporal_evolution.txt"
names_filename = "planets_names.txt"

cwd = Path(os.getcwd())
names_filepath = cwd.parent / "c++" / "output" / names_filename
datafile_path = cwd.parent / "c++" / "output" / data_filename

names = np.loadtxt(names_filepath, dtype="str")
data = np.loadtxt(datafile_path)

n_planets = int(data.shape[1]/3)

#print(n_planets)

"""
Here we are picking the wrong coordinates!! We are collecting the following:
x1 y1 z1, y1 z1 x2, z1 x2 y2... and so on
Need to put a factor 3 in front of index i of subrange i:i+3
"""
planet_coords = [data[:,3*i:3*i+3] for i in range(n_planets)]

#print(planet_coords[0])

colors = matplotlib.cm.rainbow(np.linspace(0, 1, n_planets))

fig = plt.figure(figsize=(10,6))

for pc, c, name in zip(planet_coords, colors, names):
    plt.scatter(pc[:,0], pc[:,1], color = c, label = name)

plt.xlabel("x [A.U.]")
plt.ylabel("y [A.U.]")
plt.legend(loc="lower left")
plt.show()
