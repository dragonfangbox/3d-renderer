#include "renderer.h"

vector3_t testvertices[3] = {
	{0.5, 0, 0},
	{0, 0.5, 0},
	{-0.5, 0, 0}
};

typedef struct {
	vector3_t vertices[3];
	vector4_t color;
} triangle;

static void newTriangle(triangle* t, vector3_t v[3], vector4_t color) {
	for (u16 i = 0; i < 3; i++) {
		t->vertices[i] = v[i];
	}

	t->color = color;
}

void RENDERER_init(renderer_t* r) {
	Arena_init(&r->arena, MiB);
}

void RENDERER_update() { 
	triangle t;
	newTriangle(&t, testvertices, (vector4_t){0.5, 0.2, 1, 1});
}

void RENDERER_render(SDL_Window* window) {
	glClearColor(0.5, 0.5, 0.5, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SDL_GL_SwapWindow(window);
}
