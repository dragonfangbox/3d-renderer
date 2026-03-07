#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "types.h"

void RENDERER_translateObject(renderObject_t* o, vec3 t);
void RENDERER_rotateObjectX(renderObject_t* o, float angle);
void RENDERER_rotateObjectY(renderObject_t* o, float angle);
void RENDERER_rotateObjectZ(renderObject_t* o, float angle);

#endif 
