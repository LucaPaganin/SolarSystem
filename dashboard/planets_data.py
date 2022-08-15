from pathlib import Path
import json
import pandas as pd
import numpy as np
import sys
import os
import subprocess as sp
import uuid
import time
import shutil
import multiprocessing as mp
from timeit import default_timer as timer
from .utils import dashboardlogging as Logger

logger = Logger.GetLogger(__name__, configure=True)

THISDIR = Path(__file__).parent
CPPDIR = THISDIR.parent/"cpp"
CPPOUTDIR = THISDIR.parent/"cpp/output"
WINEXEDIR = THISDIR.parent/"winexe"
WINEXE = WINEXEDIR/"SolarSystem.exe"
WINOUTDIR = WINEXEDIR/"output"
UNIXBINDIR = THISDIR.parent/"linuxbin"
UNIXOUTDIR = UNIXBINDIR/"output"
INPUTDIR = THISDIR.parent/"input"

SOLARSYSTEMNAMES = [
    "Sun",
    "Mercury",
    "Venus",
    "Earth",
    "Mars",
    "Jupiter",
    "Saturn",
    "Uranus",
    "Neptune",
    "Pluto"
]
CUR_PROCS = {
    "procs": {},
    "lock": mp.Lock()
}

with open(INPUTDIR/"solar_system_default.json", "r") as f:
    tmp = {k: v for k, v in json.load(f).items()}
    DEFAULT_SOLARSYSTEM_INCONDS = {
        k: tmp[k] for k in SOLARSYSTEMNAMES
    }


def _run_sim(infile, ndays, dt_days, sampling_step_days, workdir):
    cwd0 = os.getcwd()
    if sys.platform == "win32":
        logger.debug(f"working directory {workdir}")
        os.chdir(workdir)
        try:
            p = sp.run(f"{WINEXEDIR}/SolarSystem.exe {infile} {ndays} {dt_days} {sampling_step_days}",
                       shell=True, text=True, stdout=sp.PIPE, stderr=sp.PIPE, cwd=workdir, check=True)
            logger.info("finished running simulation")
        except sp.CalledProcessError as e:
            logger.error(e)
        os.chdir(cwd0)
    else:
        pass


def run_simulation(infile=INPUTDIR/"effemeridi.txt", ndays=365, dt_days=0.1, sampling_step_days=1):
    infile = Path(infile).resolve()
    basedir = WINOUTDIR if sys.platform == "win32" else UNIXOUTDIR
    workdir = basedir/str(uuid.uuid4())
    outdir = workdir/"output"
    outdir.mkdir(exist_ok=True, parents=True)
    proc = mp.Process(target=_run_sim, 
                      args=(infile, ndays, dt_days, sampling_step_days, workdir), 
                      daemon=True)
    logger.debug(f"available CPUs {mp.cpu_count()}")
    while len(CUR_PROCS["procs"]) > int(mp.cpu_count()/2):
        logger.debug(f"currently running processes: {len(CUR_PROCS['procs'])}, waiting...")
        time.sleep(0.1)
    proc.start()
    logger.debug(f"Started process {proc.pid}")
    with CUR_PROCS["lock"]:
        logger.debug(f"Adding process {proc.pid} to current processes")
        CUR_PROCS["procs"][proc.pid] = proc
    start = timer()
    logger.debug(f"waiting for process {proc.pid} to complete...")
    while proc.is_alive():
        time.sleep(0.1)
    proc.join()
    logger.debug(f"process {proc.pid} completed, elapsed time {timer()-start:.6f} s")
    with CUR_PROCS["lock"]:
        logger.debug(f"Removing process {proc.pid} from current processes")
        del CUR_PROCS["procs"][proc.pid]
        logger.debug(f"Correctly removed process {proc.pid} from current processes")
        data = {
            "time_evo": parse_temporal_evolution(outdir/"temporal_evolution.txt", sampling_step_days=sampling_step_days),
            "energies": parse_single_energies(outdir/"Single_energies.txt")
        }
        logger.debug(f"removing working directory {workdir}")
        shutil.rmtree(workdir)
        logger.debug(f"removed working directory {workdir}")
    return data


def parse_temporal_evolution(file, sampling_step_days=1):
    file = Path(file)
    with file.open("r") as f:
        header = f.readline()
    names = header.lstrip("#").strip().split()
    columns = []
    for n in names:
        columns.extend([f"{n}_{coord}" for coord in ("X", "Y", "Z")])
    df = pd.read_table(file, delim_whitespace=True, comment='#')
    df.columns = columns
    t = np.arange(len(df))*sampling_step_days
    df["t"] = t
    return df


def parse_single_energies(file):
    file = Path(file)
    with file.open("r") as f:
        header = f.readline()
    names = header.lstrip("#").strip().split()
    columns = ["t", *names]
    df = pd.read_table(file, delim_whitespace=True, comment='#')
    df.columns = columns
    return df
