#include <stdio.h>
#include <stdbool.h>

#define SDL_MAIN_USE_CALLBACKS
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

static SDL_Window* window;
static SDL_Renderer* renderer;

SDL_AppResult SDL_AppInit(void** appState, int argc, char* argv[])
{
    SDL_Log("Fun with SDL3");

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "gpu");
    SDL_SetHint(SDL_HINT_RENDER_GPU_LOW_POWER, "1");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL_Init() failed: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    window = SDL_CreateWindow("Fun With SDL3", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        SDL_Log("SDL_CreateWindow() failed: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
    // bool lowpower = SDL_GetHintBoolean(SDL_HINT_RENDER_GPU_LOW_POWER, lowpower);
    // SDL_Log("lowpower: %s\n", lowpower ? "true" : "false");

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        SDL_Log("SDL_CreateWindow() failed: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

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
    SDL_SetRenderDrawColor(renderer, 65, 23, 100, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

//! EOF
