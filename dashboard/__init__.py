from dash import html, dcc, Dash
import dash_bootstrap_components as dbc
from .components import *
from .callbacks import init_callbacks
from .utils import dashboardlogging as Logger
logger = Logger.configure_logger(__name__)


def init_dashboard(server):
    """Create a Plotly Dash dashboard."""
    dash_app = Dash(
        title="Solar System",
        server=server,
        routes_pathname_prefix='/dashboards/solarsystem/',
        external_stylesheets=[
            dbc.themes.BOOTSTRAP, 'static/solarsystem_dashboard.css'
        ]
    )
    logger.info("initializing dashboard")

    # Create Dash Layout
    dash_app.layout = html.Div(
        id='dash-container',
        children=[
            dbc.Tabs([
                standardSolarSystemTab()
            ], active_tab='solar-system')
        ])
    logger.info("initializing callbacks")
    init_callbacks(dash_app)

    return dash_app.server
        