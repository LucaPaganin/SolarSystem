import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("output.txt")

planet_coords = []

for i in range(11):
    planet_coords.append([data[:,i], data[:,i+1], data[:,i+2]])


