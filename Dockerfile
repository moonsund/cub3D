FROM debian:bullseye

RUN apt-get update \
 && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    git \
    make \
    pkg-config \
    nano \
    libx11-dev \
    libxext-dev \
    libbsd-dev \
    libxrandr-dev \
    libxrender-dev \
    libxfixes-dev \
    libxi-dev \
    zlib1g-dev \
    x11-apps \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /app