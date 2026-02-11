#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "glad/gl.h"
#include "types.h"
#define ARENA_IMPLEMENTATION
#include "arena.h"

typedef struct {
	Arena_t arena;
	u16 VBO;
} renderer_t;

void RENDERER_init(renderer_t* r);
void RENDERER_update();
void RENDERER_render(SDL_Window* window);

#endif
