#!/bin/sh

set -e

mkdir build

cd build

cmake ..

cmake --build .
