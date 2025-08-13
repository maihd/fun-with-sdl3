@echo off

set EMPTY= 

echo ==================================================================================================
echo Setup environment for Emscripten....
echo ==================================================================================================
call emsdk_env.bat
if not %ErrorLevel% equ 0 (
    echo Failed to setup enviroment for Emscripten!
    goto :end
)

echo >&2 >NUL
echo ==================================================================================================
echo Building with Emscripten....
echo ==================================================================================================
if not exist build_wasm (
    mkdir build_wasm
)

pushd build_wasm

call emcmake cmake .. -GNinja

call cmake --build .

popd

:end