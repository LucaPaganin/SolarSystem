from matplotlib import pyplot as plt
import numpy as np
import mpl_toolkits.mplot3d.axes3d as p3
from matplotlib import animation
from pathlib import Path
import re
import json

def load_from_file(filepath=None):

    """!
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
    solar_system = dict(zip(names, [data[:,3*i:3*i+3].T for i in range(len(names))]))

    return solar_system

def update_solar_system(num, planets_data, lines):
    for data, line in zip(planets_data, lines):
        line.set_data(data[:2, :num])
        line.set_3d_properties(data[2, :num])
    return lines

def get_plot_limits(planets_data):
    #Takes a list of 3 x Nsteps matrices
    limits = np.zeros((3,2))

    """!
    Set limits in 3x2 matrix like this
    limits =
    [[xmin, xmax],
     [ymin, ymax],
     [zmin, zmax]]
    """

    for i in range(3):
        limits[i,0] = planets_data[0][i,:].min()
        limits[i,1] = planets_data[0][i,:].max()

    for pdata in planets_data:
        for i in range(3):
            min = pdata[i,:].min()
            max = pdata[i,:].max()

            if min <= limits[i,0]:
                limits[i,0] = min
            if max >= limits[i,1]:
                limits[i,1] = max

    return limits

def get_animation_interval(data, duration):
    """!
    data: numpy matrix with a planet data
    duration: time duration of the animation in seconds
    """

    shape = np.array(data.shape)
    Nsteps = shape.max()

    dt = 1000*duration/Nsteps

    return dt

def solar_system_colormap(name):

    color_map = {"Sun": "gold",
                 "Mercury": "grey",
                 "Venus": "green",
                 "Earth": "lightblue",
                 "Mars": "red",
                 "Jupiter": "orange",
                 "Saturn": "purple",
                 "Uranus":"cyan",
                 "Neptune": "blue",
                 "Pluto": "brown"}

    return color_map[name]
