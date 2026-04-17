#include "renderer/renderobject.h"
#include "obj-parser.h"


void RENDERER_initRenderObject(renderObject_t* o, mesh_t* mesh, material_t* mat) {
	o->mesh = mesh;
	o->material = mat;
	mat4_identity(o->model);
}

renderObject_t* RENDERER_newRenderObject(mesh_t* mesh, material_t* mat) {
	renderObject_t* obj = malloc(sizeof(renderObject_t));

	RENDERER_initRenderObject(obj, mesh, mat);

	return obj;
}

void RENDERER_pushObject(renderer_t* r, renderObject_t* o) {
	ARRAY_APPEND(&r->objects, (o));
}
