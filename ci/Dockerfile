FROM debian:11-slim

ENV DEBIAN_FRONTEND=noninteractive
ENV CXXFLAGS="-std=c++17"
ENV CMAKE_CXX_STANDARD=17

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    dbus-x11 \
    git \
    libxss-dev \
    python3-dbus \
    python3-gi \
    python3-pip \
    qtbase5-dev \
    qtbase5-dev-tools \
    libxss1 \
    curl \
    wget \
    ca-certificates \
    libgtest-dev \
    libgmock-dev \
    pkg-config \
    openssh-client \
    && rm -rf /var/lib/apt/lists/*

RUN pip3 install --no-cache-dir behave

WORKDIR /workspaces