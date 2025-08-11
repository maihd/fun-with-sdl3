rm -rf build

mkdir build && cd build

cmake .. -GNinja

cmake --build .