from datetime import datetime
from dash.dependencies import Input, Output, State
from dash import callback_context as ctx
from .components import *
from .planets_data import *
from .ephemerids import retrieve_solarsystem_ephemerids
from .utils import dashboardlogging as Logger
from timeit import default_timer as timer
import traceback
logger = Logger.GetLogger(__name__, configure=True)


def iterate_planet(c, res, plId):
    if isinstance(c, dict) and 'props' in c and 'children' in c['props']:
        iterate_planet(c['props']['children'], res, plId)
    elif isinstance(c, list):
        for x in c:
            iterate_planet(x, res, plId)
    elif isinstance(c, dict) and 'props' in c and 'id' in c['props'] and 'value' in c['props'] and plId in c['props']['id']:
        cid = c['props']['id']
        prefix, suffix = cid.split("-")
        if prefix not in res:
            res[prefix] = {}
        res[prefix][suffix] = c['props']['value']


def get_planets_from_plist(plist):
    pdata = {}
    for p in plist:
        plId = p['props']['id']
        iterate_planet(plist, pdata, plId)
    planets = {
        v['label']: v for v in pdata.values()
    }
    return planets


def do_time_evolution(plist, duration, animation_step, computation_step):
    planets = get_planets_from_plist(plist)
    incondsfile = INPUTDIR / f"solarsystem.txt"
    with incondsfile.open("w") as fh:
        for key, data in planets.items():
            if data["present"]:
                fh.write("{label}\n"
                         "{Mass}\n"
                         "{X} {Y} {Z}\n"
                         "{VX} {VY} {VZ}\n".format(**data))
    outdata = run_simulation(incondsfile, ndays=duration, 
                             sampling_step_days=animation_step, 
                             dt_days=computation_step)
    return planets, outdata


def init_callbacks(app):
    @app.callback(
        [Output('solarsystem-3dplot', 'figure'),
         Output('energy-plot', 'figure'),],
        [Input('solarsystem-run-button', 'n_clicks')],
        [State('planets-list', 'children'),
         State('sim-duration', 'value'),
         State('animation-frames', 'value'),
         State('solarsystem-3dplot', 'figure'),
         State('energy-plot', 'figure')]
    )
    def solar_system_sim(run_n_clicks, plist, duration, animation_frames, curr_3d_plot, curr_energy_plot):
        try:
            animation_step = duration/animation_frames
            computation_step = 0.01
            if animation_step > computation_step:
                start = timer()
                logger.info(f"Simulation number {run_n_clicks} triggered, running it")
                logger.info(f"settings: duration {duration} days, frames {animation_frames}, steps {duration/computation_step}")
                planets, outdata = do_time_evolution(plist, duration, animation_step, computation_step)
                logger.info(f"finished running simulation, elapsed time {timer()-start} s")
                names = [k for k in SOLARSYSTEMNAMES if planets[k]['present']]
                fig3d = make_3d_plot(df=outdata['time_evo'], names=names)
                fig_energy = make_energy_plot(df=outdata["energies"])
                return fig3d, fig_energy
            else:
                logger.warning(f"animation_step {animation_step} was greater than computation_step {computation_step}, skipping computation")
                return curr_3d_plot, curr_energy_plot
        except:
            logger.error(traceback.format_exc())

    @app.callback(
        Output('planets-list', 'children'),
        inputs={
            "all_inputs": {
                "reset": Input("solarsystem-reset-button", "n_clicks"),
                "ephemerids": Input("solarsystem-ephemerids-button", "n_clicks"),
                "planets": State('planets-list', 'children'),
                "eph-date": State('ephemerids-date', 'date')
            }
        }
    )
    def reset_planets(all_inputs):
        c = ctx.args_grouping.all_inputs
        curr_planets = get_planets_from_plist(all_inputs['planets'])
        if c['ephemerids']['triggered']:
            ephdate = datetime.strptime(all_inputs['eph-date'], "%Y-%m-%d")
            ephdate = ephdate.strftime("%Y-%m-%d")
            logger.info(f"Initializing planets initial conditions from ephemerids of {ephdate}")
            ephemerids = retrieve_solarsystem_ephemerids(start_time=ephdate)
            return init_planets_from_ephemerids(ephemerids, curr_planets)
        return init_planets_default()

    @app.callback(
        [Output('sim-duration', 'value'),
         Output('animation-frames', 'value')],
        [Input('solarsystem-reset-button', 'n_clicks')]
    )
    def reset_settings(n_clicks):
        return 365, 100
