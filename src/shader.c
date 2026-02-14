#include "shader.h"

#include "arena.h"

static Arena_t arena;

void SHADER_init(u64 arena_size) {
	Arena_init(&arena, arena_size);
}

char* SHADER_loadShader(char* file) {
	FILE* shaderFile = fopen(file, "r");

	fseek(shaderFile, 0, SEEK_END);
	u32 len = ftell(shaderFile);
	fseek(shaderFile, 0, SEEK_SET);

	char* data = Arena_alloc(&arena, len + 1);

	fread(data, sizeof(char), len, shaderFile);

	data[len + 1] = '\0';

	return data;
}

void SHADER_freeArena() {
	Arena_free(&arena);
}
