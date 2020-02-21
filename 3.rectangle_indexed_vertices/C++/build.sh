#! /usr/bin/bash

rm -r CMakeCache.txt
cmake .
make
./program