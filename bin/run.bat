@echo off


echo ==================================================================================================
echo Building....
echo ==================================================================================================
if not exist build (
    mkdir build
)

pushd build

cmake .. -G "Visual Studio 17 2022" -DCMAKE_INSTALL_PREFIX="."

cmake --build .

if %ErrorLevel% == 0 (
    echo >&2 >NUL
    echo ==================================================================================================
    echo Running....
    echo ==================================================================================================

    Debug\FunWithSDL3.exe
) else (
    echo Build failed. Please check build errors above!
)

popd