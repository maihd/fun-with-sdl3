#include <stdio.h>

#define SDL_MAIN_USE_CALLBACKS
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

SDL_AppResult SDL_AppInit(void** appState, int argc, char* argv[])
{
    SDL_Log("Fun with SDL3");
    return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void* appState, SDL_AppResult appResult)
{

}


SDL_AppResult SDL_AppEvent(void* appState, SDL_Event* event)
{
    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void* appState)
{
    return SDL_APP_CONTINUE;
}

//! EOF
