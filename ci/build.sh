#!/bin/bash

set -e

# Create build directory
mkdir -p build
cd build

# Configure with qmake
qmake ..

# Build with all available cores
make -j `nproc`