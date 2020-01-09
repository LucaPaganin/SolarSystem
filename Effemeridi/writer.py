import os
from pathlib import Path

cwd = Path().resolve()

filelist = (cwd.parent.joinpath("Effemeridi", "Ephemerids")).glob("*.txt")

for f in filelist:
    output_file = f.name

    with open(f, "r") as infile, open(output_file, "w") as outfile:
        lines = infile.readlines()

        for l in lines:
            l = l.strip()
            outfile.write(f"{l}\n")
