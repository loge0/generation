#!/bin/sh
mkdir -p build                   
cd build
conan remote add SFML https://api.bintray.com/conan/bincrafters/public-conan
set -e
conan install .. --build=missing
cmake ..
cmake --build . --config RELEASE
cp bin/generation.exe ..