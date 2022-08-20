#!/bin/bash
CWD=$(pwd)

apt-get upgrade -y
apt-get update -y
echo "Installing python, nginx and supervisor"
apt-get install -y python3-pip python3-venv python3-dev build-essential \
                   python3-setuptools python3-poetry python3-cachecontrol \ 
                   libssl-dev libffi-dev supervisor nginx net-tools
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

supervisorctl reload

DROPLET_IP=$(ifconfig | egrep -o "inet [0-9\.]+" | head -1 | cut -d ' ' -f 2)
sed -i "s/server_name .*$/server_name ${DROPLET_IP};/" nginx.txt

rm -f /etc/nginx/sites-enabled/default

cat nginx.txt > /etc/nginx/sites-enabled/dash

service nginx reload