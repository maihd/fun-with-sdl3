@echo off

if exist build (
    rmdir build /S /Q
)

mkdir build && pushd build

cmake .. -G "Visual Studio 17 2022"

cmake --build .

popd