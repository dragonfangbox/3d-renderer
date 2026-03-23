#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "renderer/types.h"

void RENDERER_init(renderer_t* r, window_t* window, camera_t* camera);
void RENDERER_update(renderer_t* r);
void RENDERER_render(renderer_t* r, SDL_Window* window);
void RENDERER_destroy(renderer_t* r);

#endif

