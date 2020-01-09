import os
from pathlib import Path
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import json

filename = "test_time_evolution.txt"

cwd = Path(os.getcwd())
datafile_path = cwd.parent / "c++" / "output" / filename

data = np.loadtxt(datafile_path)

n_planets = int(data.shape[1]/3)

"""
Here we are picking the wrong coordinates!! We are collecting the following:
x1 y1 z1, y1 z1 x2, z1 x2 y2... and so on
Need to put a factor 3 in front of index i of subrange i:i+3
"""
planet_coords = [data[:,i:i+3] for i in range(n_planets)]

print(planet_coords[0])

colors = matplotlib.cm.rainbow(np.linspace(0, 1, n_planets))

for pc, c in zip(planet_coords, colors):
    plt.scatter(pc[:,0], pc[:,1], color = c)
plt.show()
