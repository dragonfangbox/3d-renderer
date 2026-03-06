#ifndef RENDERER_H
#define RENDERER_H

// change it so the render object buffer gets cleared each frame so the way to render things would be:
//
// while(true) { // main render loop
//	
//	 
//	 // edit object here
//		translate...
//		rotate...
//		scale...
//	
//	pushrenderobject(&obj);
//	renderobjects();
// }

#include <SDL2/SDL.h>
#include "glad/gl.h"

#include "arena.h"
#include "types.h"
#include "dynarr.h"
#include "gmath.h"

typedef struct {
	GLuint VBO;
	GLuint EBO;
	unsigned int vertCount;
	unsigned int indiceCount;	
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
ARRAY_DEFINE(vertArray_t, vertex_t);
ARRAY_DEFINE(indiceArray_t, int);

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

void RENDERER_init(renderer_t* r, camera_t* camera);
void RENDERER_update(renderer_t* r);
void RENDERER_render(renderer_t* r, SDL_Window* window);
void RENDERER_destroy(renderer_t* r);

void RENDERER_initMesh(mesh_t* m, vertArray_t vertices, indiceArray_t indices);
void RENDERER_initRenderObject(renderObject_t* o, mesh_t* mesh, material_t* mat);
void RENDERER_initMaterial(material_t* m, GLuint program);

void RENDERER_pushObject(renderer_t* r, renderObject_t* o);
void RENDERER_translateObject(renderObject_t* o, vec3 t);
void RENDERER_rotateObjectX(renderObject_t* o, float angle);
void RENDERER_rotateObjectY(renderObject_t* o, float angle);
void RENDERER_rotateObjectZ(renderObject_t* o, float angle);


void RENDERER_setUniformMat4(material_t* m, const char* name, mat4 mat);

#endif
