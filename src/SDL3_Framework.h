#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef struct Color
{
    uint8_t r, g, b, a;
} Color;

typedef struct Texture
{
    int32_t width;
    int32_t height;
    void*   internal_data;
} Texture;

void        InitWindow(int32_t w, int32_t h, const char* title);
void        CloseWindow(void);

bool        WindowShouldClose(void);

void        BeginDrawing(void);
void        EndDrawing(void);

void        ClearBackground(Color color);

const char* TextFormat(const char* fmt, ...);
size_t      TextFormatAlloc(char** out_text, const char* fmt, ...);

void        DrawText(const char* text, float x, float y, float font_size, Color color);
void        DrawFPS(float x, float y, Color color);

void        DrawTexture(Texture texture, float x, float y);

void        DrawRect(float x, float y, float w, float h, Color color);
void        DrawRectLines(float x, float y, float w, float h, Color color);

void        DrawCircle(float x, float y, float r, Color color);
void        DrawCircleLines(float x, float y, float r, Color color);

//! EOF
