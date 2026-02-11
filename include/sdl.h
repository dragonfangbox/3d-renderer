#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void InitSDL(); 
void InitSDLImage(); 

SDL_Window* InitWindowOPENGL(char* name, int w, int h); 
SDL_Renderer* InitRenderer(SDL_Window* window);;

#endif
