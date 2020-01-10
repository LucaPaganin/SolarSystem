import numpy as np
import os
from pathlib import Path
import matplotlib.pyplot as plt

cwd = Path().resolve()

filename = "temporal_evolution.txt"

coordfile = cwd.parent.joinpath("c++", "output", filename)

data = np.loadtxt(coordfile)

p1_coords = data[:,0:3]
p2_coords = data[:,3:6]

#print(p1_coords[:,0])
#print(p2_coords[:,0])

plt.scatter(p1_coords[:,0], p1_coords[:,1],color='r')
plt.scatter(p2_coords[:,0], p2_coords[:,1],color='b')
plt.show()
