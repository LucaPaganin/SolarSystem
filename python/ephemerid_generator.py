import os
import re
import json
from pathlib import Path
import sys

def clean_planetdata(planetdata=None):

    for k, v in planetdata.items():
        if isinstance(v, list) and len(v)>0:
            planetdata[k] = v[0]

    return planetdata

def get_mass_ratio(line=None):
    mass_ratio = None

    if line is not None:
        regex = "Mass ratio.*=\s+(([0-9]|\.)+)"
        match = re.search(regex, line)
        if match:
            mass = float(match.groups()[0])

    return mass

def get_mass(line=None):
    #Return mass in Solar masses
    Sun_mass = 1.9885
    Sun_exponent = 30
    mass = None
    exponent = None

    if line is not None:
        line = re.sub(" ","",line)
        #print(line)
        regex="Massx10\^(2[0-9])\(kg\)=(([0-9]|\.)+)"
        match = re.search(regex, line)

        if match:
            exponent = int(match.groups()[0])
            mass = float(match.groups()[1])

    #print(f"Mass = {mass} x 10^{exponent} kg")
    value = None
    if mass is not None and exponent is not None:
        mass = mass/Sun_mass
        exponent -= Sun_exponent
        value = mass*10**exponent

    return value

def get_name(line=None):
    name = None
    if line is not None:
        regex = "[0-9]{4}\s+([a-zA-Z]+)"

        match = re.search(regex, line)

        if match:
            name = match.groups()[0]
            #print(name)

    return name

def get_coords(line=None):
    coords = [x.strip() for x in re.split("[XYZ] =", line)]

    num_coords = [float(x) for x in coords[1:]]

    return num_coords

def get_velocities(line=None):
    vels = [x.strip() for x in re.split("V[XYZ]=", line)]

    num_vels = [float(x) for x in vels[1:]]

    return num_vels

def num_regexp():
    return "([0-9]|E|\.|-|\+)+"


def get_lines_fromfile(filepath=None):

    #Define keys and values for template_dict
    keys = ["Name", "Mass", "Coordinates", "Velocities", "Mass_Ratio"]
    keys.sort()
    values = [None]*len(keys)

    #Define regexps
    regexps = dict((k,None) for k in keys)
    regexps["Name"] = "^Revised.*([a-zA-Z]+)"
    regexps["Mass"] = "\s*Mass x10\^(2[0-9]).*=\s+(([0-9]|\.)+)"
    regexps["Mass_Ratio"] = "Mass ratio.*=\s+(([0-9]|\.)+)"
    regexps["Coordinates"] = "^(X|Y|Z)\s*=\s*(([0-9]|\.|E|-)+)"
    regexps["Velocities"] = "(VX|VY|VZ)\s*=\s*(([0-9]|\.|E|-)+)"

    #Define matched_lines with an empty list for each key
    matched_lines = dict((k,[]) for k in keys)

    with open(filepath, "r") as infile:
        lines = infile.readlines()

        for l in lines:
            for key, regexp in regexps.items():
                match = re.search(regexp, l)
                if match:
                    matched_lines[key].append(l.strip())

    first_matched_lines = dict((k,l[0]) for k,l in matched_lines.items() if len(l)>0)

    name = get_name(first_matched_lines["Name"])
    coords = get_coords(first_matched_lines["Coordinates"])
    vels = get_velocities(first_matched_lines["Velocities"])
    mass_ratio = None
    mass = None
    if "Mass_Ratio" in first_matched_lines.keys():
        mass_ratio = get_mass_ratio(first_matched_lines["Mass_Ratio"])
    if "Mass" in first_matched_lines.keys():
        #print(name)
        mass = get_mass(first_matched_lines["Mass"])

    data = dict((k,None) for k in first_matched_lines.keys())

    data["Name"] = name
    #if "Mass" in first_matched_lines.keys(): data["Mass"] = first_matched_lines["Mass"]
    data["Mass"] = mass
    data["Mass_Ratio"] = mass_ratio
    data["Coordinates"] = coords
    data["Velocities"] = vels

    return data


cwd = Path().resolve()

filesdir = cwd.parent / "Ephemerids" / "data"

filelist = list(filesdir.glob("*.txt"))
filelist.sort()

data = dict((k,None) for k in [f.name for f in filelist])

#print(list(data.keys()))

for k,file in zip(data.keys(), filelist):
    #print(json.dumps(get_lines_fromfile(filepath=file), indent=2))
    data[k] = get_lines_fromfile(filepath=file)

#print(json.dumps(data, indent=2))
"""
with open("planets_data.json", "w") as outfile:
    json.dump(data, outfile, indent=2)
"""

with open("effemeridi.txt", "w") as outfile:
    for k in data.keys():
        outfile.write("{}\n".format(data[k]["Name"]))
        outfile.write("{}\n".format(data[k]["Mass"]))
        outfile.write("{} {} {}\n".format(data[k]["Coordinates"][0], data[k]["Coordinates"][1], data[k]["Coordinates"][2]))
        outfile.write("{} {} {}\n".format(data[k]["Velocities"][0], data[k]["Velocities"][1], data[k]["Velocities"][2]))
