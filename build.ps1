New-Item -ItemType Directory -Force -Path build                  
cd build
conan remote add SFML https://api.bintray.com/conan/bincrafters/public-conan
$ErrorActionPreference = "Stop"
conan install .. --build=missing
cmake ..
cmake --build . --config RELEASE
cp bin/generation.exe ..
cd ..