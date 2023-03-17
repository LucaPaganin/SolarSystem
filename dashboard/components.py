from dash import html, dcc
import dash_bootstrap_components as dbc
from .planets_data import *
from .plots import *
import random
from plotly import graph_objects as go
from datetime import datetime, timedelta
from timeit import default_timer as timer
from collections import defaultdict
from pathlib import Path
from .utils import dashboardlogging as Logger
logger = Logger.GetLogger(__name__, configure=True)
THISDIR = Path(__file__).parent


def standardSolarSystemTab():
    content = dbc.Card(
        dbc.CardBody([
            dbc.Row([
                dbc.Col(
                    planetsListColumn()
                ),
                dbc.Col(
                    plotsColumn()
                )
            ])
        ]), className="mt-3")
    return dbc.Tab(content, label="Solar System", tab_id='solar-system', className="mt-3")


def planetsListColumn():
    planets = init_planets_default()
    children = [
        dbc.Row(
            dbc.Container(className='planets-header-container',
                          children=[html.H2("Solar System Simulator")])
        ),
        dbc.Row(
            dbc.Container(
                [
                    html.P((THISDIR/"description.txt").read_text(), className="text-justify"),
                    html.A("Reference to SSB", 
                           href="https://en.wikipedia.org/wiki/International_Celestial_Reference_System_and_its_realizations", 
                           target="_blank")
                ]
            )
        ),
        dbc.Row(
            dbc.Card(
                dbc.CardBody(
                    dcc.Loading(
                        dbc.Accordion(id='planets-list', children=planets)
                    ),
                    className='mt-3')
            )
        )
    ]

    return children


def plotsColumn():
    sim_duration, anim_frames, eph_date = simulationSettings()
    return dbc.Container([
        dbc.Row([
            dbc.Col(sim_duration, className="col"),
            dbc.Col(anim_frames, className="col"),
            dbc.Col(eph_date, className="col")
        ], className="row row-cols-3"),
        dbc.Row([
            dbc.Col(controlButtons())
        ]),
        dbc.Row(
            dbc.Container(plotTabs(), className="mt-3")
        )
    ])


def plotTabs():
    return dbc.Tabs([
        solarsystem3dPlotTab(),
        energyPlotTab()
    ], active_tab='3d-planets')


def solarsystem3dPlotTab():
    content = dbc.Card(
        dbc.CardBody([
            dcc.Loading(
                dcc.Graph(figure=make_3d_plot(), id='solarsystem-3dplot'), type="cube"
            )
        ])
    )
    return dbc.Tab(dbc.Container(content, className="mt-3"),
                   label="3D Planets", tab_id='3d-planets')


def energyPlotTab():
    content = dbc.Card(
        dbc.CardBody([
            dcc.Loading(
                dcc.Graph(figure=make_energy_plot(), id='energy-plot'), type="cube"
            )
        ])
    )
    return dbc.Tab(dbc.Container(content, className="mt-3"),
                   label="Energies", tab_id='energy')


def simulationSettings():
    now = datetime.today()
    sim_duration = dbc.InputGroup([
        dbc.InputGroupText("Duration"),
        dbc.Input(id=f"sim-duration", value=365, type="number", step=1, min=10, max=1e6),
        dbc.InputGroupText("d")
    ], className='mb-3')
    anim_frames = dbc.InputGroup([
        dbc.InputGroupText("frames"),
        dbc.Input(id=f"animation-frames", value=100,
                  type="number", step=1, min=10, max=500)
    ], className='mb-3')
    eph_date = dbc.Container([
        html.Div(
            "Ephemerids date",
            className="p-2 align-items-center"),
        dcc.DatePickerSingle(
            id='ephemerids-date',
            max_date_allowed=now,
            initial_visible_month=now,
            date=now,
            display_format="DD-MM-YYYY",
            className="p-2 align-items-center")
    ], className="d-flex flex-row")

    return sim_duration, anim_frames, eph_date


