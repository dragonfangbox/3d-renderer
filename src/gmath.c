#include "gmath.h"
#include <math.h>
#include <stdio.h>

void vec3_print(vec3 v) {
	printf("{ %f, %f, %f }\n", v[0], v[1], v[2]);
}

void vec4_print(vec4 v) {
	printf("{ %f, %f, %f, %f }\n", v[0], v[1], v[2], v[3]);
}

void mat4_print(mat4 m) {
	printf("{\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%f ", m[i][j]);
		}
		printf("\n");
	}
	printf("}\n");
}

void mat4_identity(mat4 m) {
	m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
	m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
	m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
	m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
}

// m1 * m2. dest can be m1 or m2.
void mat4_multmat4(const mat4 m1, const mat4 m2, mat4 dest) {
	float a00 = m1[0][0], a01 = m1[0][1], a02 = m1[0][2], a03 = m1[0][3],
		  a10 = m1[1][0], a11 = m1[1][1], a12 = m1[1][2], a13 = m1[1][3],
		  a20 = m1[2][0], a21 = m1[2][1], a22 = m1[2][2], a23 = m1[2][3],
		  a30 = m1[3][0], a31 = m1[3][1], a32 = m1[3][2], a33 = m1[3][3];

	float b00 = m2[0][0], b01 = m2[0][1], b02 = m2[0][2], b03 = m2[0][3],
		  b10 = m2[1][0], b11 = m2[1][1], b12 = m2[1][2], b13 = m2[1][3],
		  b20 = m2[2][0], b21 = m2[2][1], b22 = m2[2][2], b23 = m2[2][3],
		  b30 = m2[3][0], b31 = m2[3][1], b32 = m2[3][2], b33 = m2[3][3];

	
	dest[0][0] = a00 * b00 + a01 * b10 + a02 * b20 + a03 * b30;
	dest[0][1] = a00 * b01 + a01 * b11 + a02 * b21 + a03 * b31;
	dest[0][2] = a00 * b02 + a01 * b12 + a02 * b22 + a03 * b32;
	dest[0][3] = a00 * b03 + a01 * b13 + a02 * b23 + a03 * b33;

	dest[1][0] = a10 * b00 + a11 * b10 + a12 * b20 + a13 * b30;
	dest[1][1] = a10 * b01 + a11 * b11 + a12 * b21 + a13 * b31;
	dest[1][2] = a10 * b02 + a11 * b12 + a12 * b22 + a13 * b32;
	dest[1][3] = a10 * b03 + a11 * b13 + a12 * b23 + a13 * b33;

	dest[2][0] = a20 * b00 + a21 * b10 + a22 * b20 + a23 * b30;
	dest[2][1] = a20 * b01 + a21 * b11 + a22 * b21 + a23 * b31;
	dest[2][2] = a20 * b02 + a21 * b12 + a22 * b22 + a23 * b32;
	dest[2][3] = a20 * b03 + a21 * b13 + a22 * b23 + a23 * b33;

	dest[3][0] = a30 * b00 + a31 * b10 + a32 * b20 + a33 * b30;
	dest[3][1] = a30 * b01 + a31 * b11 + a32 * b21 + a33 * b31;
	dest[3][2] = a30 * b02 + a31 * b12 + a32 * b22 + a33 * b32;
	dest[3][3] = a30 * b03 + a31 * b13 + a32 * b23 + a33 * b33;
}

// m * v. dest can be v.
// not implemented yet
void mat4_multvec4(const mat4 m, const vec4 v, vec4 dest);

void mat4_translate(mat4 m, vec3 t) {
	mat4 T = {0};
	mat4_identity(T);

	T[0][3] = t[0];
	T[1][3] = t[1];
	T[2][3] = t[2];

	mat4_multmat4(m, T, m);
}

void mat4_scale(mat4 m, vec3 s) {
	mat4 S = {0};
	mat4_identity(S);

	S[0][0] = s[0];
	S[1][1] = s[1];
	S[2][2] = s[2];

	mat4_multmat4(m, S, m);
}

