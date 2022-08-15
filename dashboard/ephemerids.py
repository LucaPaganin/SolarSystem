import requests
import re
from datetime import datetime, timedelta
from .utils import dashboardlogging as Logger
from .constants import PLANETS_MASSES_IN_SOLAR_MASSES

logger = Logger.GetLogger(name=__name__, configure=True)

PLANETS_CMD_TO_LABEL = {
    "10": "Sun",
    "199": "Mercury",
    "299": "Venus",
    "399": "Earth",
    "499": "Mars",
    "599": "Jupiter",
    "699": "Saturn",
    "799": "Uranus",
    "899": "Neptune",
    "999": "Pluto",
}

PLANETS_LABEL_TO_CMD = {v: k for k, v in PLANETS_CMD_TO_LABEL.items()}

_mass_ratio_rgx = re.compile(r"Mass ratio \([a-zA-Z]+/[a-zA-Z]+\)\s*=\s*([\-\d\.E\+]+)")
_mass_ratio_rgx = re.compile(r"Mass ratio \([a-zA-Z]+/[a-zA-Z]+\)\s*=\s*([\-\d\.E\+]+)")
_coordrgx = re.compile(r"(X|Y|Z|VX|VY|VZ)\s*=\s*([\-\d\.E\+]+)")


def retrieve_planet_ephemerids(name, start_time):
    tmp = datetime.strptime(start_time, "%Y-%m-%d")
    stop_time = (tmp + timedelta(days=1)).strftime("%Y-%m-%d")
    command = PLANETS_LABEL_TO_CMD[name]
    params = dict(
        format='json',
        COMMAND=f"'{command}'",
        OBJ_DATA="'YES'",
        MAKE_EPHEM="'YES'",
        EPHEM_TYPE="'VECTORS'",
        OUT_UNITS='AU-D',
        CENTER="'500@0'",
        START_TIME=f"'{start_time}'",
        STOP_TIME=f"'{stop_time}'",
        QUANTITIES="'2'",
        STEP_SIZE='1d'
    )
    r = requests.get(
        "https://ssd.jpl.nasa.gov/api/horizons.api",  params=params)
    s = r.json()['result']
    coords = {
        x[0]: x[1] for x in _coordrgx.findall(s)[:7]
    }
    if name != "Sun":
        try:
            mr = float(_mass_ratio_rgx.findall(s)[0])
            m = 1/mr
        except:
            m = PLANETS_MASSES_IN_SOLAR_MASSES[name]
    else:
        m = 1
    pldata = {
        "Mass": str(m), "Name": name, **coords
    }
    return pldata


def retrieve_solarsystem_ephemerids(start_time):
    solarsystem = {}
    for name in PLANETS_LABEL_TO_CMD:
        logger.info(f"Retrieving ephemerids for '{name}' for start_time {start_time}")
        data = retrieve_planet_ephemerids(name, start_time)
        solarsystem[name] = data
    return solarsystem