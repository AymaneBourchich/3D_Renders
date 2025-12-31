#pragma once
#include <GL/glew.h>

void generateArrays(GLuint& vao, GLuint& vbo);
void uploadVerts(GLuint& vao, GLuint& vbo, const float *verts, size_t vertBytes);
void uploadVertsTextured(GLuint& vao, GLuint& vbo, const float *verts, size_t vertBytes);