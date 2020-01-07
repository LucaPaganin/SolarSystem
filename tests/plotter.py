import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("sample.txt")

for i in range(5):
    print(data[:,i], data[:,i+1])
