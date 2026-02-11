#include "../include/sdl.h"

void InitSDL() {
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL FAILED TO LOAD\n");
	}
}


void InitSDLImage() {
	if(!IMG_Init(IMG_INIT_PNG || IMG_INIT_JPG)) {
		printf("SDLIMAGE FAILED TO LOAD\n");
	}
}

SDL_Window* InitWindowOPENGL(char* name, int w, int h) {
	SDL_Window* window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	return window;
}


SDL_Renderer* InitRenderer(SDL_Window* window) {
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	return renderer;
}
