cmake_minimum_required(VERSION 3.18)
project(FunWithSDL3)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY  "https://github.com/libsdl-org/SDL.git"
    GIT_TAG         "main"
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(SDL3)

# find_package(SDL3 REQUIRED)

add_executable(FunWithSDL3 src/main.c)

target_link_libraries(FunWithSDL3 PRIVATE SDL3::SDL3)