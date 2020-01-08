import os
from pathlib import Path
import matplotlib.pyplot as plt
import numpy as np
import json

cwd = Path(os.getcwd())
datafile_path = cwd.parent / "c++" / "output" / "temporal_evolution.txt"

data = np.loadtxt(datafile_path)

n_planets = int(data.shape[1]/3)

planet_coords = [data[0:100,i:i+3] for i in range(n_planets)]

color_list = ["r","g","b"]

for pc, c in zip(planet_coords[0:4], color_list):
    plt.scatter(pc[:,0], pc[:,1], color = c)
plt.show()
