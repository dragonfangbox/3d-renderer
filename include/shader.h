#ifndef SHADER_H
#define SHADER_H

#include "types.h"

void SHADER_init(u64 arena_size);

char* SHADER_loadShader(char* file);
void SHADER_freeArena();

#endif
