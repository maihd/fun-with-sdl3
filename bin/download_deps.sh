if [ ! -d "libs/SDL3" ]; then 
    git clone https://github.com/libsdl-org/SDL libs/SDL3 --recursive --depth=1
fi

if [ ! -d "libs/SDL3_ttf" ]; then
    git clone https://github.com/libsdl-org/SDL_ttf libs/SDL3_ttf --recursive --depth=1
fi

if [ ! -d "libs/SDL3_image" ]; then
    git clone https://github.com/libsdl-org/SDL_image libs/SDL3_image --recursive --depth=1
fi