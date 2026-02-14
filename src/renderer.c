#include "renderer.h"

void RENDERER_init(renderer_t* r) {
	Arena_init(&r->arena, MiB);
	ARRAY_INIT(&r->objects);
}

void RENDERER_update(renderer_t* r) { 
	
}

void RENDERER_render(renderer_t* r, SDL_Window* window) {
	glClearColor(0.5, 0.5, 0.5, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (u16 i = 0; i < r->objects.size; i++) {
		glUseProgram(r->objects.data[i].material->shader);
		glBindVertexArray(r->objects.data[i].VAO);
		glDrawArrays(GL_TRIANGLES, 0, r->objects.data[i].mesh->vertCount);
	}

	SDL_GL_SwapWindow(window);
}

void RENDERER_initMesh(mesh_t* m, vertArray_t vertices, float* indices) {
	m->vertCount= vertices.size;
	
	glGenBuffers(1, &m->VBO);

	// if(indices != NULL) {
	//	create an EBO
	// }

	glBindBuffer(GL_ARRAY_BUFFER, m->VBO);
	glBufferData(GL_ARRAY_BUFFER, 
				 sizeof(vertex_t) * vertices.size, 
				 vertices.data,
				 GL_STATIC_DRAW
				 );

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RENDERER_initRenderObject(renderObject_t* o, mesh_t* mesh, material_t* mat) {
	o->mesh = mesh;
	o->material = mat;
	glm_mat4_identity(o->model);

	glGenVertexArrays(1, &o->VAO);
	glBindVertexArray(o->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, pos));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, color));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void RENDERER_translateObject(renderObject_t* o, float x, float y, float z) {
	vec3 v = {x, y, z};
	glm_translate(o->model, v);
}

void RENDERER_rotateObject(renderObject_t* o, float angle, float x, float y, float z) {
	vec3 v = {x, y, z};
	
	glm_rotate(o->model, glm_rad(angle), v);
}

void RENDERER_pushObject(renderer_t* r, renderObject_t o) {
	ARRAY_APPEND(&r->objects, (o));
}

void RENDERER_initMaterial(material_t* m, GLuint program) {
	m->shader = program;
}

void RENDERER_setUniformMat4(material_t* m, const char* name, mat4 mat) {
	GLuint location = glGetUniformLocation(m->shader, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, (float*)mat);
}

void RENDERER_destroy(renderer_t* r) {
	Arena_free(&r->arena);
	ARRAY_FREE(&r->objects);
}

