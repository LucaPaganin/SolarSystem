import numpy as np

def convert(A, direction=None):

    SI_val = A[0]
    dims = A[1]

    if not isinstance(dims, dict):
        print("Error: dims is not a dictionary")
        quit()
    else:
        keys = list(dims.keys())
        if keys != ["L","M","T"]:
            print("Incorrect dimension keys")
            quit()

    if isinstance(SI_val, list):
        SI_val = np.array(SI_val)

    return SI_val * conversion_factor(dims=dims, direction=direction)

def conversion_factor(dims=None, direction=None):
    a = dims["L"]
    b = dims["M"]
    c = dims["T"]

    conv = units["L"]**(-a) * units["M"]**(-b) * units["T"]**(-c)

    if direction == "SI_to_new":
        pass
    elif direction == "new_to_SI":
        conv = conv**(-1)

    return conv


G = 6.67384e-11
ul = 1.4959787066e11
um = 1.989e30
ut = 86400

#New units in SI units
#So ul = AU/meters, um = MSun/kg, ut = d/s
units = {"L": ul, "M": um, "T": ut}

GravitationalConstant = [G, {"L": 3, "M": -1, "T":-2}]
LengthUnit = [units["L"], {"L":1, "M":0, "T":0}]
MassUnit = [units["M"], {"L":0, "M":1, "T":0}]
TimeUnit = [units["T"], {"L":0, "M":0, "T":1}]

EarthMass = [5.97219e24, {"L":0, "M":1, "T":0}]
EarthPos = [np.array([-2.892698924363897E-01,9.483553307419959E-01,-1.652548618901187E-05]), {"L":1, "M":0, "T":0}]
EarthSpeed = [np.array([-1.674611909353826E-02,-5.062528512469250E-03,-1.030143695482691E-07]), {"L":1, "M":0, "T":-1}]

print("Earth position and velocity in SI units")
print(convert(EarthPos, direction="new_to_SI"))
print(convert(EarthSpeed, direction="new_to_SI"))

print("Earth Mass in new units:")
print(convert(EarthMass, direction="ST_to_new"))
