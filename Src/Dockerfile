FROM ubuntu:latest AS empty

FROM empty AS builder

RUN apt-get update && apt-get install -y \
    g++ make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . /app

WORKDIR /app/Emitter
RUN make

WORKDIR /app/Collector
RUN make

