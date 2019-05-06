#!/bin/bash

BUILD_DIR="cmake-build-debug"

mkdir $BUILD_DIR

cd $BUILD_DIR

echo "Building..."
cmake ..
echo "Running make"
make all

arg=$1
if [ "$arg" == "-r" ]
then
	./GravityJoyride
fi
