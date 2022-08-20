#!/bin/bash
CWD=$(pwd)

apt-get upgrade -y
apt-get update -y
echo "Installing python, nginx and supervisor"
apt-get install -y python3-pip python3-venv python3-dev build-essential \
                   python3-setuptools python3-poetry libssl-dev libffi-dev \
                   supervisor nginx
python3 -m venv venv
source ./venv/bin/activate
pip install poetry
poetry install

echo "Compiling c++ code"
cd ../cpp
mkdir -p obj
make
cp main.out ../linuxbin
cd ../linuxbin
mkdir output

echo "Returning to ${CWD}"
cd $(PWD)

cat supervisor.txt > /etc/supervisor/conf.d/dash.conf