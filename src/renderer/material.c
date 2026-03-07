#include "renderer/material.h"

void RENDERER_initMaterial(material_t* m, GLuint program) {
	m->shader = program;
}
