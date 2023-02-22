FROM ubuntu:latest

RUN apt-get -y update && \
    apt-get -y upgrade
RUN apt-get -y install python3-pip python3-venv python-is-python3
RUN apt-get -y install cron nano-tiny
RUN apt-get -y install wget curl

WORKDIR /usr/src/api

RUN python3 -m venv venv
RUN venv/bin/pip install pip --upgrade

COPY requirements.txt requirements.txt
RUN venv/bin/pip install -r requirements.txt

COPY . .

RUN chmod +x "./scripts/start.sh" "./scripts/entrypoint.sh"

ENTRYPOINT ["./scripts/entrypoint.sh"]
CMD ["./scripts/start.sh"]
