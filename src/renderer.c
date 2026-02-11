#include "renderer.h"


typedef struct {
	vector3_t pos;
	vector3_t color;
} vertex_t;

vertex_t testvertices[3] = {
	{{0.5, 0, 0}, {1, 0, 0}},
	{{0, 0.5, 0}, {0, 1, 0}},
	{{-0.5, 0, 0}, {0, 0, 1}}
};

typedef struct {
	vertex_t vertices[3];
} triangle;

static void newTriangle(triangle* t, vertex_t v[3], vector4_t color) {
	for (u16 i = 0; i < 3; i++) {
		t->vertices[i] = v[i];
	}

}

void RENDERER_init(renderer_t* r) {
	Arena_init(&r->arena, MiB);

	glGenBuffers(1, &r->VBO);

	glGenVertexArrays(1, &r->VAO);
}

void RENDERER_update(renderer_t* r) { 
	triangle t;
	newTriangle(&t, testvertices, (vector4_t){0.5, 0.2, 1, 1});

	glBindVertexArray(r->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, r->VBO);
	glBufferData(GL_ARRAY_BUFFER, 
				 sizeof(testvertices),
				 testvertices,
				 GL_STATIC_DRAW
				 );

	glVertexAttribPointer(0,
						  3,
						  GL_FLOAT,
						  GL_FALSE,
						  sizeof(vertex_t),
						  (void*)offsetof(vertex_t, pos)
						  );

	glVertexAttribPointer(1,
						  3,
						  GL_FLOAT,
						  GL_FALSE,
						  sizeof(vertex_t),
						  (void*)offsetof(vertex_t, color)
						  );

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void RENDERER_render(renderer_t* r, SDL_Window* window) {
	glClearColor(0.5, 0.5, 0.5, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(r->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	SDL_GL_SwapWindow(window);
}
