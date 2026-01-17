#pragma once
#include <GL/glew.h>

void generateArrays(GLuint &vao, GLuint &vbo, GLuint &ebo);
void uploadVerts(GLuint &vao, GLuint vbo, GLuint ebo, const float *verts, size_t vertBytes, const unsigned int *indices, size_t indexCount);
void uploadVertsColored(GLuint &vao, GLuint vbo, GLuint ebo, const float *verts, size_t vertBytes, const unsigned int *indices, size_t indexCount);
template <size_t VERT_COUNT, size_t INDEX_COUNT>
void uploadVertsTextured(GLuint &vao, GLuint vbo, GLuint ebo,
                         const float (&verts)[VERT_COUNT],
                         const unsigned int (&indices)[INDEX_COUNT])
{
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, VERT_COUNT * sizeof(float), verts, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDEX_COUNT * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // position (location = 0) -> vec3
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // UV (location = 1) -> vec2
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}
