#ifndef DYNARR_H
#define DYNARR_H

#define next_cap(curr) (curr != 0 ? curr * 2 : 8)
	
#define ARRAY_DEFINE(NAME, TYPE) \
	typedef struct { \
		int size; \
		int capacity; \
		TYPE* data; \
	} NAME; \

#define ARRAY_INIT(ARR) do { \
	(ARR)->size = 0;\
	(ARR)->capacity = 0;\
	(ARR)->data = NULL;\
} while (0) 

#define ARRAY_APPEND(ARR, x) do { \
	if ((ARR)->size >= (ARR)->capacity) { \
		(ARR)->capacity = next_cap((ARR)->capacity);\
		void* newData = realloc((ARR)->data, (ARR)->capacity * sizeof(*(ARR)->data));\
		if (!newData) {\
			printf("Failed to realloc dynamic array!\n");\
		}\
		\
		(ARR)->data = newData;\
	}\
	\
	(ARR)->data[(ARR)->size] = (x);\
	(ARR)->size++;\
} while(0)

#define ARRAY_FREE(ARR) do { \
	free((ARR)->data);\
	(ARR)->data= NULL;\
	(ARR)->size = 0;\
	(ARR)->capacity = 0;\
} while (0)

#endif
