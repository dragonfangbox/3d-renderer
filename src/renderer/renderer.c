#include "renderer/renderer.h"
#include "renderer/shader.h"

#include "glad/gl.h"

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
			glDrawElements(GL_TRIANGLES, obj->mesh->indices.size, GL_UNSIGNED_INT, 0);
		} else {
			glUseProgram(obj->material->shader);
			RENDERER_setUniformMat4(obj->material, "model", obj->model);
			RENDERER_setUniformMat4(obj->material, "view", r->cam->view);
			RENDERER_setUniformMat4(obj->material, "proj", r->cam->proj);
			glBindVertexArray(r->objects.data[i]->VAO);
			glDrawArrays(GL_TRIANGLES, 0, r->objects.data[i]->mesh->vertices.size);
		}
	}

	SDL_GL_SwapWindow(window);
}

void RENDERER_destroy(renderer_t* r) {
	Arena_free(&r->arena);
	ARRAY_FREE(&r->objects);
}
