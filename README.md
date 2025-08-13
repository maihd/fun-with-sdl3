# SDL3 Examples for Fun and Profit

## Targets
- Learning SDL3
- Learning CMake, Ninja for building C projects in manner of cross-platforms
- More C practices, some features from C++ use required, explore Mai C Style: https://github.com/maihd/maicstyle
- Make profits: integrate to Mai Lite Editor (so, most examples focus on features that help code editor better)

## Modules, APIs need to explore
- Renderer 2D (Prefer but not force low power GPU accelerated)
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
- Full GPU diagnostics: Video Drivers, Renderer Drivers, VSync status
- VSync
- FPS
- Platforms: Windows, MacOS, Linux (X11, Wayland but doesnot tested), Web (WebAssembly with Emscripten)
- Shape rendering: Rect, Polygon, Circle (use polygon)

## Todos
- Cmake with Clang
- Text rendering
- Image rendering
- Simple framework
- Simple immediate mode GUI for debugging, testing
- Hot reloading
- Android
- iOS: build succeed, but no Info.plist to install on the phone
- Advanced: Vietnamese typing