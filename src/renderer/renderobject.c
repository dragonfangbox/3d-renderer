#include "renderer.h"

void RENDERER_initMesh(mesh_t* m, vertArray_t vertices, indiceArray_t indices) {
	m->vertCount = vertices.size;
	m->indiceCount = indices.size;
	
	glGenBuffers(1, &m->VBO);

	if (indices.data != NULL) {
		glGenBuffers(1, &m->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->EBO);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
					 sizeof(int) * indices.size,
					 indices.data,
					 GL_STATIC_DRAW
					 );
	}

	glBindBuffer(GL_ARRAY_BUFFER, m->VBO);
	glBufferData(GL_ARRAY_BUFFER, 
				 sizeof(vertex_t) * vertices.size, 
				 vertices.data,
				 GL_STATIC_DRAW
				 );

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

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

void RENDERER_initMaterial(material_t* m, GLuint program) {
	m->shader = program;
}

void RENDERER_pushObject(renderer_t* r, renderObject_t* o) {
	ARRAY_APPEND(&r->objects, (o));
}
