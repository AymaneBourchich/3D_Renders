#pragma once
#include <GL/glew.h>

static inline void generateArrays(GLuint &vao, GLuint &vbo, GLuint &ebo)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
}
// template version of uploadVerts
template <size_t VERT_COUNT, size_t INDEX_COUNT>
static inline void uploadVerts(GLuint &vao, GLuint vbo, GLuint ebo,
                 const float (&verts)[VERT_COUNT],
                 const unsigned int (&indices)[INDEX_COUNT])
{
    glBindVertexArray(vao);

    // Upload vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, VERT_COUNT * sizeof(float), verts, GL_STATIC_DRAW);

    // Upload index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDEX_COUNT * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // position (location = 0) -> vec3
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // IMPORTANT: do NOT unbind EBO while VAO is bound
    glBindVertexArray(0);
}

static inline void uploadVertsColored(GLuint &vao, GLuint vbo, GLuint ebo, const float *verts, size_t vertBytes, const unsigned int *indices, size_t indexCount)
{
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)vertBytes, verts, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(indexCount * sizeof(unsigned int)), indices, GL_STATIC_DRAW);

    // position (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}
template <size_t VERT_COUNT, size_t INDEX_COUNT>
static inline void uploadVertsTextured(GLuint &vao, GLuint vbo, GLuint ebo,
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

template <size_t VERT_COUNT, size_t INDEX_COUNT>
inline void setupVAO(GLuint &vao, GLuint &vbo, GLuint &ebo,
                     const float (&verts)[VERT_COUNT],
                     const unsigned int (&indices)[INDEX_COUNT])
{
    generateArrays(vao, vbo, ebo);
    uploadVerts(vao, vbo, ebo, verts, indices);
}

template <size_t VERT_COUNT, size_t INDEX_COUNT>
inline void setupVAOTextured(GLuint &vao, GLuint &vbo, GLuint &ebo,
                             const float (&verts)[VERT_COUNT],
                             const unsigned int (&indices)[INDEX_COUNT])
{
    generateArrays(vao, vbo, ebo);
    uploadVertsTextured(vao, vbo, ebo, verts, indices);
}