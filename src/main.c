
#define ARENA_IMPLEMENTATION
#include "arena.h"
#include "types.h"
#include "renderer.h"
#include "sdl.h"
#include "shader.h"

int main() {
	InitSDLGL(3, 3);

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
	camera_t cam = {0};
	mat4_identity(cam.proj);
	mat4_identity(cam.view);
	mat4_perspective(cam.proj, 0, 1, PI/2.0, 1280.0/720.0);
	mat4_translate(cam.view, (vec3){0, 0, -3});
	RENDERER_init(&renderer, &cam);

	renderObject_t testObj;
	mesh_t triangleMesh;
	material_t defaultMaterial;

	vertArray_t triangleVertices;
	ARRAY_INIT(&triangleVertices);
	ARRAY_APPEND(&triangleVertices, ((vertex_t){{0.5, -1, 0}, {1, 0, 0}}));
	ARRAY_APPEND(&triangleVertices, ((vertex_t){{0, 0.5, 0}, {0, 1, 0}}));
	ARRAY_APPEND(&triangleVertices, ((vertex_t){{-0.5, -1, 0}, {0, 0, 1}}));
	RENDERER_initMesh(&triangleMesh, triangleVertices, NULL);

	mesh_t cube;
	vertArray_t cubeVertices;
	ARRAY_INIT(&cubeVertices);
	// BACK (-Z)
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{-1,-1,-1}, {1,0,0}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{ 1,-1,-1}, {0,1,0}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{ 1, 1,-1}, {0,0,1}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{ 1, 1,-1}, {0,0,1}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{-1, 1,-1}, {1,1,0}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{-1,-1,-1}, {1,0,0}}));

	// FRONT (+Z)
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{-1,-1, 1}, {1,0,1}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{ 1,-1, 1}, {0,1,1}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{ 1, 1, 1}, {0.5f,0,1}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{ 1, 1, 1}, {0.5f,0,1}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{-1, 1, 1}, {1,0.5f,0}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{-1,-1, 1}, {1,0,1}}));

	// LEFT (-X)
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{-1, 1, 1}, {1,0.5f,0}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{-1, 1,-1}, {1,1,0}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{-1,-1,-1}, {1,0,0}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{-1,-1,-1}, {1,0,0}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{-1,-1, 1}, {1,0,1}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{-1, 1, 1}, {1,0.5f,0}}));

	// RIGHT (+X)
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{ 1, 1, 1}, {0.5f,0,1}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{ 1, 1,-1}, {0,0,1}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{ 1,-1,-1}, {0,1,0}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{ 1,-1,-1}, {0,1,0}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{ 1,-1, 1}, {0,1,1}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{ 1, 1, 1}, {0.5f,0,1}}));

	// BOTTOM (-Y)
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{-1,-1,-1}, {1,0,0}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{ 1,-1,-1}, {0,1,0}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{ 1,-1, 1}, {0,1,1}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{ 1,-1, 1}, {0,1,1}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{-1,-1, 1}, {1,0,1}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{-1,-1,-1}, {1,0,0}}));

	// TOP (+Y)
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{-1, 1,-1}, {1,1,0}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{ 1, 1,-1}, {0,0,1}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{ 1, 1, 1}, {0.5f,0,1}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{ 1, 1, 1}, {0.5f,0,1}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{-1, 1, 1}, {1,0.5f,0}}));
	ARRAY_APPEND(&cubeVertices, ((vertex_t){{-1, 1,-1}, {1,1,0}}));
	RENDERER_initMesh(&cube, cubeVertices, NULL);
	RENDERER_initMaterial(&defaultMaterial, program);

	RENDERER_initRenderObject(&testObj, &cube, &defaultMaterial);

//	RENDERER_translateObject(&testObj, 0.5, 0.5, 0);

	RENDERER_pushObject(&renderer, testObj);

	bool running = TRUE;
	while(running) {
		SDL_Event event;
		while((SDL_PollEvent(&event))) {
			if (event.type == SDL_QUIT) {
				running = FALSE;
			}
		}

//		RENDERER_update(&renderer);
//
		
		RENDERER_rotateObjectY(&testObj, degToRad(360));
		RENDERER_rotateObjectX(&testObj, degToRad(360));
		RENDERER_setUniformMat4(&defaultMaterial, "model", testObj.model);
		RENDERER_setUniformMat4(&defaultMaterial, "view", renderer.cam->view);
		RENDERER_setUniformMat4(&defaultMaterial, "proj", renderer.cam->proj);
		RENDERER_render(&renderer, window);
	}

	RENDERER_destroy(&renderer);
	SDL_Quit();
	return 0;
}
