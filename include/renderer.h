#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "glad/gl.h"

#include "arena.h"
#include "types.h"
#include "dynarr.h"

typedef struct {
	GLuint VBO;
	u32 indexCount;
} mesh_t;

typedef struct {
	mesh_t* mesh;
	GLuint VAO;
	// add model transform matrix
} renderObject_t;

ARRAY_DEFINE(vertArray_t, vertex_t);
ARRAY_DEFINE(renderObjectArray_t, renderObject_t);

typedef struct {
	Arena_t arena;
	renderObjectArray_t instances;
} renderer_t;

void RENDERER_init(renderer_t* r);
void RENDERER_update(renderer_t* r);
void RENDERER_render(renderer_t* r, SDL_Window* window);
void RENDERER_destroy(renderer_t* r);

void RENDERER_initMesh(mesh_t* m, vertArray_t vertices, float* indices);
void RENDERER_initRenderObject(renderObject_t* o, mesh_t* m);

#endif
