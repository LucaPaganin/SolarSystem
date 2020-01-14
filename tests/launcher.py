from pathlib import Path
import os
import re
import argparse

cwd = Path(os.getcwd())
cppdir = cwd / "c++"
pythondir = cwd / "python"

parser = argparse.ArgumentParser(description="A launcher for a solar system simulation.",
                                 formatter_class=argparse.ArgumentDefaultsHelpFormatter)

parser.add_argument("-i", "--inputfile", required=False, default="effemeridi.txt", metavar="str", help="Name of the file with the initial conditions.")

parser.add_argument("-d", "--ndays", required=False, default=0, metavar="float",
                    help="Time duration of the simulation in days. If specified with nyears and nmonths the result will be the sum of the requested time intervals")

parser.add_argument("-m", "--nmonths", required=False, default=0, metavar="float",
                    help="Time duration of the simulation in months. If specified with ndays and nyears the result will be the sum of the requested time intervals")

parser.add_argument("-y", "--nyears", required=False, default=0, metavar="float",
                    help="Time duration of the simulation in years. If specified with ndays and nmonths the result will be the sum of the requested time intervals")

parser.add_argument("-dt", "--timestep", required=False, default=0.1, metavar="float",
                    help="Time step of the simulation, in days.")

parser.add_argument("-phdt", "--sampling_step", required=False, default=1, metavar="float",
                    help="Time step for sampling the system configuration, in days.")

parser.add_argument("-p", "--planets", required=False, default=None, nargs="+",
                    help="Planets to be shown in the animation. If not specified all planets will be shown.")

args = parser.parse_args()

#Extract parameters into variables
inputfile = args.inputfile
ndays = float(args.ndays)
nmonths = float(args.nmonths)
nyears = float(args.nyears)
timestep = float(args.timestep)
sampling_step = float(args.sampling_step)
chosen_planets = args.planets

input_path = cppdir / inputfile

if not input_path.exists():
    print(f"Error: file {inputfile} not found into directory {cppdir}.")
    quit()

planets = []

with open(input_path, "r") as infile:
    lines = infile.readlines()
    for l in lines:
        match = re.search("^([a-zA-Z]+)$", l)

        if match:
            planets.append(match.groups()[0])

if not all([p in planets for p in chosen_planets]):
    print("Error: some of the chosen planets are not present in the inputfile {}".format(inputfile))
    quit()

#print(" ".join(planets))

sim_duration = int(ndays + 30 * nmonths + 365 * nyears)

if sim_duration <= 0:
    print("Error: chosen simulation time cannot be zero or less.")
    quit()

if timestep <= 0 or timestep >= sim_duration:
    print("Error: timestep cannot be zero or negative or greater than simulation duration.")
    quit()

nsteps = sim_duration/timestep
nphotos = sim_duration/sampling_step

if nphotos >= 5000 or nphotos >= nsteps:
    print("Error: number of possible samplings exceeded.")
    quit()


print("Chosen inputfile: %s"%inputfile)
print("Chosen simulation duration: %s days"%sim_duration)
print("Chosen simulation timestep: %s days"%timestep)
print("Chosen sampling_step: %s days"%sampling_step)


print("Starting simulation:")
#Call c++ executable to do the simulation
cmd = f"{cppdir / 'main'} {cppdir / inputfile} {sim_duration} {timestep} {sampling_step}"
print(cmd)
os.system(cmd)

print("Done.")
print("Starting animation")

timeevo_filepath = cppdir.joinpath("output", "temporal_evolution.txt")

cmd = f"python3 {pythondir / '3danimate.py'} --filepath {timeevo_filepath} -p " + " ".join(chosen_planets)

os.system(cmd)
