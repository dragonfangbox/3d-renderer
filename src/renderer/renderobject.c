#include "renderer/renderobject.h"

void RENDERER_initRenderObject(renderObject_t* o, mesh_t* mesh, material_t* mat) {
	o->mesh = mesh;
	o->material = mat;
	mat4_identity(o->model);

	glGenVertexArrays(1, &o->VAO);
	glBindVertexArray(o->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
	if (mesh->EBO != 0) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, pos));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, color));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void RENDERER_pushObject(renderer_t* r, renderObject_t* o) {
	ARRAY_APPEND(&r->objects, (o));
}
