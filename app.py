import os
from dash import html, Dash
import dash_bootstrap_components as dbc
from dashboard.utils import dashboardlogging as Logger
from dashboard.callbacks import init_callbacks
from dashboard.components import standardSolarSystemTab

logger = Logger.GetLogger('app', configure=True)


def init_dashboard():
    """Create a Plotly Dash dashboard."""
    dash_app = Dash(
        title="Solar System Simulator",
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

    return dash_app

app = init_dashboard()

if __name__ == '__main__':
    debug = os.getenv("DASH_DEBUG") == "true"
    app.run_server(debug=debug)
