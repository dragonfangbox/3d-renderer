#include "renderer/shader.h"

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

GLuint SHADER_createProgram(const char* fragsrc,
							const char* vertsrc) {
	
	u16 fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragsrc, NULL);
	glCompileShader(fragShader);

	u16 vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertsrc, NULL);
	glCompileShader(vertShader);

	u16 program = glCreateProgram();
	glAttachShader(program, fragShader);
	glAttachShader(program, vertShader);
	glLinkProgram(program);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return program;
}

void SHADER_deinit() {
	Arena_free(&arena);
}

void RENDERER_setUniformMat4(material_t* m, const char* name, mat4 mat) {
	GLuint location = glGetUniformLocation(m->shader, name);
	glUniformMatrix4fv(location, 1, GL_TRUE, (float*)mat);
}
