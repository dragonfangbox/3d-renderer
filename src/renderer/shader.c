#include "renderer.h"

void RENDERER_setUniformMat4(material_t* m, const char* name, mat4 mat) {
	GLuint location = glGetUniformLocation(m->shader, name);
	glUniformMatrix4fv(location, 1, GL_TRUE, (float*)mat);
}
