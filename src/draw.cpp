#include "draw.h"
#include "shader.h"

void drawMesh(GLuint program, GLuint &vao, int indexCount, const glm::mat4 &proj, const glm::mat4 &view, const glm::mat4 &model)
{
    glUseProgram(program);
    setMat4(program, "uMVP", proj * view * model);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void drawMeshTextured(GLuint program, GLuint &vao, GLuint texture, int indexCount, const glm::mat4 &proj, const glm::mat4 &view, const glm::mat4 &model)
{
    glUseProgram(program);

    setMat4(program, "uMVP", proj * view * model);
    setVec3(program, "uAmbient", glm::vec3(0.6, 0, 0));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    setValue(program, "uTex", 0);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
}
