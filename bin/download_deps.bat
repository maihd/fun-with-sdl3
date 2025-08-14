@echo off

if not exist libs\SDL3 (
    git clone https://github.com/libsdl-org/SDL libs/SDL3 --recursive --depth=1
)

if not exist libs\SDL3_ttf (
    git clone https://github.com/libsdl-org/SDL_ttf libs/SDL3_ttf --recursive --depth=1
)

if not exist libs\SDL3_image (
    git clone https://github.com/libsdl-org/SDL_image libs/SDL3_image --recursive --depth=1
)