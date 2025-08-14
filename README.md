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

## Build notes
- C compiler
- Cmake, Ninja
- Nasm & Perl for building SDL_image
- Use vendoring build technique to build SDL3 satellite modules

## Notes
- Renderer 2D: 
    - Use "gpu" driver name, do not use default when you need SDL_GPU backend
    - Other render driver does not support low power device
- VSync:
    - VSync works on all platforms
    - Only Vulkan support Adaptive VSync

## Tasks Done
- Cmake and Ninja, with scripts for fast dev iteration
- Full GPU diagnostics: Video Drivers, Renderer Drivers, VSync status
- VSync
- FPS calculating
- Shape rendering: Rect, Polygon, Circle (use polygon)
- Text rendering: embedded debug text engine, SDL3_ttf
- Image rendering: load image to texture, render with SDL_RenderTexture
- Platforms: 
    - Windows
    - MacOS (executable only, no bundle version yet)
    - Linux (X11, Wayland but doesnot tested)
    - Web (WebAssembly with Emscripten)
    - iOS (only bundle with Info.plist, no platform specified platform source code needed)
- Scripts for independant from Cmake building progress:
    - Build SDL3 and modules (required once time only)
    - Use scripts and clang to build executable
    - Why? because im stucking on build SDL_ttf and SDL_image with Cmake/FetchContent
    - It will help hot reload faster and easier
    - They called its vendoring build

## Todos
- Cmake with Clang
- Simple framework
- Simple immediate mode GUI for debugging, testing
- Hot reloading
- Android
- Advanced: Vietnamese typing
- Advanced: Avoid create text when dynamic rendering text, using glyph to get texcoords
- Advanced: Web Assets and Web Threads

## Notes on versions
Because SDL3 is still new, and I am still learning to use its. So I decised to use latest version from main branch, fetch very latest commit from the repos. This approach is like using nightly build from other modern techs.