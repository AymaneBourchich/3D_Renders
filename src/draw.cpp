#include "draw.h"
#include "shader.h"
#include "consts.h"
void drawMesh(GLuint program, GLuint &vao, int indexCount,const glm::mat4 &model, bool debug)
{
    glUseProgram(program);
    setModel(program, model);

    if (debug)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    if (debug)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawMeshTextured(GLuint program, GLuint &vao, GLuint texture, int indexCount, const glm::mat4 &model)
{
    glUseProgram(program);
    setModel(program, model);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
}
