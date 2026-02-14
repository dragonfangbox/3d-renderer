#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "glad/gl.h"

#include "arena.h"
#include "types.h"
#include "dynarr.h"
#include "cglm/cglm.h"

typedef struct {
	GLuint VBO;
	GLuint EBO;
	u32 vertCount;
} mesh_t;

typedef struct {
	GLuint shader;
	// texture
} material_t;

typedef struct {
	mesh_t* mesh;
	material_t* material;
	GLuint VAO;
	mat4 model;
} renderObject_t;

ARRAY_DEFINE(vertArray_t, vertex_t);
ARRAY_DEFINE(renderObjectArray_t, renderObject_t);

typedef struct {
	Arena_t arena;
	renderObjectArray_t objects;
} renderer_t;

void RENDERER_init(renderer_t* r);
void RENDERER_update(renderer_t* r);
void RENDERER_render(renderer_t* r, SDL_Window* window);
void RENDERER_destroy(renderer_t* r);

void RENDERER_initMesh(mesh_t* m, vertArray_t vertices, float* indices);
void RENDERER_initRenderObject(renderObject_t* o, mesh_t* mesh, material_t* mat);
void RENDERER_initMaterial(material_t* m, GLuint program);

void RENDERER_pushObject(renderer_t* r, renderObject_t o);
void RENDERER_translateObject(renderObject_t* o, float x, float y, float z);
void RENDERER_rotateObject(renderObject_t* o, float angle, float x, float y, float z);


void RENDERER_setUniformMat4(material_t* m, const char* name, mat4 mat);

#endif
