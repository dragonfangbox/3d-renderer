#include "renderer.h"

void RENDERER_init(renderer_t* r, camera_t* camera) {
	Arena_init(&r->arena, MiB);
	ARRAY_INIT(&r->objects);

	r->cam = camera;
}

void RENDERER_update(renderer_t* r) { 
	
}

void RENDERER_render(renderer_t* r, SDL_Window* window) {
	glClearColor(0.5, 0.5, 0.5, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (u16 i = 0; i < r->objects.size; i++) {
		renderObject_t* obj = r->objects.data[i];

		if (obj->mesh->EBO != 0) {
			glUseProgram(obj->material->shader);
			
			RENDERER_setUniformMat4(obj->material, "model", obj->model);
			RENDERER_setUniformMat4(obj->material, "view", r->cam->view);
			RENDERER_setUniformMat4(obj->material, "proj", r->cam->proj);
			glBindVertexArray(r->objects.data[i]->VAO);
			glDrawElements(GL_TRIANGLES, obj->mesh->indiceCount, GL_UNSIGNED_INT, 0);
		} else {
			glUseProgram(obj->material->shader);
			RENDERER_setUniformMat4(obj->material, "model", obj->model);
			RENDERER_setUniformMat4(obj->material, "view", r->cam->view);
			RENDERER_setUniformMat4(obj->material, "proj", r->cam->proj);
			glBindVertexArray(r->objects.data[i]->VAO);
			glDrawArrays(GL_TRIANGLES, 0, r->objects.data[i]->mesh->vertCount);
		}
	}

	SDL_GL_SwapWindow(window);
}

void RENDERER_initMesh(mesh_t* m, vertArray_t vertices, indiceArray_t indices) {
	m->vertCount = vertices.size;
	m->indiceCount = indices.size;
	
	glGenBuffers(1, &m->VBO);

	if(indices.data != NULL) {
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

void RENDERER_translateObject(renderObject_t* o, float x, float y, float z) {
	vec3 v = {x, y, z};
	mat4_translate(o->model, v);
}

void RENDERER_rotateObjectY(renderObject_t* o, float angle) {
	mat4_rotateY(o->model, angle);
}

void RENDERER_rotateObjectX(renderObject_t* o, float angle) {
	mat4_rotateX(o->model, angle);
}

void RENDERER_pushObject(renderer_t* r, renderObject_t* o) {
	ARRAY_APPEND(&r->objects, (o));
}

void RENDERER_initMaterial(material_t* m, GLuint program) {
	m->shader = program;
}

void RENDERER_setUniformMat4(material_t* m, const char* name, mat4 mat) {
	GLuint location = glGetUniformLocation(m->shader, name);
	glUniformMatrix4fv(location, 1, GL_TRUE, (float*)mat);
}

void RENDERER_destroy(renderer_t* r) {
	Arena_free(&r->arena);
	ARRAY_FREE(&r->objects);
}

