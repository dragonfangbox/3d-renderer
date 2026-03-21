#define ARENA_IMPLEMENTATION
#include "arena.h"
#include "types.h"
#include "sdl.h"
#include "renderer/all.h"
#include "obj-parser.h"

#define WIDTH 720.0
#define HEIGHT 480.0

int main() {
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
	glFrontFace(GL_CW);

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
	mat4_identity(cam.view);
	mat4_identity(cam.proj);
	mat4_perspective(cam.proj, 0, 1, PI/4.0, WIDTH/HEIGHT);
	mat4_translate(cam.view, (vec3){0, 0, -3});
	RENDERER_init(&renderer, &cam);

	renderObject_t testObj;

	mesh_t triangleMesh;
	mesh_t cube;
	mesh_t objTest = OBJ_parseFile("./untitled.obj");
	RENDERER_initMesh(&objTest);

	ARRAY_INIT(&triangleMesh.vertices);
	ARRAY_APPEND(&triangleMesh.vertices, ((vertex_t){{0.5, -1, 0}, {1, 0, 0}}));
	ARRAY_APPEND(&triangleMesh.vertices, ((vertex_t){{0, 0.5, 0}, {0, 1, 0}}));
	ARRAY_APPEND(&triangleMesh.vertices, ((vertex_t){{-0.5, -1, 0}, {0, 0, 1}}));
	RENDERER_initMesh(&triangleMesh);

	ARRAY_INIT(&cube.vertices);
	ARRAY_APPEND(&cube.vertices, ((vertex_t){{-0.5f,-0.5f,-0.5f},{1.0f,0.0f,0.0f}})); // 0
	ARRAY_APPEND(&cube.vertices, ((vertex_t){{ 0.5f,-0.5f,-0.5f},{0.0f,1.0f,0.0f}})); // 1
	ARRAY_APPEND(&cube.vertices, ((vertex_t){{ 0.5f, 0.5f,-0.5f},{0.0f,0.0f,1.0f}})); // 2
	ARRAY_APPEND(&cube.vertices, ((vertex_t){{-0.5f, 0.5f,-0.5f},{1.0f,1.0f,0.0f}})); // 3
	ARRAY_APPEND(&cube.vertices, ((vertex_t){{-0.5f,-0.5f, 0.5f},{1.0f,0.0f,1.0f}})); // 4
	ARRAY_APPEND(&cube.vertices, ((vertex_t){{ 0.5f,-0.5f, 0.5f},{0.0f,1.0f,1.0f}})); // 5
	ARRAY_APPEND(&cube.vertices, ((vertex_t){{ 0.5f, 0.5f, 0.5f},{1.0f,0.5f,0.0f}})); // 6
	ARRAY_APPEND(&cube.vertices, ((vertex_t){{-0.5f, 0.5f, 0.5f},{0.5f,0.0f,1.0f}})); // 7
																					 
	ARRAY_INIT(&cube.indices);
	// Front (-Z)
	ARRAY_APPEND(&cube.indices, 0);
	ARRAY_APPEND(&cube.indices, 1);
	ARRAY_APPEND(&cube.indices, 2);

	ARRAY_APPEND(&cube.indices, 2);
	ARRAY_APPEND(&cube.indices, 3);
	ARRAY_APPEND(&cube.indices, 0);

	// Back (+Z)
	ARRAY_APPEND(&cube.indices, 4);
	ARRAY_APPEND(&cube.indices, 6);
	ARRAY_APPEND(&cube.indices, 5);

	ARRAY_APPEND(&cube.indices, 6);
	ARRAY_APPEND(&cube.indices, 4);
	ARRAY_APPEND(&cube.indices, 7);

	// Left (-X)
	ARRAY_APPEND(&cube.indices, 4);
	ARRAY_APPEND(&cube.indices, 0);
	ARRAY_APPEND(&cube.indices, 3);

	ARRAY_APPEND(&cube.indices, 3);
	ARRAY_APPEND(&cube.indices, 7);
	ARRAY_APPEND(&cube.indices, 4);

	// Right (+X)
	ARRAY_APPEND(&cube.indices, 1);
	ARRAY_APPEND(&cube.indices, 5);
	ARRAY_APPEND(&cube.indices, 6);

	ARRAY_APPEND(&cube.indices, 6);
	ARRAY_APPEND(&cube.indices, 2);
	ARRAY_APPEND(&cube.indices, 1);

	// Bottom (-Y)
	ARRAY_APPEND(&cube.indices, 4);
	ARRAY_APPEND(&cube.indices, 5);
	ARRAY_APPEND(&cube.indices, 1);

	ARRAY_APPEND(&cube.indices, 1);
	ARRAY_APPEND(&cube.indices, 0);
	ARRAY_APPEND(&cube.indices, 4);

	// Top (+Y)
	ARRAY_APPEND(&cube.indices, 3);
	ARRAY_APPEND(&cube.indices, 2);
	ARRAY_APPEND(&cube.indices, 6);

	ARRAY_APPEND(&cube.indices, 6);
	ARRAY_APPEND(&cube.indices, 7);
	ARRAY_APPEND(&cube.indices, 3);

	RENDERER_initMesh(&cube);
	material_t defaultMaterial;
	RENDERER_initMaterial(&defaultMaterial, program);

	RENDERER_initRenderObject(&testObj, &objTest, &defaultMaterial);

//	RENDERER_translateObject(&testObj, (vec3){0, 0.5, 0.5});

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
					mat4_translate(renderer.cam->view, (vec3){0, 0, 0.5});
					break;
				case SDL_SCANCODE_A:
					mat4_translate(renderer.cam->view, (vec3){0.5, 0, 0});
					break;
				case SDL_SCANCODE_S:
					mat4_translate(renderer.cam->view, (vec3){0, 0, -0.5});
					break;
				case SDL_SCANCODE_D:
					mat4_translate(renderer.cam->view, (vec3){-0.5, 0, 0});
					break;
				case SDL_SCANCODE_E:
					mat4_translate(renderer.cam->view, (vec3){0, -0.5, 0});
					break;
				case SDL_SCANCODE_Q:
					mat4_translate(renderer.cam->view, (vec3){0, 0.5, 0});
					break;
				default:
					break;
				}
			} else if (event.type == SDL_WINDOWEVENT && 
					   event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				
				int w, h;
				SDL_GL_GetDrawableSize(window, &w, &h);

				renderer.screenSize[0] = w;
				renderer.screenSize[1] = h;

				mat4_identity(renderer.cam->proj);
				mat4_perspective(renderer.cam->proj, 0, 1, PI/2.0, (float)w/h);
				
				glViewport(0, 0, w, h);	
			}
		}

		RENDERER_render(&renderer, window);
	}

	RENDERER_destroy(&renderer);
	SDL_Quit();
	return 0;
}
