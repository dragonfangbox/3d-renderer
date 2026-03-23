#define ARENA_IMPLEMENTATION
#include "arena.h"
#include "types.h"
#include "sdl.h"
#include "renderer/all.h"
#include "obj-parser.h"

#define WIDTH 720.0
#define HEIGHT 480.0

int main() {
	window_t win = {.size = {720, 480}};
	camera_t cam = {0};

	mat4_identity(cam.view);
	mat4_lookAt(cam.view, (vec3){5, 3, 2}, (vec3){0, 0, 0}, (vec3){0, 1, 0});
	mat4_identity(cam.proj);
	mat4_perspective(cam.proj, 0, 1, PI/4.0, WIDTH/HEIGHT);

	renderer_t renderer;
	RENDERER_init(&renderer, &win, &cam);

	InitSDLGL(3, 3);

	SDL_Window* window = InitWindowOPENGL("renderer test", WIDTH, HEIGHT);
	SDL_ShowWindow(window);

	SDL_GLContext glctx = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, glctx);

	if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
		printf("Failed to init GL funcs\n");
		return -1;
	}

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

	glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	SHADER_init(MiB);
	const char* fragShadersrc = SHADER_loadShader("./src/shaders/fragment-shader.frag");
	const char* vertShadersrc = SHADER_loadShader("./src/shaders/vertex-shader.vert");
	u16 program = SHADER_createProgram(fragShadersrc, vertShadersrc);


	renderObject_t testObj;

	mesh_t objTest = OBJ_parseFile("./cube.obj");
	RENDERER_initMesh(&objTest);

	material_t defaultMaterial;
	RENDERER_initMaterial(&defaultMaterial, program);

	RENDERER_initRenderObject(&testObj, &objTest, &defaultMaterial);

//	RENDERER_translateObject(&testObj, (vec3){0, 1, 0});

	RENDERER_pushObject(&renderer, &testObj);


	bool running = TRUE;
	while(running) {
		SDL_Event event;
		while((SDL_PollEvent(&event))) {
			if (event.type == SDL_QUIT) {
				running = FALSE;
			} else if (event.key.type == SDL_KEYDOWN) {
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_W:
					break;
				case SDL_SCANCODE_A:
					break;
				case SDL_SCANCODE_S:
					break;
				case SDL_SCANCODE_D:
					break;
				case SDL_SCANCODE_E:
					break;
				case SDL_SCANCODE_Q:
					break;
				default:
					break;
				}
			} else if (event.type == SDL_WINDOWEVENT && 
					   event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				
				i32 w, h;
				SDL_GL_GetDrawableSize(window, &w, &h);

				renderer.window->size[0] = w;
				renderer.window->size[1] = h;

				mat4_identity(renderer.camera->proj);
				mat4_perspective(renderer.camera->proj, 0, 1, PI/4.0, (float)w/h);
				
				glViewport(0, 0, w, h);	
			}
		}

		RENDERER_render(&renderer, window);
	}

	RENDERER_destroy(&renderer);
	SDL_Quit();
	return 0;
}
