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
./ThreadBasics
printf "Program Ended\n"
printf "*******************\n"
printf "Program Started\n"
./ThreadNativeHandle
printf "Program Ended\n"
printf "*******************\n"
printf "Program Started\n"
./ThreadsClass
printf "Program Ended\n"
printf "*******************\n"
printf "Program Started\n"
./ThreadLockGuard
printf "Program Ended\n"
printf "*******************\n"
printf "Program Started\n"
./ThreadUniqueLock
printf "Program Ended\n"
printf "*******************\n"
printf "Program Started\n"
./ThreadAtomics
printf "Program Ended\n"
printf "*******************\n"
printf "Program Started\n"
./ThreadSharedLock
printf "Program Ended\n"
printf "*******************\n"
printf "Program Started\n"
./ThreadPool
printf "Program Ended\n"
printf "*******************\n"