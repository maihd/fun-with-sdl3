@echo off

if exist build (
    rmdir build /S /Q
)

mkdir build && pushd build

cmake .. -GNinja

cmake --build .

popd