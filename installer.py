import os
from pathlib import Path

cwd = Path(os.getcwd())
cppdir = cwd / "c++"

objdir = cwd.joinpath("c++", "obj")
outputdir = cwd.joinpath("c++", "output")

if not objdir.exists():
    objdir.mkdir()

if not outputdir.exists():
    outputdir.mkdir()

os.chdir(cppdir)
os.system("make")

os.chdir(cwd)
