#include "draw.h"
#include "shader.h"
#include "consts.h"
void drawMesh(GLuint program, GLuint &vao, int indexCount, const glm::mat4 &proj, const glm::mat4 &view, const glm::mat4 &model, bool debug)
{
    glUseProgram(program);
    setMat4(program, "uMVP", proj * view * model);

    if (debug)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    if (debug)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawMeshTextured( GLuint &vao, GLuint texture, int indexCount)
{

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);


    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
}
