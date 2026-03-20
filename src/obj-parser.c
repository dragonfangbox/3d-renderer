#include "obj-parser.h"

#include <stdio.h>
#include <string.h>
#include "dynarr.h"

static void getVertices(char* line, floatArray_t* positions) {
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
		
		ARRAY_APPEND(positions, num);

		tok = strtok(NULL, " ");
		count++;
	}

	
}

// i think the best strat here is to have an array for each thing
// so i would have a vertex array, and indice array and an array for
// anything else. then when i find a line that starts with f, which has
// the format v/vt/vn, i would then reference the corresponding array.
// so if the face has v1/vt3/vn2, i would do vertarray[0]/texturecoordarray[2]/normalarray[1].
mesh_t OBJ_parseFile(const char* path) {
	// every group of 3 indices of this array is a vec3
	floatArray_t positions;
	ARRAY_INIT(&positions);
	indiceArray_t indices;
	ARRAY_INIT(&indices);

	mesh_t mesh = {0};

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
		
		if (strcmp(type, "v") == 0) {
			// line now points to the first number after the first space
			getVertices(line + 2, &positions);
		} else if (strcmp(type, "f") == 0) {

		} else if (strcmp(type, "vt") == 0) {

		}
		
	}

	printf("positions: { ");
	for (int i = 0; i < positions.size; i++) {
		printf("%f ", positions.data[i]);
	}
	printf("}\n");
	
	fclose(f);

	return mesh;
}
