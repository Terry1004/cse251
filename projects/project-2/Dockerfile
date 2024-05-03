FROM gcc:11

RUN echo "deb [trusted=yes] http://archive.debian.org/debian/ squeeze main" > /etc/apt/sources.list.d/docker.list && \
    apt update && \
    apt install -y libwxgtk2.8-dev

WORKDIR /root/workspace/Elevator
