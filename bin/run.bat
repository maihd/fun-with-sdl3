@echo off


echo ==================================================================================================
echo Building....
echo ==================================================================================================
if not exist build (
    mkdir build
)

pushd build

cmake .. -GNinja

cmake --build .

if %ErrorLevel% == 0 (
    echo >&2 >NUL
    echo ==================================================================================================
    echo Running....
    echo ==================================================================================================

    FunWithSDL3.exe
) else (
    echo Build failed. Please check build errors above!
)

popd