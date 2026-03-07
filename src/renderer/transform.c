#include "renderer/transform.h"

void RENDERER_translateObject(renderObject_t* o, vec3 t) {
	mat4_translate(o->model, t);
}

void RENDERER_rotateObjectX(renderObject_t* o, float angle) {
	mat4_rotateX(o->model, angle);
}

void RENDERER_rotateObjectY(renderObject_t* o, float angle) {
	mat4_rotateY(o->model, angle);
}

void RENDERER_rotateObjectZ(renderObject_t* o, float angle) {
	mat4_rotateZ(o->model, angle);
}
