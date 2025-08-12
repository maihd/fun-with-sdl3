cmake_minimum_required(VERSION 3.18)
project(FunWithSDL3)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force SDL build static, to run on windows without needed to copy .dll
set(BUILD_SHARED_LIBS OFF)
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

# FetchContent_Declare(
#     SDL3_ttf
#     GIT_REPOSITORY  "https://github.com/libsdl-org/SDL_ttf.git"
#     GIT_TAG         "main"
# )
# FetchContent_MakeAvailable(SDL3_ttf)
# FetchContent_GetProperties(SDL3_ttf)
# set(FETCHCONTENT_QUIET NO)
# FetchContent_Populate(SDL3_ttf)
# add_subdirectory(${SDL3_ttf_SOURCE_DIR} ${SDL3_ttf_BINARY_DIR})

# find_package(SDL3 REQUIRED)

add_executable(FunWithSDL3 src/main.c)

target_link_libraries(FunWithSDL3 PRIVATE SDL3::SDL3-static)
# target_link_libraries(FunWithSDL3 PRIVATE SDL3::SDL3-static SDL3_ttf::SDL3_ttf-static)
install(FILES $<TARGET_RUNTIME_DLLS:FunWithSDL3> TYPE BIN)