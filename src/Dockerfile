FROM ubuntu:latest

RUN apt-get -y update && \
    apt-get -y upgrade && \
    apt-get -y install python3-pip python3-venv python-is-python3

WORKDIR /usr/src/api

RUN python3 -m venv venv
RUN venv/bin/pip install pip --upgrade

COPY requirements.txt requirements.txt
RUN venv/bin/pip install -r requirements.txt

COPY docker_scripts/ docker_scripts/
COPY . .

CMD ["./docker_scripts/start.sh"]
