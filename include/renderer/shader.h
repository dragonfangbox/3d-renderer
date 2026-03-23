#ifndef RENDERER_SHADER_H
#define RENDERER_SHADER_H

#include "types.h"
#include "glad/gl.h"
#include "gmath.h"

void SHADER_init(u64 arena_size);
char* SHADER_loadShader(char* file);
GLuint SHADER_createProgram(const char* fragsrc, const char* vertsrc);
void SHADER_deinit();

void RENDERER_setUniformMat4(material_t* m, const char* name, mat4 mat);

#endif

