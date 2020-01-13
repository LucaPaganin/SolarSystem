from pathlib import Path
import os
import re
import argparse

cwd = Path(os.getcwd())

parser = argparse.ArgumentParser(description="A launcher for a solar system simulation.")

parser.add_argument("-i", "--inputfile", required=False, default="effemeridi.txt", metavar="str", help="Name of the file with the initial conditions.")

parser.add_argument("-d", "--ndays", required=False, default=None, metavar="float",
                    help="Time duration of the simulation in days. If specified with nyears and nmonths the result will be the sum of the requested time intervals")

parser.add_argument("-m", "--nmonths", required=False, default=None, metavar="float",
                    help="Time duration of the simulation in months. If specified with ndays and nyears the result will be the sum of the requested time intervals")

parser.add_argument("-y", "--nyears", required=False, default=None, metavar="float",
                    help="Time duration of the simulation in years. If specified with ndays and nmonths the result will be the sum of the requested time intervals")

parser.add_argument("-dt", "--timestep", required=False, default=0.1, metavar="float",
                    help="Time step of the simulation")

args = parser.parse_args()
