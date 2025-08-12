cmake_minimum_required(VERSION 3.18)
project(FunWithSDL3)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force SDL build static, to run on windows without needed to copy .dll
set(SDL_SHARED  OFF)
set(SDL_STATIC  ON)

include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY  "https://github.com/libsdl-org/SDL.git"
    GIT_TAG         96292a5b464258a2b926e0a3d72f8b98c2a81aa6 # release-3.2.20
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(SDL3)

# find_package(SDL3 REQUIRED)

add_executable(FunWithSDL3 src/main.c)

target_link_libraries(FunWithSDL3 PRIVATE SDL3::SDL3-static)
install(FILES $<TARGET_RUNTIME_DLLS:FunWithSDL3> TYPE BIN)