FROM ubuntu:24.04

RUN apt-get update -qq && \
    apt-get install build-essential autoconf libtool-bin -y

WORKDIR /usr/fcml-lib

COPY . /usr/fcml-lib/
