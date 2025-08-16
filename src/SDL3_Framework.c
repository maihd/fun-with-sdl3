#include "SDL3_Framework.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "SDL3_image/SDL_image.h"

#define IMGUI_ENABLE_FREETYPE
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "cimgui_impl.h"

typedef struct AppState
{
    SDL_Window*     window;
    SDL_Renderer*   renderer;

    char*           origin_title;
    
    TTF_TextEngine* text_engine;
    TTF_Font*       title_font;
    TTF_Text        title_text;

    // ImGui
    ImGuiContext*   imgui_context;
    const ImFontLoader*   imgui_font_loader;

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
    sprintf(format, "[Level = %d] %s", level, text);
    
    static char buffer[4096];
    vsprintf(buffer, format, vargs);

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

    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    SDL_WindowFlags window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
    g_app_state.window = SDL_CreateWindow(title, w * main_scale, h * main_scale, window_flags);
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

    // ImGui for debugging
    g_app_state.imgui_context = igCreateContext(NULL);
    igSetCurrentContext(g_app_state.imgui_context);

    ImGuiIO* io = igGetIO_ContextPtr(g_app_state.imgui_context);
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

    ImGuiStyle* style = igGetStyle();
    igStyleColorsDark(style);
    ImGuiStyle_ScaleAllSizes(style, main_scale);
    style->FontScaleDpi = main_scale;

    ImGui_ImplSDL3_InitForSDLRenderer(g_app_state.window, g_app_state.renderer);
    ImGui_ImplSDLRenderer3_Init(g_app_state.renderer);

    // Start the timer
    g_app_state.last_app_ticks = SDL_GetTicksNS();
    g_app_state.fps_interval = 0.1f;
}

void CloseWindow(void)
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();

    igDestroyContext(g_app_state.imgui_context);

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
        ImGui_ImplSDL3_ProcessEvent(&event);
        if (event.type == SDL_EVENT_QUIT)
        {
            return true;
        }
    }

    return false;
}

void BeginDrawing(void)
{
    SDL_FlushRenderer(g_app_state.renderer);
}

void EndDrawing(void)
{
    ImGuiIO* io = igGetIO_Nil();

    SDL_SetRenderScale(g_app_state.renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);
    ImGui_ImplSDLRenderer3_RenderDrawData(igGetDrawData(), g_app_state.renderer);

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

void OpenDebugWindow()
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();

    igNewFrame();
    {
        static bool show = true;
        igShowDemoWindow(&show);
    }
    igRender();
}

//! EOF
