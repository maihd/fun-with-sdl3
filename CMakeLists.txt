cmake_minimum_required(VERSION 3.18)
project(FunWithSDL3)

set(PRODUCT_NAME "FunWithSDL3")
set(APP_VERSION "1.0.0")
set(PRODUCT_PACKAGE "com.maihd.funwithsdl3")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force SDL build static, to run on windows without needed to copy .dll
set(BUILD_SHARED_LIBS OFF)
set(SDL_SHARED  OFF)
set(SDL_STATIC  ON)

set(SDL_WAYLAND ON)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Use vendored libs
set(SDLTTF_VENDORED ON)
set(SDLTTF_HARFBUZZ OFF)

set(SDLIMAGE_VENDORED ON)

set(SDLIMAGE_AVIF OFF)	# disable formats we don't use to make the build faster and smaller.

set(IMGUI_STATIC ON)

# This assumes the SDL source is available in libs/SDL3
add_subdirectory(libs/SDL3 EXCLUDE_FROM_ALL)

# This assumes the SDL_ttf source is available in libs/SDL3_ttf
add_subdirectory(libs/SDL3_ttf EXCLUDE_FROM_ALL)

# This assumes the SDL_image source is available in libs/SDL3_image
add_subdirectory(libs/SDL3_image EXCLUDE_FROM_ALL)

# This assumes the cimgui source is available in libs/SDL3_image
add_subdirectory(libs/cimgui EXCLUDE_FROM_ALL)

# include(FetchContent)

# FetchContent_Declare(
#     SDL3
#     GIT_REPOSITORY  "https://github.com/libsdl-org/SDL.git"
#     GIT_TAG         96292a5b464258a2b926e0a3d72f8b98c2a81aa6 # release-3.2.20
#     EXCLUDE_FROM_ALL
# )
# FetchContent_MakeAvailable(SDL3)

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

add_definitions(
    -DCIMGUI_USE_SDL3
    -DCIMGUI_USE_SDLRENDERER3
)

file(GLOB SOURCES
    src/main.c 
    src/SDL3_Framework.c

    libs/cimgui/cimgui_impl.cpp
    libs/cimgui/imgui/backends/imgui_impl_sdl3.cpp
    libs/cimgui/imgui/backends/imgui_impl_sdlrenderer3.cpp
)


target_include_directories(cimgui PUBLIC libs/cimgui/imgui/backends)

if (ANDROID)
add_executable(FunWithSDL3 ${SOURCES})
target_link_libraries(${EXECUTABLE_NAME} PUBLIC SDL3::SDL3 SDL3_ttf::SDL3_ttf SDL3_image::SDL3_image android EGL GLESv2 cimgui)
else()
add_executable(FunWithSDL3 ${SOURCES})
target_link_libraries(FunWithSDL3 PRIVATE SDL3::SDL3-static SDL3_ttf::SDL3_ttf SDL3_image::SDL3_image cimgui)
endif()

if (IOS)
    message("Building with Emscripten!")
    # set(CMAKE_OSX_SYSROOT iphoneos)
    # set(CMAKE_OSX_ARCHITECTURES arm64)

    set_target_properties(FunWithSDL3 PROPERTIES 
        MACOSX_BUNDLE               TRUE
        MACOSX_BUNDLE_INFO_PLIST    "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios/Info.plist.in"
    )
elseif (EMSCRIPTEN)
    message("Building with Emscripten!")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()