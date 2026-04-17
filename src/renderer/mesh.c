#include "renderer/mesh.h"

void RENDERER_initMesh(mesh_t* m) {
	glGenVertexArrays(1, &m->VAO);
	glBindVertexArray(m->VAO);

	glGenBuffers(1, &m->VBO);

	if (m->indices.data != NULL) {
		glGenBuffers(1, &m->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->EBO);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
					 sizeof(int) * m->indices.size,
					 m->indices.data,
					 GL_STATIC_DRAW
					 );
	}

	glBindBuffer(GL_ARRAY_BUFFER, m->VBO);
	glBufferData(GL_ARRAY_BUFFER, 
				 sizeof(vertex_t) * m->vertices.size, 
				 m->vertices.data,
				 GL_STATIC_DRAW
				 );

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, pos));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, color));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
