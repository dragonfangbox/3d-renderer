#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
typedef struct {
	float x;
	float y;
} vector2_t;

typedef struct {
	float x;
	float y;
	float z;
} vector3_t;

typedef struct {
	float x;
	float y;
	float z;
	float w;
} vector4_t;

typedef uint8_t bool;
#define TRUE 1
#define FALSE 0

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#endif
