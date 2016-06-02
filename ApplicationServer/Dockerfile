FROM ubuntu

RUN  apt-get update \
  && apt-get install -y wget
#  && rm -rf /var/lib/apt/lists/*

RUN apt-get install make
RUN apt-get install -y wget

# Instalamos cmake

RUN mkdir cmake
WORKDIR cmake
RUN wget https://cmake.org/files/v3.5/cmake-3.5.1.tar.gz
RUN tar xf cmake-3.5.1.tar.gz
WORKDIR cmake-3.5.1

# Instalamos gcc
RUN apt-get install -y gcc
RUN apt-get install -y g++

RUN ./configure
RUN make
RUN make install

# TearDown cmake

WORKDIR /
RUN rm -rf cmake

# Instalamos RocksDb

RUN mkdir rocksdb
WORKDIR rocksdb
RUN wget https://github.com/facebook/rocksdb/archive/v4.5.1.tar.gz
RUN tar xf v4.5.1.tar.gz

# Instalamos git
RUN apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys E1DD270288B4E6030699E45FA1715D88E1DF1F24
RUN echo 'deb http://ppa.launchpad.net/git-core/ppa/ubuntu trusty main' > /etc/apt/sources.list.d/git.list

RUN apt-get update 
RUN apt-get install -y git

WORKDIR rocksdb-4.5.1

RUN make static_lib
RUN mv librocksdb.a /lib/x86_64-linux-gnu/librocksdb.a

RUN mv include/rocksdb/ /usr/include/rocksdb
RUN apt-get install -y apt-util
RUN apt-get install -y libgflags-dev
RUN apt-get install -y libsnappy-dev
RUN apt-get install -y zlib1g-dev
RUN apt-get install -y libbz2-dev

# TearDown de las cosas de RocksDb

WORKDIR /
# RUN rm -rf rocksdb

COPY . /home/ApplicationServer

WORKDIR /home/ApplicationServer/ApplicationServer/app/

RUN cmake .
RUN make

WORKDIR app
