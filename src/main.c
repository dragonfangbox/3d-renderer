
#define ARENA_IMPLEMENTATION
#include "arena.h"
#include "types.h"
#include "renderer.h"
#include "sdl.h"
#include "shader.h"

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

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

	glViewport(0, 0, 1280, 720);

	SHADER_init(MiB);
	const char* fragShadersrc = SHADER_loadShader("./src/shaders/fragment-shader.frag");
	const char* vertShadersrc = SHADER_loadShader("./src/shaders/vertex-shader.vert");

	u16 fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShadersrc, NULL);
	glCompileShader(fragShader);

	u16 vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertShadersrc, NULL);
	glCompileShader(vertShader);

	u16 program = glCreateProgram();
	glAttachShader(program, fragShader);
	glAttachShader(program, vertShader);
	glLinkProgram(program);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	renderer_t renderer;
	RENDERER_init(&renderer);


	renderObject_t testObj;
	renderObject_t testObj2;

	mesh_t triangleMesh;
	vertArray_t triangleVertices;
	ARRAY_INIT(&triangleVertices);
	ARRAY_APPEND(&triangleVertices, ((vertex_t){{0.5, -1, 0}, {1, 0, 0}}));
	ARRAY_APPEND(&triangleVertices, ((vertex_t){{0, 0.5, 0}, {0, 1, 0}}));
	ARRAY_APPEND(&triangleVertices, ((vertex_t){{-0.5, -1, 0}, {0, 0, 1}}));
	RENDERER_initMesh(&triangleMesh, triangleVertices, NULL);

	mesh_t triangleMesh2;
	vertArray_t triangleVertices2;
	ARRAY_INIT(&triangleVertices2);
	ARRAY_APPEND(&triangleVertices2, ((vertex_t){{-1, -1, 0}, {1, 1, 0}}));
	ARRAY_APPEND(&triangleVertices2, ((vertex_t){{-1, 1, 0}, {0, 1, 1}}));
	ARRAY_APPEND(&triangleVertices2, ((vertex_t){{0, 1, 0}, {1, 0, 1}}));
	RENDERER_initMesh(&triangleMesh2, triangleVertices2, NULL);

	RENDERER_initRenderObject(&testObj, &triangleMesh);
	RENDERER_initRenderObject(&testObj2, &triangleMesh2);

	RENDERER_pushObject(&renderer, testObj);
	RENDERER_pushObject(&renderer, testObj2);

	bool running = TRUE;
	while(running) {
		SDL_Event event;
		while((SDL_PollEvent(&event))) {
			if (event.type == SDL_QUIT) {
				running = FALSE;
			}
		}

		RENDERER_update(&renderer);

		glUseProgram(program);
		RENDERER_render(&renderer, window);
	}

	RENDERER_destroy(&renderer);
	SDL_Quit();
	return 0;
}
