#include "obj-parser.h"

#include <stdio.h>
#include <string.h>

static void getVertices(char* line) {
	k
}

void OBJ_parseFile(const char* path, vec3* v, vec3* i) {
	FILE* f = fopen(path, "r");
	if(f == NULL) {
		printf("%s : Failed to open file\n", __FILE_NAME__);
		return;
	}

	char line[64];
	while((fgets(line, sizeof(line), f)) != NULL) {
		unsigned int len = strcspn(line, " \n\t");
		char type[2]; 	

		strncpy(type, line, len);
		type[len] = '\0';
		
		if (strcmp(type, "v") == 0) {
			printf("vertex\n");
		} else if (strcmp(type, "f") == 0) {
			printf("face\n");
		} else if (strcmp(type, "vt") == 0) {
			printf("texture coord\n");
		}
		
}
	
	fclose(f);
}
