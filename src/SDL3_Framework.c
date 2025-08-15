#include "SDL3_Framework.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "SDL3_image/SDL_image.h"

typedef struct AppState
{
    SDL_Window*     window;
    SDL_Renderer*   renderer;

    char*           origin_title;
    
    TTF_TextEngine* text_engine;
    TTF_Font*       title_font;
    TTF_Text        title_text;

    // Timer

    Uint64          frame_count;
    Uint64          frame_ticks;
    Uint64          last_app_ticks;

    double          total_time;
    double          delta_time;
    
    double          average_fps;
    double          fps_timer;
    double          fps_interval;
} AppState;

static AppState g_app_state;


void TraceLog(TraceLogLevel level, const char* text, ...)
{
    va_list vargs;
    va_start(vargs, text);

    char format[1024];
    sprintf_s(format, sizeof(format), "[Level = %d] %s", level, text);
    
    static char buffer[4096];
    vsprintf_s(buffer, sizeof(buffer), format, vargs);

    va_end(vargs);

    SDL_Log(buffer);

    if (level == LOG_FATAL)
    {
        exit(EXIT_FAILURE);
    }
}


void InitWindow(int32_t w, int32_t h, const char* title)
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        TraceLog(LOG_FATAL, "SDL_Init() failed: %s", SDL_GetError());
    }

    SDL_WindowFlags window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
    g_app_state.window = SDL_CreateWindow(title, w, h, window_flags);
    if (!g_app_state.window)
    {
        TraceLog(LOG_FATAL, "SDL_CreateWindow() failed: %s", SDL_GetError());     
    }

    SDL_SetWindowPosition(g_app_state.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(g_app_state.window);

#ifndef EMPSCRIPTEN
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "gpu");
    SDL_SetHint(SDL_HINT_RENDER_GPU_LOW_POWER, "1");
#endif

    g_app_state.renderer = SDL_CreateRenderer(g_app_state.window, NULL);
    if (!g_app_state.renderer)
    {
        TraceLog(LOG_FATAL, "SDL_CreateRenderer() failed: %s", SDL_GetError());
    }

    // Log info
    
    for (int i = 0, n = SDL_GetNumVideoDrivers(); i < n; i++)
    {
        TraceLog(LOG_INFO, "Video Driver%d: %s", i, SDL_GetVideoDriver(i));
    }

    for (int i = 0, n = SDL_GetNumRenderDrivers(); i < n; i++)
    {
        TraceLog(LOG_INFO, "Render Driver%d: %s", i, SDL_GetRenderDriver(i));
    }

    const char* renderer_driver_name = SDL_GetRendererName(g_app_state.renderer);
    TraceLog(LOG_INFO, "SDL renderer driver = %s", renderer_driver_name);

    const char* vsync_title;
    if (SDL_SetRenderVSync(g_app_state.renderer, SDL_RENDERER_VSYNC_ADAPTIVE))
    {
        vsync_title = "VSync Adaptive";
    }
    else if (SDL_SetRenderVSync(g_app_state.renderer, 1))
    {
        vsync_title = "VSync On";
    }
    else 
    {
        vsync_title = "VSync Off";
    }
    
    const char* video_driver_name = SDL_GetCurrentVideoDriver();
    const char* current_window_title = SDL_GetWindowTitle(g_app_state.window);
    char* window_title;
    SDL_asprintf(&window_title, "%s | Video Driver = %s | 2D Driver = %s - %s", current_window_title, video_driver_name, renderer_driver_name, vsync_title);
    SDL_SetWindowTitle(g_app_state.window, window_title);
    SDL_free(window_title);

    if (!TTF_Init())
    {
        TraceLog(LOG_FATAL, "TTF_Init() failed: %s", SDL_GetError());        
    }

    g_app_state.text_engine = TTF_CreateRendererTextEngine(g_app_state.renderer);
    if (!g_app_state.text_engine)
    {
        TraceLog(LOG_FATAL, "TTF_Init() failed: %s", SDL_GetError());
    }

    // Start the timer
    g_app_state.last_app_ticks = SDL_GetTicksNS();
    g_app_state.fps_interval = 1.0f;
}

void CloseWindow(void)
{
    SDL_DestroyRenderer(g_app_state.renderer);
    SDL_DestroyWindow(g_app_state.window);
    SDL_Quit();

    memset(&g_app_state, 0, sizeof(g_app_state));
}

bool WindowShouldClose(void)
{
    g_app_state.frame_count++;

    Uint64 ticks = SDL_GetTicksNS();
    g_app_state.frame_ticks = ticks - g_app_state.last_app_ticks;
    g_app_state.last_app_ticks = ticks;

    g_app_state.delta_time  = (double)g_app_state.frame_ticks / 1e9;
    g_app_state.total_time += g_app_state.delta_time;

    g_app_state.fps_timer += g_app_state.delta_time;
    if (g_app_state.fps_timer >= g_app_state.fps_interval)
    {
        g_app_state.fps_timer -= g_app_state.fps_interval;
        g_app_state.average_fps = g_app_state.frame_count / g_app_state.total_time;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            return true;
        }
    }

    return false;
}

void BeginDrawing(void)
{

}

void EndDrawing(void)
{
    char* fps_text; SDL_asprintf(&fps_text, "FPS: %.0lf", g_app_state.average_fps);
    SDL_SetRenderDrawColor(g_app_state.renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(g_app_state.renderer, 10, 10, fps_text);
    SDL_free(fps_text);

    SDL_RenderPresent(g_app_state.renderer);
}

void ClearBackground(Color color)
{
    SDL_SetRenderDrawColor(g_app_state.renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(g_app_state.renderer);
}

//! EOF
