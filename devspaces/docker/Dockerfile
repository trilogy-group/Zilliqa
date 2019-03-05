FROM ubuntu:18.04

LABEL description="This file generates a docker image containing all necessary components to build and run Zilliqa"

RUN apt-get update && \
    apt-get install -y git clang-format-5.0 clang-tidy-5.0 clang-5.0 libboost-system-dev \
    libboost-filesystem-dev libboost-test-dev libssl-dev libleveldb-dev libjsoncpp-dev \
    libsnappy-dev cmake libmicrohttpd-dev libjsonrpccpp-dev build-essential pkg-config \
    libevent-dev libminiupnpc-dev libprotobuf-dev protobuf-compiler && \
    apt-get clean

WORKDIR /data

CMD tail -f /dev/null
