# SDL3 Examples for Fun and Profit

## Targets
- Learning SDL3
- Learning CMake, Ninja for building C projects in manner of cross-platforms
- More C practices, some features from C++ use required, explore Mai C Style: https://github.com/maihd/maicstyle
- Make profit: integrate to Mai Lite Editor

## Modules, APIs need to explore
- Renderer 2D
- Audio
- TTF
- Image
- Storage
* SDL3 GPU is in other project: https://github.com/maihd/graphics-programming 

## Notes
- Renderer 2D: 
    - Use "gpu" driver name, do not use default when you need SDL_GPU backend
    - Other render driver does not support low power device
- VSync:
    - VSync works on all platforms
    - Only Vulkan support Adaptive VSync

## Tasks Done
- Full GPU diagnostics
- VSync
- FPS

## Todos
- Shape rendering
- Text rendering
- Image rendering
- Simple framework
- Hot reloading
- Android
- iOS: build succeed, but no Info.plist to install on the phone
- Wasm