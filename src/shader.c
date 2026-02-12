#include "shader.h"

#include <stdio.h>

#include "arena.h"

static Arena_t arena;

void SHADER_init(u64 arena_size) {
	Arena_init(&arena, arena_size);
}

char* SHADER_loadShader(char* file) {
	FILE* shaderFile = fopen(file, "r");

	fseek(shaderFile, 0, SEEK_END);
	u32 len = ftell(shaderFile) + 1;
	fseek(shaderFile, 0, SEEK_SET);

	char* data = Arena_alloc(&arena, len);

	fread(data, sizeof(char), len, shaderFile);

	return data;
}

void SHADER_freeArena() {
	Arena_free(&arena);
}
