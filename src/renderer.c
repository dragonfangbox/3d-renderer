#include "renderer.h"

void RENDERER_init(renderer_t* r) {
	Arena_init(&r->arena, MiB);
	ARRAY_INIT(&r->objects); // figure out a nice interface to add renderObjects to
							   // the instances array.

//	ARRAY_INIT(&triangleVertices);
//	ARRAY_APPEND(&triangleVertices, ((vertex_t){{1, -1, 0}, {1, 0, 0}}));
//	ARRAY_APPEND(&triangleVertices, ((vertex_t){{0, 1, 0}, {0, 1, 0}}));
//	ARRAY_APPEND(&triangleVertices, ((vertex_t){{-1, -1, 0}, {0, 0, 1}}));
//
//	RENDERER_initMesh(&triangleMesh, triangleVertices, NULL);
//	RENDERER_initRenderObject(&testObj, &triangleMesh);

}

void RENDERER_update(renderer_t* r) { 

}

void RENDERER_render(renderer_t* r, SDL_Window* window) {
	glClearColor(0.5, 0.5, 0.5, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (u16 i = 0; i < r->objects.size; i++) {
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

void RENDERER_initRenderObject(renderObject_t* o, mesh_t* m) {
	o->mesh = m;

	glGenVertexArrays(1, &o->VAO);
	glBindVertexArray(o->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m->VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, pos));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, color));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void RENDERER_pushObject(renderer_t* r, renderObject_t o) {
	ARRAY_APPEND(&r->objects, (o));
}

void RENDERER_destroy(renderer_t* r) {
	Arena_free(&r->arena);
	ARRAY_FREE(&r->objects);
}
