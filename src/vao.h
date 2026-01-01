#pragma once
#include <GL/glew.h>

void generateArrays(GLuint &vao, GLuint &vbo);
void uploadVerts(GLuint &vao, GLuint &vbo, const float *verts, size_t vertBytes);
void uploadVertsTextured(GLuint &vao, GLuint &vbo, const float *verts, size_t vertBytes);
void uploadVertsIndexed(GLuint &vao, GLuint vbo, GLuint ebo, const float *verts, size_t vertBytes, const unsigned int *indices,size_t indexCount);