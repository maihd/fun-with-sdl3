#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define SDL_MAIN_USE_CALLBACKS
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
// #include "SDL3_ttf/SDL_ttf.h"

static SDL_Window* window;
static SDL_Renderer* renderer;

// static TTF_Font* font;
// static SDL_Texture* fontTexture;

// static TTF_TextEngine* textEngine;

static double fps;
static double lastTime;
static double deltaTime;

static double fpsTimer      = 0.0;
static double fpsInvertal   = 0.1;

SDL_AppResult SDL_AppInit(void** appState, int argc, char* argv[])
{
    SDL_Log("Fun with SDL3");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL_Init() failed: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    for (int i = 0, n = SDL_GetNumRenderDrivers(); i < n; i++)
    {
        SDL_Log("Driver%d: %s", i, SDL_GetRenderDriver(i));
    }

    window = SDL_CreateWindow("Fun With SDL3", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        SDL_Log("SDL_CreateWindow() failed: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
    // bool lowpower = SDL_GetHintBoolean(SDL_HINT_RENDER_GPU_LOW_POWER, lowpower);
    // SDL_Log("lowpower: %s\n", lowpower ? "true" : "false");

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "gpu");
    SDL_SetHint(SDL_HINT_RENDER_GPU_LOW_POWER, "1");

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        SDL_Log("SDL_CreateWindow() failed: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    const char* driverName = SDL_GetRendererName(renderer);
    SDL_Log("SDL renderer driver = %s", driverName);

    const char* vsyncTitle;
    if (SDL_SetRenderVSync(renderer, 1))
    {
        vsyncTitle = "VSync Enabled";
    }
    else 
    {
        vsyncTitle = "VSync Disabled";
    }
    
    char* windowTitle;
    SDL_asprintf(&windowTitle, "FunWithSDL3 - SDL 2D Driver = %s - %s", driverName, vsyncTitle);
    SDL_SetWindowTitle(window, windowTitle);
    SDL_free(windowTitle);

    lastTime = (double)SDL_GetTicksNS() / 1000000000.0;
    deltaTime = 0.0f;

    // if (!TTF_Init())
    // {
    //     SDL_Log("SDL_ttf could not initialize! SDL_ttf error: %s\n", SDL_GetError());
    //     return SDL_APP_FAILURE;
    // }

    // textEngine = TTF_CreateRendererTextEngine(renderer);
    // if (!textEngine)
    // {
    //     SDL_Log("TTF_CreateRendererTextEngine() error: %s\n", SDL_GetError());
    //     return SDL_APP_FAILURE;
    // }

    return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void* appState, SDL_AppResult appResult)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}


SDL_AppResult SDL_AppEvent(void* appState, SDL_Event* event)
{
    switch (event->type)
    {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void* appState)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    // SDL_RenderDebugText(renderer, 272, 100, "Hello world!");

    // Render a simple outlined rect
    SDL_FRect rect = { 272, 100, 100, 100 };
    SDL_RenderRect(renderer, &rect);

    // Render a simple filled rect
    SDL_FRect rect2 = { 272, 300, 100, 100 };
    SDL_RenderFillRect(renderer, &rect2);

    // Render FPS text
    char* fpsText; SDL_asprintf(&fpsText, "FPS: %.1lf", fps);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, 10, 10, fpsText);
    SDL_free(fpsText);

    SDL_RenderPresent(renderer);

    // Calculate fps
    double time = ((double)SDL_GetTicksNS() / 1000000000.0);
    deltaTime = time - lastTime;
    lastTime = time;

    fpsTimer += deltaTime;
    if (fpsTimer >= fpsInvertal)
    {
        fpsTimer -= fpsInvertal;
        fps = 1.0 / deltaTime;
    }

    return SDL_APP_CONTINUE;
}

//! EOF
