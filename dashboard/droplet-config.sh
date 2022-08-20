#!/bin/bash

apt-get upgrade -y
apt-get update -y
echo "Installing python, nginx and supervisor"
apt-get install python3-pip python3-venv python3-dev build-essential \
                python3-setuptools libssl-dev libffi-dev supervisor nginx

mkdir -p /root/workdir
cd /root/workdir
python3 -m venv venv
source ./venv/bin/activate
pip install poetry
poetry install

