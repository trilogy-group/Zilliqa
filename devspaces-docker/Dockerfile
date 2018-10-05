FROM ubuntu:16.04

RUN apt-get update \
 && apt-get install -y git clang-format-5.0 clang-tidy-5.0 clang-5.0 libboost-system-dev \
    libboost-filesystem-dev libboost-test-dev libssl-dev libleveldb-dev libjsoncpp-dev \
    libsnappy-dev cmake libmicrohttpd-dev libjsonrpccpp-dev build-essential pkg-config \
    libevent-dev libminiupnpc-dev libprotobuf-dev protobuf-compiler libcurl4-openssl-dev \
    sudo psmisc \
 && rm -rf /var/lib/apt/lists/*

# Create the non-root user
RUN mkdir /data \
 && adduser --disabled-password --gecos '' dev \
 && adduser dev sudo \
 && echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers \
 && chown -R dev /data
USER dev

WORKDIR /data

CMD tail -f /dev/null
