#ifndef SCENE_H
#define SCENE_H

#if defined(__APPLE__)
#include <SDL.h>
#include <SDL_image.h>
#elif defined(__linux__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <SDL.h>
#include <SDL_image.h>
#elif defined(__CYGWIN__)
#include <SDL.h>
#include <SDL_image.h>
#else
#error "Unsupported platform"
#endif
#include "sprite.h"
//#include "game.h"

typedef struct {
    int placeholder; // Empty scene for now
} Scene;

void scene_init(Scene* scene, SDL_Renderer* renderer, int winWidth, int winHeight);
void scene_draw(Scene* scene, SDL_Renderer* renderer);
void scene_free(Scene* scene);
#endif