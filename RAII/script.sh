#!/bin/bash

# Remove old build folders
rm -r build

# Create output folder for build output. 
mkdir -p build

# Change directory to build folder
cd build

# Build Executable
cmake ..
make

# Run executable
printf "*******************\n"
printf "Program Started\n"
./main
printf "Program Ended\n"
printf "*******************\n"