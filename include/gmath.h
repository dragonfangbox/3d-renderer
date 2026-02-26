#ifndef GMATH_H
#define GMATH_H

typedef float vec3[3];
typedef float vec4[4];

typedef vec4 mat4[4];

#define PI 3.14159265358979323846

void vec3_print(vec3 v);
void vec4_print(vec4 v);
void mat4_print(mat4 m);

void mat4_identity(mat4 m);
void mat4_multmat4(mat4 m1, mat4 m2, mat4 dest);
void mat4_multvec4(mat4 m, vec4 v, vec4 dest);

void mat4_translate(mat4 m, vec3 t);
void mat4_scale(mat4 m, vec3 s);
void mat4_rotateX(mat4 m, float a);
void mat4_rotateY(mat4 m, float a);
void mat4_rotateZ(mat4 m, float a);

#endif
