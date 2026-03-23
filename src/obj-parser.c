#include "obj-parser.h"

#include <stdio.h>
#include <string.h>
#include "dynarr.h"
#include <math.h>

static void getVertices(char* line, floatArray_t* vbuf) {
	unsigned int count = 0;
	char* tok = strtok(line, " ");
	while (tok != NULL) {
		if(count == 3) {
			return;
		}

		char* end;
		float num = strtof(tok, &end);
		if (end == tok) {
			printf("%s : Failed to read vertex value, returning...\n", __FILE_NAME__);
			return;
		}
		
		ARRAY_APPEND(vbuf, num);

		tok = strtok(NULL, " ");
		count++;
	}
}

// i dont think i need to pass vnbuf and vtbuf but idk (look above "face" variable)
static void getFace(char* line, indiceArray_t* fbuf, floatArray_t* vnbuf, floatArray_t* vtbuf) {
	char* outPtr = NULL;
	char* inPtr = NULL;

	// i think i should make the face a vec4 of vec3s where each vec3 defines a vertex (v/vt/vn)
	vec4 face = {0};
	unsigned int otherCount = 0;

	char* outTok = strtok_r(line, " ", &outPtr);
	while (outTok != NULL) {
		unsigned int count = 0;

		char* inTok = strtok_r(outTok, "/", &inPtr);
		while (inTok != NULL) {
			// tacky fix to avoid messing with vn and vt, add support for those in here 
			// get rid of otherCount this is so janky holy cow
			if (count == 0) {
				face[otherCount] = strtof(inTok, NULL);
			}
			
			inTok = strtok_r(NULL, "/", &inPtr);
			count++;
		}

		otherCount++;
		outTok = strtok_r(NULL, " ", &outPtr);
	}

	if (otherCount == 4) {
		ARRAY_APPEND(fbuf, face[0] - 1);
		ARRAY_APPEND(fbuf, face[1] - 1);
		ARRAY_APPEND(fbuf, face[2] - 1);

		ARRAY_APPEND(fbuf, face[0] - 1);
		ARRAY_APPEND(fbuf, face[2] - 1);
		ARRAY_APPEND(fbuf, face[3] - 1);

	} else if (otherCount == 3) {
		ARRAY_APPEND(fbuf, face[0] - 1);
		ARRAY_APPEND(fbuf, face[1] - 1);
		ARRAY_APPEND(fbuf, face[2] - 1);
	} else {
		printf("%s : %d | Unknown amount of vertices in face\n", __FILE_NAME__, __LINE__);	
	}
}

mesh_t OBJ_parseFile(const char* path) {
	// every group of 3 indices of this array is a vec3
	floatArray_t  vbuf;
	indiceArray_t fbuf;
	floatArray_t  vtbuf;
	floatArray_t  vnbuf;
	ARRAY_INIT(&vbuf);
	ARRAY_INIT(&fbuf);
	ARRAY_INIT(&vtbuf);
	ARRAY_INIT(&vnbuf);

	mesh_t mesh = {0};
	ARRAY_INIT(&mesh.vertices);

	FILE* f = fopen(path, "r");
	if(f == NULL) {
		printf("%s : Failed to open file, %s\n", __FILE_NAME__, path);
	}

	char line[64];
	while((fgets(line, sizeof(line), f)) != NULL) {
		unsigned int len = strcspn(line, " \n\t");
		char type[2]; 	

		strncpy(type, line, len);
		type[len] = '\0';
		
		if (line[0] == '#') {
			continue;
		} else if (strcmp(type, "v") == 0) {
			// line now points to the first number after the first space
			getVertices(line + len + 1, &vbuf);
		} else if (strcmp(type, "f") == 0) {
			// i think the line "f 1 2 3 4" should get interpreted as 2 different vertices
			// with positions of,
			// v1 v2 v3, v1 v3 v4

			getFace(line + len + 1, &fbuf, &vnbuf, &vtbuf);
		} else if (strcmp(type, "vt") == 0) {

		}
	}
	
	fclose(f);

	mesh.indices = fbuf;

	for (int i = 0; i < vbuf.size / 3; i++) {
		vertex_t v = {0};
		v.pos[0] = vbuf.data[i * 3];
		v.pos[1] = vbuf.data[i * 3 + 1];
		v.pos[2] = vbuf.data[i * 3 + 2];
		v.color[0] = sin(i % 3);
		v.color[1] = sin(i * 0.3);
		v.color[2] = sin(i);
		v.color[3] = 1;

		ARRAY_APPEND(&mesh.vertices, v); 
	}

	return mesh;
}
