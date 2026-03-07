#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "types.h"
#include "glad/gl.h"

void RENDERER_initRenderObject(renderObject_t* o, mesh_t* mesh, material_t* mat);
void RENDERER_pushObject(renderer_t* r, renderObject_t* o);

#endif

