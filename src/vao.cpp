#include "vao.h"

void generateArrays(GLuint& vao, GLuint& vbo)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
}
void uploadVerts(GLuint& vao, GLuint& vbo, const float *verts, size_t vertBytes)
{
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)vertBytes, verts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * (GLsizei)sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void uploadVertsTextured(GLuint& vao, GLuint& vbo, const float *verts, size_t vertBytes)
{
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)vertBytes, verts, GL_STATIC_DRAW);

    // position (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // uv (location = 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}