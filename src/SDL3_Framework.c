#include "SDL3_Framework.h"

#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "SDL3_image/SDL_image.h"

typedef struct AppState
{
    SDL_Window*     window;
    SDL_Renderer*   renderer;

    Uint64          frame_count;
    Uint64          frame_ticks;
    Uint64          last_app_ticks;

    double          average_fps;
    double          fps_timer;
    double          fps_interval;
} AppState;

//! EOF
