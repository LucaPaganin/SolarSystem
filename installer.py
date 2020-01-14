import os
from pathlib import Path

cwd = Path(os.getcwd())
cppdir = cwd / "c++"

objdir = cwd.joinpath("c++", "obj")
outputdir = cwd.joinpath("c++", "output")

if not objdir.exists():
    print(f"Creating object directory {objdir}")
    objdir.mkdir()

if not outputdir.exists():
    print(f"Creating output directory {outputdir}")
    outputdir.mkdir()

print(f"Changing directory to {cppdir}")
os.chdir(cppdir)
print(f"Compiling C++ code...")
os.system("make")
print(f"Returning to previous directory {cwd}")
os.chdir(cwd)
print(f"Done.")