def controlButtons():
    run = dbc.Button('Run', id='solarsystem-run-button', n_clicks=0)
    reset = dbc.Button('Reset', id='solarsystem-reset-button', n_clicks=0)
    eph = dbc.Button('Get Ephemerids',
                     id='solarsystem-ephemerids-button', n_clicks=0)
    return dbc.ButtonGroup([run, reset, eph])


def init_planets_default():
    planets = []
    inital_conditions = DEFAULT_SOLARSYSTEM_INCONDS
    base_active_bodies = ["Sun", "Mercury", "Venus", "Earth", "Mars"]
    for i, (key, data) in enumerate(inital_conditions.items()):
        coords = dict(zip(['X', 'Y', 'Z'], data['Coordinates']))
        vels = dict(zip(['VX', 'VY', 'VZ'], data['Velocities']))
        mass = data['Mass']
        # active = data['active']
        active = key in base_active_bodies
        planets.append(
            planet_component(plId=f"planet{i}", label=key, mass=mass,
                             coords=coords, vels=vels, active=active)
        )
    return planets


def init_planets_from_ephemerids(ephemerids, curr_planets):
    planets = []
    for i, (key, data) in enumerate(ephemerids.items()):
        coords = {k: v for k, v in data.items() if k in ['X', 'Y', 'Z']}
        vels = {k: v for k, v in data.items() if k in ['VX', 'VY', 'VZ']}
        mass = data['Mass']
        active = curr_planets[key]['present']
        planets.append(
            planet_component(plId=f"planet{i}", label=key, mass=mass,
                             coords=coords, vels=vels, active=active)
        )
    return planets


def planet_component(plId, label, mass, coords={}, vels={}, active=True):
    _coords = defaultdict(lambda: round(random.random(), 8))
    _coords.update(coords)
    _velocs = defaultdict(lambda: round(random.random(), 8))
    _velocs.update(vels)
    rows = [
        dbc.Row([
            dbc.Col(planet_label(plId, label), className="col-auto"),
            dbc.Col(dbc.Checkbox(f"{plId}-present", label="active",
                                 value=active, className="col-auto"))
        ], className="row"),
        dbc.Row([
            dbc.Col(planet_input_field(plId, 'Mass',
                    mass, "MSun"), className="col-auto")
        ]),
        dbc.Row([
            dbc.Col(planet_coordinates(plId, _coords)),
            dbc.Col(planet_velocity(plId, _velocs))
        ], className="row row-cols-2")
    ]
    return dbc.AccordionItem(
        id=plId,
        title=label,
        className="planet-container",
        children=rows
    )


def planet_label(plId, label):
    return dbc.InputGroup([
        dbc.InputGroupText("Label"),
        dbc.Input(id=f"{plId}-label", placeholder=label,
                  value=label, type="string")
    ], className='mb-2')


def planet_coordinates(plId, values={}):
    return _vector_component(plId, values, ["X", "Y", "Z"], "coordinates")


def planet_velocity(plId, values={}):
    return _vector_component(plId, values, ["VX", "VY", "VZ"], "velocity")


def _vector_component(plId, values, labels, kind):
    units = "AU" if kind == "coordinates" else "AU/d"
    rows = [dbc.Row(html.H5(kind.capitalize()))]
    rows.extend([
        dbc.Row(planet_input_field(
            plId, label, value=values[label], units=units))
        for label in labels
    ])
    return dbc.Card(
        id=f'{plId}-planet-{kind}',
        children=rows,
        className="p-3"
    )


def planet_input_field(plId, label, value, units):
    value = f"{float(value):.4E}"
    return dbc.InputGroup(
        [
            dbc.InputGroupText(label.replace("V", "")),
            dbc.Input(id=f"{plId}-{label}", value=value, type="string"),
            dbc.InputGroupText(units)
        ], 
        className='mb-3'
    )
