#include "types.h"
#include "arena.h"

#include "renderer.h"
#include "sdl.h"

int main() {
	
	InitSDL();

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_Window* window = InitWindowOPENGL("renderer test", 1280, 720);
	SDL_ShowWindow(window);

	SDL_GLContext glctx = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, glctx);

	if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
		printf("Failed to init GL funcs\n");
		return -1;
	}

	printf("OpenGL: %s\n", glGetString(GL_VERSION));

	glViewport(0, 0, 1280, 720);

	bool running = TRUE;
	while(running) {
		SDL_Event event;
		while((SDL_PollEvent(&event))) {
			if (event.type == SDL_QUIT) {
				running = FALSE;
			}
		}

		RENDERER_update();

		RENDERER_render(window);
	}

	SDL_Quit();
	return 0;
}
