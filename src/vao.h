#pragma once
#include <GL/glew.h>

void generateArrays(GLuint &vao, GLuint &vbo, GLuint &ebo);
void uploadVerts(GLuint &vao, GLuint vbo, GLuint ebo, const float *verts, size_t vertBytes, const unsigned int *indices, size_t indexCount);
void uploadVertsColored(GLuint &vao, GLuint vbo, GLuint ebo, const float *verts, size_t vertBytes, const unsigned int *indices, size_t indexCount);
void uploadVertsTextured(GLuint &vao, GLuint vbo, GLuint ebo, const float *verts, size_t vertBytes, const unsigned int *indices, size_t indexCount);
