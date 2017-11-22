#!/bin/bash

# Delete old binary
rm Arduino_DCT

# Compile
echo "Running CMake..."

case "$1" in
    debug)
        echo "Creating DEBUG build"
        cmake -DCMAKE_BUILD_TYPE=Debug ..
        ;;
    release)
        echo "Creating RELEASE build"
        cmake -DCMAKE_BUILD_TYPE=Release ..
        ;;
    analyze)
        echo "Creating DEBUG build for static analysis"
        cmake -DCMAKE_BUILD_TYPE=Debug ..
        ;;
    *)
        echo "Choose debug or release build mode using one of the following commands:"
        echo "$0 debug"
        echo "$0 release"
        echo "$0 analyze"
        exit 1
esac

if [ "$1" == "analyze" ]
then
    scan-build make
else
    make -j 4
fi

# Clean up
echo "Cleaning up..."
rm -r CMakeFiles
rm CMakeCache.txt cmake_install.cmake Makefile

# Testrun
./Arduino_DCT -i ../signal_samples/squarewave -a 4
# gnuplot
../gnuplot/plot.sh plotting_data.dat
