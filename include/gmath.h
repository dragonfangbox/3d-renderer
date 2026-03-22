#ifndef GMATH_H
#define GMATH_H

typedef float vec2[2];
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
void mat4_perspective(mat4 m, float near, float far, float fov, float aspect);
void mat4_lookAt(vec3 eye, vec3 at, vec3 up, mat4 dest);
// make a vec3 cross function
void vec3_subvec3(const vec3 v1, const vec3 v2, vec3 dest);
void vec3_addvec3(const vec3 v1, const vec3 v2, vec3 dest);
void vec3_unit(const vec3 v, vec3 dest);
float vec3_magnitude(const vec3 v);

float degToRad(float d);

#endif
