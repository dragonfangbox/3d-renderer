#ifndef ARENA_H
#define ARENA_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define KiB 1024
#define MiB (KiB) * 1024
#define GiB (MiB) * 1024

typedef struct {
	size_t size;
	size_t capacity;
	unsigned char* memory;
} Arena_t;

void Arena_init(Arena_t* arena, size_t s);

void* Arena_alloc(Arena_t* arena, size_t s);
void Arena_free(Arena_t* arena);

#ifdef ARENA_IMPLEMENTATION
	void Arena_init(Arena_t* arena, size_t s) {
		arena->size = 0;
		arena->capacity = s;

		arena->memory= (unsigned char*)malloc(s);
		if (!arena->memory) {
			printf("ARENA FAILED TO ALLOC %zu BYTES\n", s);
		}
	}

	void* Arena_alloc(Arena_t* arena, size_t s) {
		if (arena->size + s > arena->capacity) {
			return NULL;
		}

		void* block = (arena->memory + arena->size);

		arena->size += s;

		return block;
	}

	void Arena_free(Arena_t* arena) {
		arena->size = 0;
		arena->capacity = 0;

		free(arena->memory);
	}
#endif

#endif // guard
