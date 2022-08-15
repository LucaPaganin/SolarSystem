from .planets_data import *
from .constants import SOLAR_SYSTEM_DATA
from plotly import graph_objects as go
from timeit import default_timer as timer
from pathlib import Path
from .utils import dashboardlogging as Logger
logger = Logger.GetLogger(__name__, configure=True)
THISDIR = Path(__file__).parent


def _get_3d_plot_ranges(df, names):
    coords = {
        "x": df[[f"{n}_X" for n in names]],
        "y": df[[f"{n}_Y" for n in names]],
        "z": df[[f"{n}_Z" for n in names]]
    }
    offsets = {
        "x": 0.1, "y": 0.1, "z": 0.1
    }
    ranges = {
        k: (v.min().min() - offsets[k], v.max().max() + offsets[k])
        for k, v in coords.items()
    }
    return ranges


def make_energy_plot(df=None):
    start = timer()
    logger.info("doing energy plot")
    if df is None:
        file = INPUTDIR/"defaults/Single_Energies.txt"
        df = parse_single_energies(file)
    frames = []
    names = [n for n in SOLARSYSTEMNAMES if n in df.columns[1:]]
    xrange = (df["t"].values[0] - 5, df["t"].values[-1])
    energies = df[df.columns[1:]]
    emin, emax = energies.min().min(), energies.max().max()
    yrange = emin*1.05, emax*1.05
    dt = df["t"].values[1]
    for k in range(1, len(df)):
        frame = go.Frame(
            data=[
                go.Scatter(x=df["t"].iloc[0:k],
                           y=df[n].iloc[0:k], mode='lines', name=n)
                for n in names
            ],
            layout=go.Layout(width=700, height=700),
            name=f"{k*dt:.0f} days"
        )
        frames.append(frame)
    fig = go.Figure(
        data=[
            go.Scatter(x=[df["t"].iloc[0]], y=[
                       df[n].iloc[0]], mode='lines', name=n)
            for n in names
        ],
        layout=go.Layout(width=700, height=700),
        frames=frames,
        layout_xaxis_range=xrange,
        layout_yaxis_range=yrange
    )
    configure_animation_controls(fig)
    logger.info(f"energy plot done in {timer()-start} s")
    return fig


def make_3d_plot(df=None, names=None):
    width = 750
    height = 750
    start = timer()
    logger.info(f"doing 3d planets plot")
    if df is None:
        file = INPUTDIR/"defaults/temporal_evolution.txt"
        df = parse_temporal_evolution(file)
    if names is None:
        names = SOLARSYSTEMNAMES
    dt = df["t"].values[1]
    ranges = _get_3d_plot_ranges(df, names)
    sizes = {
        k: 10*SOLAR_SYSTEM_DATA[k]['radius'] for k in names
    }
    frames = []
    scattermode = 'lines+markers'
    for k in range(1, len(df)+1):
        frame = go.Frame(
            data=[
                go.Scatter3d(x=df[f"{n}_X"].iloc[0:k],
                             y=df[f"{n}_Y"].iloc[0:k],
                             z=df[f"{n}_Z"].iloc[0:k],
                             mode=scattermode, name=n,
                             marker=dict(size=sizes[n]))
                for n in names
            ],
            layout=go.Layout(width=width,
                             height=height,
                             scene=dict(xaxis=dict(range=ranges['x']),
                                        yaxis=dict(range=ranges['y']),
                                        zaxis=dict(range=ranges['z']),
                                        aspectmode='cube')),
            name=f"{k*dt:.0f} days"
        )
        frames.append(frame)

    fig = go.Figure(
        data=[
            go.Scatter3d(x=[df[f"{n}_X"].iloc[0]],
                         y=[df[f"{n}_Y"].iloc[0]],
                         z=[df[f"{n}_Z"].iloc[0]],
                         mode=scattermode, name=n,
                         marker=dict(size=sizes[n]))
            for n in names
        ],
        layout=go.Layout(width=width, height=height,
                         scene=dict(
                             xaxis=dict(range=ranges['x']),
                             yaxis=dict(range=ranges['y']),
                             zaxis=dict(range=ranges['z']),
                             aspectmode='cube')
                         ),
        frames=frames
    )
    configure_animation_controls(fig)
    logger.info(f"3d planets plot done in {timer()-start} s")
    return fig


def configure_animation_controls(fig, duration=30):
    def frame_args(duration, redraw):
        return {
            "frame": {"duration": duration, "redraw": redraw},
            "mode": "immediate",
            "fromcurrent": True,
            "transition": {
                "duration": duration,
                "easing": "linear"
            },
        }

    fig.layout.updatemenus = [
        {
            "buttons": [
                {
                    "args": [None, frame_args(duration, True)],
                    "label": "&#9654;",
                    "method": "animate",
                },
                {
                    "args": [[None], frame_args(0, False)],
                    "label": "&#9724;",
                    "method": "animate",
                },
            ],
            "direction": "left",
            "pad": {"r": 10, "t": 70},
            "showactive": False,
            "type": "buttons",
            "x": 0.1,
            "xanchor": "right",
            "y": 0,
            "yanchor": "top",
        }
    ]
    fig.layout.sliders = [
        {
            "active": 0,
            "yanchor": "top",
            "xanchor": "left",
            "currentvalue": {
                "prefix": "t = "
            },
            "pad": {"b": 10, "t": 60},
            "len": 0.9,
            "x": 0.1,
            "y": 0,
            "steps": [
                {
                    "args": [
                        [f.name],
                        frame_args(0, True)
                    ],
                    "label": f.name,
                    "method": "animate",
                }
                for f in fig.frames
            ],
        }
    ]
