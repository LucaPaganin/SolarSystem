import os
from pathlib import Path
import matplotlib.pyplot as plt
import numpy as np

cwd = Path(os.getcwd())
datafile_path = cwd.parent / "c++" / "output" / "temporal_evolution.txt"

data = np.loadtxt(datafile_path)

planet_coords = []

for i in range(11):
    planet_coords.append([data[:,i], data[:,i+1], data[:,i+2]])
