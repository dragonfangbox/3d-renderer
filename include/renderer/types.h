#ifndef RENDERER_TYPES_H
#define RENDERER_TYPES_H

#include "gmath.h"
// define the vertex_t type here using the gmath
// vectors and stuff.
#include "../types.h"
#include "dynarr.h"
#include "arena.h"

typedef unsigned int GLuint;

ARRAY_DEFINE(floatArray_t, float);
ARRAY_DEFINE(indiceArray_t, int);

typedef struct {
	vec3 pos;
	vec4 color;
} vertex_t;
ARRAY_DEFINE(vertArray_t, vertex_t);

typedef struct {
	GLuint VBO;
	GLuint EBO;
	vertArray_t vertices;
	indiceArray_t indices;
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
ARRAY_DEFINE(renderObjectArray_t, renderObject_t*);

typedef struct {
	mat4 view;
	mat4 proj;
} camera_t;

typedef struct {
	Arena_t arena;
	renderObjectArray_t objects;
	camera_t* cam;
	vec2 screenSize;
} renderer_t;

#endif
