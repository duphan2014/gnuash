#ifndef RENDERER_H
#define RENDERER_H

#if defined(__APPLE__)
#include <SDL.h>
#elif defined(__linux__)
#include <SDL2/SDL.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <SDL.h>
#elif defined(__CYGWIN__)
#include <SDL.h>
#else
#error "Unsupported platform"
#endif

#include "ball.h"
#include "platform.h"

void renderer_draw_filled_circle(SDL_Renderer *renderer, int cx, int cy, int radius);
void renderer_draw_circle_outline(SDL_Renderer *renderer, int cx, int cy, int radius, int thickness);
void renderer_draw_ball(SDL_Renderer *renderer, const Ball *ball);
void renderer_draw_balls(SDL_Renderer *renderer, const Ball balls[], int count);

void renderer_draw_filled_heart(SDL_Renderer *renderer, int x, int y, int size);

void renderer_draw_platform(SDL_Renderer *renderer, const Platform *platform);

#endif // RENDERER_H