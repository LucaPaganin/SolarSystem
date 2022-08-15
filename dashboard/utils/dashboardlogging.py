import logging
import sys

def GetLogger(name=None, configure=False, logfile=None):
    logger = logging.getLogger(name) if name is not None else logging.getLogger()
    logger.propagate = False
    if logger.hasHandlers():
        logger.handlers.clear()
    if configure:
        logger = configure_logger(name, logfile=logfile)
    return logger

def configure_logger(name=None, logfile=None):
    logger = GetLogger(name)
    logger.setLevel(logging.DEBUG)
    log_fmt = '%(asctime)s.%(msecs)03d-%(name)s-%(levelname)s: %(message)s'
    log_formatter = logging.Formatter(log_fmt, datefmt="%Y-%m-%dT%H:%M:%S")
    stdout_handler = logging.StreamHandler(sys.stdout)
    stdout_handler.setLevel(logging.DEBUG)
    stdout_handler.setFormatter(log_formatter)
    logger.addHandler(stdout_handler)
    if logfile is not None:
        fh = logging.FileHandler(logfile, mode='w')
        fh.setLevel(logging.DEBUG)
        fh.setFormatter(log_formatter)
        logger.addHandler(fh)
    return logger