void mat4_rotateX(mat4 m, float a) {
	mat4 r = {0};
	mat4_identity(r);

	r[1][1] = cos(a);
	r[1][2] = -sin(a);
	r[2][1] = sin(a);
	r[2][2] = cos(a);

	mat4_multmat4(m, r, m);
}

void mat4_rotateY(mat4 m, float a) {
	mat4 r = {0};
	mat4_identity(r);

	r[0][0] = cos(a);
	r[0][2] = sin(a);
	r[2][0] = -sin(a);
	r[2][2] = cos(a);

	mat4_multmat4(m, r, m);
}

void mat4_rotateZ(mat4 m, float a) {
	mat4 r = {0};
	mat4_identity(r);

	r[0][0] = cos(a);
	r[0][1] = -sin(a);
	r[1][0] = sin(a);
	r[1][1] = cos(a);

	mat4_multmat4(m, r, m);
}

void mat4_perspective(mat4 m, float near, 
					  float far, float fov, 
					  float aspect) 
{
	mat4 p = {0};
	
	p[0][0] = 1 / (tan(fov / 2) * aspect);
	p[1][1] = 1 / (tan(fov / 2));
	p[2][2] = (far + near) / (near - far);
	p[2][3] = (2 * far * near) / (near - far);
	p[3][2] = -1;

	mat4_multmat4(m, p, m);
}

// up should typically be (0, 1, 0)
void mat4_lookAt(mat4 m, vec3 eye, vec3 center, vec3 up) {
	vec3 forward, right, trueUp;

	vec3_subvec3(center, eye, forward);
	vec3_unit(forward);

	vec3_cross(forward, up, right);
	vec3_unit(right);

	vec3_cross(right, forward, trueUp);
	vec3_unit(trueUp);

	mat4 l = {0};
	l[0][0] = right[0];	   l[0][1] = right[1];    l[0][2] = right[2];    l[0][3] = -vec3_dot(right, eye);
	l[1][0] = trueUp[0];   l[1][1] = trueUp[1];   l[1][2] = trueUp[2];   l[1][3] = -vec3_dot(trueUp, eye);
	l[2][0] = -forward[0]; l[2][1] = -forward[1]; l[2][2] = -forward[2]; l[2][3] = vec3_dot(forward, eye);
	l[3][0] = 0;		   l[3][1] = 0;			  l[3][2] = 0;			 l[3][3] = 1;

	mat4_multmat4(m, l, m);
}

void vec3_cross(const vec3 v1, const vec3 v2, vec3 dest) {
	float x = v1[1] * v2[2] - v1[2] * v2[1];
	float y = v1[2] * v2[0] - v1[0] * v2[2];
	float z = v1[0] * v2[1] - v1[1] * v2[0];
	dest[0] = x;
	dest[1] = y;
	dest[2] = z;
}

void vec3_subvec3(const vec3 v1, const vec3 v2, vec3 dest) {
	dest[0] = v1[0] - v2[0];
	dest[1] = v1[1] - v2[1];
	dest[2] = v1[2] - v2[2];
}

void vec3_addvec3(const vec3 v1, const vec3 v2, vec3 dest) {
	dest[0] = v1[0] + v2[0];
	dest[1] = v1[1] + v2[1];
	dest[2] = v1[2] + v2[2];
}

void vec3_unit(vec3 v) {
	float mag = vec3_magnitude(v);
	if (mag == 0) {
		v[0] = v[1] = v[2] = 0.0f;
		return;
	}

	v[0] = v[0] / mag;
	v[1] = v[1] / mag;
	v[2] = v[2] / mag;
}

inline float vec3_magnitude(const vec3 v) {
	return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

inline float vec3_dot(const vec3 v1, const vec3 v2) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

inline float degToRad(float d) {
	return (d) * (PI / 180);
}
