#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "glad/gl.h"

#define ARENA_IMPLEMENTATION
#include "arena.h"
#include "types.h"

typedef struct {
	Arena_t arena;
	GLuint VBO;
	GLuint VAO;
} renderer_t;

void RENDERER_init(renderer_t* r);
void RENDERER_update(renderer_t* r);
void RENDERER_render(renderer_t* r, SDL_Window* window);

#endif
